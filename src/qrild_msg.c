
#include <errno.h>
#include <linux/qrtr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "libqrtr.h"
#include "logging.h"

#include "list.h"
#include "qrild.h"
#include "qrild_msg.h"
#include "qrild_qmi.h"
#include "util.h"

#include "qmi_uim.h"
#include "qmi_tlv.h"

static uint16_t txn = 0;

void print_service(struct qmi_service_info *pkt)
{
	if (!pkt)
		return;

	LOGD("| %4d | %4d | %5d | %4d  | %4d  | %s", pkt->type, pkt->node,
	     pkt->port, pkt->major, pkt->minor,
	     pkt->name ? pkt->name : "<unknown>");
}

/**
 * @brief: Send a qrild_msg and free it
 * NOTE: Must be called with msg_mutex locked!
 * 
 * @state: RIL state object
 * @msg: The message to send
 */
static int qrild_qrtr_send_msg(struct rild_state *state, struct qrild_msg *msg)
{
	struct qmi_service_info *service;
	int rc;

	pthread_mutex_lock(&state->services_mutex);
	service = qmi_service_get(&state->services, msg->svc);
	if (!service) {
		LOGE("Failed to find service %d (%s)", msg->svc,
		     qmi_service_to_string(msg->svc, false));
		return -1;
	}

	printf("Sending to service '%s'\n", service->name);
	print_hex_dump("QRTR TX", msg->buf, msg->buf_len);

	rc = qrtr_sendto(state->sock, service->node, service->port, msg->buf, msg->buf_len);
	if (rc < 0) {
		free(msg);
		return rc;
	}

	pthread_mutex_unlock(&state->services_mutex);

	/* Free the buffer allocated by qrild_qrtr_send_to_service */
	free(msg->buf);

	return 0;
}

/**
 * @brief: send all the unsent messages in the pending_tx queue
 * 
 * @state: RIL state object
 */
int qrild_qrtr_send_queued(struct rild_state *state)
{
	struct qrild_msg *msg;

	pthread_mutex_lock(&state->msg_mutex);
	list_for_each_entry(msg, &state->pending_tx, li) {
		if (!msg->sent) {
			qrild_qrtr_send_msg(state, msg);
			msg->sent = true;
		} else {
			/* 
			 * If we find an already sent message
			 * then there won't be any unsent messages
			 * after it.
			 */
			break;
		}
	}
	pthread_mutex_unlock(&state->msg_mutex);

	return 0;
}

int qrild_next_transaction_id()
{
	if (txn > 6000)
		txn = 0;
	return txn++;
}

static void timespec_add(struct timespec *ts, int ms)
{
	// 1000000000
	time_t seconds = ms / 1000;
	long int nsec = (ms % 1000) * 1000000;
	long int ns_diff = ts->tv_nsec - nsec;

	if (ns_diff < 0)
		ts->tv_nsec = 0;
	if (nsec != 0)
		ts->tv_nsec += nsec + ns_diff;

	ts->tv_sec += seconds;

}

/**
 * @brief Build a QMI message and add is to the pending_tx list
 * to be sent by the msg thread.
 * 
 * @state: RIL state object
 * @svc_id: ID of the QMI service to send the message to
 * @data: The encoded QMI message to send
 * @sz: length of data buffer
 * @sync: should we block until there is a reply
 * 
 * @returns 0 on success, < 0 on failure
 */
int qrild_qrtr_send_to_service(struct rild_state *state,
			       enum qmi_service svc_id, const void *data,
			       size_t sz, bool sync, int timeout_ms)
{
	struct qrild_msg *msg, *msg2;
	const struct qmi_header *qmi;
	struct timespec timeout; // = {0, 1000000 * timeout_ms};
	int rc = 0;
	bool found = false;

	if (svc_id == QMI_SERVICE_CTL) {
		LOGW("CTL service not supported by QRTR");
		return -1;
	}

	qmi = (const struct qmi_header *)data;

	msg = qrild_msg_new(state->txn, qmi->msg_id, &state->msg_mutex);
	msg->svc = svc_id;
	/* Copy the message buffer so the sender can safely free data */
	msg->buf = malloc(sz);
	memcpy(msg->buf, data, sz);
	msg->buf_len = sz;

	// The transaction ID is encoded in the QMI packet, it must be incremented for
	// every transmit so we can map a response to a request
	state->txn++;

	/* Queue the message to be sent by the msg thread */
	pthread_mutex_lock(&state->msg_mutex);
	list_prepend(&state->pending_tx, &msg->li);
	/* for async just return */
	if (!sync) {
		goto unlock_out;
	}

	/*
	 * wait for a response with the right txn_id otherwise
	 * timeout
	 */
	clock_gettime(CLOCK_REALTIME, &timeout);
	timespec_add(&timeout, timeout_ms);
	// Check in case the msg thread somehow beat us to it and handled the response
	// before we got here
	msg2 = qrild_msg_get_by_txn(&state->pending_rx, msg->txn);
	found = msg2 && msg2->txn == msg->txn;
	while (rc != ETIMEDOUT && !found) {
		//printf("Before timedwait (%d)\n", rc);
		rc = pthread_cond_timedwait(&state->msg_change, &state->msg_mutex,
					&timeout);
		msg2 = qrild_msg_get_by_txn(&state->pending_rx, msg->txn);
		found = msg2 && msg2->txn == msg->txn;
	}
	if (rc > 0 && !found) {
		LOGE("Failed waiting for response: %d (%s)\n", rc, strerror(rc));
		rc = QRILD_STATE_ERROR;
		goto unlock_out;
	}
	printf("Got response for msg {id: 0x%x, txn: %u}: {id: 0x%x, txn: %u} (rc: %d)\n",
		msg->msg_id, msg->txn, msg2->msg_id, msg2->txn, rc);

unlock_out:
	pthread_mutex_unlock(&state->msg_mutex);
	return rc;
}

void qrild_qrtr_recv(struct rild_state *state)
{
	struct qrtr_packet pkt;
	struct sockaddr_qrtr sq;
	socklen_t sl = sizeof(sq);
	void *buf = zalloc(256);
	int ret;
	struct qmi_service_info *service;
	const struct qmi_header *qmi;
	struct qmi_tlv *tlv;
	struct qrild_msg *msg;

	ret = recvfrom(state->sock, buf, 256, 0, (void *)&sq, &sl);
	if (ret < 0) {
		if (errno == ENETRESET || errno == EAGAIN) {
			LOGE("[QRTR] recvfrom got %d (%s)\n", ret, strerror(errno));
			return;
		} else {
			LOGE("[QRTR] recvfrom failed: %d (%s)\n", errno, strerror(errno));
		}
		exit(1);
	}

	ret = qrtr_decode(&pkt, buf, ret, &sq);
	if (ret < 0) {
		LOGE("[QRTR] failed to decode qrtr packet\n");
		return;
	}

	switch (pkt.type) {
	case QRTR_TYPE_NEW_SERVER:
		if (!pkt.service && !pkt.instance && !pkt.node && !pkt.port)
			break;

		service = zalloc(sizeof(*service));

		service->type = pkt.service;
		service->node = pkt.node;
		service->port = pkt.port;
		service->major = pkt.instance & 0xff;
		service->minor = pkt.instance >> 8;
		service->name = qmi_service_to_string(service->type, false);
		service->mut = &state->services_mutex;

		print_service(service);

		pthread_mutex_lock(&state->services_mutex);
		list_append(&state->services, &service->li);
		pthread_mutex_unlock(&state->services_mutex);
		break;
	case QRTR_TYPE_DEL_SERVER:
		service = qmi_service_get(&state->services, pkt.service);
		if (!service)
			break;
		printf("Removing server %s\n", service->name);
		list_remove(&service->li);
		free(service);

		break;
	case QRTR_TYPE_DATA:
		/*
		 * When receiving a message, we look it up in the pending_tx
		 * list, we remove it from the list and add it to the
		 * pending_rx list so that the main thread can process it.
		 * For indication messages which won't have a match we create
		 * a message object and add it to the pending_rx list.
		 */
		qmi = qmi_get_header(&pkt);
		if (!qmi) {
			fprintf(stderr, "[QRTR] Failed to get QMI header!\n");
			return;
		}
		pthread_mutex_lock(&state->msg_mutex);
		msg = qrild_msg_get_by_txn(&state->pending_tx, qmi->txn_id);
		if (!msg) {
			if (qmi->type == QMI_RESPONSE)
				fprintf(stderr, "Unsolicited response!\n");
			msg = qrild_msg_new(qmi->txn_id, qmi->msg_id, &state->msg_mutex);
		} else {
			// Remove the message from the pending_tx list
			list_remove(&msg->li);
		}

		list_append(&state->pending_rx, &msg->li);
		if (msg->msg_id != qmi->msg_id) {
			fprintf(stderr, "FIXME: txn %u: req->msg_id (%u) != resp->msg_id (%u)\n", qmi->txn_id, msg->msg_id, qmi->msg_id);
			msg->msg_id = qmi->msg_id;
		}

		msg->buf = pkt.data;
		msg->buf_len = pkt.data_len;
		msg->type = qmi->type;

		printf("[QRTR] data packet from port %d, msg_id: 0x%2x, txn: %d, type: %u\n",
		       sq.sq_port, msg->msg_id, msg->txn, msg->type);

		print_hex_dump("QRTR RX", pkt.data, pkt.data_len);
		// Only dump responses to avoid some noise
		//                                                 qmi->type
		tlv = qmi_tlv_decode(msg->buf, msg->buf_len, NULL, 2);
		if (tlv) {
			qmi_tlv_dump(tlv);
			free(tlv);
		}

		// Notify other threads of the received message
		pthread_cond_broadcast(&state->msg_change);
		pthread_mutex_unlock(&state->msg_mutex);
		break;
	default:
		printf("Unsupported pkt type %u\n", pkt.type);
		print_hex_dump("QRTR RX", pkt.data, pkt.data_len);
		break;
	};
}

/* QRTR doesn't implement the QMI CTL service */
bool qrild_qrtr_do_lookup(struct rild_state *state)
{
	struct qrtr_ctrl_pkt pkt;
	int rc;

	if (state->sock < 0)
		return false;

	memset(&pkt, 0, sizeof(pkt));

	pkt.cmd = QRTR_TYPE_NEW_LOOKUP;

	rc = qrtr_sendto(state->sock, 1, QRTR_PORT_CTRL, &pkt, sizeof(pkt));
	if (rc < 0)
		PLOGE_AND_EXIT("Couldn't send lookup");

	return true;
}

struct qmi_result *qrild_qmi_get_result(struct qmi_tlv *tlv)
{
	struct qmi_result *res = qmi_tlv_get(tlv, 2, NULL);
	return res;
}

void qrild_qmi_result_print(struct qmi_result *res)
{
	fprintf(stderr, "Result: %u, error: %u\n", res->result, res->error);
}

/**
 * @brief synchronously send a QMI message and wait for the response
 * 
 * @state: RIL state object
 * @svc_id: ID of the service to send the message to
 * @data: encoded QMI message
 * @sz: size of buffer
 * @timeout_ms: maximum time to wait in ms (defaults to 500ms if less than 0)
 * @resp: Pointer to reponse to return, set to NULL to ignore response
 * 
 * @returns 0 on success, < 0 on error
 */
int qrild_msg_send_sync(struct rild_state *state, enum qmi_service svc_id,
			void *data, size_t sz, int timeout_ms,
			struct qrild_msg **resp)
{
	struct qrtr_packet pkt;
	unsigned short txn_id;
	int rc = qrild_qrtr_send_to_service(state, svc_id, data, sz, true,
					    timeout_ms);
	if (rc < 0)
		return rc;

	/* Find the response message */
	pkt.data = data;
	pkt.data_len = sz;
	qmi_decode_header2(&pkt, NULL, NULL, &txn_id);

	if (resp)
		*resp = qrild_msg_get_by_txn(&state->pending_rx, txn_id);

	return 0;
}

int qrild_msg_send_async(struct rild_state *state,
				enum qmi_service svc_id, void *data, size_t sz)
{
	return qrild_qrtr_send_to_service(state, svc_id, data, sz, false, 0);
}

/**
 * @brief Synchronously send a message and check the result of the response. This is
 * a helper for messages where the response is only an ack and can be discarded.
 * 
 * @state: RIL state object
 * @svc_id: ID of the service to send the message to
 * @data: encoded QMI message
 * @sz: size of buffer
 * @timeout_ms: maximum time to wait in ms (defaults to 500ms if less than 0)
 * @res: qmi_result object to copy the result TLV into, or NULL to discard it
 * NOTE: res must be allocated, the response message buffer is free'd.
 *
 * @returns 0 on success or < 0 on failure
 */
int qrild_msg_send_resp_check(struct rild_state *state,
				     enum qmi_service svc_id, void *data,
				     size_t sz, int timeout_ms, struct qmi_result *res)
{
	struct qmi_tlv *tlv;
	struct qrild_msg *resp = NULL;
	struct qmi_result *_res;
	int rc;

	rc = qrild_msg_send_sync(state, svc_id, data, sz, timeout_ms, &resp);
	if (rc < 0)
		return rc;

	tlv = qmi_tlv_decode(resp->buf, resp->buf_len, NULL, 2);
	_res = qrild_qmi_get_result(tlv);
	if (res) {
		res->result = _res->result;
		res->error = _res->error;
	}

	qmi_tlv_free(tlv);
	qrild_msg_free(resp);
	if (!_res->result)
		return 0;

	return -1;
}

/**
 * @brief Send a basic QMI request which doesn't have any parameters
 * 
 * @state: RIL state object
 * @svc_id: The QMI service to send the request to
 * @msg_id: The message ID of the request
 * @resp: The response to fill if the request is synchronous, unused for async
 * @sync: Should we wait for the response message?
 */
static inline int qrild_qmi_send_basic_request(struct rild_state *state, enum qmi_service svc_id, uint32_t msg_id, struct qrild_msg **resp, bool sync)
{
	void *buf;
	size_t buf_sz;
	int rc;
	struct qmi_tlv *req = qmi_tlv_init(state->txn, msg_id, 0);
	
	buf = qmi_tlv_encode(req, &buf_sz);

	if (sync)
		rc = qrild_msg_send_sync(state, svc_id, buf, buf_sz, TIMEOUT_DEFAULT, resp);
	else
		rc = qrild_msg_send_async(state, svc_id, buf, buf_sz);

	qmi_tlv_free(req);
	return rc;
}

/**
 * @brief Send a basic QMI request and populate resp with the response message.
 * 
 * @state: RIL state object
 * @svc_id: The QMI service to send the request to
 * @msg_id: The message ID of the request
 * @resp: The response to fill.
 */
int qrild_qmi_send_basic_request_sync(struct rild_state *state, enum qmi_service svc_id, uint32_t msg_id, struct qrild_msg **resp)
{
	return qrild_qmi_send_basic_request(state, svc_id, msg_id, resp, true);
}

/**
 * @brief Send a basic QMI request and return immediately.
 * 
 * @state: RIL state object
 * @svc_id: The QMI service to send the request to
 * @msg_id: The message ID of the request
 */
int qrild_qmi_send_basic_request_async(struct rild_state *state, enum qmi_service svc_id, uint32_t msg_id)
{
	return qrild_qmi_send_basic_request(state, svc_id, msg_id, NULL, false);
}

/**
 * @brief Create a new qrild_msg object
 * 
 * @txn: the transaction ID used for this message
 * @msg_id: the ID of the message
 * @service: The QMI service the message is for/from
 * @shared_mutex: A pointer to the shared mutex used for accessing message objects
 * 
 * @returns The created struct qrild_msg object.
 */
struct qrild_msg *qrild_msg_new(uint16_t txn, uint32_t msg_id,
	pthread_mutex_t *shared_mutex)
{
	struct qrild_msg *msg = zalloc(sizeof(struct qrild_msg));
	msg->txn = txn;
	msg->msg_id = msg_id;
	msg->mut = shared_mutex;

	return msg;
}

/**
 * @brief remove a message from it's pending list and free it
 * NOTE: requires that msg->mut be locked!
 * 
 * @state: RIL state object
 * @msg: the message to free
 */
void qrild_msg_free_locked(struct qrild_msg *msg)
{
	if (!msg) {
		fprintf(stderr, "%s called for NULL msg\n", __func__);
		return;
	}
	LOGD("Freeing msg {id: %x, txn: %d}", msg->msg_id, msg->txn);
	list_remove(&msg->li);
	if (msg->buf)
		free(msg->buf);
	free(msg);
}

void qrild_msg_free(struct qrild_msg *msg)
{
	pthread_mutex_t *mut = msg->mut;
	pthread_mutex_lock(mut);

	qrild_msg_free_locked(msg);

	pthread_mutex_unlock(mut);
}

/**
 * @brief Get the qmi_service_info for a particular service
 * NOTE: Must be called with services_mutex locked!
 * 
 * @list: The list of services to search
 * @svc: The service ID
 * 
 * @returns the service or NULL if it isn't in the list
 */
struct qmi_service_info *qmi_service_get(struct list_head *list,
					 enum qmi_service svc)
{
	struct qmi_service_info *service, *out = NULL;
	list_for_each_entry(service, list, li)
	{
		if (service->type == svc) {
			out = service;
			break;
		};
	}

	return out;
}

int qmi_service_get_port(struct list_head *list, enum qmi_service svc)
{
	struct qmi_service_info *service = qmi_service_get(list, svc);
	return service ? service->port : -1;
}

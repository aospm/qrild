
#include <errno.h>
#include <linux/qrtr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <linux/time.h>

#include "libqrtr.h"
#include "logging.h"

#include "list.h"
#include "qrild.h"
#include "qrild_msg.h"
#include "qrild_qmi.h"
#include "util.h"

#include "qmi_uim.h"
#include "qmi_tlv.h"

void print_service(struct qmi_service_info *pkt)
{
	if (!pkt)
		return;

	LOGD("| %4d | %4d | %5d | %4d  | %4d  | %s", pkt->type, pkt->node,
	     pkt->port, pkt->major, pkt->minor,
	     pkt->name ? pkt->name : "<unknown>");
}

/**
 * @brief send a QMI message and optionally block until a reply
 * for that message is received.
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
	struct qrild_msg *msg;
	struct qmi_service_info *service;
	const struct qmi_header *qmi;
	struct timespec timeout; // = {0, 1000000 * timeout_ms};
	int rc;

	if (svc_id == QMI_SERVICE_CTL) {
		LOGW("CTL service not supported by QRTR");
		return -1;
	}

	qmi = (const struct qmi_header *)data;

	service = qmi_service_get(&state->services, svc_id);
	if (!service) {
		LOGE("Failed to find service %d (%s)", svc_id,
		     qmi_service_to_string(svc_id, false));
		return -1;
	}

	msg = qrild_msg_new(state->txn, qmi->msg_id, &state->msg_mutex);

	// The transaction ID is encoded in the QMI packet, it must be incremented for
	// every transmit so we can map a response to a request
	state->txn++;

	printf("Sending to service '%s'\n", service->name);
	print_hex_dump("QRTR TX", data, sz);

	rc = qrtr_sendto(state->sock, service->node, service->port, data, sz);
	if (rc < 0) {
		free(msg);
		return rc;
	}

	list_append(&state->pending_tx, &msg->li);
	/* for async just return */
	if (!sync)
		return rc;

	/*
	 * wait for a response with the right txn_id otherwise
	 * timeout
	 */
	clock_gettime(CLOCK_REALTIME, &timeout);
	timeout.tv_nsec += 1000000 * timeout_ms;
	pthread_mutex_lock(&state->msg_mutex);
	while (!qrild_msg_get_by_txn(&state->pending_rx, msg->txn))
		rc = pthread_cond_timedwait(&state->rx_msg, &state->msg_mutex,
					    &timeout);
	pthread_mutex_unlock(&state->msg_mutex);
	printf("Got response or timeout for message %u (%u) (rc: %d)\n", msg->msg_id, msg->txn, rc);

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
	struct qrild_msg *msg;

	ret = recvfrom(state->sock, buf, 256, 0, (void *)&sq, &sl);
	if (ret < 0) {
		if (errno == ENETRESET)
			LOGE("[QRTR] received ENETRESET, please retry\n");
		else
			LOGE("[QRTR] recvfrom failed\n");
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
		list_init(&service->li);

		service->type = pkt.service;
		service->node = pkt.node;
		service->port = pkt.port;
		service->major = pkt.instance & 0xff;
		service->minor = pkt.instance >> 8;
		service->name = qmi_service_to_string(service->type, false);

		printf("Found new service:\n");
		print_service(service);

		list_append(&state->services, &service->li);
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
		msg = qrild_msg_get_by_txn(&state->pending_tx, qmi->txn_id);
		if (!msg) {
			if (qmi->type == QMI_RESPONSE)
				fprintf(stderr, "Unsolicited response!\n");
			msg = qrild_msg_new(qmi->txn_id, qmi->msg_id, &state->msg_mutex);
		} else {
			// Remove the message from the pending_tx list
			list_remove(msg);
		}

		list_append(&state->pending_rx, &msg->li);
		if (msg->msg_id != qmi->msg_id) {
			fprintf(stderr, "FIXME: txn %u: req->msg_id (%u) != resp->msg_id (%u)\n", qmi->txn_id, msg->msg_id, qmi->msg_id);
			msg->msg_id = qmi->msg_id;
		}

		msg->buf = pkt.data;
		msg->buf_len = pkt.data_len;

		printf("[QRTR] data packet from port %d, msg_id: 0x%2x, txn: %d\n",
		       sq.sq_port, msg->msg_id, msg->txn);

		print_hex_dump("QRTR RX", pkt.data, pkt.data_len);

		// Notify other threads of the received message
		pthread_cond_broadcast(&state->rx_msg);
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

inline struct qmi_result *qrild_qmi_get_result(struct qmi_tlv *tlv)
{
	struct qmi_result *res = qmi_tlv_get(tlv, 2, NULL);
	return res;
}

inline void qrild_qmi_result_print(struct qmi_result *res)
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
 * @resp: The response message or NULL on error
 * 
 * @returns 0 on success, < 0 on error
 */
int qrild_msg_send_sync(struct rild_state *state, enum qmi_service svc_id,
			void *data, size_t sz, int timeout_ms,
			struct qrild_msg *resp)
{
	struct qrtr_packet pkt;
	unsigned short txn_id;
	int rc = qrild_qrtr_send_to_service(state, svc_id, data, sz, true,
					    timeout_ms);
	if (rc < 0)
		return NULL;

	/* Find the response message */
	pkt.data = data;
	pkt.data_len = sz;
	qmi_decode_header2(&pkt, NULL, NULL, txn_id);

	resp = qrild_msg_get_by_txn(&state->pending_rx, txn_id);
	return 0;
}

inline int qrild_msg_send_async(struct rild_state *state,
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
inline int qrild_msg_send_resp_check(struct rild_state *state,
				     enum qmi_service svc_id, void *data,
				     size_t sz, int timeout_ms, struct qmi_result *res)
{
	struct qmi_tlv *tlv;
	struct qrild_msg *resp;
	struct qmi_result *_res;
	int rc;

	rc = qrild_msg_send_sync(state, svc_id, data, sz, timeout_ms, resp);
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
static inline int qrild_qmi_send_basic_request(struct rild_state *state, enum qmi_service svc_id, uint32_t msg_id, struct qrild_msg *resp, bool sync)
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
inline int qrild_qmi_send_basic_request_sync(struct rild_state *state, enum qmi_service svc_id, uint32_t msg_id, struct qrild_msg *resp)
{
	qrild_qmi_send_basic_request(state, svc_id, msg_id, resp, true);
}

/**
 * @brief Send a basic QMI request and return immediately.
 * 
 * @state: RIL state object
 * @svc_id: The QMI service to send the request to
 * @msg_id: The message ID of the request
 */
inline int qrild_qmi_send_basic_request_async(struct rild_state *state, enum qmi_service svc_id, uint32_t msg_id)
{
	qrild_qmi_send_basic_request(state, svc_id, msg_id, NULL, false);
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
	list_init(&msg->li);

	return msg;
}

/**
 * @brief remove a message from it's pending list and free it
 * 
 * @state: RIL state object
 * @msg: the message to free
 */
void qrild_msg_free(struct qrild_msg *msg)
{
	pthread_mutex_t *mut = msg->mut;
	if (!msg) {
		fprintf(stderr, "%s called for NULL msg\n", __func__);
		return;
	}
	pthread_mutex_lock(mut);
	list_remove(&msg->li);
	if (msg->buf)
		free(msg->buf);
	free(msg);
	pthread_mutex_unlock(mut);
}

/**
 * @brief Get the qmi_service_info for a particular service
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

inline int qmi_service_get_port(struct list_head *list, enum qmi_service svc)
{
	struct qmi_service_info *service = qmi_service_get(list, svc);
	return service ? service->port : -1;
}
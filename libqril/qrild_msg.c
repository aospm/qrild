
#include <errno.h>
#include <linux/qrtr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "q_log.h"

#include "libqrtr.h"

#include "list.h"
#include "qrild.h"
#include "qrild_msg.h"
#include "qrild_qmi.h"
#include "util.h"

#include "qmi_uim.h"

void print_service(struct qmi_service_info *pkt)
{
	static int count = 0;
	if (!pkt) {
		count = 0;
		return;
	}

	if (!count)
		log_debug("| Type | Node | Port | Major | Minor | Service Name");

	log_debug("| %4d | %4d | %5d | %4d  | %4d  | %s", pkt->type, pkt->node,
	     pkt->port, pkt->major, pkt->minor,
	     pkt->name ? pkt->name : "<unknown>");

	count++;
}

void dump_messages(struct list_head *list) {
	struct qrild_msg *msg;
	list_for_each_entry(msg, (list), li) {
		log_info("{id: 0x%4x, txn: 0x%2x}", msg->msg_id, msg->txn);
	}
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
	struct qmi_service_info service, *svc;
	int rc;

	q_thread_mutex_lock(&state->services_mutex);
	svc = qmi_service_get(&state->services, msg->svc);
	if (!svc) {
		log_error("Failed to find service %d (%s)", msg->svc,
		     qmi_service_to_string(msg->svc, false));
		return -1;
	}
	memcpy(&service, svc, sizeof(struct qmi_service_info));
	service.name = strdup(svc->name);
	q_thread_mutex_unlock(&state->services_mutex);

	log_trace("[QRTR] TX: '%s'", service.name);
	qmi_tlv_dump_buf(msg->buf, msg->buf_len, service.type);

	rc = qrtr_sendto(state->sock, service.node, service.port, msg->buf, msg->buf_len);
	if (rc < 0) {
		free(msg);
		return rc;
	}

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

	q_thread_mutex_lock(&state->msg_mutex);
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
	q_thread_mutex_unlock(&state->msg_mutex);

	return 0;
}

uint16_t qrild_next_transaction_id()
{
	static uint16_t txn = 4;
	if (txn > 65534)
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
		log_error("CTL service not supported by QRTR");
		return -1;
	}

	qmi = (const struct qmi_header *)data;

	msg = qrild_msg_new(qmi->txn_id, qmi->msg_id, &state->msg_mutex);
	msg->svc = svc_id;
	/* Copy the message buffer so the sender can safely free data */
	msg->buf = malloc(sz);
	memcpy(msg->buf, data, sz);
	msg->buf_len = sz;

	/* Queue the message to be sent by the msg thread */
	q_thread_mutex_lock(&state->msg_mutex);
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
	log_debug("Waiting for response to msg {id: 0x%x, txn: %u}", msg->msg_id, msg->txn);
	msg2 = qrild_msg_get_by_txn(&state->pending_rx, msg->txn);
	found = msg2 && msg2->txn == msg->txn;
	while (!found && rc != ETIMEDOUT) {
		rc = q_thread_cond_timedwait(&state->msg_change, &state->msg_mutex,
					&timeout);
		msg2 = qrild_msg_get_by_txn(&state->pending_rx, msg->txn);
		found = msg2 && msg2->txn == msg->txn;
	}
	if (rc > 0 && !found) {
		log_error("Failed waiting for response: %d (%s)", rc, strerror(rc));
		rc = QRILD_STATE_ERROR;
		dump_messages(&state->pending_rx);
		goto unlock_out;
	}
	log_debug("Got response for msg {id: 0x%x, txn: %u}",
		msg->msg_id, msg->txn);

unlock_out:
	q_thread_mutex_unlock(&state->msg_mutex);
	return rc;
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
int qrild_qrtr_send_to_service_async(struct rild_state *state,
			       enum qmi_service svc_id, const void *data,
			       size_t sz, async_msg_handler_t handler)
{
	struct qrild_msg *msg, *msg2;
	const struct qmi_header *qmi;
	struct timespec timeout; // = {0, 1000000 * timeout_ms};
	int rc = 0;
	bool found = false;

	if (svc_id == QMI_SERVICE_CTL) {
		log_error("CTL service not supported by QRTR");
		return -1;
	}

	qmi = (const struct qmi_header *)data;

	msg = qrild_msg_new(qmi->txn_id, qmi->msg_id, &state->msg_mutex);
	msg->svc = svc_id;
	/* Copy the message buffer so the sender can safely free data */
	msg->buf = malloc(sz);
	memcpy(msg->buf, data, sz);
	msg->buf_len = sz;
	msg->handler = handler;

	/* Queue the message to be sent by the msg thread */
	q_thread_mutex_lock(&state->msg_mutex);
	list_prepend(&state->pending_tx, &msg->li);
	q_thread_mutex_unlock(&state->msg_mutex);
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
	char svc_name[32];
	int svc_id;
	const struct qmi_header *qmi;
	struct qmi_tlv *tlv;
	struct qrild_msg *msg;
	memset(&svc_name, 0, 32);

	ret = recvfrom(state->sock, buf, 256, 0, (void *)&sq, &sl);
	if (ret < 0) {
		if (errno == ENETRESET || errno == EAGAIN) {
			log_error("[QRTR] recvfrom got %d (%s)", ret, strerror(errno));
			return;
		} else {
			log_error("[QRTR] recvfrom failed: %d (%s)", errno, strerror(errno));
		}
		exit(1);
	}

	ret = qrtr_decode(&pkt, buf, ret, &sq);
	if (ret < 0) {
		log_error("[QRTR] failed to decode qrtr packet");
		return;
	}

	switch (pkt.type) {
	case QRTR_TYPE_NEW_SERVER:
		if (!pkt.service && !pkt.instance && !pkt.node && !pkt.port) {
			print_service(NULL);
			break;
		}

		service = zalloc(sizeof(*service));

		service->type = pkt.service;
		service->node = pkt.node;
		service->port = pkt.port;
		service->major = pkt.instance & 0xff;
		service->minor = pkt.instance >> 8;
		service->name = qmi_service_to_string(service->type, false);
		service->mut = &state->services_mutex;

		print_service(service);

		q_thread_mutex_lock(&state->services_mutex);
		list_append(&state->services, &service->li);
		q_thread_mutex_unlock(&state->services_mutex);

		break;
	case QRTR_TYPE_DEL_SERVER:
		q_thread_mutex_lock(&state->services_mutex);
		service = qmi_service_get(&state->services, pkt.service);
		if (!service)
			break;
		log_info("Removing server %s", service->name);
		list_remove(&service->li);
		q_thread_mutex_unlock(&state->services_mutex);
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
			log_error("[QRTR] Failed to get QMI header!");
			return;
		}
		q_thread_mutex_lock(&state->msg_mutex);
		msg = qrild_msg_get_by_txn(&state->pending_tx, qmi->txn_id);
		if (!msg) {
			if (qmi->type == QMI_RESPONSE)
				log_error("Unsolicited response!");
			msg = qrild_msg_new(qmi->txn_id, qmi->msg_id, &state->msg_mutex);
		} else {
			// Remove the message from the pending_tx list
			list_remove(&msg->li);
		}

		if (msg->msg_id != qmi->msg_id) {
			log_error("FIXME: txn %u: req->msg_id (%u) != resp->msg_id (%u)", qmi->txn_id, msg->msg_id, qmi->msg_id);
			msg->msg_id = qmi->msg_id;
		}

		msg->buf = pkt.data;
		msg->buf_len = pkt.data_len;
		msg->type = qmi->type;
		q_thread_mutex_lock(&state->services_mutex);
		service = qmi_service_from_port(&state->services, sq.sq_port);
		strncpy(svc_name, service->name, 32);
		svc_id = service->type;
		q_thread_mutex_unlock(&state->services_mutex);
		log_info("[QRTR] RX: '%s'", (char*)svc_name);
		qmi_tlv_dump_buf(msg->buf, msg->buf_len, svc_id);
		// Only dump responses to avoid some noise
		//                                                 qmi->type
		// tlv = qmi_tlv_decode(msg->buf, msg->buf_len, NULL, 2);
		// if (tlv) {
		// 	qmi_tlv_dump(tlv);
		// 	free(tlv);
		// }

		list_append(&state->pending_rx, &msg->li);

		if (msg->handler) {
			ret = msg->handler(state, msg); 
		}

		// Notify other threads of the received message
		q_thread_mutex_unlock(&state->msg_mutex);
		pthread_cond_broadcast(&state->msg_change);
		break;
	default:
		log_warn("Unsupported pkt type %u", pkt.type);
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
		log_error("Couldn't send lookup");

	return true;
}

void qrild_qmi_result_print(struct qmi_response_type_v01 *res)
{
	log_error("Result: %u, error: %u", res->result, res->error);
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
				     size_t sz, int timeout_ms, struct qmi_response_type_v01 *res)
{
	struct qmi_tlv *tlv;
	struct qrild_msg *resp = NULL;
	struct qmi_response_type_v01 *_res;
	int rc;

	rc = qrild_msg_send_sync(state, svc_id, data, sz, timeout_ms, &resp);
	if (rc < 0)
		return rc;

	tlv = qmi_tlv_decode(resp->buf, resp->buf_len);
	_res = qmi_tlv_get_result(tlv);
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
	struct qmi_tlv *req = qmi_tlv_init(qrild_next_transaction_id(), msg_id, 0);
	
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
		log_error("%s called for NULL msg", __func__);
		return;
	}
	log_info("Freeing msg {id: %x, txn: %d}", msg->msg_id, msg->txn);
	list_remove(&msg->li);
	if (msg->buf)
		free(msg->buf);
	free(msg);
}

void qrild_msg_free(struct qrild_msg *msg)
{
	pthread_mutex_t *mut = msg->mut;
	q_thread_mutex_lock(mut);

	qrild_msg_free_locked(msg);

	q_thread_mutex_unlock(mut);
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

/**
 * @brief Get the qmi_service_info for a particular service
 * NOTE: Must be called with services_mutex locked!
 * 
 * @list: The list of services to search
 * @svc: The service ID
 * 
 * @returns the service or NULL if it isn't in the list
 */
struct qmi_service_info *qmi_service_from_port(struct list_head *list,
					 uint16_t port)
{
	struct qmi_service_info *service, *out = NULL;
	list_for_each_entry(service, list, li)
	{
		if (service->port == port) {
			out = service;
			break;
		};
	}

	return out;
}

const struct enum_value qmi_error_names[] = {
	{ QMI_ERR_NONE, "QMI_ERR_NONE", "" },
	{ QMI_ERR_MALFORMED_MESSAGE, "QMI_ERR_MALFORMED_MESSAGE", "" },
	{ QMI_ERR_NO_MEMORY, "QMI_ERR_NO_MEMORY", "" },
	{ QMI_ERR_INTERNAL, "QMI_ERR_INTERNAL", "" },
	{ QMI_ERR_ABORTED, "QMI_ERR_ABORTED", "" },
	{ QMI_ERR_CLIENT_IDS_EXHAUSTED, "QMI_ERR_CLIENT_IDS_EXHAUSTED", "" },
	{ QMI_ERR_UNABORTABLE_TRANSACTION, "QMI_ERR_UNABORTABLE_TRANSACTION", "" },
	{ QMI_ERR_INVALID_CLIENT_ID, "QMI_ERR_INVALID_CLIENT_ID", "" },
	{ QMI_ERR_NO_THRESHOLDS_PROVIDED, "QMI_ERR_NO_THRESHOLDS_PROVIDED", "" },
	{ QMI_ERR_INVALID_HANDLE, "QMI_ERR_INVALID_HANDLE", "" },
	{ QMI_ERR_INVALID_PROFILE, "QMI_ERR_INVALID_PROFILE", "" },
	{ QMI_ERR_INVALID_PIN_ID, "QMI_ERR_INVALID_PIN_ID", "" },
	{ QMI_ERR_INCORRECT_PIN, "QMI_ERR_INCORRECT_PIN", "" },
	{ QMI_ERR_NO_NETWORK_FOUND, "QMI_ERR_NO_NETWORK_FOUND", "" },
	{ QMI_ERR_CALL_FAILED, "QMI_ERR_CALL_FAILED", "" },
	{ QMI_ERR_OUT_OF_CALL, "QMI_ERR_OUT_OF_CALL", "" },
	{ QMI_ERR_NOT_PROVISIONED, "QMI_ERR_NOT_PROVISIONED", "" },
	{ QMI_ERR_MISSING_ARGUMENT, "QMI_ERR_MISSING_ARGUMENT", "" },
	{ QMI_ERR_ARGUMENT_TOO_LONG, "QMI_ERR_ARGUMENT_TOO_LONG", "" },
	{ QMI_ERR_INVALID_TRANSACTION_ID, "QMI_ERR_INVALID_TRANSACTION_ID", "" },
	{ QMI_ERR_DEVICE_IN_USE, "QMI_ERR_DEVICE_IN_USE", "" },
	{ QMI_ERR_NETWORK_UNSUPPORTED, "QMI_ERR_NETWORK_UNSUPPORTED", "" },
	{ QMI_ERR_DEVICE_UNSUPPORTED, "QMI_ERR_DEVICE_UNSUPPORTED", "" },
	{ QMI_ERR_NO_EFFECT, "QMI_ERR_NO_EFFECT", "" },
	{ QMI_ERR_NO_FREE_PROFILE, "QMI_ERR_NO_FREE_PROFILE", "" },
	{ QMI_ERR_INVALID_PDP_TYPE, "QMI_ERR_INVALID_PDP_TYPE", "" },
	{ QMI_ERR_INVALID_TECHNOLOGY_PREFERENCE, "QMI_ERR_INVALID_TECHNOLOGY_PREFERENCE", "" },
	{ QMI_ERR_INVALID_PROFILE_TYPE, "QMI_ERR_INVALID_PROFILE_TYPE", "" },
	{ QMI_ERR_INVALID_SERVICE_TYPE, "QMI_ERR_INVALID_SERVICE_TYPE", "" },
	{ QMI_ERR_INVALID_REGISTER_ACTION, "QMI_ERR_INVALID_REGISTER_ACTION", "" },
	{ QMI_ERR_INVALID_PS_ATTACH_ACTION, "QMI_ERR_INVALID_PS_ATTACH_ACTION", "" },
	{ QMI_ERR_AUTHENTICATION_FAILED, "QMI_ERR_AUTHENTICATION_FAILED", "" },
	{ QMI_ERR_PIN_BLOCKED, "QMI_ERR_PIN_BLOCKED", "" },
	{ QMI_ERR_PIN_ALWAYS_BLOCKED, "QMI_ERR_PIN_ALWAYS_BLOCKED", "" },
	{ QMI_ERR_UIM_UNINITIALIZED, "QMI_ERR_UIM_UNINITIALIZED", "" },
	{ QMI_ERR_MAXIMUM_QOS_REQUESTS_IN_USE, "QMI_ERR_MAXIMUM_QOS_REQUESTS_IN_USE", "" },
	{ QMI_ERR_INCORRECT_FLOW_FILTER, "QMI_ERR_INCORRECT_FLOW_FILTER", "" },
	{ QMI_ERR_NETWORK_QOS_UNAWARE, "QMI_ERR_NETWORK_QOS_UNAWARE", "" },
	{ QMI_ERR_INVALID_QOS_ID, "QMI_ERR_INVALID_QOS_ID", "" },
	{ QMI_ERR_REQUESTED_NUMBER_UNSUPPORTED, "QMI_ERR_REQUESTED_NUMBER_UNSUPPORTED", "" },
	{ QMI_ERR_INTERFACE_NOT_FOUND, "QMI_ERR_INTERFACE_NOT_FOUND", "" },
	{ QMI_ERR_FLOW_SUSPENDED, "QMI_ERR_FLOW_SUSPENDED", "" },
	{ QMI_ERR_INVALID_DATA_FORMAT, "QMI_ERR_INVALID_DATA_FORMAT", "" },
	{ QMI_ERR_GENERAL_ERROR, "QMI_ERR_GENERAL_ERROR", "" },
	{ QMI_ERR_UNKNOWN_ERROR, "QMI_ERR_UNKNOWN_ERROR", "" },
	{ QMI_ERR_INVALID_ARGUMENT, "QMI_ERR_INVALID_ARGUMENT", "" },
	{ QMI_ERR_INVALID_INDEX, "QMI_ERR_INVALID_INDEX", "" },
	{ QMI_ERR_NO_ENTRY, "QMI_ERR_NO_ENTRY", "" },
	{ QMI_ERR_DEVICE_STORAGE_FULL, "QMI_ERR_DEVICE_STORAGE_FULL", "" },
	{ QMI_ERR_DEVICE_NOT_READY, "QMI_ERR_DEVICE_NOT_READY", "" },
	{ QMI_ERR_NETWORK_NOT_READY, "QMI_ERR_NETWORK_NOT_READY", "" },
	{ QMI_ERR_WMS_CAUSE_CODE, "QMI_ERR_WMS_CAUSE_CODE", "" },
	{ QMI_ERR_WMS_MESSAGE_NOT_SENT, "QMI_ERR_WMS_MESSAGE_NOT_SENT", "" },
	{ QMI_ERR_WMS_MESSAGE_DELIVERY_FAILURE, "QMI_ERR_WMS_MESSAGE_DELIVERY_FAILURE", "" },
	{ QMI_ERR_WMS_INVALID_MESSAGE_ID, "QMI_ERR_WMS_INVALID_MESSAGE_ID", "" },
	{ QMI_ERR_WMS_ENCODING, "QMI_ERR_WMS_ENCODING", "" },
	{ QMI_ERR_AUTHENTICATION_LOCK, "QMI_ERR_AUTHENTICATION_LOCK", "" },
	{ QMI_ERR_INVALID_TRANSITION, "QMI_ERR_INVALID_TRANSITION", "" },
	{ QMI_ERR_NOT_MCAST_INTERFACE, "QMI_ERR_NOT_MCAST_INTERFACE", "" },
	{ QMI_ERR_MAXIMUM_MCAST_REQUESTS_IN_USE, "QMI_ERR_MAXIMUM_MCAST_REQUESTS_IN_USE", "" },
	{ QMI_ERR_INVALID_MCAST_HANDLE, "QMI_ERR_INVALID_MCAST_HANDLE", "" },
	{ QMI_ERR_INVALID_IP_FAMILY_PREFERENCE, "QMI_ERR_INVALID_IP_FAMILY_PREFERENCE", "" },
	{ QMI_ERR_SESSION_INACTIVE, "QMI_ERR_SESSION_INACTIVE", "" },
	{ QMI_ERR_SESSION_INVALID, "QMI_ERR_SESSION_INVALID", "" },
	{ QMI_ERR_SESSION_OWNERSHIP, "QMI_ERR_SESSION_OWNERSHIP", "" },
	{ QMI_ERR_INSUFFICIENT_RESOURCES, "QMI_ERR_INSUFFICIENT_RESOURCES", "" },
	{ QMI_ERR_DISABLED, "QMI_ERR_DISABLED", "" },
	{ QMI_ERR_INVALID_OPERATION, "QMI_ERR_INVALID_OPERATION", "" },
	{ QMI_ERR_INVALID_QMI_COMMAND, "QMI_ERR_INVALID_QMI_COMMAND", "" },
	{ QMI_ERR_WMS_T_PDU_TYPE, "QMI_ERR_WMS_T_PDU_TYPE", "" },
	{ QMI_ERR_WMS_SMSC_ADDRESS, "QMI_ERR_WMS_SMSC_ADDRESS", "" },
	{ QMI_ERR_INFORMATION_UNAVAILABLE, "QMI_ERR_INFORMATION_UNAVAILABLE", "" },
	{ QMI_ERR_SEGMENT_TOO_LONG, "QMI_ERR_SEGMENT_TOO_LONG", "" },
	{ QMI_ERR_SEGMENT_ORDER, "QMI_ERR_SEGMENT_ORDER", "" },
	{ QMI_ERR_BUNDLING_NOT_SUPPORTED, "QMI_ERR_BUNDLING_NOT_SUPPORTED", "" },
	{ QMI_ERR_OPERATION_PARTIAL_FAILURE, "QMI_ERR_OPERATION_PARTIAL_FAILURE", "" },
	{ QMI_ERR_POLICY_MISMATCH, "QMI_ERR_POLICY_MISMATCH", "" },
	{ QMI_ERR_SIM_FILE_NOT_FOUND, "QMI_ERR_SIM_FILE_NOT_FOUND", "" },
	{ QMI_ERR_EXTENDED_INTERNAL, "QMI_ERR_EXTENDED_INTERNAL", "" },
	{ QMI_ERR_ACCESS_DENIED, "QMI_ERR_ACCESS_DENIED", "" },
	{ QMI_ERR_HARDWARE_RESTRICTED, "QMI_ERR_HARDWARE_RESTRICTED", "" },
	{ QMI_ERR_ACK_NOT_SENT, "QMI_ERR_ACK_NOT_SENT", "" },
	{ QMI_ERR_INJECT_TIMEOUT, "QMI_ERR_INJECT_TIMEOUT", "" },
	{ QMI_ERR_INCOMPATIBLE_STATE, "QMI_ERR_INCOMPATIBLE_STATE", "" },
	{ QMI_ERR_FDN_RESTRICT, "QMI_ERR_FDN_RESTRICT", "" },
	{ QMI_ERR_SUPS_FAILURE_CASE, "QMI_ERR_SUPS_FAILURE_CASE", "" },
	{ QMI_ERR_NO_RADIO, "QMI_ERR_NO_RADIO", "" },
	{ QMI_ERR_NOT_SUPPORTED, "QMI_ERR_NOT_SUPPORTED", "" },
	{ QMI_ERR_NO_SUBSCRIPTION, "QMI_ERR_NO_SUBSCRIPTION", "" },
	{ QMI_ERR_CARD_CALL_CONTROL_FAILED, "QMI_ERR_CARD_CALL_CONTROL_FAILED", "" },
	{ QMI_ERR_NETWORK_ABORTED, "QMI_ERR_NETWORK_ABORTED", "" },
	{ QMI_ERR_MSG_BLOCKED, "QMI_ERR_MSG_BLOCKED", "" },
	{ QMI_ERR_INVALID_SESSION_TYPE, "QMI_ERR_INVALID_SESSION_TYPE", "" },
	{ QMI_ERR_INVALID_PB_TYPE, "QMI_ERR_INVALID_PB_TYPE", "" },
	{ QMI_ERR_NO_SIM, "QMI_ERR_NO_SIM", "" },
	{ QMI_ERR_PB_NOT_READY, "QMI_ERR_PB_NOT_READY", "" },
	{ QMI_ERR_PIN_RESTRICTION, "QMI_ERR_PIN_RESTRICTION", "" },
	{ QMI_ERR_PIN2_RESTRICTION, "QMI_ERR_PIN2_RESTRICTION", "" },
	{ QMI_ERR_PUK_RESTRICTION, "QMI_ERR_PUK_RESTRICTION", "" },
	{ QMI_ERR_PUK2_RESTRICTION, "QMI_ERR_PUK2_RESTRICTION", "" },
	{ QMI_ERR_PB_ACCESS_RESTRICTED, "QMI_ERR_PB_ACCESS_RESTRICTED", "" },
	{ QMI_ERR_PB_DELETE_IN_PROGRESS, "QMI_ERR_PB_DELETE_IN_PROGRESS", "" },
	{ QMI_ERR_PB_TEXT_TOO_LONG, "QMI_ERR_PB_TEXT_TOO_LONG", "" },
	{ QMI_ERR_PB_NUMBER_TOO_LONG, "QMI_ERR_PB_NUMBER_TOO_LONG", "" },
	{ QMI_ERR_PB_HIDDEN_KEY_RESTRICTION, "QMI_ERR_PB_HIDDEN_KEY_RESTRICTION", "" },
	{ QMI_ERR_PB_NOT_AVAILABLE, "QMI_ERR_PB_NOT_AVAILABLE", "" },
	{ QMI_ERR_DEVICE_MEMORY_ERROR, "QMI_ERR_DEVICE_MEMORY_ERROR", "" },
	{ QMI_ERR_NO_PERMISSION, "QMI_ERR_NO_PERMISSION", "" },
	{ QMI_ERR_TOO_SOON, "QMI_ERR_TOO_SOON", "" },
	{ QMI_ERR_TIME_NOT_ACQUIRED, "QMI_ERR_TIME_NOT_ACQUIRED", "" },
	{ QMI_ERR_OPERATION_IN_PROGRESS, "QMI_ERR_OPERATION_IN_PROGRESS", "" },
	{ QMI_ERR_FW_WRITE_FAILED, "QMI_ERR_FW_WRITE_FAILED", "" },
	{ QMI_ERR_FW_INFO_READ_FAILED, "QMI_ERR_FW_INFO_READ_FAILED", "" },
	{ QMI_ERR_FW_FILE_NOT_FOUND, "QMI_ERR_FW_FILE_NOT_FOUND", "" },
	{ QMI_ERR_FW_DIR_NOT_FOUND, "QMI_ERR_FW_DIR_NOT_FOUND", "" },
	{ QMI_ERR_FW_ALREADY_ACTIVATED, "QMI_ERR_FW_ALREADY_ACTIVATED", "" },
	{ QMI_ERR_FW_CANNOT_GENERIC_IMAGE, "QMI_ERR_FW_CANNOT_GENERIC_IMAGE", "" },
	{ QMI_ERR_FW_FILE_OPEN_FAILED, "QMI_ERR_FW_FILE_OPEN_FAILED", "" },
	{ QMI_ERR_FW_UPDATE_DISCONTINUOUS_FRAME, "QMI_ERR_FW_UPDATE_DISCONTINUOUS_FRAME", "" },
	{ QMI_ERR_FW_UPDATE_FAILED, "QMI_ERR_FW_UPDATE_FAILED", "" },
	{ QMI_ERR_CAT_EVENT_REGISTRATION_FAILED, "QMI_ERR_CAT_EVENT_REGISTRATION_FAILED", "" },
	{ QMI_ERR_CAT_INVALID_TERMINAL_RESPONSE, "QMI_ERR_CAT_INVALID_TERMINAL_RESPONSE", "" },
	{ QMI_ERR_CAT_INVALID_ENVELOPE_COMMAND, "QMI_ERR_CAT_INVALID_ENVELOPE_COMMAND", "" },
	{ QMI_ERR_CAT_ENVELOPE_COMMAND_BUSY, "QMI_ERR_CAT_ENVELOPE_COMMAND_BUSY", "" },
	{ QMI_ERR_CAT_ENVELOPE_COMMAND_FAILED, "QMI_ERR_CAT_ENVELOPE_COMMAND_FAILED", "" },
	{ QMI_ERR_QRILD, "QRILD_ERR", "" },
	{0, NULL, NULL },
};

const struct enum_value qmi_service_values[] = {
	{ QMI_SERVICE_UNKNOWN, "QMI_SERVICE_UNKNOWN", "unknown" },
	{ QMI_SERVICE_CTL, "QMI_SERVICE_CTL", "ctl" },
	{ QMI_SERVICE_WDS, "QMI_SERVICE_WDS", "wds" },
	{ QMI_SERVICE_DMS, "QMI_SERVICE_DMS", "dms" },
	{ QMI_SERVICE_NAS, "QMI_SERVICE_NAS", "nas" },
	{ QMI_SERVICE_QOS, "QMI_SERVICE_QOS", "qos" },
	{ QMI_SERVICE_WMS, "QMI_SERVICE_WMS", "wms" },
	{ QMI_SERVICE_PDS, "QMI_SERVICE_PDS", "pds" },
	{ QMI_SERVICE_AUTH, "QMI_SERVICE_AUTH", "auth" },
	{ QMI_SERVICE_AT, "QMI_SERVICE_AT", "at" },
	{ QMI_SERVICE_VOICE, "QMI_SERVICE_VOICE", "voice" },
	{ QMI_SERVICE_CAT2, "QMI_SERVICE_CAT2", "cat2" },
	{ QMI_SERVICE_UIM, "QMI_SERVICE_UIM", "uim" },
	{ QMI_SERVICE_PBM, "QMI_SERVICE_PBM", "pbm" },
	{ QMI_SERVICE_QCHAT, "QMI_SERVICE_QCHAT", "qchat" },
	{ QMI_SERVICE_RMTFS, "QMI_SERVICE_RMTFS", "rmtfs" },
	{ QMI_SERVICE_TEST, "QMI_SERVICE_TEST", "test" },
	{ QMI_SERVICE_LOC, "QMI_SERVICE_LOC", "loc" },
	{ QMI_SERVICE_SAR, "QMI_SERVICE_SAR", "sar" },
	{ QMI_SERVICE_IMS, "QMI_SERVICE_IMS", "ims" },
	{ QMI_SERVICE_ADC, "QMI_SERVICE_ADC", "adc" },
	{ QMI_SERVICE_CSD, "QMI_SERVICE_CSD", "csd" },
	{ QMI_SERVICE_MFS, "QMI_SERVICE_MFS", "mfs" },
	{ QMI_SERVICE_TIME, "QMI_SERVICE_TIME", "time" },
	{ QMI_SERVICE_TS, "QMI_SERVICE_TS", "ts" },
	{ QMI_SERVICE_TMD, "QMI_SERVICE_TMD", "tmd" },
	{ QMI_SERVICE_SAP, "QMI_SERVICE_SAP", "sap" },
	{ QMI_SERVICE_WDA, "QMI_SERVICE_WDA", "wda" },
	{ QMI_SERVICE_TSYNC, "QMI_SERVICE_TSYNC", "tsync" },
	{ QMI_SERVICE_RFSA, "QMI_SERVICE_RFSA", "rfsa" },
	{ QMI_SERVICE_CSVT, "QMI_SERVICE_CSVT", "csvt" },
	{ QMI_SERVICE_QCMAP, "QMI_SERVICE_QCMAP", "qcmap" },
	{ QMI_SERVICE_IMSP, "QMI_SERVICE_IMSP", "imsp" },
	{ QMI_SERVICE_IMSVT, "QMI_SERVICE_IMSVT", "imsvt" },
	{ QMI_SERVICE_IMSA, "QMI_SERVICE_IMSA", "imsa" },
	{ QMI_SERVICE_COEX, "QMI_SERVICE_COEX", "coex" },
	{ QMI_SERVICE_PDC, "QMI_SERVICE_PDC", "pdc" },
	{ QMI_SERVICE_STX, "QMI_SERVICE_STX", "stx" },
	{ QMI_SERVICE_BIT, "QMI_SERVICE_BIT", "bit" },
	{ QMI_SERVICE_IMSRTP, "QMI_SERVICE_IMSRTP", "imsrtp" },
	{ QMI_SERVICE_RFRPE, "QMI_SERVICE_RFRPE", "rfrpe" },
	{ QMI_SERVICE_DSD, "QMI_SERVICE_DSD", "dsd" },
	{ QMI_SERVICE_SSCTL, "QMI_SERVICE_SSCTL", "ssctl" },
	{ QMI_SERVICE_DPM, "QMI_SERVICE_DPM", "dpm" },
	{ QMI_SERVICE_CAT, "QMI_SERVICE_CAT", "cat" },
	{ QMI_SERVICE_RMS, "QMI_SERVICE_RMS", "rms" },
	{ QMI_SERVICE_OMA, "QMI_SERVICE_OMA", "oma" },
	{ QMI_SERVICE_FOTA, "QMI_SERVICE_FOTA", "fota" },
	{ QMI_SERVICE_GMS, "QMI_SERVICE_GMS", "gms" },
	{ QMI_SERVICE_GAS, "QMI_SERVICE_GAS", "gas" },
	{ 0, NULL, NULL }
};
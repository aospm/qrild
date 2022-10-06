/*
 * Copyright (C) 2022, Linaro Ltd.
 * Author: Caleb Connolly <caleb.connolly@linaro.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 * This file is responsible for wrapping libqrtr's QMI
 * message handling.
 */

#include <errno.h>
#include <linux/qrtr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "libqrtr.h"

#include "timespec.h"
#include "list.h"
#include "libqril_private.h"
#include "util.h"

#include "q_log.h"
#include "workqueue.h"

#define log_trace_msg(msg, fmt, ...)                                                               \
	log_trace("0x%04x|0x%04x: " fmt, msg->qmi_header.msg_id, msg->qmi_header.txn_id,           \
		  ##__VA_ARGS__)

#define QMI_MSG_MAX_SIZE 1024

static pthread_mutex_t message_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t message_received = PTHREAD_COND_INITIALIZER;
static struct list_head pending_tx = LIST_INIT(pending_tx);
static struct list_head pending_rx = LIST_INIT(pending_rx);
static uint16_t qmi_txn = 1;

pthread_t recv_thread;
int qrtr_fd;

/**
 * @brief The message_lifetime struct is used
 * to track the lifetime of a QMI transaction. It is
 * constructed when the client sends a request and
 * destroyed when the response is returned. A lifetime
 * is also constructed when the mode sends an indication.
 * 
 * @hdr: A copy of the qmi_header of the message, used
 *       for parsing and filtering.
 * @service: The service this message is for
 * @name: Friendly name for the message, may be unset
 * @buf: The encoded QMI message
 * @buf_len: Length of encoded message
 * @li: List entry
 * @mut: Pointer to the mutex to lock when interacting with this message
 * @handler: Callback handler for async clients
 * @cb_data: Client context pointer, passed in to the async handler
 * @resp_header: Response message to decode, not valid for indications
 * @async_work: work item to process an async message
 * @indication_work: work item to process an indication message
 */
struct message_lifetime {
	struct qmi_header hdr;
	enum qmi_service service;
	const char *name;
	bool sent;

	void *buf;
	size_t buf_len;

	struct list_head li;
	pthread_mutex_t *mut;

	qmi_message_handler_t handler;
	void *cb_data;
	struct qmi_message_header *resp_header;
	struct q_work async_work;

	struct q_work indication_work;
};

/**
 * @brief print a message header into a human readable string @buf
 * 
 * @msg: The message to dump
 * @buf: The buffer to dump into
 * @buf_len: Length of the buffer
 * 
 * @returns result of snprintf, number of bytes written or negative error
 * the message was only written successfully if the number of bytes written
 * is less than @buf_len
 */
static int _print_qmi_msg(struct qmi_header *hdr, const char *name, enum qmi_service service,
			  char *out_buf, size_t buf_len)
{
	return snprintf(out_buf, buf_len,
			"%1$s:\n"
			"	type: %2$1d, txn_id: %3$4d\n"
			"	msg_id: 0x%4$04x, msg_len: 0x%5$04x\n"
			"	service: %6$s",
			name, hdr->type, hdr->txn_id, hdr->msg_id, hdr->msg_len,
			libqril_qmi_service_name(service));
}

static int _print_message(struct qmi_message_header *msg, char *buf, size_t buf_len)
{
	return _print_qmi_msg(&msg->qmi_header, msg->name, msg->service, buf, buf_len);
}

static int _print_lifetime(struct message_lifetime *lt, char *buf, size_t buf_len)
{
	return _print_qmi_msg(&lt->hdr, lt->name, lt->service, buf, buf_len);
}

// Call with message_mutex locked!!
static void _dump_pending()
{
	struct message_lifetime *lt;
	char msg_buf[256];

	log_trace("Pending messages:\n\t\tPENDING TX:");
	list_for_each_entry(lt, &pending_tx, li)
	{
		memset(msg_buf, 0, 256);
		_print_lifetime(lt, msg_buf, 256);
		log_trace("%s", msg_buf);
	}
	log_trace("\t\tPENDING RX:");
	list_for_each_entry(lt, &pending_rx, li)
	{
		memset(msg_buf, 0, 256);
		_print_lifetime(lt, msg_buf, 256);
		log_trace("%s", msg_buf);
	}
}

/**
 * @brief decode a response into the lifetime resp_header.
 * Not valid for indications
 *
 * @lt: The message to decode
 *
 * @returns 0 on success, negative err on failure
 */
int _message_decode(struct message_lifetime *lt)
{
	if (!lt->resp_header) {
		return -EINVAL;
	}

	ssize_t len = qmi_decode_message2(lt->buf, lt->buf_len, lt->resp_header);
	if (len <= 0) {
		return len;
	}

	return 0;
}

static void _message_indication_work(void *_data)
{
	struct message_lifetime *lt = _data;
	event_new_indication(lt->service, lt->buf, lt);
}

static void _message_async_work(void *_data)
{
	struct message_lifetime *lt = _data;
	int rc = _message_decode(lt);
	if (rc) {
		log_error("Failed to decode message: 0x%04x (%d)", lt->hdr.msg_id, lt->hdr.txn_id);
		return;
	}
	lt->handler(lt->cb_data, lt->resp_header);

	messages_free_lifetime(lt);
}

static void _message_lifetime_new(struct message_lifetime **lt, const struct qmi_header *hdr,
				  enum qmi_service service, const char *name, void *buf,
				  size_t buf_len, qmi_message_handler_t handler,
				  struct qmi_message_header *resp, void *cb_data)
{
	struct message_lifetime *lifetime;
	lifetime = *lt = zalloc(sizeof(struct message_lifetime));

	lifetime->hdr = *hdr;
	lifetime->service = service;
	lifetime->name = name;
	lifetime->buf = buf;
	lifetime->buf_len = buf_len;
	lifetime->cb_data = cb_data;
	if (handler) {
		lifetime->handler = handler;
		lifetime->async_work.data = lifetime;
		lifetime->async_work.func = _message_async_work;
	}

	lifetime->resp_header = resp;
	lifetime->indication_work.data = lifetime;
	lifetime->indication_work.func = _message_indication_work;
}

/**
 * @brief: Check if the message has received a response yet
 * 
 * @lt: The lifetime to check
 */
static bool _find_response(struct message_lifetime *lt)
{
	struct message_lifetime *m;

	list_for_each_entry(m, &pending_rx, li)
	{
		if (m == lt)
			return true;
	}

	return false;
}

/**
 * @brief Find a pending message by transaction ID
 * 
 * @txn_id: The unique ID to search for
 */
static struct message_lifetime *_find_pending_msg(uint16_t txn_id)
{
	struct message_lifetime *m;

	list_for_each_entry(m, &pending_tx, li)
	{
		if (m->hdr.txn_id == txn_id)
			return m;
	}

	return NULL;
}

/* Receive and process a QMI message */
static void _recv_message(struct qrtr_packet *pkt, struct sockaddr_qrtr *sq)
{
	struct message_lifetime *lt = NULL;
	const struct qmi_header *hdr;
	struct qmi_tlv *tlv;
	enum qmi_service service;
	char buf[256];
	int rc;

	hdr = qmi_get_header(pkt);
	if (!hdr) {
		log_error("Couldn't decode message");
		return;
	}

	rc = qmi_service_from_port(sq->sq_port, &service);
	if (rc) {
		log_error("Message from unknown service on port: %u", sq->sq_port);
		return;
	}

	_print_qmi_msg(hdr, "", service, buf, 256);
	log_info("Received msg: %s", buf);

	if (hdr->type == QMI_INDICATION) {
		_message_lifetime_new(&lt, hdr, service, NULL, pkt->data, pkt->data_len, NULL, NULL,
				      NULL);
		tlv = qmi_tlv_decode(lt->buf, lt->buf_len);
		qmi_tlv_dump(tlv, service, "UNKNOWN");
		qmi_tlv_free(tlv);
	} else {
		q_thread_mutex_lock(&message_mutex);
		lt = _find_pending_msg(hdr->txn_id);
		if (!lt) {
			log_error("Failed to find pending lifetime for msg 0x%04x (txn: 0x%04x)",
				  hdr->msg_id, hdr->txn_id);
			return;
		}
		list_remove(&lt->li);
		q_thread_mutex_unlock(&message_mutex);

		memcpy(&lt->hdr, hdr, sizeof(struct qmi_header));
	}

	if (!lt) {
		log_error("No lifetime for message 0x%04x (%d)", hdr->msg_id, hdr->txn_id);
		return;
	}

	lt->buf = pkt->data;
	lt->buf_len = pkt->data_len;
	log_info("[QRTR] RX: svc: %s, msg: %s (0x%04x)", libqril_qmi_service_name(service),
		lt->name ?: "UNKNOWN", lt->hdr.msg_id);

	if (lt->handler) {
		log_trace("Scheduling async handler...");
		q_work_schedule_now(&lt->async_work);
		return;
	}

	if (hdr->type == QMI_INDICATION) {
		log_trace("Broadcasting new qmi indication event");
		q_work_schedule_now(&lt->indication_work);
		return;
	}

	q_thread_mutex_lock(&message_mutex);
	list_append(&pending_rx, &lt->li);
	pthread_cond_broadcast(&message_received);
	q_thread_mutex_unlock(&message_mutex);
}

static int _recv_pending()
{
	void *buf = zalloc(QMI_MSG_MAX_SIZE);
	struct qrtr_packet pkt;
	struct sockaddr_qrtr sq;
	socklen_t sl = sizeof(sq);
	int rc;

	memset(buf, 0, QMI_MSG_MAX_SIZE);

	rc = recvfrom(qrtr_fd, buf, QMI_MSG_MAX_SIZE, 0, (void *)&sq, &sl);
	if (rc < 0) {
		if (errno == ENETRESET || errno == EAGAIN) {
			log_error("[QRTR] recvfrom got %d (%s)", rc, strerror(errno));
			return rc;
		}
		log_error("[QRTR] recvfrom failed: %d (%s)", errno, strerror(errno));
		abort();
	}

	// Decode the buffer into a qrtr_packet
	rc = qrtr_decode(&pkt, buf, rc, &sq);
	if (rc < 0) {
		log_error("[QRTR] failed to decode qrtr packet");
		return rc;
	}

	// Failing to decode a packet isn't a fatal error
	switch (pkt.type) {
	case QRTR_TYPE_NEW_SERVER:
		qmi_service_new(&pkt);
		break;
	case QRTR_TYPE_DEL_SERVER:
		qmi_service_goodbye(pkt.service);
		break;
	case QRTR_TYPE_DATA:
		_recv_message(&pkt, &sq);
		break;
	default:
		log_warn("[QRTR] Unknown packet type: %u", pkt.type);
		print_hex_dump("[QRTR] Unknown packet content:", pkt.data, pkt.data_len);
	}

	return 0;
}

/**
 * @brief: Send a QMI message, message_mutex must be locked
 *
 * @lt: The message to send
 * @node: The QRTR node to send to
 * @port: The QRTR port to send to
 */
static void _send_msg(struct message_lifetime *lt)
{
	int rc;
	const char *service = libqril_qmi_service_name(lt->service);
	int port, node;

	rc = qmi_service_get(lt->service, &port, &node);
	if (rc) {
		log_error("Couldn't send message %s: service not found! %d", lt->name, rc);
		return;
	}

	log_trace("[QRTR] TX: svc: %s, msg: %s", service ?: "UNKNOWN", lt->name ?: "UNKNOWN");
	qmi_tlv_dump_buf(lt->buf, lt->buf_len, lt->service, lt->name);

	rc = qrtr_sendto(qrtr_fd, node, port, lt->buf, lt->buf_len);
	if (rc) {
		log_error("Couldn't send message: %d (%s)", rc, strerror(rc));
		return;
	}

	lt->sent = true;
	free(lt->buf);

	return;
}

static void _send_pending()
{
	struct message_lifetime *lt;

	q_thread_mutex_lock(&message_mutex);
	if (list_empty(&pending_tx)) {
		q_thread_mutex_unlock(&message_mutex);
		return;
	}

	log_trace("Sending pending messages..");

	list_for_each_entry(lt, &pending_tx, li)
	{
		if (!lt->sent)
			_send_msg(lt);
		else
			break;
	}
	q_thread_mutex_unlock(&message_mutex);
}

static void *_recv_loop(void *_)
{
	struct qrtr_ctrl_pkt pkt;
	int rc;

	// Find all QRTR services
	memset(&pkt, 0, sizeof(pkt));
	pkt.cmd = QRTR_TYPE_NEW_LOOKUP;
	rc = qrtr_sendto(qrtr_fd, 1, QRTR_PORT_CTRL, &pkt, sizeof(pkt));
	if (rc < 0) {
		log_error("[MSGLOOP] Failed to look up QRTR services: %d", rc);
		return NULL;
	}
	log_info("Sent QRTR lookup");

	while (true) {
		_send_pending();

		rc = qrtr_poll(qrtr_fd, 50);
		if (rc < 0 && errno == EINTR)
			continue;
		if (rc < 0) {
			log_error("[MSGLOOP] poll() failed: %d (%s)", errno, strerror(errno));
			continue;
		}

		if (rc)
			_recv_pending();
	}

	log_info("[MSGLOOP] Quitting!");
	qrtr_close(qrtr_fd);

	return NULL;
}

/****** Internal API ******/

void messages_init()
{
	qrtr_fd = qrtr_open(0);
	if (qrtr_fd < 0) {
		log_error("Failed to open QRTR socket: %d", qrtr_fd);
		abort();
	}

	if (pthread_create(&recv_thread, NULL, _recv_loop, NULL)) {
		log_error("Failed to create msg thread");
		abort();
	}

	return;
}

void messages_dump_pending()
{
	_dump_pending();
}

void messages_free_lifetime(struct message_lifetime *lt)
{
	free(lt->buf);
	free(lt);
}

/****** Public API ********/

// Declared in libqril.h
int libqril_send_message_sync(struct qmi_message_header *msg, struct qmi_message_header *resp)
{
	// FIXME: recycle buffers here
	uint8_t *buf = zalloc(QMI_MSG_MAX_SIZE);
	struct message_lifetime *lifetime = NULL;
	int rc, len;
	int port, node;
	enum qmi_service service = msg->service;
	struct timespec timeout;
	struct qmi_response_type_v01 res;
	struct qmi_tlv *tlv;
	bool found = false;

	if (!msg || !resp)
		return -EINVAL;

	rc = qmi_service_get(service, &port, &node);
	if (rc < 0)
		return rc;

	len = qmi_encode_message2(buf, QMI_MSG_MAX_SIZE, qmi_txn++, msg);
	if (len < 0) {
		log_error("Failed to encode message (%d)", len);
		return len;
	}

	log_trace_msg(msg, "Encoded message. %s is on node %d, port %d", libqril_qmi_service_name(service),
		      port, node);

	_message_lifetime_new(&lifetime, &msg->qmi_header, service, msg->name, buf, len, NULL, resp,
			      NULL);


	/* This will mean messages are sent in LIFO order */
	q_thread_mutex_lock(&message_mutex);
	list_append(&pending_tx, &lifetime->li);

	timeout = timespec_add(timespec_now(), timespec_from_ms(5000));
	while (!(found = _find_response(lifetime)) && rc != ETIMEDOUT) {
		rc = q_thread_cond_timedwait(&message_received, &message_mutex, &timeout);
	}
	if (rc && !found) {
		log_trace("Failed waiting for response: %d", rc);
		q_thread_mutex_unlock(&message_mutex);
		return -rc;
	}
	list_remove(&lifetime->li);
	q_thread_mutex_unlock(&message_mutex);

	tlv = qmi_tlv_decode(lifetime->buf, lifetime->buf_len);
	res = qmi_tlv_get_result(tlv);
	qmi_tlv_dump(tlv, service, resp ? resp->name : "UNKNOWN");
	qmi_tlv_free(tlv);

	// Decode the response into resp
	rc = _message_decode(lifetime);

	messages_free_lifetime(lifetime);
	
	if (rc < 0)
		return rc;

	return res.error;
}

// FIXME: reduce duplication with _sync()
int libqril_send_message_async(struct qmi_message_header *msg, struct qmi_message_header *resp,
			       void *cb_data, qmi_message_handler_t cb)
{
	// FIXME: recycle buffers here
	uint8_t *buf = zalloc(QMI_MSG_MAX_SIZE);
	struct message_lifetime *lifetime = NULL;
	int rc, len;
	int port, node;
	enum qmi_service service = msg->service;

	rc = qmi_service_get(service, &port, &node);
	if (rc < 0)
		return rc;

	len = qmi_encode_message2(buf, QMI_MSG_MAX_SIZE, qmi_txn++, msg);

	if (len < 0) {
		log_error("Failed to encode message (%d)", len);
		return len;
	}

	_message_lifetime_new(&lifetime, &msg->qmi_header, service, msg->name, buf, len, cb, resp,
			      cb_data);

	/* This will mean messages are sent in LIFO order */
	q_thread_mutex_lock(&message_mutex);
	list_append(&pending_tx, &lifetime->li);
	q_thread_mutex_unlock(&message_mutex);
	// This will be replaced by the response buffer
	free(lifetime->buf);

	return 0;
}

int libqril_send_basic_request_sync(enum qmi_service service, uint16_t message_id,
				    struct qmi_message_header *resp)
{
	struct qmi_message_header req = { .qmi_header = { QMI_REQUEST, 0, message_id, 0 },
					  .service = service };

	return libqril_send_message_sync(&req, resp);
}

int libqril_send_basic_request_async(enum qmi_service service, uint16_t message_id,
				     struct qmi_message_header *resp, void *cb_data,
				     qmi_message_handler_t cb)
{
	struct qmi_message_header req = { .qmi_header = { QMI_REQUEST, 0, message_id, 0 },
					  .service = service };

	return libqril_send_message_async(&req, resp, cb_data, cb);
}

static struct _basic_qmi_response {
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;
};

static struct qmi_elem_info _basic_qmi_response_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct _basic_qmi_response, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{}
};

int libqril_send_message_ack_sync(struct qmi_message_header *req)
{
	struct _basic_qmi_response resp = { .hdr = { .qmi_header = { QMI_RESPONSE, 0, req->qmi_header.msg_id, 0 },
					  .service = req->service, .ei = _basic_qmi_response_ei } };

	int rc = libqril_send_message_sync(req, &resp);
	if (rc)
		return rc;
	
	return resp.res.error;
}

int libqril_async_ack_get_error(struct qmi_message_header *msg)
{
	if (msg->ei != _basic_qmi_response_ei)
		return -EINVAL;
	
	return ((struct _basic_qmi_response*)msg)->res.error;
}

int libqril_send_message_ack_async(struct qmi_message_header *req, void *cb_data,
				     qmi_message_handler_t cb)
{
	struct _basic_qmi_response resp = { .hdr = { .qmi_header = { QMI_RESPONSE, 0, req->qmi_header.msg_id, 0 },
					  .service = req->service, .ei = _basic_qmi_response_ei } };

	return libqril_send_message_async(req, &resp, cb_data, cb);
}

int libqril_send_message_basic_ack_sync(enum qmi_service service, uint16_t message_id)
{
	struct qmi_message_header req = { .qmi_header = { QMI_REQUEST, 0, message_id, 0 },
					  .service = service };
	return libqril_send_message_ack_sync(&req);
}

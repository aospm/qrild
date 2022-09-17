/*
 * This file is responsible for wrapping libqrtr's QMI
 * message wrapping and transceiving.
 */

#include <errno.h>
#include <linux/qrtr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "q_log.h"
#include "workqueue.h"

#include "libqrtr.h"

#include "timespec.h"
#include "list.h"
#include "libqril_private.h"
#include "qrild_msg.h"
#include "qrild_qmi.h"
#include "util.h"

#include "qmi_uim.h"

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
int _print_message(struct qmi_message_header *msg, char *buf, size_t buf_len)
{
	struct qmi_header *hdr = &msg->qmi_header;
	return snprintf(buf, buf_len,
		 "%s:\n"
		 "	type: %1$1d, txn_id: %2$4d\n"
		 "	msg_id: 0x%3$04x, msg_len: 0x%3$04x\n"
		 "	service: %4$s",
		 hdr->type, hdr->txn_id, hdr->msg_id, hdr->msg_len,
		 qmi_service_get_name(msg->service));
}

/**
 * @brief decode a response into resp_header. Not valid for indications
 * 
 * @lt: The message to decode
 * 
 * @returns 0 on success, negative err on failure
 */
int _message_decode(struct message_lifetime *lt)
{
	if (!lt->resp_header) {
		log_error("Message has no response header! 0x%04x (%d)", lt->hdr.msg_id,
			lt->hdr.txn_id);
		return -EINVAL;
	}

	ssize_t len = qmi_decode_message2(lt->buf, lt->buf_len, lt->resp_header);
	if (len <= 0) {
		log_error("Failed to decode message: 0x%04x (%d)", lt->hdr.msg_id,
			lt->hdr.txn_id);
		return len;
	}

	return 0;
}

void _message_indication_work(struct message_lifetime *lt)
{

}

void _message_async_work(struct message_lifetime *lt)
{
	// decode message and call handler
}

void _message_lifetime_new(struct message_lifetime **lt,
			    struct qmi_header *hdr, enum qmi_service service,
			    const char *name, void *buf, size_t buf_len,
			    qmi_message_handler_t handler, struct qmi_message_header *resp)
{
	struct message_lifetime *lifetime;
	lifetime = *lt = zalloc(sizeof(struct message_lifetime));

	lifetime->hdr = *hdr;
	lifetime->service = service;
	lifetime->name = name;
	lifetime->buf = buf;
	lifetime->buf_len = buf_len;
	if (handler) {
		lifetime->handler = handler;
		lifetime->async_work.data = lifetime;
		lifetime->async_work.func = _message_async_work;
		lifetime->resp_header = resp;
	}

	lifetime->indication_work.data = lifetime;
	lifetime->indication_work.func = _message_indication_work;
}

/**
 * @brief: Check if the message has received a response yet
 * 
 * @lt: The lifetime to check
 */
bool _find_response(struct message_lifetime *lt)
{
	struct message_lifetime *m;

	list_for_each_entry(m, &pending_rx, li) {
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
int _find_pending_msg(uint16_t txn_id)
{
	struct message_lifetime *m;

	list_for_each_entry(m, &pending_rx, li) {
		if (m->hdr.txn_id == txn_id)
			return m;
	}

	return NULL;
}

/**
 * @brief: Send a QMI message, message_mutex must be locked
 *
 * @lt: The message to send
 * @node: The QRTR node to send to
 * @port: The QRTR port to send to
 */
int _send_msg(struct message_lifetime *lt, int node, int port)
{
	int rc;
	const char *service = qmi_service_get_name(lt->service);
	log_trace("[QRTR] TX: %s - %s", service, lt->name);
	qmi_tlv_dump_buf(lt->buf, lt->buf_len, lt->service);

	rc = qrtr_sendto(qrtr_fd, node, port, lt->buf, lt->buf_len);
	if (rc)
		return rc;
	
	list_append(&pending_tx, &lt->li);

	return rc;
}

/* Receive and process a QMI message */
void _recv_message(struct qrtr_packet *pkt, struct sockaddr_qrtr *sq);
{
	struct message_lifetime *lt = NULL;
	struct qmi_header *hdr;
	enum qmi_service service;
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

	if (hdr->type == QMI_INDICATION) {
		_message_lifetime_new(&lt, hdr, service, NULL,
			pkt->data, pkt->data_len, NULL, NULL);
	}

	if (type != QMI_INDICATION) {
		q_thread_mutex_lock(&message_mutex);
		lt = _find_pending_msg(txn_id);
		list_remove(&lt->li);
		q_thread_mutex_unlock(&message_mutex);

		memcpy(&lt->hdr, hdr, sizeof(struct qmi_header));
	}
	
	if (!lt) {
		log_error("No lifetime for message 0x%04x (%d)", msg_id, txn_id);
		return;
	}

	lt->buf = pkt->data;
	lt->buf_len = pkt->data_len;
	log_info("[QRTR] RX: %s - %s (0x%04x)", qmi_service_get_name(service),
		lt->name, lt->hdr.msg_id);

	if (lt->handler) {
		log_trace("Scheduling async handler...");
		q_work_schedule_now(&lt->async_work);
		return;
	}

	q_thread_mutex_lock(&message_mutex);
	list_append(&pending_rx, &lt->li);
	q_thread_mutex_unlock(&message_mutex);
}

int _recv_pending()
{
	static void *buf = zalloc(QMI_MSG_MAX_SIZE);

	struct message_lifetime *lt;
	struct qrtr_packet pkt;
	struct sockaddr_qrtr sq;
	socklen_t sl = sizeof(sq);
	int rc;

	memset(buf, 0, QMI_MSG_MAX_SIZE);

	rc = recvfrom(qrtr_fd, buf, QMI_MSG_MAX_SIZE, 0, (void*)&sq, &sl);
	if (rc < 0) {
		if (errno == ENETRESET || errno == EAGAIN) {
			log_error("[QRTR] recvfrom got %d (%s)", ret, strerror(errno));
			return;
		}
		log_error("[QRTR] recvfrom failed: %d (%s)", errno, strerror(errno));
		abort();
	}

	ret = qrtr_decode(&pkt, buf, ret, &sq);
	if (ret < 0) {
		log_error("[QRTR] failed to decode qrtr packet");
		return;
	}

	switch(pkt.type) {
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
		print_hex_dump("[QRTR] Unknown packet content:",
			pkt.data, pkt.data_len);
	}
}

static void *_recv_loop(void * _)
{
	struct qrtr_ctrl_pkt pkt;
	
	int rc;

	// Find all QRTR services
	memset(&pkt, 0, sizeof(pkt));
	pkt.cmd = QRTR_TYPE_NEW_LOOKUP;
	rc = qrtr_sendto(qrtr_fd, 1, QRTR_PORT_CTRL, &pkt, sizeof(pkt));
	if (rc < 0) {
		log_error("[MSGLOOP] Failed to look up QRTR services: %d", rc);
		return (void*)rc;
	}

	while (true) {
		rc = qrtr_poll(qrtr_fd, -1);
		if (rc < 0 && errno == EINTR)
			continue;
		if (rc < 0)
			log_error("[MSGLOOP] poll() failed: %d (%s)", errno, strerror(errno));

		if (rc > 0)
			qrild_qrtr_recv(state);
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

/****** Public API ********/

// Declared in libqril.h
int libqril_send_message_sync(struct qmi_message_header *msg,
			      struct qmi_message_header *resp)
{
	// FIXME: recycle buffers here
	uint8_t *buf = zalloc(QMI_MSG_MAX_SIZE);
	char msg_dump[256];
	struct message_lifetime *lifetime = NULL;
	int rc, len;
	int port, node;
	enum qmi_service service = msg->service;
	struct timespec timeout = timespec_from_ms(5000);
	bool found = false;

	rc = qmi_service_get(service, &port, &node);
	if (rc < 0)
		return rc;

	len = rc = qmi_encode_message2(buf, QMI_MSG_MAX_SIZE, qmi_txn++, msg);
	_print_message(msg, msg_dump, 256);

	if (rc < 0) {
		log_error("Failed to encode message: %s", msg_dump);
		return rc;
	}

	log_debug("Encoded message: %s", msg_dump);

	_message_lifetime_new(&lifetime, &msg->qmi_header, service, msg->name,
		buf, len, NULL, resp);
	
	q_thread_mutex_lock(&message_mutex);
	/* This will mean messages are sent in LIFO order */
	rc = _send_msg(lifetime);
	if (rc < 0) {
		log_error("Failed to send message: %d", rc);
		free(lifetime);
		q_thread_mutex_unlock(&message_mutex);
		return rc;
	}
	while (!(found = _find_response(lifetime)) && rc != ETIMEDOUT) {
		rc = q_thread_cond_timedwait(&message_received,
			&message_mutex, &timeout);
	}
	if (rc && !found) {
		log_error("Failed waiting for response: %d", rc);
		q_thread_mutex_unlock(&message_mutex);
		return rc;
	}

	free(lifetime->buf);
	q_thread_mutex_unlock(&message_mutex);

	return 0;
}


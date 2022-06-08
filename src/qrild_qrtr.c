
#include <errno.h>
#include <linux/qrtr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "libqrtr.h"
#include "logging.h"

#include "list.h"
#include "qrild.h"
#include "qrild_qrtr.h"
#include "qrild_qmi.h"
#include "util.h"

#include "qmi_uim.h"

void print_service(struct qmi_service_info *pkt)
{
	if (!pkt)
		return;

	LOGD("| %4d | %4d | %5d | %4d  | %4d  | %s", pkt->type, pkt->node,
	     pkt->port, pkt->major, pkt->minor,
	     pkt->name ? pkt->name : "<unknown>");
}

int qrild_qrtr_send_to_service(struct rild_state *state,
			       enum qmi_service svc_id, const void *data,
			       size_t sz)
{
	struct qrild_msg *msg;
	struct qmi_service_info *service;
	const struct qmi_header *qmi;
	int rc;

	if (svc_id == QMI_SERVICE_CTL) {
		LOGW("CTL service not supported by QRTR");
		return -1;
	}

	qmi = (const struct qmi_header*)data;

	msg = malloc(sizeof(struct qrild_msg));
	msg->txn = state->txn;
	msg->msg_id = qmi->msg_id;
	list_init(&msg->li);

	// The TX n is encoded in the QMI packet, it must be incremented for
	// every transmit
	state->txn++;

	service = qmi_service_get(&state->services, svc_id);
	if (!service) {
		LOGE("Failed to find service %d (%s)", svc_id,
		     qmi_service_to_string(svc_id, false));
		return -1;
	}

	msg->service = service;

	printf("Sending to service '%s'\n", service->name);
	print_hex_dump("QRTR TX", data, sz);

	rc = qrtr_sendto(state->sock, service->node, service->port, data, sz);
	if (rc == 0)
		list_append(&state->resp_queue, &msg->li);
	else
		free(msg);
	
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
		list_remove(&service->li);
		free(service);

		break;
	case QRTR_TYPE_DATA:
		qmi = qmi_get_header(&pkt);
		if (!qmi) {
			fprintf(stderr, "[QRTR] Failed to get QMI header!\n");
			return;
		}
		msg = qrild_msg_get_by_txn(&state->resp_queue, qmi->txn_id);
		if (!msg) {
			fprintf(stderr, "FIXME!!! can't find msg, creating\n");
			msg = zalloc(sizeof(struct qrild_msg));
			msg->txn = qmi->txn_id;
			list_append(&state->resp_queue, &msg->li);
		}
		msg->msg_id = qmi->msg_id;
		msg->buf = pkt.data;
		msg->buf_len = pkt.data_len;

		printf("[QRTR] data packet from port %d, msg_id: 0x%2x, txn: %d\n",
		       sq.sq_port, msg->msg_id, msg->txn);

		if (state->resp_pending) {
			fprintf(stderr,
				"[QRTR] dropping unhandled pending response"
				" (msg_id: 0x%2x, txn: %d)\n",
				state->resp_pending->msg_id, state->resp_pending->txn);
			list_remove(&msg->li);
			if (msg->buf)
				free(msg->buf);
			free(msg);
		}

		state->resp_pending = msg;

		print_hex_dump("QRTR RX", pkt.data, pkt.data_len);
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

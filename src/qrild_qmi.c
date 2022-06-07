
#include <errno.h>
#include <linux/qrtr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "libqrtr.h"
#include "logging.h"

#include "list.h"
#include "util.h"
#include "qrild.h"
#include "qrild_qmi.h"
#include "qrild_qrtr.h"
#include "qmi_uim.h"
#include "qmi_dms.h"

struct qmi_result {
	uint16_t result;
	uint16_t error;
};

/**
 * qmux_add_header() - add a qmux header to a QMI packet
 *
 * @service: the QMI service to send the data to
 * @client: the client ID
 * @data: the encoded QMI packet
 * @len: length of data
 *
 * @return: a pointer to the QMI packet with the QMUX header prepended
 *
 * This function frees data and replaces it with
 * a new pointer with the QMUX header prepended.
 * len is updated to the new length of the buffer.
 */
// uint8_t *qmi_qmux_add_header(struct qmi_service_info *service, uint8_t *data,
// 			     size_t *len)
// {
// 	uint8_t *buf = (uint8_t *)malloc(*len + sizeof(struct qmux_header));
// 	struct qmux_header *header = (struct qmux_header *)buf;

// 	memset(buf, 0, sizeof(struct qmux_header));
// 	memcpy(buf + sizeof(struct qmux_header), data, *len);

// 	*len += sizeof(struct qmux_header);

// 	free(data);

// 	header->tf = 1;
// 	header->len = *len - 1;
// 	header->ctrl_flag = 0;
// 	header->service = service->type;
// 	header->client = service->client_id;

// 	return buf;
// }

static struct qmi_result *qmi_get_result(void *tlv, char *prefix)
{
	struct qmi_result *res = qmi_tlv_get((struct qmi_tlv *)tlv, 2, NULL);
	if (prefix)
		printf("%s: result: %u, error: %u\n", prefix, res->result,
		       res->error);

	return res;
}

static bool qrild_msg_is_pending(struct list_head *list, uint32_t msg_id)
{
	struct qrild_msg *msg;
	bool res = false;
	int i = 0;
	if (!list->head)
		return false;
	printf("looking for pending msg_id: %d\n", msg_id);
	list_for_each_entry(msg, (list), li)
	{
		if (!msg)
			continue;
		printf("i: %d, id: %d, txn: %u\n", i++, msg->msg_id,
		       msg->txn);
		if (msg->msg_id == msg_id) {
			printf("found match for msg_id: %u\n", msg_id);
			return true;
		}
	}
	return false;
}

// int qrild_qmi_ctl_allocate_cid(struct rild_state *state) {
// 	size_t len;
// 	int rc;
// 	struct qmi_service_info *uim_service =
// 	    qmi_service_get(&state->services, QMI_SERVICE_UIM);
// 	struct qrild_svc_ctl_allocate_cid_req *req =
// 	    qrild_svc_ctl_allocate_cid_req_alloc(state->txn);
// 	qrild_svc_ctl_allocate_cid_req_set_service(req, QMI_SERVICE_CTL);

// 	if (!uim_service) {
// 		LOGW("Can't find UIM service!\n");
// 		return -1;
// 	}

// 	uint8_t *buf =
// 	    (uint8_t *)qrild_svc_ctl_allocate_cid_req_encode(req, &len);
// 	//buf = qmi_qmux_add_header(uim_service, buf, &len);
// 	print_hex_dump("allocate CID", buf, len);

// 	rc = qrild_qrtr_send_to_service(state, QMI_SERVICE_CTL, (void *)buf,
// 					len);
// 	if (rc < 0) {
// 		uim_service->client_id = 1;
// 	}

// 	return rc;
// }

static void dms_get_operating_mode_request(struct rild_state *state)
{
	struct dms_get_operating_mode_req *req;
	struct qrild_msg *msg;
	void *buf;
	size_t len;

	printf("sending dms_get_operating_mode_request\n");

	req = dms_get_operating_mode_req_alloc(state->txn);
	buf = dms_get_operating_mode_req_encode(req, &len);

	qrild_qrtr_send_to_service(state, QMI_SERVICE_DMS, buf, len);
	dms_get_operating_mode_req_free(req);
}

/*
 * check if the pending message is one of the msg_ids passed. The last argument
 * must always be 0
 *
 * returns 0 on success, -1 if it doesn't match or -2 if there is no
 * pending response
 *
 * Example:
 * qrild_qmi_get_msg_if_match(state, msg, QMI_DMS_GET_OPERATING_MODE, QMI_DMS_SET_OPERATING_MODE, 0);
 */
int qrild_qmi_get_msg_if_match(struct rild_state *state, struct qrild_msg *msg,
			       ...)
{
	va_list ap;
	uint32_t msg_id;

	if (!state->resp_pending)
		return -2;

	va_start(ap, msg);
	msg_id = va_arg(ap, int);
	while (msg_id) {
		if (msg_id == state->resp_pending->msg_id) {
			msg = state->resp_pending;
			state->resp_pending = NULL;
			va_end(ap);
			return 0;
		}
	}

	va_end(ap);
	return -1;
}

/*
 * The power up sequence is as follows:
 * 1. sent DMS get operating mode request
 * 2. parse response
 * 3. if modem is not offline, send a DMS
 *    SET operating mode request to turn it on
 * 4. parse response
 */
int qrild_qmi_powerup(struct rild_state *state)
{
	struct dms_set_operating_mode_req *req;
	struct dms_get_operating_mode_resp *resp;
	struct qrild_msg *msg = NULL;
	void *buf;
	size_t len;
	uint8_t mode = 0, hw_restricted = 0;
	uint32_t txn;
	int rc;

	if (!qmi_service_get(&state->services, QMI_SERVICE_DMS))
		return QRILD_STATE_PENDING;

	printf("before get_msg_if_match\n");
	rc = qrild_qmi_get_msg_if_match(state, msg, QMI_DMS_GET_OPERATING_MODE,
					QMI_DMS_SET_OPERATING_MODE, 0);
	printf("Got rc=%d\n", rc);
	switch (rc) {
	case -1: // some other request is pending, some other handler should deal with it
	case -2: // no pending response, so we should be sending a request
		if (!qrild_msg_is_pending(&state->resp_queue,
					  QMI_DMS_GET_OPERATING_MODE)) {
			dms_get_operating_mode_request(state);
		}
		return QRILD_STATE_PENDING;
	case 0:
	default:
		break;
	}

	if (!msg->buf) {
		fprintf(stderr, "msg pending but no buf!!!\n");
		return QRILD_STATE_ERROR;
	}
	// This could be parsing the respone for a SET or GET, it doesn't matter
	// as if it's a SET we're only going to read the result which is
	// common to both
	resp = dms_get_operating_mode_resp_parse(msg->buf, msg->buf_len, &txn);
	printf("Got response txn %u\n", txn);

	if (txn != msg->txn) {
		fprintf(stderr,
			"[QMI] %s: mismatched txn, should NOT happen!\n",
			__func__);
		return QRILD_STATE_ERROR;
	}

	qmi_get_result((void *)resp, "DMS Operating Mode");

	if (msg->msg_id == QMI_DMS_SET_OPERATING_MODE) {
		printf("Modem powerup success!");
		list_remove(&msg->li);
		free(msg->buf);
		free(msg);
		return QRILD_STATE_DONE;
	}

	dms_get_operating_mode_resp_get_mode(resp, &mode);
	dms_get_operating_mode_resp_get_hardware_restricted(resp, &mode);
	printf("Operating mode:\n"
	       "\tmode: %u\n"
	       "\thw_restriced: %s\n",
	       mode, hw_restricted ? "Yes" : "No");

	dms_get_operating_mode_resp_free(resp);

	switch (mode) {
	case QMI_DMS_OPERATING_MODE_ONLINE:
		printf("Modem online!\n");
		return QRILD_STATE_DONE;
	case QMI_DMS_OPERATING_MODE_OFFLINE:
	case QMI_DMS_OPERATING_MODE_SHUTTING_DOWN:
		printf("Turning on modem\n");
		break;
	default:
		LOGE("Unknown modem state!\n");
		return QRILD_STATE_ERROR;
	}

	req = dms_set_operating_mode_req_alloc(state->txn);
	dms_set_operating_mode_req_set_mode(req, QMI_DMS_OPERATING_MODE_ONLINE);

	buf = dms_set_operating_mode_req_encode(req, &len);

	qrild_qrtr_send_to_service(state, QMI_SERVICE_DMS, buf, len);

	return QRILD_STATE_DONE;
}

static void dump_card_status(struct uim_card_status *cs)
{
	int i, ii, iii;
	printf("index_gw_primary: %u, ", cs->index_gw_primary);
	printf("index_1x_primary: %u, ", cs->index_1x_primary);
	printf("index_gw_secondary: %u, ", cs->index_gw_secondary);
	printf("index_1x_secondary: %u, ", cs->index_1x_secondary);
	printf("cards_n: %u", cs->cards_n);

	for (i = 0; i < cs->cards_n; i++) {
		printf("\ncard %d:\n\t", i);
		printf("card_state: %u, ", cs->cards[i].card_state);
		printf("upin_state: %u, ", cs->cards[i].upin_state);
		printf("upin_retries: %u, ", cs->cards[i].upin_retries);
		printf("upuk_retries: %u, ", cs->cards[i].upuk_retries);
		printf("error_code: %u, ", cs->cards[i].error_code);
		printf("applications_n: %u, ", cs->cards[i].applications_n);
		for (ii = 0; ii < cs->cards[i].applications_n; ii++) {
			printf("\n\tapplication %d:\n\t\t", ii);
			printf("type: %u, ",
			       cs->cards[i].applications[ii].type);
			printf("state: %u, ",
			       cs->cards[i].applications[ii].state);
			printf("personalization_state: %u, ",
			       cs->cards[i]
				       .applications[ii]
				       .personalization_state);
			printf("personalization_feature: %u, ",
			       cs->cards[i]
				       .applications[ii]
				       .personalization_feature);
			printf("personalization_retries: %u, ",
			       cs->cards[i]
				       .applications[ii]
				       .personalization_retries);
			printf("application_identifier_value_n: %u, ",
			       cs->cards[i]
				       .applications[ii]
				       .application_identifier_value_n);
			printf("\n\t\tapplication identifier\n\t\t\t");
			for (iii = 0;
			     iii < cs->cards[i]
					   .applications[ii]
					   .application_identifier_value_n;
			     iii++) {
				printf("[%u], ",
				       cs->cards[i]
					       .applications[ii]
					       .application_identifier_value
						       [iii]);
			}
			printf("\n\t\t");
			printf("pin2_state: %u, ",
			       cs->cards[i].applications[ii].pin2_state);
			printf("pin2_retries: %u, ",
			       cs->cards[i].applications[ii].pin2_retries);
			printf("puk2_retries: %u, ",
			       cs->cards[i].applications[ii].puk2_retries);
		}
	}
	printf("\n");
}

static int uim_get_card_status_request(struct rild_state *state)
{
	size_t len;
	int rc;
	struct uim_get_card_status_req *req;

	if (!qmi_service_get(&state->services, QMI_SERVICE_UIM))
		return -1;

	req = uim_get_card_status_req_alloc(state->txn);

	void *buf = uim_get_card_status_req_encode(req, &len);

	print_hex_dump("Get card status", (uint8_t *)buf, len);

	rc = qrild_qrtr_send_to_service(state, QMI_SERVICE_UIM, buf, len);

	uim_get_card_status_req_free(req);

	return 0;
}

int qrild_qmi_uim_get_card_status(struct rild_state *state)
{
	size_t buf_sz;
	struct qrild_msg *msg = NULL;
	uint32_t txn;
	struct uim_get_card_status_resp *resp;

	switch (qrild_qmi_get_msg_if_match(state, msg, QMI_UIM_GET_CARD_STATUS,
					   0)) {
	case -1: // some other request is pending, some other handler should deal with it
	case -2: // no pending response, so we should be sending a request
		// but only if we haven't already
		if (!qrild_msg_is_pending(&state->resp_queue,
					  QMI_UIM_GET_CARD_STATUS))
			uim_get_card_status_request(state);
		return QRILD_STATE_PENDING;
	case 0:
	default:
		break;
	}

	resp = uim_get_card_status_resp_parse(msg->buf, msg->buf_len, &txn);

	qmi_get_result((void *)resp, "UIM get card status");

	uint8_t *ptr = qmi_tlv_get((struct qmi_tlv *)resp, 16, &buf_sz);
	print_hex_dump("UIM card status resp", ptr, buf_sz);

	state->card_status = uim_get_card_status_resp_get_status(resp);

	dump_card_status(state->card_status);

	return QRILD_STATE_DONE;
}

const char *qmi_service_to_string(enum qmi_service service, bool short_name)
{
	const struct enum_value *v = &qmi_service_values[0];
	while (v->value_str) {
		if (v->value == service)
			return short_name ? v->name : v->value_str;
		v++;
	}

	return NULL;
}

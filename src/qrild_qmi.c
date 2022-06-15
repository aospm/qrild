
#include <errno.h>
#include <linux/qrtr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <arpa/inet.h>

#include "libqrtr.h"
#include "logging.h"

#include "list.h"
#include "util.h"
#include "qrild.h"
#include "qrild_link.h"
#include "qrild_qmi.h"
#include "qrild_qrtr.h"

#include "qmi_uim.h"
#include "qmi_dpm.h"
#include "qmi_dms.h"
#include "qmi_wda.h"
#include "qmi_wds.h"

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
	if (!list->head)
		return false;
	list_for_each_entry(msg, (list), li)
	{
		if (!msg)
			continue;
		if (msg->msg_id == msg_id) {
			printf("found pending msg msg_id: %u\n", msg_id);
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
int qrild_qmi_get_msg_if_match(struct rild_state *state, struct qrild_msg **msg,
			       ...)
{
	va_list ap;
	uint32_t msg_id;

	if (!state->resp_pending)
		return -2;

	va_start(ap, msg);
	msg_id = va_arg(ap, int);
	while (msg_id) {
		printf("Checking for id %u\n", msg_id);
		if (msg_id == state->resp_pending->msg_id) {
			*msg = state->resp_pending;
			state->resp_pending = NULL;
			list_remove(&(*msg)->li);
			va_end(ap);
			printf("Got response for {msg_id: %u, txn: %u}\n", msg_id, (*msg)->txn);
			return 0;
		}
		msg_id = va_arg(ap, int);
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
	struct qmi_result *res;
	void *buf;
	size_t len;
	uint8_t mode = 0, hw_restricted = 0;
	uint32_t txn;
	int rc;

	if (!qmi_service_get(&state->services, QMI_SERVICE_DMS))
		return QRILD_STATE_PENDING;

	printf("before get_msg_if_match\n");
	rc = qrild_qmi_get_msg_if_match(state, &msg, QMI_DMS_GET_OPERATING_MODE,
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

	printf("Handling pending msg {id: %u, txn: %u}\n", msg->msg_id, msg->txn);

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

	res = qmi_get_result((void *)resp, "DMS Operating Mode");

	if (msg->msg_id == QMI_DMS_SET_OPERATING_MODE && res->result == 0) {
		printf("Modem powerup success!");
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

	return QRILD_STATE_PENDING;
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

	return rc;
}

int qrild_qmi_uim_get_card_status(struct rild_state *state)
{
	size_t buf_sz;
	struct qrild_msg *msg = NULL;
	uint32_t txn;
	struct uim_get_card_status_resp *resp;

	switch (qrild_qmi_get_msg_if_match(state, &msg, QMI_UIM_GET_CARD_STATUS,
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

	free(msg->buf);
	free(msg);

	return QRILD_STATE_DONE;
}

static int qrild_uim_change_provisioning_send_req(struct rild_state *state) {
	struct uim_provisioning_session_change change;
	struct uim_provisioning_session_application application;
	struct card_status_cards_applications *appn = NULL;
	struct uim_change_provisioning_session_req *req;
	int rc, i = 0;
	void *buf;
	size_t buf_sz;

	while (!appn && i < state->card_status->cards_n) {
		if (state->card_status->cards[i].applications)
			appn = state->card_status->cards[i].applications;
	}

	if (!appn) {
		fprintf(stderr, "No valid application found!\n");
		return QRILD_STATE_ERROR;
	}

	printf("Provisioning slot %d!\n", i);

	change.session_type = QMI_UIM_SESSION_TYPE_PRIMARY_GW_PROVISIONING;
	change.activate = true;

	application.slot = i + 1;
	application.application_identifier_value_n = appn->application_identifier_value_n;
	application.application_identifier_value = appn->application_identifier_value;

	req = uim_change_provisioning_session_req_alloc(state->txn);
	uim_change_provisioning_session_req_set_session_change(req, &change);
	uim_change_provisioning_session_req_set_application_information(req, &application);

	buf = uim_change_provisioning_session_req_encode(req, &buf_sz);

	rc = qrild_qrtr_send_to_service(state, QMI_SERVICE_UIM, buf, buf_sz);

	uim_change_provisioning_session_req_free(req);

	return rc;
}

int qrild_qmi_uim_set_provisioning(struct rild_state *state)
{
	struct uim_change_provisioning_session_resp *resp;
	struct qmi_result *res;
	uint32_t txn;
	struct qrild_msg *msg;
	int rc;

	if (!state->card_status) {
		fprintf(stderr, "Card status not set!\n");
		return QRILD_STATE_ERROR;
	}

	rc = qrild_qmi_get_msg_if_match(state, &msg, QMI_UIM_CHANGE_PROVISIONING_SESSION,
					   0);
	printf("got RC=%d\n", rc);

	switch (rc) {
	case -1: // some other request is pending, some other handler should deal with it
	case -2: // no pending response, so we should be sending a request
		// but only if we haven't already
		if (!qrild_msg_is_pending(&state->resp_queue,
					  QMI_UIM_CHANGE_PROVISIONING_SESSION))
			qrild_uim_change_provisioning_send_req(state);
		return QRILD_STATE_PENDING;
	case 0:
	default:
		break;
	}

	resp = uim_change_provisioning_session_resp_parse(msg->buf, msg->buf_len, &txn);

	res = qmi_get_result((void *)resp, "UIM set provisioning");

	free(msg->buf);
	free(msg);

	return res->result == 0 ? QRILD_STATE_DONE : QRILD_STATE_ERROR;
}

static int qrild_qmi_dpm_open_port_send_req(struct rild_state *state) {
	struct dpm_open_port_req *req;
	struct dpm_control_port port;
	int rc;
	void *buf;
	size_t buf_sz;

	port.ep_type = 4;
	port.iface_id = 1;
	port.consumer_pipe_num = 2;
	port.producer_pipe_num = 10;

	printf("Opening port!\n");

	req = dpm_open_port_req_alloc(state->txn);
	dpm_open_port_req_set_port_list(req, &port, 1);

	buf = dpm_open_port_req_encode(req, &buf_sz);

	rc = qrild_qrtr_send_to_service(state, QMI_SERVICE_DPM, buf, buf_sz);

	dpm_open_port_req_free(req);

	return rc;
}

int qrild_qmi_dpm_open_port(struct rild_state *state) {
	struct dpm_open_port_resp *resp;
	struct qmi_result *res;
	uint32_t txn;
	struct qrild_msg *msg;
	int rc;

	if (!state->card_status) {
		fprintf(stderr, "Card status not set!\n");
		return QRILD_STATE_ERROR;
	}

	rc = qrild_qmi_get_msg_if_match(state, &msg, QMI_DPM_OPEN_PORT,
					   0);
	printf("got RC=%d\n", rc);

	switch (rc) {
	case -1: // some other request is pending, some other handler should deal with it
	case -2: // no pending response, so we should be sending a request
		// but only if we haven't already
		if (!qrild_msg_is_pending(&state->resp_queue,
					  QMI_DPM_OPEN_PORT))
			qrild_qmi_dpm_open_port_send_req(state);
		return QRILD_STATE_PENDING;
	case 0:
	default:
		break;
	}

	resp = dpm_open_port_resp_parse(msg->buf, msg->buf_len, &txn);

	res = qmi_get_result((void *)resp, "DPM open port");

	free(msg->buf);
	free(msg);

	return res->result == 0 ? QRILD_STATE_DONE : QRILD_STATE_ERROR;
}

static int qrild_qmi_wda_set_data_format_send_req(struct rild_state *state) {
	struct wda_set_data_format_req *req;
	struct wda_ep_type_iface_id ep_type;
	int rc;
	void *buf;
	size_t buf_sz;

	printf("Setting data format!\n");

	req = wda_set_data_format_req_alloc(state->txn);
	wda_set_data_format_req_set_link_prot(req, 2);
	wda_set_data_format_req_set_ul_data_aggregation_protocol(req, 8);
	wda_set_data_format_req_set_dl_data_aggregation_protocol(req, 8);
	wda_set_data_format_req_set_dl_data_aggretation_max_datagrams(req, 1);
	wda_set_data_format_req_set_dl_data_aggregation_max_size(req, 1504);

	ep_type.ep_type = 4;
	ep_type.iface_id = 1;

	wda_set_data_format_req_set_ep_type(req, &ep_type);

	buf = wda_set_data_format_req_encode(req, &buf_sz);

	rc = qrild_qrtr_send_to_service(state, QMI_SERVICE_WDA, buf, buf_sz);

	wda_set_data_format_req_free(req);

	return rc;
}

int qrild_qmi_wda_set_data_format(struct rild_state *state) {
	struct wda_set_data_format_resp *resp;
	struct qmi_result *res;
	uint32_t txn;
	struct qrild_msg *msg;
	int rc;

	if (!state->card_status) {
		fprintf(stderr, "Card status not set!\n");
		return QRILD_STATE_ERROR;
	}

	rc = qrild_qmi_get_msg_if_match(state, &msg, QMI_WDA_SET_DATA_FORMAT,
					   0);
	printf("got RC=%d\n", rc);

	switch (rc) {
	case -1: // some other request is pending, some other handler should deal with it
	case -2: // no pending response, so we should be sending a request
		// but only if we haven't already
		if (!qrild_msg_is_pending(&state->resp_queue,
					  QMI_WDA_SET_DATA_FORMAT))
			qrild_qmi_wda_set_data_format_send_req(state);
		return QRILD_STATE_PENDING;
	case 0:
	default:
		break;
	}

	resp = wda_set_data_format_resp_parse(msg->buf, msg->buf_len, &txn);

	res = qmi_get_result((void *)resp, "WDA Set data format");

	free(msg->buf);
	free(msg);

	return res->result == 0 ? QRILD_STATE_DONE : QRILD_STATE_ERROR;
}

static int qrild_qmi_wds_bind_subscription_send_req(struct rild_state *state) {
	struct wds_bind_subscription_req *req;
	int rc;
	void *buf;
	size_t buf_sz;

	printf("Binding subscription!\n");

	req = wds_bind_subscription_req_alloc(state->txn);
	
	wds_bind_subscription_req_set_subscription(req, 0);

	buf = wds_bind_subscription_req_encode(req, &buf_sz);

	rc = qrild_qrtr_send_to_service(state, QMI_SERVICE_WDS, buf, buf_sz);

	wds_bind_subscription_req_free(req);

	return rc;
}

int qrild_qmi_wds_bind_subscription(struct rild_state *state) {
	struct wds_bind_subscription_resp *resp;
	struct qmi_result *res;
	uint32_t txn;
	struct qrild_msg *msg;
	int rc;

	if (!state->card_status) {
		fprintf(stderr, "Card status not set!\n");
		return QRILD_STATE_ERROR;
	}

	rc = qrild_qmi_get_msg_if_match(state, &msg, QMI_WDS_BIND_SUBSCRIPTION,
					   0);
	printf("got RC=%d\n", rc);

	switch (rc) {
	case -1: // some other request is pending, some other handler should deal with it
	case -2: // no pending response, so we should be sending a request
		// but only if we haven't already
		if (!qrild_msg_is_pending(&state->resp_queue,
					  QMI_WDS_BIND_SUBSCRIPTION))
			qrild_qmi_wds_bind_subscription_send_req(state);
		return QRILD_STATE_PENDING;
	case 0:
	default:
		break;
	}

	resp = wds_bind_subscription_resp_parse(msg->buf, msg->buf_len, &txn);

	res = qmi_get_result((void *)resp, "WDS Bind subscription");

	free(msg->buf);
	free(msg);

	return res->result == 0 ? QRILD_STATE_DONE : QRILD_STATE_ERROR;
}

static int qrild_qmi_wds_bind_mux_data_port_send_req(struct rild_state *state) {
	struct wds_bind_mux_data_port_req *req;
	struct wds_ep_type_iface_id ep_type;
	int rc;
	void *buf;
	size_t buf_sz;

	printf("Muxing data port!\n");

	req = wds_bind_mux_data_port_req_alloc(state->txn);
	
	ep_type.ep_type = 4;
	ep_type.iface_id = 1;
	wds_bind_mux_data_port_req_set_ep_id(req, &ep_type);
	wds_bind_mux_data_port_req_set_mux_id(req, 1);

	buf = wds_bind_mux_data_port_req_encode(req, &buf_sz);

	rc = qrild_qrtr_send_to_service(state, QMI_SERVICE_WDS, buf, buf_sz);

	wds_bind_mux_data_port_req_free(req);

	return rc;
}

int qrild_qmi_wds_bind_mux_data_port(struct rild_state *state) {
	struct wds_bind_mux_data_port_resp *resp;
	struct qmi_result *res;
	uint32_t txn;
	struct qrild_msg *msg;
	int rc;

	if (!state->card_status) {
		fprintf(stderr, "Card status not set!\n");
		return QRILD_STATE_ERROR;
	}

	rc = qrild_qmi_get_msg_if_match(state, &msg, QMI_WDS_BIND_MUX_DATA_PORT,
					   0);
	printf("got RC=%d\n", rc);

	switch (rc) {
	case -1: // some other request is pending, some other handler should deal with it
	case -2: // no pending response, so we should be sending a request
		// but only if we haven't already
		if (!qrild_msg_is_pending(&state->resp_queue,
					  QMI_WDS_BIND_MUX_DATA_PORT))
			qrild_qmi_wds_bind_mux_data_port_send_req(state);
		return QRILD_STATE_PENDING;
	case 0:
	default:
		break;
	}

	resp = wds_bind_mux_data_port_resp_parse(msg->buf, msg->buf_len, &txn);

	res = qmi_get_result((void *)resp, "WDS Bind mux data port");

	free(msg->buf);
	free(msg);

	return res->result == 0 ? QRILD_STATE_DONE : QRILD_STATE_ERROR;
}

static int qrild_qmi_wds_start_network_interface_send_req(struct rild_state *state) {
	struct wds_start_network_interface_req *req;
	int rc;
	void *buf;
	size_t buf_sz;
	char *apn_name = "three.co.uk";

	printf("Starting net ifaces!\n");

	req = wds_start_network_interface_req_alloc(state->txn);
	
	wds_start_network_interface_req_set_apn_name(req, apn_name, strlen(apn_name));
	wds_start_network_interface_req_set_ip_family_preference(req, 4);

	buf = wds_start_network_interface_req_encode(req, &buf_sz);

	rc = qrild_qrtr_send_to_service(state, QMI_SERVICE_WDS, buf, buf_sz);

	wds_start_network_interface_req_free(req);

	return rc;
}

static int qrild_qmi_handle_wds_pkt_srvc(struct qrild_msg *msg) {
	uint32_t txn;
	struct wds_get_pkt_srvc_status_ind *ind = wds_get_pkt_srvc_status_ind_parse(msg->buf, msg->buf_len, &txn);
	struct wds_pkt_srvc_status *status = wds_get_pkt_srvc_status_ind_get_status(ind);

	printf("Connection status: %u\n", status->connection_status);
	return 0;
}

int qrild_qmi_wds_start_network_interface(struct rild_state *state) {
	struct wds_start_network_interface_resp *resp;
	struct qmi_result *res;
	uint32_t txn;
	struct qrild_msg *msg;
	int rc;

	if (!state->card_status) {
		fprintf(stderr, "Card status not set!\n");
		return QRILD_STATE_ERROR;
	}

	rc = qrild_qmi_get_msg_if_match(state, &msg, QMI_WDS_START_NETWORK_INTERFACE,
					   QMI_WDS_PKT_SRVC_STATUS, 0);
	printf("got RC=%d\n", rc);

	switch (rc) {
	case -1: // some other request is pending, some other handler should deal with it
	case -2: // no pending response, so we should be sending a request
		// but only if we haven't already
		if (!qrild_msg_is_pending(&state->resp_queue,
					  QMI_WDS_START_NETWORK_INTERFACE))
			qrild_qmi_wds_start_network_interface_send_req(state);
		return QRILD_STATE_PENDING;
	case 0:
	default:
		break;
	}

	if (msg->msg_id == QMI_WDS_PKT_SRVC_STATUS) {
		qrild_qmi_handle_wds_pkt_srvc(msg);
		state->started = true;
		free(msg->buf);
		free(msg);
		return QRILD_STATE_DONE;
	}

	resp = wds_start_network_interface_resp_parse(msg->buf, msg->buf_len, &txn);

	res = qmi_get_result((void *)resp, "WDS Start net ifaces");
	printf("Started ? %d\n", state->started);

	free(msg->buf);
	free(msg);

	return res->result == 0 ? (state->started ? QRILD_STATE_DONE : QRILD_STATE_PENDING) : QRILD_STATE_ERROR;
}

static int qrild_qmi_wds_get_current_settings_send_req(struct rild_state *state) {
	struct wds_get_current_settings_req *req;
	int rc;
	void *buf;
	size_t buf_sz;

	printf("Getting runtime settings!\n");

	req = wds_get_current_settings_req_alloc(state->txn);

	wds_get_current_settings_req_set_requested_settings(req,
		1 << 8 | 1 << 9 | 1 << 13 | 1 << 15);

	buf = wds_get_current_settings_req_encode(req, &buf_sz);

	rc = qrild_qrtr_send_to_service(state, QMI_SERVICE_WDS, buf, buf_sz);

	wds_get_current_settings_req_free(req);

	return rc;
}

int qrild_qmi_wds_get_current_settings(struct rild_state *state) {
	struct wds_get_current_settings_resp *resp;
	struct qmi_result *res;
	uint32_t txn;
	struct qrild_msg *msg;
	struct in_addr ip, brd, sub;
	uint32_t val;
	uint8_t val8;
	int rc;

	if (!state->card_status) {
		fprintf(stderr, "Card status not set!\n");
		return QRILD_STATE_ERROR;
	}

	rc = qrild_qmi_get_msg_if_match(state, &msg, QMI_WDS_GET_CURRENT_SETTINGS,
					   0);
	printf("got RC=%d\n", rc);

	switch (rc) {
	case -1: // some other request is pending, some other handler should deal with it
	case -2: // no pending response, so we should be sending a request
		// but only if we haven't already
		if (!qrild_msg_is_pending(&state->resp_queue,
					  QMI_WDS_GET_CURRENT_SETTINGS))
			qrild_qmi_wds_get_current_settings_send_req(state);
		return QRILD_STATE_PENDING;
	case 0:
	default:
		break;
	}

	resp = wds_get_current_settings_resp_parse(msg->buf, msg->buf_len, &txn);

	free(msg->buf);
	free(msg);

	res = qmi_get_result((void *)resp, "Get runtime settings");
	if (res->result)
		return QRILD_STATE_ERROR;

	rc = wds_get_current_settings_resp_get_ipv4_address_preference(resp, &val);
	if (rc < 0) {
		fprintf(stderr, "Failed to get IPv4 address preference: %d\n", rc);
		return QRILD_STATE_ERROR;
	}
	ip.s_addr = htonl(val);
	printf("IPv4 Address Preference: %s\n", inet_ntoa(ip));

	rc = wds_get_current_settings_resp_get_ipv4_gateway_addr(resp, &val);
	if (rc < 0) {
		fprintf(stderr, "Failed to get IPv4 Gateway Address: %d\n", rc);
		return QRILD_STATE_ERROR;
	}
	brd.s_addr = htonl(val);
	printf("IPv4 Gateway Address: %s\n", inet_ntoa(brd));

	rc = wds_get_current_settings_resp_get_ipv4_subnet_mask(resp, &val);
	if (rc < 0) {
		fprintf(stderr, "Failed to get IPv4 Subnet Mask: %d\n", rc);
		return QRILD_STATE_ERROR;
	}
	sub.s_addr = htonl(val);
	printf("IPv4 Subnet Mask: %s (NL endienness: 0x%x, host endianness: 0x%x)\n",
		inet_ntoa(sub), sub.s_addr, val);
	
	rc = wds_get_current_settings_resp_get_mtu(resp, &val);
	if (rc < 0) {
		fprintf(stderr, "Failed to get MTU: %d\n", rc);
		return QRILD_STATE_ERROR;
	}
	printf("MTU: %d\n", val);

	rc = wds_get_current_settings_resp_get_ip_family(resp, &val8);
	if (rc < 0) {
		fprintf(stderr, "Failed to get IP Family: %d\n", rc);
		return QRILD_STATE_ERROR;
	}
	printf("IP Family: %d\n", val8);

	if (!state->no_configure_inet)
		return qrild_link_configure(&ip, &sub, &brd);
	
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

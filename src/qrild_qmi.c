
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
#include "qrild_msg.h"

#include "qmi_tlv.h"
#include "qmi_uim.h"
#include "qmi_dpm.h"
#include "qmi_dms.h"
#include "qmi_wda.h"
#include "qmi_wds.h"

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

/**
 * @brief Synchronously get the modem operating modem
 * 
 * @state: RIL state object
 * 
 * @returns DMS_OPERATING_MODE or < 0 on error
 */
static int dms_get_operating_mode(struct rild_state *state)
{
	struct dms_get_operating_mode_req *req;
	struct qrild_msg *resp_msg = NULL;
	struct dms_get_operating_mode_resp *resp;
	uint8_t mode = 0, hw_restricted = 0;
	int rc;
	void *buf;
	size_t len;

	printf("sending dms_get_operating_mode_request\n");

	req = dms_get_operating_mode_req_alloc(state->txn);
	buf = dms_get_operating_mode_req_encode(req, &len);

	rc = qrild_msg_send_sync(state, QMI_SERVICE_DMS, buf, len, TIMEOUT_DEFAULT, resp_msg);
	dms_get_operating_mode_req_free(req);
	if (rc < 0 || !resp_msg)
		return QRILD_STATE_ERROR;

	resp = dms_get_operating_mode_resp_parse(resp_msg->buf, resp_msg->buf_len, NULL);

	dms_get_operating_mode_resp_get_mode(resp, &mode);
	dms_get_operating_mode_resp_get_hardware_restricted(resp, &hw_restricted);
	LOGD("Operating mode:\n"
	       "\tmode: %u\n"
	       "\thw_restriced: %s\n",
	       mode, hw_restricted ? "Yes" : "No");

	dms_get_operating_mode_resp_free(resp);

	qrild_msg_free(state, resp_msg);

	return mode;
}

/**
 * @brief synchronously set the operating mode
 * 
 * @state: RIL state object
 * @mode: mode to set
 */
static int dms_set_operating_mode(struct rild_state *state, uint8_t mode)
{
	struct dms_set_operating_mode_req *req;
	void *buf;
	size_t len;

	req = dms_set_operating_mode_req_alloc(state->txn);
	dms_set_operating_mode_req_set_mode(req, mode);

	buf = dms_set_operating_mode_req_encode(req, &len);

	return qrild_msg_send_resp_check(state, QMI_SERVICE_DMS, buf, len, TIMEOUT_DEFAULT);
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
	struct qrild_msg *msg = NULL;
	struct qmi_result *res;
	int mode;
	void *buf;
	size_t len;
	uint32_t txn;
	int rc;

	if (!qmi_service_get(&state->services, QMI_SERVICE_DMS))
		return QRILD_STATE_PENDING;

	mode = dms_get_operating_mode(state);

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

	dms_set_operating_mode(state, QMI_DMS_OPERATING_MODE_ONLINE);

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

int qrild_qmi_uim_get_card_status(struct rild_state *state)
{
	struct qrild_msg *msg = NULL;
	uint32_t txn;
	struct uim_get_card_status_resp *resp;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_UIM, QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_UIM, QMI_UIM_GET_CARD_STATUS, msg);
	if (rc < 0 || !msg) {
		fprintf(stderr, "%s: didn't get a response or timed out!\n");
		return QRILD_STATE_ERROR;
	}

	resp = uim_get_card_status_resp_parse(msg->buf, msg->buf_len, &txn);
	if (!qrild_qmi_result_success((struct qmi_tlv *)resp)) {
		qrild_qmi_result_print((struct qmi_tlv *)resp);
		return QRILD_STATE_ERROR;
	}

	state->card_status = uim_get_card_status_resp_get_status(resp);

	dump_card_status(state->card_status);

	qrild_msg_free(msg);

	return QRILD_STATE_DONE;
}

int qrild_qmi_uim_set_provisioning(struct rild_state *state)
{
	struct uim_provisioning_session_change change;
	struct uim_provisioning_session_application application;
	struct card_status_cards_applications *appn = NULL;
	struct uim_change_provisioning_session_req *req;
	struct qmi_result res;
	int rc, i = 0;
	void *buf;
	size_t buf_sz;
	int rc;

	if (!state->card_status) {
		fprintf(stderr, "Card status not set!\n");
		return QRILD_STATE_PENDING;
	}

	while (!appn && i < state->card_status->cards_n) {
		if (state->card_status->cards[i].applications)
			appn = state->card_status->cards[i].applications;
		i++;
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

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_UIM, buf, buf_sz, TIMEOUT_DEFAULT, &res);

	uim_change_provisioning_session_req_free(req);

	if (rc < 0) {
		LOGE("Failed to set provisioning\n");
		qrild_qmi_result_print(&res);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_dpm_open_port(struct rild_state *state) {
	struct dpm_open_port_req *req;
	struct dpm_control_port port;
	struct qmi_result res;
	void *buf;
	size_t buf_sz;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_DPM, QRILD_STATE_PENDING);

	printf("Opening default port!\n");

	port.ep_type = 4;
	port.iface_id = 1;
	port.consumer_pipe_num = 2;
	port.producer_pipe_num = 10;

	req = dpm_open_port_req_alloc(state->txn);
	dpm_open_port_req_set_port_list(req, &port, 1);

	buf = dpm_open_port_req_encode(req, &buf_sz);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_DPM, buf, buf_sz, TIMEOUT_DEFAULT, &res);

	dpm_open_port_req_free(req);

	if (rc < 0) {
		LOGE("Failed to open port:\n");
		qrild_qmi_result_print(&res);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_wda_set_data_format(struct rild_state *state) {
	struct wda_set_data_format_req *req;
	struct wda_ep_type_iface_id ep_type;
	void *buf;
	size_t buf_sz;
	struct qmi_result res;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_WDA, QRILD_STATE_PENDING);

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

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_WDA, buf, buf_sz, TIMEOUT_DEFAULT, &res);

	wda_set_data_format_req_free(req);
	if (rc < 0) {
		LOGE("Failed to set data format:\n");
		qrild_qmi_result_print(&res);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_wds_bind_subscription(struct rild_state *state) {
	struct wds_bind_subscription_req *req;
	struct qmi_result res;
	void *buf;
	size_t buf_sz;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_WDS, QRILD_STATE_PENDING);

	printf("Binding subscription!\n");

	req = wds_bind_subscription_req_alloc(state->txn);
	
	wds_bind_subscription_req_set_subscription(req, 0);

	buf = wds_bind_subscription_req_encode(req, &buf_sz);

	rc = qrild_qrtr_send_to_service(state, QMI_SERVICE_WDS, buf, buf_sz);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_WDA, buf, buf_sz, TIMEOUT_DEFAULT, &res);

	wds_bind_subscription_req_free(req);
	if (rc < 0) {
		LOGE("Failed to bind subscription:\n");
		qrild_qmi_result_print(&res);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
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
		if (!qrild_msg_is_pending(&state->pending_tx,
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
		if (!qrild_msg_is_pending(&state->pending_tx,
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
		if (!qrild_msg_is_pending(&state->pending_tx,
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


#include <errno.h>
#include <linux/qrtr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include <arpa/inet.h>

#include "libqrtr.h"
#include "logging.h"

#include "list.h"
#include "util.h"
#include "qrild.h"
#include "qrild_link.h"
#include "qrild_qmi.h"
#include "qrild_msg.h"

#include "qmi_uim.h"
#include "qmi_dpm.h"
#include "qmi_dms.h"
#include "qmi_nas.h"
#include "qmi_wda.h"
#include "qmi_wds.h"

/**
 * @brief Synchronously get the modem operating modem
 * 
 * @state: RIL state object
 * 
 * @returns DMS_OPERATING_MODE or < 0 on error
 */
int qrild_qmi_dms_get_operating_mode(struct rild_state *state)
{
	struct dms_get_operating_mode_req *req;
	struct qrild_msg *resp_msg = NULL;
	struct dms_get_operating_mode_resp *resp;
	uint8_t mode = QMI_DMS_OPERATING_MODE_UNKNOWN, hw_restricted = 0;
	int rc;
	void *buf;
	size_t len;

	req = dms_get_operating_mode_req_alloc(qrild_next_transaction_id());
	buf = dms_get_operating_mode_req_encode(req, &len);

	rc = qrild_msg_send_sync(state, QMI_SERVICE_DMS, buf, len,
				 TIMEOUT_DEFAULT, &resp_msg);
	dms_get_operating_mode_req_free(req);
	if (rc < 0 || !resp_msg)
		return QRILD_STATE_ERROR;

	resp = dms_get_operating_mode_resp_parse(resp_msg->buf,
						 resp_msg->buf_len);

	dms_get_operating_mode_resp_get_mode(resp, &mode);
	dms_get_operating_mode_resp_get_hardware_restricted(resp,
							    &hw_restricted);
	LOGD("Operating mode:\n"
	     "\tmode: %u\n"
	     "\thw_restriced: %s\n",
	     mode, hw_restricted ? "Yes" : "No");

	dms_get_operating_mode_resp_free(resp);

	qrild_msg_free(resp_msg);

	return mode;
}

/**
 * @brief synchronously set the operating mode
 * 
 * @state: RIL state object
 * @mode: mode to set
 */
struct qmi_response_type_v01 qrild_qmi_dms_set_operating_mode(
	struct rild_state *state, uint8_t mode)
{
	struct dms_set_operating_mode_req *req;
	struct qmi_response_type_v01 res;
	void *buf;
	size_t len;
	int rc;

	req = dms_set_operating_mode_req_alloc(qrild_next_transaction_id());
	dms_set_operating_mode_req_set_mode(req, mode);

	buf = dms_set_operating_mode_req_encode(req, &len);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_DMS, buf, len,
				       TIMEOUT_DEFAULT, &res);
	if (rc < 0) {
		LOGE("Failed to set operating mode!");
		res.result = 1;
		// FIXME: This is jank, please do something about it future Caleb
		res.error = QMI_ERR_QRILD;
	}

	return res;
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
	int mode;
	struct qmi_response_type_v01 res;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_DMS,
			      QRILD_STATE_PENDING);
	mode = qrild_qmi_dms_get_operating_mode(state);
	if (mode < 0) {
		LOGE("Failed to get operating mode!");
		return QRILD_STATE_ERROR;
	}
	printf("Modem state: %d\n", mode);

	switch (mode) {
	case QMI_DMS_OPERATING_MODE_ONLINE:
		printf("Modem online!\n");
		return QRILD_STATE_DONE;
	case QMI_DMS_OPERATING_MODE_OFFLINE:
	case QMI_DMS_OPERATING_MODE_SHUTTING_DOWN:
	case QMI_DMS_OPERATING_MODE_RESET:
		printf("Turning on modem\n");
		break;
	default:
		LOGE("Unknown modem state!");
		return QRILD_STATE_ERROR;
	}

	res = qrild_qmi_dms_set_operating_mode(state,
					       QMI_DMS_OPERATING_MODE_ONLINE);
	if (res.result) {
		LOGE("Failed to set modem online: %u\n", res.error);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_dms_get_revision(struct rild_state *state, char **revision)
{
	struct dms_get_revision_resp *resp;
	struct qrild_msg *msg = NULL;
	int rc;
	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_DMS,
			      QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_DMS,
					       QMI_DMS_GET_REVISION, &msg);
	if (rc < 0) {
		LOGE("Couldn't get modem revision");
		return rc;
	}

	resp = dms_get_revision_resp_parse(msg->buf, msg->buf_len);

	*revision = dms_get_revision_resp_get_revision(resp);
	if (rc < 0) {
		LOGE("Couldn't read mode revision");
		return rc;
	}

	qrild_msg_free(msg);

	return QRILD_STATE_DONE;
}

int qrild_qmi_dms_get_ids(struct rild_state *state, struct dms_get_ids_resp_data *ids)
{
	struct qrild_msg *msg = NULL;
	struct dms_get_ids_resp *resp;
	struct qmi_response_type_v01 *res;
	int rc;
	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_DMS,
			      QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_DMS,
					       QMI_DMS_GET_IDS, &msg);
	if (rc < 0) {
		LOGE("Couldn't get modem IDs");
		return rc;
	}

	resp = dms_get_ids_resp_parse(msg->buf, msg->buf_len);

	res = qmi_tlv_get_result((struct qmi_tlv *)resp);
	if (res->result) {
		LOGE("Couldn't get IDs, modem returned error:");
		qrild_qmi_result_print(res);
		qrild_msg_free(msg);
		return QRILD_STATE_ERROR;
	}

	dms_get_ids_resp_getall(resp, ids);

	qrild_msg_free(msg);

	return QRILD_STATE_DONE;
}

int qrild_qmi_nas_register_indications(struct rild_state *state)
{
	struct nas_register_indications_req *req;
	struct nas_network_reject_info reject_info;
	struct qmi_response_type_v01 res;
	int rc;
	void *buf;
	size_t buf_len;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_NAS,
			      QRILD_STATE_PENDING);

	req = nas_register_indications_req_alloc(qrild_next_transaction_id());

	nas_register_indications_req_set_system_selection_preference(req,
								     false);
	nas_register_indications_req_set_ddtm_events(req, false);
	nas_register_indications_req_set_serving_system_events(req, true);
	nas_register_indications_req_set_dual_standby_preference(req, false);
	nas_register_indications_req_set_subscription_info(req, true);
	nas_register_indications_req_set_network_time(req, true);
	nas_register_indications_req_set_system_info(req, false);
	nas_register_indications_req_set_signal_info(req, true);
	nas_register_indications_req_set_error_rate(req, true);
	nas_register_indications_req_set_hdr_new_uati_assigned(req, false);
	nas_register_indications_req_set_hdr_session_closed(req, false);
	nas_register_indications_req_set_managed_roaming(req, true);
	nas_register_indications_req_set_current_plmn_name(req, true);
	nas_register_indications_req_set_embms_status(req, false);
	// FIXME: the QMI message this sends isn't documented
	nas_register_indications_req_set_rf_band_information(req, false);
	reject_info.enable_network_reject_indications = true;
	reject_info.suppress_system_info_indications = true;
	nas_register_indications_req_set_network_reject_information(
		req, &reject_info);

	buf = nas_register_indications_req_encode(req, &buf_len);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_NAS, buf, buf_len,
				       TIMEOUT_DEFAULT, &res);
	nas_register_indications_req_free(req);
	if (rc < 0) {
		LOGE("Failed to register network indications");
		qrild_qmi_result_print(&res);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

/**
 * @brief: parses a NAS_SERVING_SYSTEM_REPORT message and populates @status
 * with the data.
 * NOTE: freeing the qrild_msg will free the data in @status!
 * FIXME: This whole function should be autogenerated for every QMI message!!!!
 * 
 * @state: ril state
 * @msg: The msg for the system report message
 * @status: struct to populate
 */
int qrild_qmi_nas_parse_serving_system_ind(
	struct rild_state *state, struct qrild_msg *msg,
	struct nas_serving_system_ind_msg *status)
{
	struct nas_serving_system_ind *ind;

	if (!msg)
		return -1;
	if (msg->msg_id != QMI_NAS_SERVING_SYSTEM_REPORT) {
		fprintf(stderr, "%s: invalid msg id: 0x%20x", __func__, msg->msg_id);
		return -1;
	}

	ind = nas_serving_system_ind_parse(msg->buf, msg->buf_len);
	if (!ind) {
		fprintf(stderr, "Couldn't parse indication!\n");
		return -1;
	}

	status->system = nas_serving_system_ind_get_system(ind);
	nas_serving_system_ind_get_data_service_cap(ind,
						    &status->data_service_cap);
	status->plmn = nas_serving_system_ind_get_plmn(ind);
	status->status = nas_serving_system_ind_get_status(ind);

	return 0;
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
	struct uim_get_card_status_resp *resp;
	struct qmi_response_type_v01 *res;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_UIM,
			      QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_UIM,
					       QMI_UIM_GET_CARD_STATUS, &msg);
	if (rc < 0 || !msg) {
		fprintf(stderr, "%s: didn't get a response or timed out!\n",
			__func__);
		return QRILD_STATE_ERROR;
	}

	resp = uim_get_card_status_resp_parse(msg->buf, msg->buf_len);
	res = qmi_tlv_get_result((void *)resp);
	if (res->result) {
		LOGE("Failed to get card status:");
		qrild_qmi_result_print(res);
		return QRILD_STATE_ERROR;
	}

	state->card_status = uim_get_card_status_resp_get_status(resp);

	dump_card_status(state->card_status);

	qrild_msg_free(msg);

	return QRILD_STATE_DONE;
}

int qrild_qmi_uim_get_slot_status(struct rild_state *state,
				  struct uim_get_slot_status_resp_data *slot_status)
{
	struct qrild_msg *msg = NULL;
	struct uim_get_slot_status_resp *resp;
	struct qmi_response_type_v01 *res;
	size_t eid_count;
	int rc, ret = QRILD_STATE_DONE;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_UIM,
			      QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_UIM,
					       QMI_UIM_GET_SLOT_STATUS, &msg);
	if (rc < 0 || !msg) {
		fprintf(stderr, "%s: didn't get a response or timed out!\n",
			__func__);
		return QRILD_STATE_ERROR;
	}

	resp = uim_get_slot_status_resp_parse(msg->buf, msg->buf_len);
	res = qmi_tlv_get_result((void *)resp);
	if (res->result) {
		LOGE("Failed to get card status:");
		qrild_qmi_result_print(res);
		ret = QRILD_STATE_ERROR;
		goto out_free;
	}

	uim_get_slot_status_resp_getall(resp, slot_status);

out_free:
	qrild_msg_free(msg);
	return ret;
}

int qrild_qmi_uim_set_provisioning(struct rild_state *state)
{
	struct uim_provisioning_session_change change;
	struct uim_provisioning_session_application application;
	struct card_status_cards_applications *appn = NULL;
	struct uim_change_provisioning_session_req *req;
	struct qmi_response_type_v01 res;
	int rc, i = 0;
	void *buf;
	size_t buf_sz;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_UIM,
			      QRILD_STATE_PENDING);

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

	application.slot = i;
	application.application_identifier_value_n =
		appn->application_identifier_value_n;
	application.application_identifier_value =
		appn->application_identifier_value;

	req = uim_change_provisioning_session_req_alloc(
		qrild_next_transaction_id());
	uim_change_provisioning_session_req_set_session_change(req, &change);
	uim_change_provisioning_session_req_set_application_information(
		req, &application);

	buf = uim_change_provisioning_session_req_encode(req, &buf_sz);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_UIM, buf, buf_sz,
				       TIMEOUT_DEFAULT, &res);

	uim_change_provisioning_session_req_free(req);

	if (rc < 0) {
		LOGE("Failed to set provisioning, is your SIM inserted?");
		qrild_qmi_result_print(&res);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_dpm_open_port(struct rild_state *state)
{
	struct dpm_open_port_req *req;
	struct dpm_control_port port;
	struct qmi_response_type_v01 res;
	void *buf;
	size_t buf_sz;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_DPM,
			      QRILD_STATE_PENDING);

	printf("Opening default port!\n");

	port.ep_type = 4;
	port.iface_id = 1;
	port.consumer_pipe_num = 2;
	port.producer_pipe_num = 10;

	req = dpm_open_port_req_alloc(qrild_next_transaction_id());
	dpm_open_port_req_set_port_list(req, &port, 1);

	buf = dpm_open_port_req_encode(req, &buf_sz);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_DPM, buf, buf_sz,
				       TIMEOUT_DEFAULT, &res);

	dpm_open_port_req_free(req);

	if (rc < 0) {
		LOGE("Failed to open port:");
		qrild_qmi_result_print(&res);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_wda_set_data_format(struct rild_state *state)
{
	struct wda_set_data_format_req *req;
	struct wda_ep_type_iface_id ep_type;
	void *buf;
	size_t buf_sz;
	struct qmi_response_type_v01 res;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_WDA,
			      QRILD_STATE_PENDING);

	printf("Setting data format!\n");

	req = wda_set_data_format_req_alloc(qrild_next_transaction_id());
	wda_set_data_format_req_set_link_prot(req, 2);
	wda_set_data_format_req_set_ul_data_aggregation_protocol(req, 8);
	wda_set_data_format_req_set_dl_data_aggregation_protocol(req, 8);
	wda_set_data_format_req_set_dl_data_aggretation_max_datagrams(req, 1);
	wda_set_data_format_req_set_dl_data_aggregation_max_size(req, 1504);

	ep_type.ep_type = 4;
	ep_type.iface_id = 1;

	wda_set_data_format_req_set_ep_type(req, &ep_type);

	buf = wda_set_data_format_req_encode(req, &buf_sz);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_WDA, buf, buf_sz,
				       TIMEOUT_DEFAULT, &res);

	wda_set_data_format_req_free(req);
	if (rc < 0) {
		LOGE("Failed to set data format:");
		qrild_qmi_result_print(&res);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_wds_bind_subscription(struct rild_state *state)
{
	struct wds_bind_subscription_req *req;
	struct qmi_response_type_v01 res;
	void *buf;
	size_t buf_sz;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_WDS,
			      QRILD_STATE_PENDING);

	printf("Binding subscription!\n");

	req = wds_bind_subscription_req_alloc(qrild_next_transaction_id());

	wds_bind_subscription_req_set_subscription(req, 0);

	buf = wds_bind_subscription_req_encode(req, &buf_sz);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_WDS, buf, buf_sz,
				       TIMEOUT_DEFAULT, &res);

	wds_bind_subscription_req_free(req);
	if (rc < 0) {
		LOGE("Failed to bind subscription:");
		qrild_qmi_result_print(&res);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_wds_bind_mux_data_port(struct rild_state *state)
{
	struct wds_bind_mux_data_port_req *req;
	struct wds_ep_type_iface_id ep_type;
	struct qmi_response_type_v01 res;
	void *buf;
	size_t buf_sz;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_WDS,
			      QRILD_STATE_PENDING);

	printf("Muxing data port!\n");

	req = wds_bind_mux_data_port_req_alloc(qrild_next_transaction_id());

	ep_type.ep_type = 4;
	ep_type.iface_id = 1;
	wds_bind_mux_data_port_req_set_ep_id(req, &ep_type);
	wds_bind_mux_data_port_req_set_mux_id(req, 1);

	buf = wds_bind_mux_data_port_req_encode(req, &buf_sz);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_WDS, buf, buf_sz,
				       TIMEOUT_DEFAULT, &res);

	wds_bind_mux_data_port_req_free(req);
	if (rc < 0) {
		LOGE("Failed to bind data port:");
		qrild_qmi_result_print(&res);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_nas_get_signal_strength(struct rild_state *state,
				      struct nas_get_signal_strength_resp_data *strength)
{
	struct nas_get_signal_strength_req *req;
	struct nas_get_signal_strength_resp *resp;
	struct nas_signal_strength *qmi_strength;
	struct qmi_response_type_v01 *res;
	struct qrild_msg *msg;
	int rc, i;
	void *buf;
	size_t buf_len;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_NAS,
			      QRILD_STATE_PENDING);

	req = nas_get_signal_strength_req_alloc(qrild_next_transaction_id());

	nas_get_signal_strength_req_set_mask(
		req, QMI_NAS_SIGNAL_STRENGTH_REQUEST_LTE_SNR);

	buf = nas_get_signal_strength_req_encode(req, &buf_len);

	rc = qrild_msg_send_sync(state, QMI_SERVICE_NAS, buf, buf_len,
				 TIMEOUT_DEFAULT, &msg);
	nas_get_signal_strength_req_free(req);

	resp = nas_get_signal_strength_resp_parse(msg->buf, msg->buf_len);

	nas_get_signal_strength_resp_getall(resp, strength);

	return QRILD_STATE_DONE;
}

int qrild_qmi_nas_show_signal_strength(struct rild_state *state)
{
	struct nas_get_signal_strength_req *req;
	struct nas_get_signal_strength_resp *resp;
	struct nas_signal_strength *qmi_strength;
	struct nas_signal_strength_list *strength_list;
	struct signal_strength_list_interfaces *le;
	int16_t lte_snr;
	struct qmi_response_type_v01 *res;
	struct qrild_msg *msg;
	int rc, i;
	void *buf;
	size_t buf_len;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_NAS,
			      QRILD_STATE_PENDING);

	req = nas_get_signal_strength_req_alloc(qrild_next_transaction_id());

	nas_get_signal_strength_req_set_mask(
		req, QMI_NAS_SIGNAL_STRENGTH_REQUEST_LTE_SNR);

	buf = nas_get_signal_strength_req_encode(req, &buf_len);

	rc = qrild_msg_send_sync(state, QMI_SERVICE_NAS, buf, buf_len,
				 TIMEOUT_DEFAULT, &msg);
	nas_get_signal_strength_req_free(req);

	resp = nas_get_signal_strength_resp_parse(msg->buf, msg->buf_len);

	res = qmi_tlv_get_result((struct qmi_tlv*)resp);
	if (res->result > 0) {
		LOGE("Failed to get signal strength");
		qrild_qmi_result_print(res);
		return QRILD_STATE_ERROR;
	}

	qmi_strength = nas_get_signal_strength_resp_get_strength(resp);
	if (qmi_strength)
		printf("Signal strength:\n"
		       "  interface: %d, strength: %d\n",
		       qmi_strength->interface, qmi_strength->strength);

	rc = nas_get_signal_strength_resp_get_lte_snr(resp, &lte_snr);
	if (rc == 0)
		printf("LTE SNR: %d\n", lte_snr);

	strength_list = nas_get_signal_strength_resp_get_strength_list(resp);
	if (strength_list) {
		printf("Strength_list: \n");
		for (i = 0; i < strength_list->interfaces_n; i++) {
			le = &strength_list->interfaces[i];
			printf("  interface: %d, strength: %d\n", le->interface,
			       le->strength);
		}
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_nas_get_lte_cphy_ca_info(struct rild_state *state,
				       struct nas_get_lte_cphy_ca_info_resp_data *data)
{
	struct nas_get_lte_cphy_ca_info_resp *resp;
	struct nas_lte_cphy_agg_scell *scell_info;
	uint32_t dl_bandwidth;
	struct qmi_response_type_v01 *res;
	struct qrild_msg *msg;
	int rc, i;
	void *buf;
	size_t buf_len;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_NAS,
			      QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(
		state, QMI_SERVICE_NAS, QMI_NAS_GET_LTE_CPY_CA_INFO, &msg);
	if (rc < 0)
		return QRILD_STATE_ERROR;

	resp = nas_get_lte_cphy_ca_info_resp_parse(msg->buf, msg->buf_len);

	nas_get_lte_cphy_ca_info_resp_getall(resp, data);

	return QRILD_STATE_DONE;
}

int qrild_qmi_wds_start_network_interface_resp(struct rild_state *state,
					       struct qrild_msg *msg)
{
	struct wds_start_network_interface_resp *resp;
	struct qmi_response_type_v01 *res;

	resp = wds_start_network_interface_resp_parse(msg->buf, msg->buf_len);

	res = (struct qmi_response_type_v01 *)qmi_tlv_get_result(resp);
	if (res->result) {
		LOGE("Failed to start network interface! QMI err: %u",
		     res->error);
		state->exit = true;
	}

	wds_start_network_interface_resp_get_pkt_data_handle(
		resp, &state->wds_pkt_data_handle);
	LOGD("Got WDS packet data handle: %u", state->wds_pkt_data_handle);

	return 0;
}

/*
 * This can fail if data signal is weak, should be retried.
 * error 14: ERR_CALL_FAILED
 */
int qrild_qmi_wds_start_network_interface(struct rild_state *state)
{
	struct wds_start_network_interface_req *req;
	struct qmi_header *qmi;
	void *buf;
	size_t buf_sz;
	int rc, i;
	uint16_t txn = qrild_next_transaction_id();
	char *apn_name = "three.co.uk";

	if (!state->card_status) {
		fprintf(stderr, "Card status not set!\n");
		return QRILD_STATE_ERROR;
	}

	printf("Starting net ifaces!\n");

	req = wds_start_network_interface_req_alloc(txn);

	wds_start_network_interface_req_set_apn_name(req, apn_name,
						     strlen(apn_name));
	wds_start_network_interface_req_set_ip_family_preference(req, 4);

	buf = wds_start_network_interface_req_encode(req, &buf_sz);
	qmi = (struct qmi_header *)buf;

	rc = qrild_msg_send_async(state, QMI_SERVICE_WDS, buf, buf_sz);
	wds_start_network_interface_req_free(req);
	if (rc < 0) {
		LOGE("Failed to start network interface:");
		return QRILD_STATE_ERROR;
	}

	rc = THREAD_WAIT(state, connection_status);
	if (rc < 0) {
		LOGE("Didn't receive connection status indication!");
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_wds_get_current_settings(struct rild_state *state)
{
	struct wds_get_current_settings_req *req;
	struct wds_get_current_settings_resp *resp;
	struct qrild_msg *msg = NULL;
	struct qmi_response_type_v01 *res;
	struct in_addr ip, brd, sub;
	uint32_t val;
	uint8_t val8;
	void *buf;
	size_t buf_sz;
	int rc;

	printf("Getting runtime settings!\n");

	req = wds_get_current_settings_req_alloc(qrild_next_transaction_id());

	wds_get_current_settings_req_set_requested_settings(
		req, 1 << 8 | 1 << 9 | 1 << 13 | 1 << 15);

	buf = wds_get_current_settings_req_encode(req, &buf_sz);

	rc = qrild_msg_send_sync(state, QMI_SERVICE_WDS, buf, buf_sz,
				 TIMEOUT_DEFAULT, &msg);
	wds_get_current_settings_req_free(req);
	if (rc < 0 || !msg) {
		LOGE("Failed to send wds_get_current_settings request!");
		list_for_each_entry(msg, &state->pending_rx, li)
		{
			printf("msg {id: %x, txn: %d, type: %u}\n", msg->msg_id,
			       msg->txn, msg->type);
		}
		return QRILD_STATE_ERROR;
	}

	resp = wds_get_current_settings_resp_parse(msg->buf, msg->buf_len);

	free(msg->buf);
	free(msg);

	res = qmi_tlv_get_result((void *)resp);
	if (res->result)
		return QRILD_STATE_ERROR;

	rc = wds_get_current_settings_resp_get_ipv4_address_preference(resp,
								       &val);
	if (rc < 0) {
		fprintf(stderr, "Failed to get IPv4 address preference: %d\n",
			rc);
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
	printf("IP Family: %u\n", val8);

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

static int qrild_qmi_handle_wds_pkt_srvc(struct rild_state *state,
					 struct qrild_msg *msg)
{
	struct wds_get_pkt_srvc_status_ind *ind =
		wds_get_pkt_srvc_status_ind_parse(msg->buf, msg->buf_len);
	struct wds_pkt_srvc_status *status =
		wds_get_pkt_srvc_status_ind_get_status(ind);

	printf("Connection status: %u\n", status->connection_status);
	pthread_mutex_lock(&state->connection_status_mutex);
	state->connection_status = status->connection_status;
	pthread_mutex_unlock(&state->connection_status_mutex);

	pthread_cond_broadcast(&state->connection_status_change);

	return 0;
}

/**
 * @brief: Do idle actions like polling for signal strength
 *
 * @state: the RIL state object
 */
int qrild_qmi_idle(struct rild_state *state)
{
	//qrild_qmi_nas_show_signal_strength(state);

	usleep(6000 * 1000);

	return QRILD_STATE_PENDING;
}

/**
 * @brief: Process any pending indication messages from the modem.
 * 
 * @state: the RIL state object
 */
int qrild_qmi_process_indications(struct rild_state *state)
{
	struct qrild_msg *msg;
	pthread_mutex_lock(&state->msg_mutex);
	list_for_each_entry(msg, &state->pending_rx, li)
	{
		if (msg->type != 0x4)
			continue;

		pthread_mutex_unlock(&state->msg_mutex);
		// notify the indication processing thread
		// FIXME: not sure this description offers much confidence
		// in my implementation...
		pthread_cond_broadcast(&state->pending_indications);
		return 0;

		// switch (msg->msg_id) {
		// case QMI_WDS_PKT_SRVC_STATUS:
		// 	qrild_qmi_handle_wds_pkt_srvc(state, msg);
		// 	break;
		// case QMI_NAS_SUBSCRIPTION_INFO_REPORT:
		// case QMI_NAS_ERROR_RATE_REPORT:
		// case QMI_NAS_RF_BAND_INFO_REPORT:
		// 	printf("Undocumented QMI NAS indication\n");
		// default:
		// 	LOGW("Dropping unknown message {id: 0x%x, txn: %u}",
		// 	     msg->msg_id, msg->txn);
		// 	print_hex_dump("Unknown msg", msg->buf, msg->buf_len);
		// 	break;
		// }
		// qrild_msg_free_locked(msg);
	}
	pthread_mutex_unlock(&state->msg_mutex);

	return 0;
}

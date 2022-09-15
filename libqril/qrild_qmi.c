
#include <errno.h>
#include <linux/qrtr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include <arpa/inet.h>

#include "q_log.h"
#include "libqrtr.h"

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

	rc = qrild_msg_send_sync(state, QMI_SERVICE_DMS, buf, len, TIMEOUT_DEFAULT, &resp_msg);
	dms_get_operating_mode_req_free(req);
	if (rc < 0 || !resp_msg)
		return QRILD_STATE_ERROR;

	resp = dms_get_operating_mode_resp_parse(resp_msg->buf, resp_msg->buf_len);

	dms_get_operating_mode_resp_get_mode(resp, &mode);
	dms_get_operating_mode_resp_get_hardware_restricted(resp, &hw_restricted);
	log_debug("Operating mode:"
		  "\tmode: %u"
		  "\thw_restriced: %s",
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
struct qmi_response_type_v01 qrild_qmi_dms_set_operating_mode(struct rild_state *state,
							      uint8_t mode)
{
	struct dms_set_operating_mode_req *req;
	struct qmi_response_type_v01 res;
	void *buf;
	size_t len;
	int rc;

	req = dms_set_operating_mode_req_alloc(qrild_next_transaction_id());
	dms_set_operating_mode_req_set_mode(req, mode);

	buf = dms_set_operating_mode_req_encode(req, &len);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_DMS, buf, len, TIMEOUT_DEFAULT, &res);
	if (rc < 0) {
		log_error("Failed to set operating mode!");
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

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_DMS, QRILD_STATE_PENDING);
	mode = qrild_qmi_dms_get_operating_mode(state);
	if (mode < 0) {
		log_error("Failed to get operating mode!");
		return QRILD_STATE_ERROR;
	}
	log_info("Modem state: %d", mode);

	switch (mode) {
	case QMI_DMS_OPERATING_MODE_ONLINE:
		log_info("Modem online!");
		return QRILD_STATE_DONE;
	case QMI_DMS_OPERATING_MODE_OFFLINE:
	case QMI_DMS_OPERATING_MODE_SHUTTING_DOWN:
	case QMI_DMS_OPERATING_MODE_RESET:
		log_info("Turning on modem");
		break;
	default:
		log_error("Unknown modem state!");
		return QRILD_STATE_ERROR;
	}

	res = qrild_qmi_dms_set_operating_mode(state, QMI_DMS_OPERATING_MODE_ONLINE);
	if (res.result) {
		log_error("Failed to set modem online: %u", res.error);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_dms_get_revision(struct rild_state *state, char **revision)
{
	struct dms_get_revision_resp *resp;
	struct qrild_msg *msg = NULL;
	int rc;
	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_DMS, QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_DMS, QMI_DMS_GET_REVISION, &msg);
	if (rc < 0) {
		log_error("Couldn't get modem revision");
		return rc;
	}

	resp = dms_get_revision_resp_parse(msg->buf, msg->buf_len);

	*revision = dms_get_revision_resp_get_revision(resp);
	if (rc < 0) {
		log_error("Couldn't read mode revision");
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
	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_DMS, QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_DMS, QMI_DMS_GET_IDS, &msg);
	if (rc < 0) {
		log_error("Couldn't get modem IDs");
		return rc;
	}

	resp = dms_get_ids_resp_parse(msg->buf, msg->buf_len);

	res = qmi_tlv_get_result((struct qmi_tlv *)resp);
	if (res->result) {
		log_error("Couldn't get IDs, modem returned error:");
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

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_NAS, QRILD_STATE_PENDING);

	req = nas_register_indications_req_alloc(qrild_next_transaction_id());

	nas_register_indications_req_set_system_selection_preference(req, false);
	nas_register_indications_req_set_ddtm_events(req, true);
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
	reject_info.suppress_system_info_indications = false;
	nas_register_indications_req_set_network_reject_information(req, &reject_info);

	buf = nas_register_indications_req_encode(req, &buf_len);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_NAS, buf, buf_len, TIMEOUT_DEFAULT, &res);
	nas_register_indications_req_free(req);
	if (rc < 0) {
		log_error("Failed to register network indications");
		qrild_qmi_result_print(&res);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_uim_get_card_status(struct rild_state *state,
				  struct uim_get_card_status_resp_data *data)
{
	struct qrild_msg *msg = NULL;
	struct uim_get_card_status_resp *resp;
	struct qmi_response_type_v01 *res;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_UIM, QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_UIM, QMI_UIM_GET_CARD_STATUS,
					       &msg);
	if (rc < 0 || !msg) {
		log_error("%s: didn't get a response or timed out!", __func__);
		return QRILD_STATE_ERROR;
	}

	resp = uim_get_card_status_resp_parse(msg->buf, msg->buf_len);
	if (!resp) {
		log_error("Failed to get card status");
		return QRILD_STATE_ERROR;
	}

	uim_get_card_status_resp_getall(resp, data);

	uim_get_card_status_resp_free(resp);

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

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_UIM, QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_UIM, QMI_UIM_GET_SLOT_STATUS,
					       &msg);
	if (rc < 0 || !msg) {
		log_error("%s: didn't get a response or timed out!", __func__);
		return QRILD_STATE_ERROR;
	}

	resp = uim_get_slot_status_resp_parse(msg->buf, msg->buf_len);
	res = qmi_tlv_get_result((void *)resp);
	if (res->result) {
		log_error("Failed to get card status:");
		qrild_qmi_result_print(res);
		ret = QRILD_STATE_ERROR;
		goto out_free;
	}

	uim_get_slot_status_resp_getall(resp, slot_status);

out_free:
	qrild_msg_free(msg);
	return ret;
}

/**
 * Provision the SIM primary application.
 * @state: RIL state
 * @slot: Logical slot to provision - index starts at 1
 * @aid: application ID to provision
 * @aid_len: Length of AID
 */
int qrild_qmi_uim_set_provisioning(struct rild_state *state, int slot, uint8_t *aid,
				   uint8_t aid_len)
{
	struct uim_provisioning_session_change change;
	struct uim_provisioning_session_application application;
	struct uim_change_provisioning_session_req *req;
	struct qmi_response_type_v01 res;
	int rc;
	void *buf;
	size_t buf_sz;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_UIM, QRILD_STATE_PENDING);

	log_info("Provisioning slot %d!", slot);

	change.session_type = QMI_UIM_SESSION_TYPE_PRIMARY_GW_PROVISIONING;
	change.activate = true;

	application.slot = slot;
	application.application_identifier_value_n = aid_len;
	application.application_identifier_value = aid;

	req = uim_change_provisioning_session_req_alloc(qrild_next_transaction_id());
	uim_change_provisioning_session_req_set_session_change(req, &change);
	uim_change_provisioning_session_req_set_application_information(req, &application);

	buf = uim_change_provisioning_session_req_encode(req, &buf_sz);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_UIM, buf, buf_sz, TIMEOUT_DEFAULT, &res);

	uim_change_provisioning_session_req_free(req);

	if (rc < 0) {
		log_error("Failed to set provisioning, is your SIM inserted?");
		qrild_qmi_result_print(&res);
		return QRILD_STATE_ERROR;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_uim_icc_open_logical_channel(struct rild_state *state, int slot, const char *aid,
					   int fileControl,
					   struct uim_icc_open_logical_channel_resp_data *resp_data)
{
	struct uim_icc_open_logical_channel_req *req;
	struct qmi_response_type_v01 res;
	struct qrild_msg *msg;
	void *buf;
	size_t buf_sz, aid_len;
	uint8_t *b_aid;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_UIM, QRILD_STATE_PENDING);

	req = uim_icc_open_logical_channel_req_alloc(qrild_next_transaction_id());
	uim_icc_open_logical_channel_req_set_slot(req, (uint8_t)slot);

	b_aid = bytes_from_hex_str(aid, &aid_len);
	if (!b_aid) {
		log_error("Couldn't parse aid: %s", aid);
		uim_icc_open_logical_channel_req_free(req);
		return QRILD_STATE_ERROR;
	}
	uim_icc_open_logical_channel_req_set_application_id(req, b_aid, aid_len);

	// Optional
	(void)fileControl;

	buf = uim_icc_open_logical_channel_req_encode(req, &buf_sz);

	rc = qrild_msg_send_sync(state, QMI_SERVICE_UIM, buf, buf_sz, TIMEOUT_DEFAULT, &msg);

	uim_icc_open_logical_channel_req_free(req);

	if (rc < 0) {
		log_error("Failed to open logical channel: %d", rc);
		return QRILD_STATE_ERROR;
	}

	uim_icc_open_logical_channel_resp_getall(
		uim_icc_open_logical_channel_resp_parse(msg->buf, msg->buf_len), resp_data);

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

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_DPM, QRILD_STATE_PENDING);

	log_info("Opening default port!");

	port.ep_type = 4;
	port.iface_id = 1;
	port.consumer_pipe_num = 2;
	port.producer_pipe_num = 10;

	req = dpm_open_port_req_alloc(qrild_next_transaction_id());
	dpm_open_port_req_set_port_list(req, &port, 1);

	buf = dpm_open_port_req_encode(req, &buf_sz);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_DPM, buf, buf_sz, TIMEOUT_DEFAULT, &res);

	dpm_open_port_req_free(req);

	if (rc < 0) {
		log_error("Failed to open port:");
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

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_WDA, QRILD_STATE_PENDING);

	log_info("Setting data format!");

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

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_WDA, buf, buf_sz, TIMEOUT_DEFAULT, &res);

	wda_set_data_format_req_free(req);
	if (rc < 0) {
		log_error("Failed to set data format:");
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

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_WDS, QRILD_STATE_PENDING);

	log_info("Binding subscription!");

	req = wds_bind_subscription_req_alloc(qrild_next_transaction_id());

	wds_bind_subscription_req_set_subscription(req, 0);

	buf = wds_bind_subscription_req_encode(req, &buf_sz);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_WDS, buf, buf_sz, TIMEOUT_DEFAULT, &res);

	wds_bind_subscription_req_free(req);
	if (rc < 0) {
		log_error("Failed to bind subscription:");
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

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_WDS, QRILD_STATE_PENDING);

	log_info("Muxing data port!");

	req = wds_bind_mux_data_port_req_alloc(qrild_next_transaction_id());

	ep_type.ep_type = 4;
	ep_type.iface_id = 1;
	wds_bind_mux_data_port_req_set_ep_id(req, &ep_type);
	wds_bind_mux_data_port_req_set_mux_id(req, 1);

	buf = wds_bind_mux_data_port_req_encode(req, &buf_sz);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_WDS, buf, buf_sz, TIMEOUT_DEFAULT, &res);

	wds_bind_mux_data_port_req_free(req);
	if (rc < 0) {
		log_error("Failed to bind data port:");
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

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_NAS, QRILD_STATE_PENDING);

	req = nas_get_signal_strength_req_alloc(qrild_next_transaction_id());

	// FIXME: is there ever a reason not to request ALL information?
	nas_get_signal_strength_req_set_mask(
		req, QMI_NAS_SIGNAL_STRENGTH_REQUEST_RSSI | QMI_NAS_SIGNAL_STRENGTH_REQUEST_ECIO |
			     QMI_NAS_SIGNAL_STRENGTH_REQUEST_IO |
			     QMI_NAS_SIGNAL_STRENGTH_REQUEST_SINR |
			     QMI_NAS_SIGNAL_STRENGTH_REQUEST_ERROR_RATE |
			     QMI_NAS_SIGNAL_STRENGTH_REQUEST_RSRQ |
			     QMI_NAS_SIGNAL_STRENGTH_REQUEST_LTE_SNR |
			     QMI_NAS_SIGNAL_STRENGTH_REQUEST_LTE_RSRP);

	buf = nas_get_signal_strength_req_encode(req, &buf_len);

	rc = qrild_msg_send_sync(state, QMI_SERVICE_NAS, buf, buf_len, TIMEOUT_DEFAULT, &msg);
	nas_get_signal_strength_req_free(req);
	if (rc < 0) {
		log_error("%s: Failed to send request", __func__);
		return QRILD_STATE_ERROR;
	}

	resp = nas_get_signal_strength_resp_parse(msg->buf, msg->buf_len);

	nas_get_signal_strength_resp_getall(resp, strength);

	qrild_msg_free(msg);

	return QRILD_STATE_DONE;
}

#define nas_ss_print(data, name, val)                                                              \
	({                                                                                         \
		int i = 0;                                                                         \
		if (data->name##_valid) {                                                          \
			log_info("\t" #name ": ");                                                 \
			for (i = 0; i < data->name##_n; i++) {                                     \
				log_info("\t\tinterface: %d, rssi: %d", data->name[i].interface,   \
					 data->name[i].val);                                       \
			}                                                                          \
		}                                                                                  \
	})

int qrild_qmi_nas_show_signal_strength(struct nas_get_signal_strength_resp_data *data)
{
	struct nas_signal_strength *s;
	log_info("Signal strength info:");
	if (data->strength_valid)
		log_info("\tinterface: %d, strength: %d", data->strength->interface,
			 data->strength->strength);

	nas_ss_print(data, strength_list, strength);
	nas_ss_print(data, rssi_list, val);
	nas_ss_print(data, ecio_list, val);
	nas_ss_print(data, err_rate_list, val);

	if (data->lte_snr_valid)
		log_info("\tLTE SNR: %d", data->lte_snr);

	if (data->rsrq_valid)
		log_info("\tRSRQ: %d", data->rsrq);

	if (data->sinr_valid)
		log_info("\tSINR: %d", data->sinr);

	if (data->io_valid)
		log_info("\tIO: %d", data->io);

	return QRILD_STATE_DONE;
}

int qrild_qmi_nas_get_cell_loc_info(struct rild_state *state,
				    struct nas_get_cell_loc_info_data *data)
{
	struct nas_get_cell_loc_info *resp;
	struct nas_lte_cphy_agg_scell *scell_info;
	uint32_t dl_bandwidth;
	struct qmi_response_type_v01 *res;
	struct qrild_msg *msg;
	int rc, i;
	void *buf;
	size_t buf_len;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_NAS, QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_NAS,
					       QMI_NAS_GET_CELL_LOCATION_INFO, &msg);
	if (rc < 0)
		return QRILD_STATE_ERROR;

	resp = nas_get_cell_loc_info_parse(msg->buf, msg->buf_len);
	if (!resp) {
		return QRILD_STATE_ERROR;
	}

	nas_get_cell_loc_info_getall(resp, data);

	qrild_msg_free(msg);

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

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_NAS, QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_NAS, QMI_NAS_GET_LTE_CPY_CA_INFO,
					       &msg);
	if (rc < 0)
		return QRILD_STATE_ERROR;

	resp = nas_get_lte_cphy_ca_info_resp_parse(msg->buf, msg->buf_len);
	if (!resp) {
		return QRILD_STATE_ERROR;
	}

	nas_get_lte_cphy_ca_info_resp_getall(resp, data);

	qrild_msg_free(msg);

	return QRILD_STATE_DONE;
}

int qrild_qmi_nas_get_system_prefs(struct rild_state *state, struct nas_get_system_prefs_data *data)
{
	struct nas_get_system_prefs *resp;
	struct qrild_msg *msg;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_NAS, QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_NAS, QMI_NAS_GET_SYSTEM_PREFS,
					       &msg);
	if (rc < 0)
		return QRILD_STATE_ERROR;

	resp = nas_get_system_prefs_parse(msg->buf, msg->buf_len);
	if (!resp) {
		return QRILD_STATE_ERROR;
	}

	nas_get_system_prefs_getall(resp, data);

	qrild_msg_free(msg);

	return QRILD_STATE_DONE;
}

int qrild_qmi_nas_get_serving_system(struct rild_state *state,
				     struct nas_serving_system_resp_data *data)
{
	struct nas_serving_system_resp *resp;
	struct qrild_msg *msg;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_NAS, QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_NAS,
					       QMI_NAS_SERVING_SYSTEM_REPORT, &msg);
	if (rc < 0)
		return QRILD_STATE_ERROR;

	resp = nas_serving_system_resp_parse(msg->buf, msg->buf_len);
	if (!resp) {
		return QRILD_STATE_ERROR;
	}

	nas_serving_system_resp_getall(resp, data);

	qrild_msg_free(msg);

	return QRILD_STATE_DONE;
}

/**
 * @brief Register with a network
 * NOTE: Only AUTOMATIC registration support, the TLVs for manual aren't implemented
 * 
 * @state: ril state object
 * @action: 1 - automatic registration, 2 - manual registration
 * 
 * @returns 0 on success, 1 if the QMI service is unavailable, -QMI_ERR on error
 */
int qrild_qmi_nas_network_register(struct rild_state *state, uint8_t action)
{
	struct nas_initiate_network_register *req;
	struct qmi_response_type_v01 res;
	void *buf;
	size_t buf_sz;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_NAS, QRILD_STATE_PENDING);

	if (action != 1) {
		log_error("Only automatic network registration is supported!!!");
		return -QMI_ERR_QRILD;
	}

	req = nas_initiate_network_register_alloc(qrild_next_transaction_id());

	nas_initiate_network_register_set_action(req, action);

	buf = nas_initiate_network_register_encode(req, &buf_sz);

	rc = qrild_msg_send_resp_check(state, QMI_SERVICE_NAS, buf, buf_sz, TIMEOUT_DEFAULT, &res);

	nas_initiate_network_register_free(req);
	if (rc < 0) {
		log_error("Failed to initiate network register");
		return -res.error;
	}

	return QRILD_STATE_DONE;
}

int qrild_qmi_dms_uim_get_imsi(struct rild_state *state, struct dms_uim_get_imsi_data *data)
{
	struct dms_uim_get_imsi *resp;
	struct qrild_msg *msg;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_DMS, QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_DMS, QMI_DMS_UIM_GET_IMSI, &msg);
	if (rc < 0)
		return QRILD_STATE_ERROR;

	resp = dms_uim_get_imsi_parse(msg->buf, msg->buf_len);
	if (!resp) {
		return QRILD_STATE_ERROR;
	}

	dms_uim_get_imsi_getall(resp, data);
	qrild_msg_free(msg);
	return QRILD_STATE_DONE;
}

int qrild_qmi_dms_get_msisdn(struct rild_state *state, struct dms_get_msisdn_data *data)
{
	struct dms_get_msisdn *resp;
	struct qrild_msg *msg;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_DMS, QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_DMS, QMI_DMS_GET_MSISDN, &msg);
	if (rc < 0)
		return QRILD_STATE_ERROR;

	resp = dms_get_msisdn_parse(msg->buf, msg->buf_len);
	if (!resp) {
		return QRILD_STATE_ERROR;
	}

	dms_get_msisdn_getall(resp, data);
	qrild_msg_free(msg);

	return QRILD_STATE_DONE;
}

int qrild_qmi_nas_get_operator_name(struct rild_state *state,
				    struct nas_get_operator_name_resp_data *data)
{
	struct nas_get_operator_name_resp *resp;
	struct qrild_msg *msg;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_NAS, QRILD_STATE_PENDING);

	rc = qrild_qmi_send_basic_request_sync(state, QMI_SERVICE_NAS, QMI_NAS_GET_OPERATOR_NAME,
					       &msg);
	if (rc < 0)
		return QRILD_STATE_ERROR;

	resp = nas_get_operator_name_resp_parse(msg->buf, msg->buf_len);
	if (!resp) {
		return QRILD_STATE_ERROR;
	}

	nas_get_operator_name_resp_getall(resp, data);
	qrild_msg_free(msg);

	return QRILD_STATE_DONE;
}

int qrild_qmi_nas_get_plmn_name(struct rild_state *state,
				struct nas_get_plmn_name_req_data *req_data,
				struct nas_get_plmn_name_resp_data *data)
{
	struct nas_get_plmn_name_req *req;
	struct nas_get_plmn_name_resp *resp;
	struct qrild_msg *msg;
	void *buf;
	size_t buf_sz;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_NAS, QRILD_STATE_PENDING);

	req = nas_get_plmn_name_req_alloc(qrild_next_transaction_id());
	nas_get_plmn_name_req_set_plmn(req, req_data->plmn);
	if (req_data->send_all_info_valid)
		nas_get_plmn_name_req_set_send_all_info(req, req_data->send_all_info);

	buf = nas_get_plmn_name_req_encode(req, &buf_sz);

	rc = qrild_msg_send_sync(state, QMI_SERVICE_NAS, buf, buf_sz, TIMEOUT_DEFAULT, &msg);
	if (rc < 0)
		return QRILD_STATE_ERROR;

	resp = nas_get_plmn_name_resp_parse(msg->buf, msg->buf_len);
	if (!resp) {
		return QRILD_STATE_ERROR;
	}

	nas_get_plmn_name_resp_getall(resp, data);
	qrild_msg_free(msg);

	return QRILD_STATE_DONE;
}

int qrild_qmi_wds_start_network_interface_resp(struct rild_state *state, struct qrild_msg *msg)
{
	struct wds_start_network_interface_resp *resp;
	struct qmi_response_type_v01 *res;

	resp = wds_start_network_interface_resp_parse(msg->buf, msg->buf_len);

	res = (struct qmi_response_type_v01 *)qmi_tlv_get_result(resp);
	if (res->result) {
		log_error("Failed to start network interface! QMI err: %u", res->error);
		state->exit = true;
	}

	wds_start_network_interface_resp_get_pkt_data_handle(resp, &state->wds_pkt_data_handle);
	log_debug("Got WDS packet data handle: %u", state->wds_pkt_data_handle);

	return 0;
}

/*
 * This can fail if data signal is weak, should be retried.
 * error 14: ERR_CALL_FAILED
 */
int qrild_qmi_wds_start_network_interface(struct rild_state *state,
					  struct wds_start_network_interface_resp_data *data)
{
	struct wds_start_network_interface_req *req;
	struct wds_start_network_interface_resp *resp;
	struct qmi_header *qmi;
	struct qrild_msg *msg;
	void *buf;
	size_t buf_sz;
	int rc, i;
	uint16_t txn = qrild_next_transaction_id();
	char *apn_name = "Three.co.uk";

	log_info("Starting net ifaces!");

	req = wds_start_network_interface_req_alloc(txn);

	wds_start_network_interface_req_set_apn_name(req, apn_name, strlen(apn_name));
	wds_start_network_interface_req_set_ip_family_preference(req, 4);

	buf = wds_start_network_interface_req_encode(req, &buf_sz);
	qmi = (struct qmi_header *)buf;

	rc = qrild_msg_send_sync(state, QMI_SERVICE_WDS, buf, buf_sz, TIMEOUT_DEFAULT, &msg);
	wds_start_network_interface_req_free(req);
	if (rc < 0) {
		log_error("Failed to start network interface:");
		return QRILD_STATE_ERROR;
	}

	resp = wds_start_network_interface_resp_parse(msg->buf, msg->buf_len);
	if (!resp)
		return QRILD_STATE_ERROR;

	wds_start_network_interface_resp_getall(resp, data);
	wds_start_network_interface_resp_free(resp);
	qrild_msg_free(msg);

	return QRILD_STATE_DONE;
}

int qrild_qmi_wds_get_current_settings(struct rild_state *state, struct wds_data_settings *settings)
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

	log_info("Getting runtime settings!");

	req = wds_get_current_settings_req_alloc(qrild_next_transaction_id());

	wds_get_current_settings_req_set_requested_settings(req,
							    1 << 8 | 1 << 9 | 1 << 13 | 1 << 15);

	buf = wds_get_current_settings_req_encode(req, &buf_sz);

	rc = qrild_msg_send_sync(state, QMI_SERVICE_WDS, buf, buf_sz, TIMEOUT_DEFAULT, &msg);
	wds_get_current_settings_req_free(req);
	if (rc < 0 || !msg) {
		log_error("Failed to send wds_get_current_settings request!");
		return QRILD_STATE_ERROR;
	}

	resp = wds_get_current_settings_resp_parse(msg->buf, msg->buf_len);

	qrild_msg_free(msg);

	res = qmi_tlv_get_result((void *)resp);
	if (res->result)
		return QRILD_STATE_ERROR;

	rc = wds_get_current_settings_resp_get_ipv4_address_preference(resp, &val);
	if (rc < 0) {
		log_error("Failed to get IPv4 address preference: %d", rc);
		return QRILD_STATE_ERROR;
	}
	ip.s_addr = htonl(val);
	log_info("IPv4 Address Preference: %s", inet_ntoa(ip));

	rc = wds_get_current_settings_resp_get_ipv4_gateway_addr(resp, &val);
	if (rc < 0) {
		log_error("Failed to get IPv4 Gateway Address: %d", rc);
		return QRILD_STATE_ERROR;
	}
	brd.s_addr = htonl(val);
	log_info("IPv4 Gateway Address: %s", inet_ntoa(brd));

	rc = wds_get_current_settings_resp_get_ipv4_subnet_mask(resp, &val);
	if (rc < 0) {
		log_error("Failed to get IPv4 Subnet Mask: %d", rc);
		return QRILD_STATE_ERROR;
	}
	sub.s_addr = htonl(val);
	log_info("IPv4 Subnet Mask: %s (NL endienness: 0x%x, host endianness: 0x%x)",
		 inet_ntoa(sub), sub.s_addr, val);

	rc = wds_get_current_settings_resp_get_mtu(resp, &val);
	if (rc < 0) {
		log_error("Failed to get MTU: %d", rc);
		return QRILD_STATE_ERROR;
	}
	log_info("MTU: %d", val);

	rc = wds_get_current_settings_resp_get_ip_family(resp, &val8);
	if (rc < 0) {
		log_error("Failed to get IP Family: %d", rc);
		return QRILD_STATE_ERROR;
	}
	log_info("IP Family: %u", val8);

	settings->ip = ip;
	settings->brd = brd;
	settings->sub = sub;
	settings->ip_family = val8;
	settings->mtu = val;

	// if (!state->no_configure_inet)
	// 	return qrild_link_configure(&ip, &sub, &brd);

	return QRILD_STATE_DONE;
}

#define QMI_SET_TLV(msg, tlv, req, data)                                                           \
	({                                                                                         \
		int rc = msg##_set_##tlv(req, data->tlv);                                         \
		if (rc < 0) {                                                                      \
			log_error("%s: couldn't set %s", __func__, #tlv);                          \
			return rc;                                                                 \
		}                                                                                  \
	})

int qrild_qmi_uim_read_transparent(struct rild_state *state,
				   struct uim_read_transparent_req_data *data,
				   struct uim_read_transparent_resp_data *resp_data)
{
	struct uim_read_transparent_req *req;
	struct uim_read_transparent_resp *resp;
	void *buf;
	size_t buf_len;
	struct qrild_msg *msg;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_UIM, QRILD_STATE_PENDING);

	req = uim_read_transparent_req_alloc(qrild_next_transaction_id());

	// FIXME: add >setall generator
	QMI_SET_TLV(uim_read_transparent_req, session, req, data);
	QMI_SET_TLV(uim_read_transparent_req, file, req, data);
	QMI_SET_TLV(uim_read_transparent_req, read_info, req, data);
	if (data->resp_in_ind_valid)
		QMI_SET_TLV(uim_read_transparent_req, resp_in_ind, req, data);
	if (data->encrypt_data_valid)
		QMI_SET_TLV(uim_read_transparent_req, encrypt_data, req, data);

	buf = uim_read_transparent_req_encode(req, &buf_len);

	rc = qrild_msg_send_sync(state, QMI_SERVICE_UIM, buf, buf_len, TIMEOUT_DEFAULT, &msg);
	uim_read_transparent_req_free(req);
	if (rc < 0)
		return rc;

	resp = uim_read_transparent_resp_parse(msg->buf, msg->buf_len);
	uim_read_transparent_resp_getall(resp, resp_data);

	return QRILD_STATE_DONE;
}

int qrild_qmi_uim_read_record(struct rild_state *state, struct uim_read_record_req_data *data,
			      struct uim_read_record_resp_data *resp_data)
{
	struct uim_read_record_req *req;
	struct uim_read_record_resp *resp;
	void *buf;
	size_t buf_len;
	struct qrild_msg *msg;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_UIM, QRILD_STATE_PENDING);

	req = uim_read_record_req_alloc(qrild_next_transaction_id());

	// FIXME: add >setall generator
	QMI_SET_TLV(uim_read_record_req, session, req, data);
	QMI_SET_TLV(uim_read_record_req, file, req, data);
	QMI_SET_TLV(uim_read_record_req, read_info, req, data);
	if (data->resp_in_ind_valid)
		QMI_SET_TLV(uim_read_record_req, resp_in_ind, req, data);

	buf = uim_read_record_req_encode(req, &buf_len);

	rc = qrild_msg_send_sync(state, QMI_SERVICE_UIM, buf, buf_len, TIMEOUT_DEFAULT, &msg);
	uim_read_record_req_free(req);
	if (rc < 0)
		return QRILD_STATE_ERROR;

	resp = uim_read_record_resp_parse(msg->buf, msg->buf_len);
	uim_read_record_resp_getall(resp, resp_data);

	return QRILD_STATE_DONE;
}

int qrild_qmi_uim_get_file_attrs(struct rild_state *state, struct uim_get_file_attrs_req_data *data,
				 struct uim_get_file_attrs_resp_data *resp_data)
{
	struct uim_get_file_attrs_req *req;
	struct uim_get_file_attrs_resp *resp;
	void *buf;
	size_t buf_len;
	struct qrild_msg *msg;
	int rc;

	QMI_SERVICE_OR_RETURN(&state->services, QMI_SERVICE_UIM, QRILD_STATE_PENDING);

	req = uim_get_file_attrs_req_alloc(qrild_next_transaction_id());

	// FIXME: add >setall generator
	QMI_SET_TLV(uim_get_file_attrs_req, session, req, data);
	QMI_SET_TLV(uim_get_file_attrs_req, file, req, data);
	if (data->resp_in_ind_valid)
		QMI_SET_TLV(uim_get_file_attrs_req, resp_in_ind, req, data);

	buf = uim_get_file_attrs_req_encode(req, &buf_len);

	rc = qrild_msg_send_sync(state, QMI_SERVICE_UIM, buf, buf_len, TIMEOUT_DEFAULT, &msg);
	uim_get_file_attrs_req_free(req);
	if (rc < 0)
		return QRILD_STATE_ERROR;

	resp = uim_get_file_attrs_resp_parse(msg->buf, msg->buf_len);
	uim_get_file_attrs_resp_getall(resp, resp_data);

	return QRILD_STATE_DONE;
}

const char *qmi_error_string(uint16_t err)
{
	const struct enum_value *v = &qmi_error_names[0];
	while (v->value_str) {
		if (v->value == err)
			return v->value_str;
		v++;
	}

	return "NULL";
}

static int qrild_qmi_handle_wds_pkt_srvc(struct rild_state *state, struct qrild_msg *msg)
{
	struct wds_get_pkt_srvc_status_ind *ind =
		wds_get_pkt_srvc_status_ind_parse(msg->buf, msg->buf_len);
	struct wds_pkt_srvc_status *status = wds_get_pkt_srvc_status_ind_get_status(ind);

	log_info("Connection status: %u", status->connection_status);
	q_thread_mutex_lock(&state->connection_status_mutex);
	state->connection_status = status->connection_status;
	q_thread_mutex_unlock(&state->connection_status_mutex);

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
	q_thread_mutex_lock(&state->msg_mutex);
	list_for_each_entry(msg, &state->pending_rx, li)
	{
		if (msg->type != 0x4)
			continue;

		q_thread_mutex_unlock(&state->msg_mutex);
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
		// 	log_info("Undocumented QMI NAS indication");
		// default:
		// 	LOGW("Dropping unknown message {id: 0x%x, txn: %u}",
		// 	     msg->msg_id, msg->txn);
		// 	print_hex_dump("Unknown msg", msg->buf, msg->buf_len);
		// 	break;
		// }
		// qrild_msg_free_locked(msg);
	}
	q_thread_mutex_unlock(&state->msg_mutex);

	return 0;
}

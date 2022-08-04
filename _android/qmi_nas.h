#ifndef __QMI_NAS_H__
#define __QMI_NAS_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <libqrtr.h>

#ifdef __cplusplus
extern "C" {
#endif

#define get_next(_type, _sz) ({ \
	void* buf = ptr + len; \
	len += _sz; \
	if (len > buf_sz) goto err_wrong_len; \
	*(_type*)buf; \
})

#define QMI_NAS_EVENT_REPORT 2
#define QMI_NAS_REGISTER_INDICATIONS 3
#define QMI_NAS_SERVING_SYSTEM_REPORT 36
#define QMI_NAS_GET_OPERATOR_NAME 57
#define QMI_NAS_SUBSCRIPTION_INFO_REPORT 72
#define QMI_NAS_ERROR_RATE_REPORT 83
#define QMI_NAS_RF_BAND_INFO_REPORT 102
#define QMI_NAS_GET_LTE_CPY_CA_INFO 172
#define QMI_NAS_DL_BANDWIDTH_1_4 0
#define QMI_NAS_DL_BANDWIDTH_3 1
#define QMI_NAS_DL_BANDWIDTH_5 2
#define QMI_NAS_DL_BANDWIDTH_10 3
#define QMI_NAS_DL_BANDWIDTH_15 4
#define QMI_NAS_DL_BANDWIDTH_20 5
#define QMI_NAS_DL_BANDWIDTH_INVALID 6
#define QMI_NAS_SIGNAL_STRENGTH_REQUEST_NONE 0
#define QMI_NAS_SIGNAL_STRENGTH_REQUEST_RSSI 1
#define QMI_NAS_SIGNAL_STRENGTH_REQUEST_ECIO 2
#define QMI_NAS_SIGNAL_STRENGTH_REQUEST_IO 4
#define QMI_NAS_SIGNAL_STRENGTH_REQUEST_SINR 8
#define QMI_NAS_SIGNAL_STRENGTH_REQUEST_ERROR_RATE 16
#define QMI_NAS_SIGNAL_STRENGTH_REQUEST_RSRQ 32
#define QMI_NAS_SIGNAL_STRENGTH_REQUEST_LTE_SNR 64
#define QMI_NAS_SIGNAL_STRENGTH_REQUEST_LTE_RSRP 128
#define QMI_NAS_GET_SIGNAL_STRENGTH 32
#define QMI_NAS_REGISTRATION_STATE_NOT_REGISTERED 0
#define QMI_NAS_REGISTRATION_STATE_REGISTERED 1
#define QMI_NAS_REGISTRATION_STATE_NOT_REGISTERED_SEARCHING 2
#define QMI_NAS_REGISTRATION_STATE_REGISTRATION_DENIED 3
#define QMI_NAS_REGISTRATION_STATE_UNKNOWN 4
#define QMI_NAS_ATTACH_STATE_UNKNOWN 0
#define QMI_NAS_ATTACH_STATE_ATTACHED 1
#define QMI_NAS_ATTACH_STATE_DETACHED 2
#define QMI_NAS_RADIO_INTERFACE_UNKNOWN 255
#define QMI_NAS_RADIO_INTERFACE_NONE 0
#define QMI_NAS_RADIO_INTERFACE_CDMA_1X 1
#define QMI_NAS_RADIO_INTERFACE_CDMA_1XEVDO 2
#define QMI_NAS_RADIO_INTERFACE_AMPS 3
#define QMI_NAS_RADIO_INTERFACE_GSM 4
#define QMI_NAS_RADIO_INTERFACE_UMTS 5
#define QMI_NAS_RADIO_INTERFACE_LTE 8
#define QMI_NAS_RADIO_INTERFACE_TD_SCDMA 9
#define QMI_NAS_RADIO_INTERFACE_5GNR 12

struct nas_signal_strength {
	int8_t strength;
	int8_t interface;
};

struct nas_ss_value {
	uint8_t val;
	int8_t interface;
};

struct nas_network_reject_info {
	uint8_t enable_network_reject_indications;
	uint8_t suppress_system_info_indications;
};

struct nas_lte_cphy_agg_scell {
	uint16_t pci;
	uint16_t rx_chan;
	uint32_t dl_bandwidth;
	uint16_t lte_band;
	uint32_t state;
};

struct nas_serving_system {
	uint8_t registration_state;
	uint8_t cs_attach_state;
	uint8_t ps_attach_state;
	uint8_t selected_network;
	uint8_t radio_interfaces_n;
	uint8_t *radio_interfaces;
};

struct nas_current_plmn {
	uint16_t mcc;
	uint16_t mnc;
	char *description;
};

struct nas_service_status {
	uint8_t status;
	uint8_t capability;
	uint8_t hdr_status;
	uint8_t hdr_hybrid;
	uint8_t forbidden;
};

struct nas_service_provider_name {
	uint8_t display_condition;
	char *name;
};

struct nas_operator_plmn {
	char mcc[3];
	char mnc[3];
	uint16_t lac1;
	uint16_t lac2;
	uint8_t name_record_indicator;
};

struct nas_operator_plmn_name {
	uint8_t name_encoding;
	uint8_t short_country_initials;
	uint8_t long_name_spare_bits;
	uint8_t short_name_spare_bits;
	uint8_t long_name_n;
	uint8_t *long_name;
	uint8_t short_name_n;
	uint8_t *short_name;
};

struct nas_geran_info {
	uint8_t x;
};

struct nas_register_indications_req;
struct nas_get_signal_strength_req;
struct nas_get_signal_strength_resp;
struct nas_serving_system_ind;
struct nas_set_operating_mode_req;
struct nas_set_operating_mode_resp;
struct nas_get_operator_name_resp;
struct nas_get_cell_loc_info;
struct nas_get_lte_cphy_ca_info_resp;


#define QMI_NUM_MESSAGES_NAS 9
extern const struct qmi_tlv_msg_name nas_msg_name_map[9];

/*
 * nas_register_indications_req message
 */
struct nas_register_indications_req *nas_register_indications_req_alloc(unsigned txn);
void *nas_register_indications_req_encode(struct nas_register_indications_req *register_indications_req, size_t *len);
void nas_register_indications_req_free(struct nas_register_indications_req *register_indications_req);

int nas_register_indications_req_set_system_selection_preference(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_ddtm_events(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_serving_system_events(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_dual_standby_preference(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_subscription_info(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_network_time(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_system_info(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_signal_info(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_error_rate(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_hdr_new_uati_assigned(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_hdr_session_closed(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_managed_roaming(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_current_plmn_name(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_embms_status(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_rf_band_information(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_set_network_reject_information(struct nas_register_indications_req *register_indications_req, struct nas_network_reject_info *val);

/*
 * nas_get_signal_strength_req message
 */
struct nas_get_signal_strength_req *nas_get_signal_strength_req_alloc(unsigned txn);
void *nas_get_signal_strength_req_encode(struct nas_get_signal_strength_req *get_signal_strength_req, size_t *len);
void nas_get_signal_strength_req_free(struct nas_get_signal_strength_req *get_signal_strength_req);

int nas_get_signal_strength_req_set_mask(struct nas_get_signal_strength_req *get_signal_strength_req, uint16_t val);
/*
 * nas_get_signal_strength_resp message
 */

struct nas_get_signal_strength_resp_data {
	bool strength_valid;
	struct nas_signal_strength *strength;
	struct qmi_response_type_v01 *res;
	bool strength_list_valid;
	size_t strength_list_n;
	struct nas_signal_strength *strength_list;
	bool rssi_list_valid;
	size_t rssi_list_n;
	struct nas_ss_value *rssi_list;
	bool ecio_list_valid;
	size_t ecio_list_n;
	struct nas_ss_value *ecio_list;
	bool io_valid;
	uint32_t io;
	bool sinr_valid;
	uint8_t sinr;
	bool err_rate_list_valid;
	size_t err_rate_list_n;
	struct nas_ss_value *err_rate_list;
	bool rsrq_valid;
	struct nas_ss_value *rsrq;
	bool lte_snr_valid;
	int16_t lte_snr;
	bool lte_rsrp_valid;
	int16_t lte_rsrp;
};

struct nas_get_signal_strength_resp *nas_get_signal_strength_resp_parse(void *buf, size_t len);
void nas_get_signal_strength_resp_getall(struct nas_get_signal_strength_resp *get_signal_strength_resp, struct nas_get_signal_strength_resp_data *data);
void nas_get_signal_strength_resp_data_free(struct nas_get_signal_strength_resp_data *data);
void nas_get_signal_strength_resp_free(struct nas_get_signal_strength_resp *get_signal_strength_resp);

struct nas_signal_strength *nas_get_signal_strength_resp_get_strength(struct nas_get_signal_strength_resp *get_signal_strength_resp);
void nas_signal_strength_free(struct nas_signal_strength *val);

struct nas_signal_strength *nas_get_signal_strength_resp_get_strength_list(struct nas_get_signal_strength_resp *get_signal_strength_resp, size_t *count);


struct nas_ss_value *nas_get_signal_strength_resp_get_rssi_list(struct nas_get_signal_strength_resp *get_signal_strength_resp, size_t *count);


struct nas_ss_value *nas_get_signal_strength_resp_get_ecio_list(struct nas_get_signal_strength_resp *get_signal_strength_resp, size_t *count);


int nas_get_signal_strength_resp_get_io(struct nas_get_signal_strength_resp *get_signal_strength_resp, uint32_t *val);

int nas_get_signal_strength_resp_get_sinr(struct nas_get_signal_strength_resp *get_signal_strength_resp, uint8_t *val);

struct nas_ss_value *nas_get_signal_strength_resp_get_err_rate_list(struct nas_get_signal_strength_resp *get_signal_strength_resp, size_t *count);


struct nas_ss_value *nas_get_signal_strength_resp_get_rsrq(struct nas_get_signal_strength_resp *get_signal_strength_resp);
void nas_ss_value_free(struct nas_ss_value *val);

int nas_get_signal_strength_resp_get_lte_snr(struct nas_get_signal_strength_resp *get_signal_strength_resp, int16_t *val);

int nas_get_signal_strength_resp_get_lte_rsrp(struct nas_get_signal_strength_resp *get_signal_strength_resp, int16_t *val);

/*
 * nas_serving_system_ind message
 */

struct nas_serving_system_ind_data {
	bool system_valid;
	struct nas_serving_system *system;
	bool data_service_cap_valid;
	uint8_t data_service_cap;
	bool plmn_valid;
	struct nas_current_plmn *plmn;
	bool status_valid;
	struct nas_service_status *status;
};

struct nas_serving_system_ind *nas_serving_system_ind_parse(void *buf, size_t len);
void nas_serving_system_ind_getall(struct nas_serving_system_ind *serving_system_ind, struct nas_serving_system_ind_data *data);
void nas_serving_system_ind_data_free(struct nas_serving_system_ind_data *data);
struct nas_serving_system_ind *nas_serving_system_ind_alloc(unsigned txn);
void *nas_serving_system_ind_encode(struct nas_serving_system_ind *serving_system_ind, size_t *len);
void nas_serving_system_ind_free(struct nas_serving_system_ind *serving_system_ind);

int nas_serving_system_ind_set_system(struct nas_serving_system_ind *serving_system_ind, struct nas_serving_system *val);
struct nas_serving_system *nas_serving_system_ind_get_system(struct nas_serving_system_ind *serving_system_ind);
void nas_serving_system_free(struct nas_serving_system *val);

int nas_serving_system_ind_set_data_service_cap(struct nas_serving_system_ind *serving_system_ind, uint8_t val);
int nas_serving_system_ind_get_data_service_cap(struct nas_serving_system_ind *serving_system_ind, uint8_t *val);

int nas_serving_system_ind_set_plmn(struct nas_serving_system_ind *serving_system_ind, struct nas_current_plmn *val);
struct nas_current_plmn *nas_serving_system_ind_get_plmn(struct nas_serving_system_ind *serving_system_ind);
void nas_current_plmn_free(struct nas_current_plmn *val);

int nas_serving_system_ind_set_status(struct nas_serving_system_ind *serving_system_ind, struct nas_service_status *val);
struct nas_service_status *nas_serving_system_ind_get_status(struct nas_serving_system_ind *serving_system_ind);
void nas_service_status_free(struct nas_service_status *val);

/*
 * nas_set_operating_mode_req message
 */
struct nas_set_operating_mode_req *nas_set_operating_mode_req_alloc(unsigned txn);
void *nas_set_operating_mode_req_encode(struct nas_set_operating_mode_req *set_operating_mode_req, size_t *len);
void nas_set_operating_mode_req_free(struct nas_set_operating_mode_req *set_operating_mode_req);

int nas_set_operating_mode_req_set_mode(struct nas_set_operating_mode_req *set_operating_mode_req, uint8_t val);
/*
 * nas_set_operating_mode_resp message
 */
struct nas_set_operating_mode_resp *nas_set_operating_mode_resp_alloc(unsigned txn);
void *nas_set_operating_mode_resp_encode(struct nas_set_operating_mode_resp *set_operating_mode_resp, size_t *len);
void nas_set_operating_mode_resp_free(struct nas_set_operating_mode_resp *set_operating_mode_resp);

/*
 * nas_get_operator_name_resp message
 */

struct nas_get_operator_name_resp_data {
	struct qmi_response_type_v01 *res;
	bool provider_name_valid;
	struct nas_service_provider_name *provider_name;
	bool operator_plmn_list_valid;
	size_t operator_plmn_list_n;
	struct nas_operator_plmn *operator_plmn_list;
	bool operator_plmn_names_valid;
	size_t operator_plmn_names_n;
	struct nas_operator_plmn_name *operator_plmn_names;
	bool operator_string_name_valid;
	char *operator_string_name;
	bool nitz_info_valid;
	struct nas_operator_plmn_name *nitz_info;
};

struct nas_get_operator_name_resp *nas_get_operator_name_resp_parse(void *buf, size_t len);
void nas_get_operator_name_resp_getall(struct nas_get_operator_name_resp *get_operator_name_resp, struct nas_get_operator_name_resp_data *data);
void nas_get_operator_name_resp_data_free(struct nas_get_operator_name_resp_data *data);
void nas_get_operator_name_resp_free(struct nas_get_operator_name_resp *get_operator_name_resp);

struct nas_service_provider_name *nas_get_operator_name_resp_get_provider_name(struct nas_get_operator_name_resp *get_operator_name_resp);
void nas_service_provider_name_free(struct nas_service_provider_name *val);

struct nas_operator_plmn *nas_get_operator_name_resp_get_operator_plmn_list(struct nas_get_operator_name_resp *get_operator_name_resp, size_t *count);


struct nas_operator_plmn_name *nas_get_operator_name_resp_get_operator_plmn_names(struct nas_get_operator_name_resp *get_operator_name_resp, size_t *count);


char *nas_get_operator_name_resp_get_operator_string_name(struct nas_get_operator_name_resp *get_operator_name_resp);

struct nas_operator_plmn_name *nas_get_operator_name_resp_get_nitz_info(struct nas_get_operator_name_resp *get_operator_name_resp);
void nas_operator_plmn_name_free(struct nas_operator_plmn_name *val);

/*
 * nas_get_cell_loc_info message
 */
struct nas_get_cell_loc_info *nas_get_cell_loc_info_parse(void *buf, size_t len);
void nas_get_cell_loc_info_free(struct nas_get_cell_loc_info *get_cell_loc_info);

/*
 * nas_get_lte_cphy_ca_info_resp message
 */

struct nas_get_lte_cphy_ca_info_resp_data {
	struct qmi_response_type_v01 *res;
	bool dl_bandwidth_valid;
	uint32_t dl_bandwidth;
	bool phy_scell_info_valid;
	struct nas_lte_cphy_agg_scell *phy_scell_info;
};

struct nas_get_lte_cphy_ca_info_resp *nas_get_lte_cphy_ca_info_resp_parse(void *buf, size_t len);
void nas_get_lte_cphy_ca_info_resp_getall(struct nas_get_lte_cphy_ca_info_resp *get_lte_cphy_ca_info_resp, struct nas_get_lte_cphy_ca_info_resp_data *data);
void nas_get_lte_cphy_ca_info_resp_data_free(struct nas_get_lte_cphy_ca_info_resp_data *data);
void nas_get_lte_cphy_ca_info_resp_free(struct nas_get_lte_cphy_ca_info_resp *get_lte_cphy_ca_info_resp);

int nas_get_lte_cphy_ca_info_resp_get_dl_bandwidth(struct nas_get_lte_cphy_ca_info_resp *get_lte_cphy_ca_info_resp, uint32_t *val);

struct nas_lte_cphy_agg_scell *nas_get_lte_cphy_ca_info_resp_get_phy_scell_info(struct nas_get_lte_cphy_ca_info_resp *get_lte_cphy_ca_info_resp);
void nas_lte_cphy_agg_scell_free(struct nas_lte_cphy_agg_scell *val);

#ifdef __cplusplus
}
#endif

#endif

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
#define QMI_NAS_INITIATE_NETWORK_REGISTER 34
#define QMI_NAS_SERVING_SYSTEM_REPORT 36
#define QMI_NAS_SET_SYSTEM_PREFS 51
#define QMI_NAS_GET_SYSTEM_PREFS 52
#define QMI_NAS_GET_OPERATOR_NAME 57
#define QMI_NAS_GET_CELL_LOCATION_INFO 67
#define QMI_NAS_GET_PLMN_NAME 68
#define QMI_NAS_SUBSCRIPTION_INFO_REPORT 72
#define QMI_NAS_GET_SIGNAL_INFO 79
#define QMI_NAS_SIGNAL_INFO_REPORT 81
#define QMI_NAS_ERROR_RATE_REPORT 83
#define QMI_NAS_RF_BAND_INFO_REPORT 102
#define QMI_NAS_FORCE_NETWORK_SEARCH 103
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

struct nas_operator_plmn_arr {
	uint16_t operators_n;
	struct operator_plmn_arr_operators {
		char mcc[3];
		char mnc[3];
		uint16_t lac1;
		uint16_t lac2;
		uint8_t name_record_indicator;
	} *operators;
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

struct nas_operator_plmn_name_arr {
	uint8_t operators_n;
	struct operator_plmn_name_arr_operators {
		uint8_t name_encoding;
		uint8_t short_country_initials;
		uint8_t long_name_spare_bits;
		uint8_t short_name_spare_bits;
		uint8_t long_name_n;
		uint8_t *long_name;
		uint8_t short_name_n;
		uint8_t *short_name;
	} *operators;
};

struct nas_network_selection_pref {
	uint8_t mode;
	uint16_t mcc;
	uint16_t mnc;
};

struct nas_geran_info {
	uint32_t cell_id;
	uint8_t plmn[3];
	uint16_t lac;
	uint16_t abs_channel_num;
	uint8_t bsic;
	uint32_t timing_advance;
	uint16_t rx_level;
	uint8_t cells_n;
	struct geran_info_cells {
		uint32_t cell_id;
		uint8_t plmn[3];
		uint16_t lac;
		uint16_t abs_channel_num;
		uint8_t bsic;
		uint16_t rx_level;
	} *cells;
};

struct nas_umts_info {
	uint16_t cell_id;
	uint8_t plmn[3];
	uint16_t lac;
	uint16_t abs_channel_num;
	uint16_t psc;
	int16_t rscp;
	int16_t ecio;
	uint8_t cells_n;
	struct umts_info_cells {
		uint16_t abs_channel_num;
		uint16_t psc;
		int16_t rscp;
		int16_t ecio;
	} *cells;
	uint8_t gerans_n;
	struct umts_info_cells_gerans {
		uint16_t abs_channel_num;
		uint8_t network_color_code;
		uint8_t base_station_color_code;
		int8_t rssi;
	} *gerans;
};

struct nas_cdma_info {
	uint16_t system_id;
	uint16_t network_id;
	uint16_t bsid;
	uint16_t reference_pn;
	uint32_t latitude;
	uint32_t longitude;
};

struct nas_intrafreq_lte_info {
	uint8_t ue_idle;
	uint8_t plmn[3];
	uint16_t tac;
	uint32_t global_cell_id;
	uint16_t abs_channel_num;
	uint16_t serving_cell_id;
	uint8_t crp;
	uint8_t s_non_intra_search_threshold;
	uint8_t serving_cell_low_threshold;
	uint8_t s_intra_search_threshold;
	uint8_t cells_n;
	struct intrafreq_lte_info_cells {
		uint16_t pci;
		int16_t rsrq;
		int16_t rsrp;
		int16_t rssi;
		int16_t rx_level;
	} *cells;
};

struct nas_plmn_id {
	uint16_t mcc;
	uint16_t mnc;
};

struct nas_eons_plmn_name {
	uint8_t sp_name_encoding;
	uint8_t sp_name_n;
	uint8_t *sp_name;
	uint8_t short_name_encoding;
	uint8_t short_name_country_initials;
	uint8_t short_name_spare_bits;
	uint8_t short_name_n;
	uint8_t *short_name;
	uint8_t long_name_encoding;
	uint8_t long_name_country_initials;
	uint8_t long_name_spare_bits;
	uint8_t long_name_n;
	uint8_t *long_name;
};

struct nas_ss_cdma {
	int8_t rssi;
	int16_t ecio;
};

struct nas_ss_hdr {
	int8_t rssi;
	int16_t ecio;
	uint8_t sinr;
	int32_t io;
};

struct nas_ss_wcdma {
	int8_t rssi;
	int16_t ecio;
};

struct nas_ss_lte {
	int8_t rssi;
	int8_t rsrq;
	int16_t rsrp;
	int16_t snr;
};

struct nas_ss_tdma_ext {
	uint32_t rssi;
	int32_t rscp;
	int32_t ecio;
	int32_t sinr;
};

struct nas_register_indications_req;
struct nas_get_signal_strength_req;
struct nas_get_signal_strength_resp;
struct nas_initiate_network_register;
struct nas_serving_system_resp;
struct nas_serving_system_ind;
struct nas_set_operating_mode_req;
struct nas_set_operating_mode_resp;
struct nas_set_system_prefs;
struct nas_get_system_prefs;
struct nas_get_operator_name_resp;
struct nas_operator_name_ind;
struct nas_get_cell_loc_info;
struct nas_get_plmn_name_req;
struct nas_get_plmn_name_resp;
struct nas_get_signal_info;
struct nas_signal_info_ind;
struct nas_get_lte_cphy_ca_info_resp;


#define QMI_NUM_MESSAGES_NAS 18
extern const struct qmi_tlv_msg_name nas_msg_name_map[18];

/*
 * nas_register_indications_req message
 */

struct nas_register_indications_req_data {
	uint8_t system_selection_preference;
	uint8_t ddtm_events;
	uint8_t serving_system_events;
	uint8_t dual_standby_preference;
	uint8_t subscription_info;
	uint8_t network_time;
	uint8_t system_info;
	uint8_t signal_info;
	uint8_t error_rate;
	uint8_t hdr_new_uati_assigned;
	uint8_t hdr_session_closed;
	uint8_t managed_roaming;
	uint8_t current_plmn_name;
	uint8_t embms_status;
	uint8_t rf_band_information;
	struct nas_network_reject_info *network_reject_information;
};

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

struct nas_get_signal_strength_req_data {
	uint16_t mask;
};

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
 * nas_initiate_network_register message
 */

struct nas_initiate_network_register_data {
	uint8_t action;
};

struct nas_initiate_network_register *nas_initiate_network_register_alloc(unsigned txn);
void *nas_initiate_network_register_encode(struct nas_initiate_network_register *initiate_network_register, size_t *len);
void nas_initiate_network_register_free(struct nas_initiate_network_register *initiate_network_register);

int nas_initiate_network_register_set_action(struct nas_initiate_network_register *initiate_network_register, uint8_t val);
/*
 * nas_serving_system_resp message
 */

struct nas_serving_system_resp_data {
	struct qmi_response_type_v01 *res;
	bool system_valid;
	struct nas_serving_system *system;
	bool data_service_cap_valid;
	size_t data_service_cap_n;
	uint8_t *data_service_cap;
	bool plmn_valid;
	struct nas_current_plmn *plmn;
	bool lac_valid;
	uint16_t lac;
	bool cid_valid;
	uint16_t cid;
	bool status_valid;
	struct nas_service_status *status;
};

struct nas_serving_system_resp *nas_serving_system_resp_parse(void *buf, size_t len);
void nas_serving_system_resp_getall(struct nas_serving_system_resp *serving_system_resp, struct nas_serving_system_resp_data *data);
void nas_serving_system_resp_data_free(struct nas_serving_system_resp_data *data);
void nas_serving_system_resp_free(struct nas_serving_system_resp *serving_system_resp);

struct nas_serving_system *nas_serving_system_resp_get_system(struct nas_serving_system_resp *serving_system_resp);
void nas_serving_system_free(struct nas_serving_system *val);

uint8_t *nas_serving_system_resp_get_data_service_cap(struct nas_serving_system_resp *serving_system_resp, size_t *count);

struct nas_current_plmn *nas_serving_system_resp_get_plmn(struct nas_serving_system_resp *serving_system_resp);
void nas_current_plmn_free(struct nas_current_plmn *val);

int nas_serving_system_resp_get_lac(struct nas_serving_system_resp *serving_system_resp, uint16_t *val);

int nas_serving_system_resp_get_cid(struct nas_serving_system_resp *serving_system_resp, uint16_t *val);

struct nas_service_status *nas_serving_system_resp_get_status(struct nas_serving_system_resp *serving_system_resp);
void nas_service_status_free(struct nas_service_status *val);

/*
 * nas_serving_system_ind message
 */

struct nas_serving_system_ind_data {
	bool system_valid;
	struct nas_serving_system *system;
	bool data_service_cap_valid;
	size_t data_service_cap_n;
	uint8_t *data_service_cap;
	bool plmn_valid;
	struct nas_current_plmn *plmn;
	bool lac_valid;
	uint16_t lac;
	bool cid_valid;
	uint16_t cid;
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

int nas_serving_system_ind_set_data_service_cap(struct nas_serving_system_ind *serving_system_ind, uint8_t *val, size_t count);
uint8_t *nas_serving_system_ind_get_data_service_cap(struct nas_serving_system_ind *serving_system_ind, size_t *count);

int nas_serving_system_ind_set_plmn(struct nas_serving_system_ind *serving_system_ind, struct nas_current_plmn *val);
struct nas_current_plmn *nas_serving_system_ind_get_plmn(struct nas_serving_system_ind *serving_system_ind);
void nas_current_plmn_free(struct nas_current_plmn *val);

int nas_serving_system_ind_set_lac(struct nas_serving_system_ind *serving_system_ind, uint16_t val);
int nas_serving_system_ind_get_lac(struct nas_serving_system_ind *serving_system_ind, uint16_t *val);

int nas_serving_system_ind_set_cid(struct nas_serving_system_ind *serving_system_ind, uint16_t val);
int nas_serving_system_ind_get_cid(struct nas_serving_system_ind *serving_system_ind, uint16_t *val);

int nas_serving_system_ind_set_status(struct nas_serving_system_ind *serving_system_ind, struct nas_service_status *val);
struct nas_service_status *nas_serving_system_ind_get_status(struct nas_serving_system_ind *serving_system_ind);
void nas_service_status_free(struct nas_service_status *val);

/*
 * nas_set_operating_mode_req message
 */

struct nas_set_operating_mode_req_data {
	uint8_t mode;
};

struct nas_set_operating_mode_req *nas_set_operating_mode_req_alloc(unsigned txn);
void *nas_set_operating_mode_req_encode(struct nas_set_operating_mode_req *set_operating_mode_req, size_t *len);
void nas_set_operating_mode_req_free(struct nas_set_operating_mode_req *set_operating_mode_req);

int nas_set_operating_mode_req_set_mode(struct nas_set_operating_mode_req *set_operating_mode_req, uint8_t val);
/*
 * nas_set_operating_mode_resp message
 */

struct nas_set_operating_mode_resp_data {
	struct qmi_response_type_v01 *res;
};

struct nas_set_operating_mode_resp *nas_set_operating_mode_resp_alloc(unsigned txn);
void *nas_set_operating_mode_resp_encode(struct nas_set_operating_mode_resp *set_operating_mode_resp, size_t *len);
void nas_set_operating_mode_resp_free(struct nas_set_operating_mode_resp *set_operating_mode_resp);

/*
 * nas_set_system_prefs message
 */

struct nas_set_system_prefs_data {
	bool network_selection_valid;
	struct nas_network_selection_pref *network_selection;
};

struct nas_set_system_prefs *nas_set_system_prefs_alloc(unsigned txn);
void *nas_set_system_prefs_encode(struct nas_set_system_prefs *set_system_prefs, size_t *len);
void nas_set_system_prefs_free(struct nas_set_system_prefs *set_system_prefs);

int nas_set_system_prefs_set_network_selection(struct nas_set_system_prefs *set_system_prefs, struct nas_network_selection_pref *val);

/*
 * nas_get_system_prefs message
 */

struct nas_get_system_prefs_data {
	struct qmi_response_type_v01 *res;
	bool network_selection_valid;
	uint8_t network_selection;
};

struct nas_get_system_prefs *nas_get_system_prefs_parse(void *buf, size_t len);
void nas_get_system_prefs_getall(struct nas_get_system_prefs *get_system_prefs, struct nas_get_system_prefs_data *data);
void nas_get_system_prefs_data_free(struct nas_get_system_prefs_data *data);
void nas_get_system_prefs_free(struct nas_get_system_prefs *get_system_prefs);

int nas_get_system_prefs_get_network_selection(struct nas_get_system_prefs *get_system_prefs, uint8_t *val);

/*
 * nas_get_operator_name_resp message
 */

struct nas_get_operator_name_resp_data {
	struct qmi_response_type_v01 *res;
	bool provider_name_valid;
	struct nas_service_provider_name *provider_name;
	bool operator_plmns_valid;
	struct nas_operator_plmn_arr *operator_plmns;
	bool operator_plmn_names_valid;
	struct nas_operator_plmn_name_arr *operator_plmn_names;
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

struct nas_operator_plmn_arr *nas_get_operator_name_resp_get_operator_plmns(struct nas_get_operator_name_resp *get_operator_name_resp);
void nas_operator_plmn_arr_free(struct nas_operator_plmn_arr *val);

struct nas_operator_plmn_name_arr *nas_get_operator_name_resp_get_operator_plmn_names(struct nas_get_operator_name_resp *get_operator_name_resp);
void nas_operator_plmn_name_arr_free(struct nas_operator_plmn_name_arr *val);

char *nas_get_operator_name_resp_get_operator_string_name(struct nas_get_operator_name_resp *get_operator_name_resp);

struct nas_operator_plmn_name *nas_get_operator_name_resp_get_nitz_info(struct nas_get_operator_name_resp *get_operator_name_resp);
void nas_operator_plmn_name_free(struct nas_operator_plmn_name *val);

/*
 * nas_operator_name_ind message
 */

struct nas_operator_name_ind_data {
	bool provider_name_valid;
	struct nas_service_provider_name *provider_name;
	bool operator_plmns_valid;
	struct nas_operator_plmn_arr *operator_plmns;
	bool operator_plmn_names_valid;
	struct nas_operator_plmn_name_arr *operator_plmn_names;
	bool operator_string_name_valid;
	char *operator_string_name;
	bool nitz_info_valid;
	struct nas_operator_plmn_name *nitz_info;
};

struct nas_operator_name_ind *nas_operator_name_ind_parse(void *buf, size_t len);
void nas_operator_name_ind_getall(struct nas_operator_name_ind *operator_name_ind, struct nas_operator_name_ind_data *data);
void nas_operator_name_ind_data_free(struct nas_operator_name_ind_data *data);
struct nas_operator_name_ind *nas_operator_name_ind_alloc(unsigned txn);
void *nas_operator_name_ind_encode(struct nas_operator_name_ind *operator_name_ind, size_t *len);
void nas_operator_name_ind_free(struct nas_operator_name_ind *operator_name_ind);

int nas_operator_name_ind_set_provider_name(struct nas_operator_name_ind *operator_name_ind, struct nas_service_provider_name *val);
struct nas_service_provider_name *nas_operator_name_ind_get_provider_name(struct nas_operator_name_ind *operator_name_ind);
void nas_service_provider_name_free(struct nas_service_provider_name *val);

int nas_operator_name_ind_set_operator_plmns(struct nas_operator_name_ind *operator_name_ind, struct nas_operator_plmn_arr *val);
struct nas_operator_plmn_arr *nas_operator_name_ind_get_operator_plmns(struct nas_operator_name_ind *operator_name_ind);
void nas_operator_plmn_arr_free(struct nas_operator_plmn_arr *val);

int nas_operator_name_ind_set_operator_plmn_names(struct nas_operator_name_ind *operator_name_ind, struct nas_operator_plmn_name_arr *val);
struct nas_operator_plmn_name_arr *nas_operator_name_ind_get_operator_plmn_names(struct nas_operator_name_ind *operator_name_ind);
void nas_operator_plmn_name_arr_free(struct nas_operator_plmn_name_arr *val);

int nas_operator_name_ind_set_operator_string_name(struct nas_operator_name_ind *operator_name_ind, char *buf, size_t len);
char *nas_operator_name_ind_get_operator_string_name(struct nas_operator_name_ind *operator_name_ind);

int nas_operator_name_ind_set_nitz_info(struct nas_operator_name_ind *operator_name_ind, struct nas_operator_plmn_name *val);
struct nas_operator_plmn_name *nas_operator_name_ind_get_nitz_info(struct nas_operator_name_ind *operator_name_ind);
void nas_operator_plmn_name_free(struct nas_operator_plmn_name *val);

/*
 * nas_get_cell_loc_info message
 */

struct nas_get_cell_loc_info_data {
	struct qmi_response_type_v01 *res;
	bool geran_valid;
	struct nas_geran_info *geran;
	bool umts_valid;
	struct nas_umts_info *umts;
	bool cdma_valid;
	struct nas_cdma_info *cdma;
	bool intra_lte_valid;
	struct nas_intrafreq_lte_info *intra_lte;
};

struct nas_get_cell_loc_info *nas_get_cell_loc_info_parse(void *buf, size_t len);
void nas_get_cell_loc_info_getall(struct nas_get_cell_loc_info *get_cell_loc_info, struct nas_get_cell_loc_info_data *data);
void nas_get_cell_loc_info_data_free(struct nas_get_cell_loc_info_data *data);
void nas_get_cell_loc_info_free(struct nas_get_cell_loc_info *get_cell_loc_info);

struct nas_geran_info *nas_get_cell_loc_info_get_geran(struct nas_get_cell_loc_info *get_cell_loc_info);
void nas_geran_info_free(struct nas_geran_info *val);

struct nas_umts_info *nas_get_cell_loc_info_get_umts(struct nas_get_cell_loc_info *get_cell_loc_info);
void nas_umts_info_free(struct nas_umts_info *val);

struct nas_cdma_info *nas_get_cell_loc_info_get_cdma(struct nas_get_cell_loc_info *get_cell_loc_info);
void nas_cdma_info_free(struct nas_cdma_info *val);

struct nas_intrafreq_lte_info *nas_get_cell_loc_info_get_intra_lte(struct nas_get_cell_loc_info *get_cell_loc_info);
void nas_intrafreq_lte_info_free(struct nas_intrafreq_lte_info *val);

/*
 * nas_get_plmn_name_req message
 */

struct nas_get_plmn_name_req_data {
	struct nas_plmn_id *plmn;
	bool send_all_info_valid;
	uint8_t send_all_info;
};

struct nas_get_plmn_name_req *nas_get_plmn_name_req_alloc(unsigned txn);
void *nas_get_plmn_name_req_encode(struct nas_get_plmn_name_req *get_plmn_name_req, size_t *len);
void nas_get_plmn_name_req_free(struct nas_get_plmn_name_req *get_plmn_name_req);

int nas_get_plmn_name_req_set_plmn(struct nas_get_plmn_name_req *get_plmn_name_req, struct nas_plmn_id *val);

int nas_get_plmn_name_req_set_send_all_info(struct nas_get_plmn_name_req *get_plmn_name_req, uint8_t val);
/*
 * nas_get_plmn_name_resp message
 */

struct nas_get_plmn_name_resp_data {
	struct qmi_response_type_v01 *res;
	bool plmn_name_valid;
	struct nas_eons_plmn_name *plmn_name;
};

struct nas_get_plmn_name_resp *nas_get_plmn_name_resp_parse(void *buf, size_t len);
void nas_get_plmn_name_resp_getall(struct nas_get_plmn_name_resp *get_plmn_name_resp, struct nas_get_plmn_name_resp_data *data);
void nas_get_plmn_name_resp_data_free(struct nas_get_plmn_name_resp_data *data);
void nas_get_plmn_name_resp_free(struct nas_get_plmn_name_resp *get_plmn_name_resp);

struct nas_eons_plmn_name *nas_get_plmn_name_resp_get_plmn_name(struct nas_get_plmn_name_resp *get_plmn_name_resp);
void nas_eons_plmn_name_free(struct nas_eons_plmn_name *val);

/*
 * nas_get_signal_info message
 */

struct nas_get_signal_info_data {
	struct qmi_response_type_v01 *res;
	bool cdma_valid;
	struct nas_ss_cdma *cdma;
	bool hdr_valid;
	struct nas_ss_hdr *hdr;
	bool gsm_valid;
	int8_t gsm;
	bool wcdma_valid;
	struct nas_ss_wcdma *wcdma;
	bool lte_valid;
	struct nas_ss_lte *lte;
	bool tdma_valid;
	int8_t tdma;
	bool tdma_ext_valid;
	struct nas_ss_tdma_ext *tdma_ext;
};

struct nas_get_signal_info *nas_get_signal_info_parse(void *buf, size_t len);
void nas_get_signal_info_getall(struct nas_get_signal_info *get_signal_info, struct nas_get_signal_info_data *data);
void nas_get_signal_info_data_free(struct nas_get_signal_info_data *data);
void nas_get_signal_info_free(struct nas_get_signal_info *get_signal_info);

struct nas_ss_cdma *nas_get_signal_info_get_cdma(struct nas_get_signal_info *get_signal_info);
void nas_ss_cdma_free(struct nas_ss_cdma *val);

struct nas_ss_hdr *nas_get_signal_info_get_hdr(struct nas_get_signal_info *get_signal_info);
void nas_ss_hdr_free(struct nas_ss_hdr *val);

int nas_get_signal_info_get_gsm(struct nas_get_signal_info *get_signal_info, int8_t *val);

struct nas_ss_wcdma *nas_get_signal_info_get_wcdma(struct nas_get_signal_info *get_signal_info);
void nas_ss_wcdma_free(struct nas_ss_wcdma *val);

struct nas_ss_lte *nas_get_signal_info_get_lte(struct nas_get_signal_info *get_signal_info);
void nas_ss_lte_free(struct nas_ss_lte *val);

int nas_get_signal_info_get_tdma(struct nas_get_signal_info *get_signal_info, int8_t *val);

struct nas_ss_tdma_ext *nas_get_signal_info_get_tdma_ext(struct nas_get_signal_info *get_signal_info);
void nas_ss_tdma_ext_free(struct nas_ss_tdma_ext *val);

/*
 * nas_signal_info_ind message
 */

struct nas_signal_info_ind_data {
	bool cdma_valid;
	struct nas_ss_cdma *cdma;
	bool hdr_valid;
	struct nas_ss_hdr *hdr;
	bool gsm_valid;
	int8_t gsm;
	bool wcdma_valid;
	struct nas_ss_wcdma *wcdma;
	bool lte_valid;
	struct nas_ss_lte *lte;
	bool tdma_valid;
	int8_t tdma;
};

struct nas_signal_info_ind *nas_signal_info_ind_parse(void *buf, size_t len);
void nas_signal_info_ind_getall(struct nas_signal_info_ind *signal_info_ind, struct nas_signal_info_ind_data *data);
void nas_signal_info_ind_data_free(struct nas_signal_info_ind_data *data);
struct nas_signal_info_ind *nas_signal_info_ind_alloc(unsigned txn);
void *nas_signal_info_ind_encode(struct nas_signal_info_ind *signal_info_ind, size_t *len);
void nas_signal_info_ind_free(struct nas_signal_info_ind *signal_info_ind);

int nas_signal_info_ind_set_cdma(struct nas_signal_info_ind *signal_info_ind, struct nas_ss_cdma *val);
struct nas_ss_cdma *nas_signal_info_ind_get_cdma(struct nas_signal_info_ind *signal_info_ind);
void nas_ss_cdma_free(struct nas_ss_cdma *val);

int nas_signal_info_ind_set_hdr(struct nas_signal_info_ind *signal_info_ind, struct nas_ss_hdr *val);
struct nas_ss_hdr *nas_signal_info_ind_get_hdr(struct nas_signal_info_ind *signal_info_ind);
void nas_ss_hdr_free(struct nas_ss_hdr *val);

int nas_signal_info_ind_set_gsm(struct nas_signal_info_ind *signal_info_ind, int8_t val);
int nas_signal_info_ind_get_gsm(struct nas_signal_info_ind *signal_info_ind, int8_t *val);

int nas_signal_info_ind_set_wcdma(struct nas_signal_info_ind *signal_info_ind, struct nas_ss_wcdma *val);
struct nas_ss_wcdma *nas_signal_info_ind_get_wcdma(struct nas_signal_info_ind *signal_info_ind);
void nas_ss_wcdma_free(struct nas_ss_wcdma *val);

int nas_signal_info_ind_set_lte(struct nas_signal_info_ind *signal_info_ind, struct nas_ss_lte *val);
struct nas_ss_lte *nas_signal_info_ind_get_lte(struct nas_signal_info_ind *signal_info_ind);
void nas_ss_lte_free(struct nas_ss_lte *val);

int nas_signal_info_ind_set_tdma(struct nas_signal_info_ind *signal_info_ind, int8_t val);
int nas_signal_info_ind_get_tdma(struct nas_signal_info_ind *signal_info_ind, int8_t *val);

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

#ifndef __QMI_NAS_H__
#define __QMI_NAS_H__

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <libqrtr.h>

#define get_next(_type, _sz) ({ \
	void* buf = ptr + len; \
	len += _sz; \
	if (len > buf_sz) goto err_wrong_len; \
	*(_type*)buf; \
})

#define QMI_NAS_EVENT_REPORT 2
#define QMI_NAS_REGISTER_INDICATIONS 3
#define QMI_NAS_SUBSCRIPTION_INFO_REPORT 72
#define QMI_NAS_ERROR_RATE_REPORT 83
#define QMI_NAS_RF_BAND_INFO_REPORT 102
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

struct nas_signal_strength {
	int8_t strength;
	int8_t interface;
};

struct nas_signal_strength_list {
	uint8_t interfaces_n;
	struct signal_strength_list_interfaces {
		int8_t strength;
		int8_t interface;
	} *interfaces;
};

struct nas_network_reject_info {
	uint8_t enable_network_reject_indications;
	uint8_t suppress_system_info_indications;
};

struct nas_register_indications_req;
struct nas_get_signal_strength_req;
struct nas_get_signal_strength_resp;
struct nas_set_operating_mode_req;
struct nas_set_operating_mode_resp;

/*
 * nas_register_indications_req message
 */
struct nas_register_indications_req *nas_register_indications_req_alloc(unsigned txn);
struct nas_register_indications_req *nas_register_indications_req_parse(void *buf, size_t len);
void *nas_register_indications_req_encode(struct nas_register_indications_req *register_indications_req, size_t *len);
void nas_register_indications_req_free(struct nas_register_indications_req *register_indications_req);

int nas_register_indications_req_set_system_selection_preference(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_system_selection_preference(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_ddtm_events(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_ddtm_events(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_serving_system_events(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_serving_system_events(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_dual_standby_preference(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_dual_standby_preference(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_subscription_info(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_subscription_info(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_network_time(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_network_time(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_system_info(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_system_info(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_signal_info(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_signal_info(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_error_rate(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_error_rate(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_hdr_new_uati_assigned(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_hdr_new_uati_assigned(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_hdr_session_closed(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_hdr_session_closed(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_managed_roaming(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_managed_roaming(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_current_plmn_name(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_current_plmn_name(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_embms_status(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_embms_status(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_rf_band_information(struct nas_register_indications_req *register_indications_req, uint8_t val);
int nas_register_indications_req_get_rf_band_information(struct nas_register_indications_req *register_indications_req, uint8_t *val);

int nas_register_indications_req_set_network_reject_information(struct nas_register_indications_req *register_indications_req, struct nas_network_reject_info *val);
struct nas_network_reject_info *nas_register_indications_req_get_network_reject_information(struct nas_register_indications_req *register_indications_req);

/*
 * nas_get_signal_strength_req message
 */
struct nas_get_signal_strength_req *nas_get_signal_strength_req_alloc(unsigned txn);
struct nas_get_signal_strength_req *nas_get_signal_strength_req_parse(void *buf, size_t len);
void *nas_get_signal_strength_req_encode(struct nas_get_signal_strength_req *get_signal_strength_req, size_t *len);
void nas_get_signal_strength_req_free(struct nas_get_signal_strength_req *get_signal_strength_req);

int nas_get_signal_strength_req_set_mask(struct nas_get_signal_strength_req *get_signal_strength_req, uint16_t val);
int nas_get_signal_strength_req_get_mask(struct nas_get_signal_strength_req *get_signal_strength_req, uint16_t *val);

/*
 * nas_get_signal_strength_resp message
 */
struct nas_get_signal_strength_resp *nas_get_signal_strength_resp_alloc(unsigned txn);
struct nas_get_signal_strength_resp *nas_get_signal_strength_resp_parse(void *buf, size_t len);
void *nas_get_signal_strength_resp_encode(struct nas_get_signal_strength_resp *get_signal_strength_resp, size_t *len);
void nas_get_signal_strength_resp_free(struct nas_get_signal_strength_resp *get_signal_strength_resp);

int nas_get_signal_strength_resp_set_lte_snr(struct nas_get_signal_strength_resp *get_signal_strength_resp, int16_t val);
int nas_get_signal_strength_resp_get_lte_snr(struct nas_get_signal_strength_resp *get_signal_strength_resp, int16_t *val);

int nas_get_signal_strength_resp_set_lte_rsrp(struct nas_get_signal_strength_resp *get_signal_strength_resp, int16_t val);
int nas_get_signal_strength_resp_get_lte_rsrp(struct nas_get_signal_strength_resp *get_signal_strength_resp, int16_t *val);

int nas_get_signal_strength_resp_set_strength(struct nas_get_signal_strength_resp *get_signal_strength_resp, struct nas_signal_strength *val);
struct nas_signal_strength *nas_get_signal_strength_resp_get_strength(struct nas_get_signal_strength_resp *get_signal_strength_resp);

int nas_get_signal_strength_resp_set_strength_list(struct nas_get_signal_strength_resp *get_signal_strength_resp, struct nas_signal_strength_list *val);
struct nas_signal_strength_list *nas_get_signal_strength_resp_get_strength_list(struct nas_get_signal_strength_resp *get_signal_strength_resp);

/*
 * nas_set_operating_mode_req message
 */
struct nas_set_operating_mode_req *nas_set_operating_mode_req_alloc(unsigned txn);
struct nas_set_operating_mode_req *nas_set_operating_mode_req_parse(void *buf, size_t len);
void *nas_set_operating_mode_req_encode(struct nas_set_operating_mode_req *set_operating_mode_req, size_t *len);
void nas_set_operating_mode_req_free(struct nas_set_operating_mode_req *set_operating_mode_req);

int nas_set_operating_mode_req_set_mode(struct nas_set_operating_mode_req *set_operating_mode_req, uint8_t val);
int nas_set_operating_mode_req_get_mode(struct nas_set_operating_mode_req *set_operating_mode_req, uint8_t *val);

/*
 * nas_set_operating_mode_resp message
 */
struct nas_set_operating_mode_resp *nas_set_operating_mode_resp_alloc(unsigned txn);
struct nas_set_operating_mode_resp *nas_set_operating_mode_resp_parse(void *buf, size_t len);
void *nas_set_operating_mode_resp_encode(struct nas_set_operating_mode_resp *set_operating_mode_resp, size_t *len);
void nas_set_operating_mode_resp_free(struct nas_set_operating_mode_resp *set_operating_mode_resp);

#endif

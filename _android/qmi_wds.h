#ifndef __QMI_WDS_H__
#define __QMI_WDS_H__

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define get_next(_type, _sz) ({ \
	void* buf = ptr + len; \
	len += _sz; \
	if (len > buf_sz) goto err_wrong_len; \
	*(_type*)buf; \
})

struct qmi_tlv;

struct qmi_tlv *qmi_tlv_init(unsigned txn, unsigned msg_id, unsigned type);
struct qmi_tlv *qmi_tlv_init_ctl(unsigned txn, unsigned msg_id, unsigned type);
struct qmi_tlv *qmi_tlv_decode(void *buf, size_t len, unsigned *txn, unsigned type);
struct qmi_tlv *qmi_tlv_decode_ctl(void *buf, size_t len, unsigned *txn, unsigned type);
void *qmi_tlv_encode(struct qmi_tlv *tlv, size_t *len);
void *qmi_tlv_encode_ctl(struct qmi_tlv *tlv, size_t *len);
void qmi_tlv_free(struct qmi_tlv *tlv);

void *qmi_tlv_get(struct qmi_tlv *tlv, unsigned id, size_t *len);
void *qmi_tlv_get_array(struct qmi_tlv *tlv, unsigned id, unsigned len_size, size_t *len, size_t *size);
int qmi_tlv_set(struct qmi_tlv *tlv, unsigned id, void *buf, size_t len);
int qmi_tlv_set_array(struct qmi_tlv *tlv, unsigned id, unsigned len_size, void *buf, size_t len, size_t size);

#define QMI_WDS_SERVICE 1
#define QMI_WDS_START_NETWORK_INTERFACE 32
#define QMI_WDS_PKT_SRVC_STATUS 34
#define QMI_WDS_GET_CURRENT_SETTINGS 45
#define QMI_WDS_BIND_MUX_DATA_PORT 162
#define QMI_WDS_BIND_SUBSCRIPTION 175

struct wds_qmi_result {
	uint16_t result;
	uint16_t error;
};

struct wds_ep_type_iface_id {
	uint32_t ep_type;
	uint32_t iface_id;
};

struct wds_pkt_srvc_status {
	uint8_t connection_status;
	uint8_t reconfiguration_required;
};

struct wds_call_end_reason_ext {
	uint16_t call_end_reason_type;
	uint16_t call_end_reason;
};

struct wds_start_network_interface_req;
struct wds_start_network_interface_resp;
struct wds_get_pkt_srvc_status_ind;
struct wds_get_current_settings_req;
struct wds_get_current_settings_resp;
struct wds_bind_mux_data_port_req;
struct wds_bind_mux_data_port_resp;
struct wds_bind_subscription_req;
struct wds_bind_subscription_resp;

/*
 * wds_start_network_interface_req message
 */
struct wds_start_network_interface_req *wds_start_network_interface_req_alloc(unsigned txn);
struct wds_start_network_interface_req *wds_start_network_interface_req_parse(void *buf, size_t len, unsigned *txn);
void *wds_start_network_interface_req_encode(struct wds_start_network_interface_req *start_network_interface_req, size_t *len);
void wds_start_network_interface_req_free(struct wds_start_network_interface_req *start_network_interface_req);

int wds_start_network_interface_req_set_apn_name(struct wds_start_network_interface_req *start_network_interface_req, char *buf, size_t len);
int wds_start_network_interface_req_get_apn_name(struct wds_start_network_interface_req *start_network_interface_req, char *buf, size_t buflen);

int wds_start_network_interface_req_set_apn_type(struct wds_start_network_interface_req *start_network_interface_req, uint32_t val);
int wds_start_network_interface_req_get_apn_type(struct wds_start_network_interface_req *start_network_interface_req, uint32_t *val);

int wds_start_network_interface_req_set_ip_family_preference(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val);
int wds_start_network_interface_req_get_ip_family_preference(struct wds_start_network_interface_req *start_network_interface_req, uint8_t *val);

int wds_start_network_interface_req_set_ep_type(struct wds_start_network_interface_req *start_network_interface_req, struct wds_ep_type_iface_id *val);
struct wds_ep_type_iface_id *wds_start_network_interface_req_get_ep_type(struct wds_start_network_interface_req *start_network_interface_req);

int wds_start_network_interface_req_set_bring_up_by_apn_name(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val);
int wds_start_network_interface_req_get_bring_up_by_apn_name(struct wds_start_network_interface_req *start_network_interface_req, uint8_t *val);

int wds_start_network_interface_req_set_call_type(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val);
int wds_start_network_interface_req_get_call_type(struct wds_start_network_interface_req *start_network_interface_req, uint8_t *val);

int wds_start_network_interface_req_set_profile_index(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val);
int wds_start_network_interface_req_get_profile_index(struct wds_start_network_interface_req *start_network_interface_req, uint8_t *val);

/*
 * wds_start_network_interface_resp message
 */
struct wds_start_network_interface_resp *wds_start_network_interface_resp_alloc(unsigned txn);
struct wds_start_network_interface_resp *wds_start_network_interface_resp_parse(void *buf, size_t len, unsigned *txn);
void *wds_start_network_interface_resp_encode(struct wds_start_network_interface_resp *start_network_interface_resp, size_t *len);
void wds_start_network_interface_resp_free(struct wds_start_network_interface_resp *start_network_interface_resp);

int wds_start_network_interface_resp_set_r(struct wds_start_network_interface_resp *start_network_interface_resp, struct wds_qmi_result *val);
struct wds_qmi_result *wds_start_network_interface_resp_get_r(struct wds_start_network_interface_resp *start_network_interface_resp);

int wds_start_network_interface_resp_set_pkt_data_handle(struct wds_start_network_interface_resp *start_network_interface_resp, uint32_t val);
int wds_start_network_interface_resp_get_pkt_data_handle(struct wds_start_network_interface_resp *start_network_interface_resp, uint32_t *val);

int wds_start_network_interface_resp_set_call_end_reason(struct wds_start_network_interface_resp *start_network_interface_resp, uint16_t val);
int wds_start_network_interface_resp_get_call_end_reason(struct wds_start_network_interface_resp *start_network_interface_resp, uint16_t *val);

int wds_start_network_interface_resp_set_ext(struct wds_start_network_interface_resp *start_network_interface_resp, struct wds_call_end_reason_ext *val);
struct wds_call_end_reason_ext *wds_start_network_interface_resp_get_ext(struct wds_start_network_interface_resp *start_network_interface_resp);

/*
 * wds_get_pkt_srvc_status_ind message
 */
struct wds_get_pkt_srvc_status_ind *wds_get_pkt_srvc_status_ind_alloc(unsigned txn);
struct wds_get_pkt_srvc_status_ind *wds_get_pkt_srvc_status_ind_parse(void *buf, size_t len, unsigned *txn);
void *wds_get_pkt_srvc_status_ind_encode(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, size_t *len);
void wds_get_pkt_srvc_status_ind_free(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind);

int wds_get_pkt_srvc_status_ind_set_status(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, struct wds_pkt_srvc_status *val);
struct wds_pkt_srvc_status *wds_get_pkt_srvc_status_ind_get_status(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind);

int wds_get_pkt_srvc_status_ind_set_ip_family(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint8_t val);
int wds_get_pkt_srvc_status_ind_get_ip_family(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint8_t *val);

int wds_get_pkt_srvc_status_ind_set_tech_name(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint16_t val);
int wds_get_pkt_srvc_status_ind_get_tech_name(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint16_t *val);

int wds_get_pkt_srvc_status_ind_set_xlat_capable(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint8_t val);
int wds_get_pkt_srvc_status_ind_get_xlat_capable(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint8_t *val);

/*
 * wds_get_current_settings_req message
 */
struct wds_get_current_settings_req *wds_get_current_settings_req_alloc(unsigned txn);
struct wds_get_current_settings_req *wds_get_current_settings_req_parse(void *buf, size_t len, unsigned *txn);
void *wds_get_current_settings_req_encode(struct wds_get_current_settings_req *get_current_settings_req, size_t *len);
void wds_get_current_settings_req_free(struct wds_get_current_settings_req *get_current_settings_req);

int wds_get_current_settings_req_set_requested_settings(struct wds_get_current_settings_req *get_current_settings_req, uint32_t val);
int wds_get_current_settings_req_get_requested_settings(struct wds_get_current_settings_req *get_current_settings_req, uint32_t *val);

/*
 * wds_get_current_settings_resp message
 */
struct wds_get_current_settings_resp *wds_get_current_settings_resp_alloc(unsigned txn);
struct wds_get_current_settings_resp *wds_get_current_settings_resp_parse(void *buf, size_t len, unsigned *txn);
void *wds_get_current_settings_resp_encode(struct wds_get_current_settings_resp *get_current_settings_resp, size_t *len);
void wds_get_current_settings_resp_free(struct wds_get_current_settings_resp *get_current_settings_resp);

int wds_get_current_settings_resp_set_r(struct wds_get_current_settings_resp *get_current_settings_resp, struct wds_qmi_result *val);
struct wds_qmi_result *wds_get_current_settings_resp_get_r(struct wds_get_current_settings_resp *get_current_settings_resp);

int wds_get_current_settings_resp_set_ipv4_address_preference(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t val);
int wds_get_current_settings_resp_get_ipv4_address_preference(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t *val);

int wds_get_current_settings_resp_set_ipv4_gateway_addr(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t val);
int wds_get_current_settings_resp_get_ipv4_gateway_addr(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t *val);

int wds_get_current_settings_resp_set_ipv4_subnet_mask(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t val);
int wds_get_current_settings_resp_get_ipv4_subnet_mask(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t *val);

int wds_get_current_settings_resp_set_mtu(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t val);
int wds_get_current_settings_resp_get_mtu(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t *val);

int wds_get_current_settings_resp_set_ip_family(struct wds_get_current_settings_resp *get_current_settings_resp, uint8_t val);
int wds_get_current_settings_resp_get_ip_family(struct wds_get_current_settings_resp *get_current_settings_resp, uint8_t *val);

/*
 * wds_bind_mux_data_port_req message
 */
struct wds_bind_mux_data_port_req *wds_bind_mux_data_port_req_alloc(unsigned txn);
struct wds_bind_mux_data_port_req *wds_bind_mux_data_port_req_parse(void *buf, size_t len, unsigned *txn);
void *wds_bind_mux_data_port_req_encode(struct wds_bind_mux_data_port_req *bind_mux_data_port_req, size_t *len);
void wds_bind_mux_data_port_req_free(struct wds_bind_mux_data_port_req *bind_mux_data_port_req);

int wds_bind_mux_data_port_req_set_ep_id(struct wds_bind_mux_data_port_req *bind_mux_data_port_req, struct wds_ep_type_iface_id *val);
struct wds_ep_type_iface_id *wds_bind_mux_data_port_req_get_ep_id(struct wds_bind_mux_data_port_req *bind_mux_data_port_req);

int wds_bind_mux_data_port_req_set_mux_id(struct wds_bind_mux_data_port_req *bind_mux_data_port_req, uint8_t val);
int wds_bind_mux_data_port_req_get_mux_id(struct wds_bind_mux_data_port_req *bind_mux_data_port_req, uint8_t *val);

/*
 * wds_bind_mux_data_port_resp message
 */
struct wds_bind_mux_data_port_resp *wds_bind_mux_data_port_resp_alloc(unsigned txn);
struct wds_bind_mux_data_port_resp *wds_bind_mux_data_port_resp_parse(void *buf, size_t len, unsigned *txn);
void *wds_bind_mux_data_port_resp_encode(struct wds_bind_mux_data_port_resp *bind_mux_data_port_resp, size_t *len);
void wds_bind_mux_data_port_resp_free(struct wds_bind_mux_data_port_resp *bind_mux_data_port_resp);

int wds_bind_mux_data_port_resp_set_r(struct wds_bind_mux_data_port_resp *bind_mux_data_port_resp, struct wds_qmi_result *val);
struct wds_qmi_result *wds_bind_mux_data_port_resp_get_r(struct wds_bind_mux_data_port_resp *bind_mux_data_port_resp);

/*
 * wds_bind_subscription_req message
 */
struct wds_bind_subscription_req *wds_bind_subscription_req_alloc(unsigned txn);
struct wds_bind_subscription_req *wds_bind_subscription_req_parse(void *buf, size_t len, unsigned *txn);
void *wds_bind_subscription_req_encode(struct wds_bind_subscription_req *bind_subscription_req, size_t *len);
void wds_bind_subscription_req_free(struct wds_bind_subscription_req *bind_subscription_req);

int wds_bind_subscription_req_set_subscription(struct wds_bind_subscription_req *bind_subscription_req, uint32_t val);
int wds_bind_subscription_req_get_subscription(struct wds_bind_subscription_req *bind_subscription_req, uint32_t *val);

/*
 * wds_bind_subscription_resp message
 */
struct wds_bind_subscription_resp *wds_bind_subscription_resp_alloc(unsigned txn);
struct wds_bind_subscription_resp *wds_bind_subscription_resp_parse(void *buf, size_t len, unsigned *txn);
void *wds_bind_subscription_resp_encode(struct wds_bind_subscription_resp *bind_subscription_resp, size_t *len);
void wds_bind_subscription_resp_free(struct wds_bind_subscription_resp *bind_subscription_resp);

int wds_bind_subscription_resp_set_r(struct wds_bind_subscription_resp *bind_subscription_resp, struct wds_qmi_result *val);
struct wds_qmi_result *wds_bind_subscription_resp_get_r(struct wds_bind_subscription_resp *bind_subscription_resp);

#endif

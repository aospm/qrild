#ifndef __QMI_WDS_H__
#define __QMI_WDS_H__

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

#define QMI_WDS_SERVICE 1
#define QMI_WDS_START_NETWORK_INTERFACE 32
#define QMI_WDS_PKT_SRVC_STATUS 34
#define QMI_WDS_GET_CURRENT_SETTINGS 45
#define QMI_WDS_BIND_MUX_DATA_PORT 162
#define QMI_WDS_BIND_SUBSCRIPTION 175
#define QMI_WDS_CONNECTION_STATUS_UNKNOWN 0
#define QMI_WDS_CONNECTION_STATUS_DISCONNECTED 1
#define QMI_WDS_CONNECTION_STATUS_CONNECTED 2
#define QMI_WDS_CONNECTION_STATUS_SUSPENDED 3
#define QMI_WDS_CONNECTION_STATUS_AUTHENTICATING 4

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


#define QMI_NUM_MESSAGES_WDS 9
extern const struct qmi_tlv_msg_name wds_msg_name_map[9];

/*
 * wds_start_network_interface_req message
 */

struct wds_start_network_interface_req_data {
	bool apn_name_valid;
	char *apn_name;
	bool apn_type_valid;
	uint32_t apn_type;
	bool ip_family_preference_valid;
	uint8_t ip_family_preference;
	bool ep_type_valid;
	struct wds_ep_type_iface_id *ep_type;
	bool bring_up_by_apn_name_valid;
	uint8_t bring_up_by_apn_name;
	bool call_type_valid;
	uint8_t call_type;
	bool profile_index_valid;
	uint8_t profile_index;
};

struct wds_start_network_interface_req *wds_start_network_interface_req_alloc(unsigned txn);
void *wds_start_network_interface_req_encode(struct wds_start_network_interface_req *start_network_interface_req, size_t *len);
void wds_start_network_interface_req_free(struct wds_start_network_interface_req *start_network_interface_req);

int wds_start_network_interface_req_set_apn_name(struct wds_start_network_interface_req *start_network_interface_req, char *buf, size_t len);
int wds_start_network_interface_req_set_apn_type(struct wds_start_network_interface_req *start_network_interface_req, uint32_t val);
int wds_start_network_interface_req_set_ip_family_preference(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val);
int wds_start_network_interface_req_set_ep_type(struct wds_start_network_interface_req *start_network_interface_req, struct wds_ep_type_iface_id *val);

int wds_start_network_interface_req_set_bring_up_by_apn_name(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val);
int wds_start_network_interface_req_set_call_type(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val);
int wds_start_network_interface_req_set_profile_index(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val);
/*
 * wds_start_network_interface_resp message
 */

struct wds_start_network_interface_resp_data {
	struct qmi_response_type_v01 *res;
	uint32_t pkt_data_handle;
	bool call_end_reason_valid;
	uint16_t call_end_reason;
	bool ext_valid;
	struct wds_call_end_reason_ext *ext;
};

struct wds_start_network_interface_resp *wds_start_network_interface_resp_parse(void *buf, size_t len);
void wds_start_network_interface_resp_getall(struct wds_start_network_interface_resp *start_network_interface_resp, struct wds_start_network_interface_resp_data *data);
void wds_start_network_interface_resp_data_free(struct wds_start_network_interface_resp_data *data);
void wds_start_network_interface_resp_free(struct wds_start_network_interface_resp *start_network_interface_resp);

int wds_start_network_interface_resp_get_pkt_data_handle(struct wds_start_network_interface_resp *start_network_interface_resp, uint32_t *val);

int wds_start_network_interface_resp_get_call_end_reason(struct wds_start_network_interface_resp *start_network_interface_resp, uint16_t *val);

struct wds_call_end_reason_ext *wds_start_network_interface_resp_get_ext(struct wds_start_network_interface_resp *start_network_interface_resp);
void wds_call_end_reason_ext_free(struct wds_call_end_reason_ext *val);

/*
 * wds_get_pkt_srvc_status_ind message
 */

struct wds_get_pkt_srvc_status_ind_data {
	struct wds_pkt_srvc_status *status;
	bool ip_family_valid;
	uint8_t ip_family;
	bool tech_name_valid;
	uint16_t tech_name;
	bool xlat_capable_valid;
	uint8_t xlat_capable;
};

struct wds_get_pkt_srvc_status_ind *wds_get_pkt_srvc_status_ind_parse(void *buf, size_t len);
void wds_get_pkt_srvc_status_ind_getall(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, struct wds_get_pkt_srvc_status_ind_data *data);
void wds_get_pkt_srvc_status_ind_data_free(struct wds_get_pkt_srvc_status_ind_data *data);
struct wds_get_pkt_srvc_status_ind *wds_get_pkt_srvc_status_ind_alloc(unsigned txn);
void *wds_get_pkt_srvc_status_ind_encode(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, size_t *len);
void wds_get_pkt_srvc_status_ind_free(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind);

int wds_get_pkt_srvc_status_ind_set_status(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, struct wds_pkt_srvc_status *val);
struct wds_pkt_srvc_status *wds_get_pkt_srvc_status_ind_get_status(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind);
void wds_pkt_srvc_status_free(struct wds_pkt_srvc_status *val);

int wds_get_pkt_srvc_status_ind_set_ip_family(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint8_t val);
int wds_get_pkt_srvc_status_ind_get_ip_family(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint8_t *val);

int wds_get_pkt_srvc_status_ind_set_tech_name(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint16_t val);
int wds_get_pkt_srvc_status_ind_get_tech_name(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint16_t *val);

int wds_get_pkt_srvc_status_ind_set_xlat_capable(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint8_t val);
int wds_get_pkt_srvc_status_ind_get_xlat_capable(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint8_t *val);

/*
 * wds_get_current_settings_req message
 */

struct wds_get_current_settings_req_data {
	bool requested_settings_valid;
	uint32_t requested_settings;
};

struct wds_get_current_settings_req *wds_get_current_settings_req_alloc(unsigned txn);
void *wds_get_current_settings_req_encode(struct wds_get_current_settings_req *get_current_settings_req, size_t *len);
void wds_get_current_settings_req_free(struct wds_get_current_settings_req *get_current_settings_req);

int wds_get_current_settings_req_set_requested_settings(struct wds_get_current_settings_req *get_current_settings_req, uint32_t val);
/*
 * wds_get_current_settings_resp message
 */

struct wds_get_current_settings_resp_data {
	struct qmi_response_type_v01 *res;
	bool ipv4_address_preference_valid;
	uint32_t ipv4_address_preference;
	bool ipv4_gateway_addr_valid;
	uint32_t ipv4_gateway_addr;
	bool ipv4_subnet_mask_valid;
	uint32_t ipv4_subnet_mask;
	bool mtu_valid;
	uint32_t mtu;
	bool ip_family_valid;
	uint8_t ip_family;
};

struct wds_get_current_settings_resp *wds_get_current_settings_resp_parse(void *buf, size_t len);
void wds_get_current_settings_resp_getall(struct wds_get_current_settings_resp *get_current_settings_resp, struct wds_get_current_settings_resp_data *data);
void wds_get_current_settings_resp_data_free(struct wds_get_current_settings_resp_data *data);
void wds_get_current_settings_resp_free(struct wds_get_current_settings_resp *get_current_settings_resp);

int wds_get_current_settings_resp_get_ipv4_address_preference(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t *val);

int wds_get_current_settings_resp_get_ipv4_gateway_addr(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t *val);

int wds_get_current_settings_resp_get_ipv4_subnet_mask(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t *val);

int wds_get_current_settings_resp_get_mtu(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t *val);

int wds_get_current_settings_resp_get_ip_family(struct wds_get_current_settings_resp *get_current_settings_resp, uint8_t *val);

/*
 * wds_bind_mux_data_port_req message
 */

struct wds_bind_mux_data_port_req_data {
	bool ep_id_valid;
	struct wds_ep_type_iface_id *ep_id;
	bool mux_id_valid;
	uint8_t mux_id;
};

struct wds_bind_mux_data_port_req *wds_bind_mux_data_port_req_alloc(unsigned txn);
void *wds_bind_mux_data_port_req_encode(struct wds_bind_mux_data_port_req *bind_mux_data_port_req, size_t *len);
void wds_bind_mux_data_port_req_free(struct wds_bind_mux_data_port_req *bind_mux_data_port_req);

int wds_bind_mux_data_port_req_set_ep_id(struct wds_bind_mux_data_port_req *bind_mux_data_port_req, struct wds_ep_type_iface_id *val);

int wds_bind_mux_data_port_req_set_mux_id(struct wds_bind_mux_data_port_req *bind_mux_data_port_req, uint8_t val);
/*
 * wds_bind_mux_data_port_resp message
 */

struct wds_bind_mux_data_port_resp_data {
	struct qmi_response_type_v01 *res;
};

struct wds_bind_mux_data_port_resp *wds_bind_mux_data_port_resp_parse(void *buf, size_t len);
void wds_bind_mux_data_port_resp_getall(struct wds_bind_mux_data_port_resp *bind_mux_data_port_resp, struct wds_bind_mux_data_port_resp_data *data);
void wds_bind_mux_data_port_resp_data_free(struct wds_bind_mux_data_port_resp_data *data);
void wds_bind_mux_data_port_resp_free(struct wds_bind_mux_data_port_resp *bind_mux_data_port_resp);

/*
 * wds_bind_subscription_req message
 */

struct wds_bind_subscription_req_data {
	bool subscription_valid;
	uint32_t subscription;
};

struct wds_bind_subscription_req *wds_bind_subscription_req_alloc(unsigned txn);
void *wds_bind_subscription_req_encode(struct wds_bind_subscription_req *bind_subscription_req, size_t *len);
void wds_bind_subscription_req_free(struct wds_bind_subscription_req *bind_subscription_req);

int wds_bind_subscription_req_set_subscription(struct wds_bind_subscription_req *bind_subscription_req, uint32_t val);
/*
 * wds_bind_subscription_resp message
 */

struct wds_bind_subscription_resp_data {
	struct qmi_response_type_v01 *res;
};

struct wds_bind_subscription_resp *wds_bind_subscription_resp_parse(void *buf, size_t len);
void wds_bind_subscription_resp_getall(struct wds_bind_subscription_resp *bind_subscription_resp, struct wds_bind_subscription_resp_data *data);
void wds_bind_subscription_resp_data_free(struct wds_bind_subscription_resp_data *data);
void wds_bind_subscription_resp_free(struct wds_bind_subscription_resp *bind_subscription_resp);

#ifdef __cplusplus
}
#endif

#endif

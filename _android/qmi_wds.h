#ifndef __QMI_WDS_H__
#define __QMI_WDS_H__

#include <stdint.h>
#include <stdbool.h>

#include "libqrtr.h"

extern struct qmi_elem_info wds_start_network_interface_req_ei[];
extern struct qmi_elem_info wds_start_network_interface_resp_ei[];
extern struct qmi_elem_info wds_get_pkt_srvc_status_ind_ei[];
extern struct qmi_elem_info wds_get_current_settings_req_ei[];
extern struct qmi_elem_info wds_get_current_settings_resp_ei[];
extern struct qmi_elem_info wds_bind_mux_data_port_req_ei[];
extern struct qmi_elem_info wds_bind_mux_data_port_resp_ei[];
extern struct qmi_elem_info wds_bind_subscription_req_ei[];
extern struct qmi_elem_info wds_bind_subscription_resp_ei[];

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

struct wds_start_network_interface_req { // 0x0020
	struct qmi_message_header header;
	uint32_t apn_name_len;
	char apn_name[256]; // 0x14
	bool apn_type_valid;
	uint32_t apn_type;  // 0x38
	bool ip_family_preference_valid;
	uint8_t ip_family_preference;  // 0x19
	bool ep_type_valid;
	struct wds_ep_type_iface_id ep_type;  // 0x3b
	bool bring_up_by_apn_name_valid;
	uint8_t bring_up_by_apn_name;  // 0x3c
	bool call_type_valid;
	uint8_t call_type;  // 0x35
	bool profile_index_valid;
	uint8_t profile_index;  // 0x31
};

struct wds_start_network_interface_resp { // 0x0020
	struct qmi_message_header header;
	struct qmi_response_type_v01 res;  // 0x02
	uint32_t pkt_data_handle;  // 0x01
	bool call_end_reason_valid;
	uint16_t call_end_reason;  // 0x10
	bool ext_valid;
	struct wds_call_end_reason_ext ext;  // 0x11
};

struct wds_get_pkt_srvc_status_ind { // 0x0022
	struct qmi_message_header header;
	struct wds_pkt_srvc_status status;  // 0x01
	bool ip_family_valid;
	uint8_t ip_family;  // 0x12
	bool tech_name_valid;
	uint16_t tech_name;  // 0x13
	bool xlat_capable_valid;
	uint8_t xlat_capable;  // 0x15
};

struct wds_get_current_settings_req { // 0x002d
	struct qmi_message_header header;
	bool requested_settings_valid;
	uint32_t requested_settings;  // 0x10
};

struct wds_get_current_settings_resp { // 0x002d
	struct qmi_message_header header;
	struct qmi_response_type_v01 res;  // 0x02
	bool ipv4_address_preference_valid;
	uint32_t ipv4_address_preference;  // 0x1e
	bool ipv4_gateway_addr_valid;
	uint32_t ipv4_gateway_addr;  // 0x20
	bool ipv4_subnet_mask_valid;
	uint32_t ipv4_subnet_mask;  // 0x21
	bool mtu_valid;
	uint32_t mtu;  // 0x29
	bool ip_family_valid;
	uint8_t ip_family;  // 0x2b
};

struct wds_bind_mux_data_port_req { // 0x00a2
	struct qmi_message_header header;
	bool ep_id_valid;
	struct wds_ep_type_iface_id ep_id;  // 0x10
	bool mux_id_valid;
	uint8_t mux_id;  // 0x11
};

struct wds_bind_mux_data_port_resp { // 0x00a2
	struct qmi_message_header header;
	struct qmi_response_type_v01 res;  // 0x02
};

struct wds_bind_subscription_req { // 0x00af
	struct qmi_message_header header;
	bool subscription_valid;
	uint32_t subscription;  // 0x01
};

struct wds_bind_subscription_resp { // 0x00af
	struct qmi_message_header header;
	struct qmi_response_type_v01 res;  // 0x02
};

#define WDS_START_NETWORK_INTERFACE_REQ_NEW ({ \
	struct wds_start_network_interface_req *ptr = malloc(sizeof(struct wds_start_network_interface_req)); \
	ptr->qmi_header->type = 0; \
	ptr->qmi_header->msg_id = 0x0020; \
	ptr->qmi_header->service = 0x00; \
	ptr->ei = &wds_start_network_interface_req_ei; ptr })
#define WDS_START_NETWORK_INTERFACE_REQ_INITIALIZER { { 0, 0, 0x0020, 0 }, &wds_start_network_interface_req_ei, "start_network_interface_req", 0, NULL, 0, 0, {}, 0, 0, 0 }
#define WDS_START_NETWORK_INTERFACE_RESP_NEW ({ \
	struct wds_start_network_interface_resp *ptr = malloc(sizeof(struct wds_start_network_interface_resp)); \
	ptr->qmi_header->type = 2; \
	ptr->qmi_header->msg_id = 0x0020; \
	ptr->qmi_header->service = 0x00; \
	ptr->ei = &wds_start_network_interface_resp_ei; ptr })
#define WDS_START_NETWORK_INTERFACE_RESP_INITIALIZER { { 2, 0, 0x0020, 0 }, &wds_start_network_interface_resp_ei, "start_network_interface_resp", {}, 0, 0, {} }
#define WDS_GET_PKT_SRVC_STATUS_IND_NEW ({ \
	struct wds_get_pkt_srvc_status_ind *ptr = malloc(sizeof(struct wds_get_pkt_srvc_status_ind)); \
	ptr->qmi_header->type = 4; \
	ptr->qmi_header->msg_id = 0x0022; \
	ptr->qmi_header->service = 0x00; \
	ptr->ei = &wds_get_pkt_srvc_status_ind_ei; ptr })
#define WDS_GET_PKT_SRVC_STATUS_IND_INITIALIZER { { 4, 0, 0x0022, 0 }, &wds_get_pkt_srvc_status_ind_ei, "get_pkt_srvc_status_ind", {}, 0, 0, 0 }
#define WDS_GET_CURRENT_SETTINGS_REQ_NEW ({ \
	struct wds_get_current_settings_req *ptr = malloc(sizeof(struct wds_get_current_settings_req)); \
	ptr->qmi_header->type = 0; \
	ptr->qmi_header->msg_id = 0x002d; \
	ptr->qmi_header->service = 0x00; \
	ptr->ei = &wds_get_current_settings_req_ei; ptr })
#define WDS_GET_CURRENT_SETTINGS_REQ_INITIALIZER { { 0, 0, 0x002d, 0 }, &wds_get_current_settings_req_ei, "get_current_settings_req", 0 }
#define WDS_GET_CURRENT_SETTINGS_RESP_NEW ({ \
	struct wds_get_current_settings_resp *ptr = malloc(sizeof(struct wds_get_current_settings_resp)); \
	ptr->qmi_header->type = 2; \
	ptr->qmi_header->msg_id = 0x002d; \
	ptr->qmi_header->service = 0x00; \
	ptr->ei = &wds_get_current_settings_resp_ei; ptr })
#define WDS_GET_CURRENT_SETTINGS_RESP_INITIALIZER { { 2, 0, 0x002d, 0 }, &wds_get_current_settings_resp_ei, "get_current_settings_resp", {}, 0, 0, 0, 0, 0 }
#define WDS_BIND_MUX_DATA_PORT_REQ_NEW ({ \
	struct wds_bind_mux_data_port_req *ptr = malloc(sizeof(struct wds_bind_mux_data_port_req)); \
	ptr->qmi_header->type = 0; \
	ptr->qmi_header->msg_id = 0x00a2; \
	ptr->qmi_header->service = 0x00; \
	ptr->ei = &wds_bind_mux_data_port_req_ei; ptr })
#define WDS_BIND_MUX_DATA_PORT_REQ_INITIALIZER { { 0, 0, 0x00a2, 0 }, &wds_bind_mux_data_port_req_ei, "bind_mux_data_port_req", {}, 0 }
#define WDS_BIND_MUX_DATA_PORT_RESP_NEW ({ \
	struct wds_bind_mux_data_port_resp *ptr = malloc(sizeof(struct wds_bind_mux_data_port_resp)); \
	ptr->qmi_header->type = 2; \
	ptr->qmi_header->msg_id = 0x00a2; \
	ptr->qmi_header->service = 0x00; \
	ptr->ei = &wds_bind_mux_data_port_resp_ei; ptr })
#define WDS_BIND_MUX_DATA_PORT_RESP_INITIALIZER { { 2, 0, 0x00a2, 0 }, &wds_bind_mux_data_port_resp_ei, "bind_mux_data_port_resp", {} }
#define WDS_BIND_SUBSCRIPTION_REQ_NEW ({ \
	struct wds_bind_subscription_req *ptr = malloc(sizeof(struct wds_bind_subscription_req)); \
	ptr->qmi_header->type = 0; \
	ptr->qmi_header->msg_id = 0x00af; \
	ptr->qmi_header->service = 0x00; \
	ptr->ei = &wds_bind_subscription_req_ei; ptr })
#define WDS_BIND_SUBSCRIPTION_REQ_INITIALIZER { { 0, 0, 0x00af, 0 }, &wds_bind_subscription_req_ei, "bind_subscription_req", 0 }
#define WDS_BIND_SUBSCRIPTION_RESP_NEW ({ \
	struct wds_bind_subscription_resp *ptr = malloc(sizeof(struct wds_bind_subscription_resp)); \
	ptr->qmi_header->type = 2; \
	ptr->qmi_header->msg_id = 0x00af; \
	ptr->qmi_header->service = 0x00; \
	ptr->ei = &wds_bind_subscription_resp_ei; ptr })
#define WDS_BIND_SUBSCRIPTION_RESP_INITIALIZER { { 2, 0, 0x00af, 0 }, &wds_bind_subscription_resp_ei, "bind_subscription_resp", {} }

#endif

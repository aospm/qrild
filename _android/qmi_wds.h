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

struct wds_start_network_interface_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	uint32_t apn_name_len;
	char apn_name[256];
	bool apn_type_valid;
	uint32_t apn_type;
	bool ip_family_preference_valid;
	uint8_t ip_family_preference;
	bool ep_type_valid;
	struct wds_ep_type_iface_id ep_type;
	bool bring_up_by_apn_name_valid;
	uint8_t bring_up_by_apn_name;
	bool call_type_valid;
	uint8_t call_type;
	bool profile_index_valid;
	uint8_t profile_index;
};

struct wds_start_network_interface_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct wds_qmi_response_type_v01 res;
	uint32_t pkt_data_handle;
	bool call_end_reason_valid;
	uint16_t call_end_reason;
	bool ext_valid;
	struct wds_call_end_reason_ext ext;
};

struct wds_get_pkt_srvc_status_ind {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct wds_pkt_srvc_status status;
	bool ip_family_valid;
	uint8_t ip_family;
	bool tech_name_valid;
	uint16_t tech_name;
	bool xlat_capable_valid;
	uint8_t xlat_capable;
};

struct wds_get_current_settings_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	bool requested_settings_valid;
	uint32_t requested_settings;
};

struct wds_get_current_settings_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct wds_qmi_response_type_v01 res;
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

struct wds_bind_mux_data_port_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	bool ep_id_valid;
	struct wds_ep_type_iface_id ep_id;
	bool mux_id_valid;
	uint8_t mux_id;
};

struct wds_bind_mux_data_port_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct wds_qmi_response_type_v01 res;
};

struct wds_bind_subscription_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	bool subscription_valid;
	uint32_t subscription;
};

struct wds_bind_subscription_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct wds_qmi_response_type_v01 res;
};

#define WDS_START_NETWORK_INTERFACE_REQ_NEW ({ \
	struct wds_start_network_interface_req *ptr = malloc(sizeof(struct wds_start_network_interface_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x0020; \
	ptr->ei = &wds_start_network_interface_req_ei; ptr })
#define WDS_START_NETWORK_INTERFACE_REQ_INITIALIZER { { 0, 0, 0x0020, 0 }, &wds_start_network_interface_req_ei, 0, NULL, 0, 0, {}, 0, 0, 0 }
#define WDS_START_NETWORK_INTERFACE_RESP_NEW ({ \
	struct wds_start_network_interface_resp *ptr = malloc(sizeof(struct wds_start_network_interface_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0020; \
	ptr->ei = &wds_start_network_interface_resp_ei; ptr })
#define WDS_START_NETWORK_INTERFACE_RESP_INITIALIZER { { 2, 0, 0x0020, 0 }, &wds_start_network_interface_resp_ei, {}, 0, 0, {} }
#define WDS_GET_PKT_SRVC_STATUS_IND_NEW ({ \
	struct wds_get_pkt_srvc_status_ind *ptr = malloc(sizeof(struct wds_get_pkt_srvc_status_ind)); \
	ptr->qmi_header->type = 4; ptr->qmi_header->msg_id = 0x0022; \
	ptr->ei = &wds_get_pkt_srvc_status_ind_ei; ptr })
#define WDS_GET_PKT_SRVC_STATUS_IND_INITIALIZER { { 4, 0, 0x0022, 0 }, &wds_get_pkt_srvc_status_ind_ei, {}, 0, 0, 0 }
#define WDS_GET_CURRENT_SETTINGS_REQ_NEW ({ \
	struct wds_get_current_settings_req *ptr = malloc(sizeof(struct wds_get_current_settings_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x002d; \
	ptr->ei = &wds_get_current_settings_req_ei; ptr })
#define WDS_GET_CURRENT_SETTINGS_REQ_INITIALIZER { { 0, 0, 0x002d, 0 }, &wds_get_current_settings_req_ei, 0 }
#define WDS_GET_CURRENT_SETTINGS_RESP_NEW ({ \
	struct wds_get_current_settings_resp *ptr = malloc(sizeof(struct wds_get_current_settings_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x002d; \
	ptr->ei = &wds_get_current_settings_resp_ei; ptr })
#define WDS_GET_CURRENT_SETTINGS_RESP_INITIALIZER { { 2, 0, 0x002d, 0 }, &wds_get_current_settings_resp_ei, {}, 0, 0, 0, 0, 0 }
#define WDS_BIND_MUX_DATA_PORT_REQ_NEW ({ \
	struct wds_bind_mux_data_port_req *ptr = malloc(sizeof(struct wds_bind_mux_data_port_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x00a2; \
	ptr->ei = &wds_bind_mux_data_port_req_ei; ptr })
#define WDS_BIND_MUX_DATA_PORT_REQ_INITIALIZER { { 0, 0, 0x00a2, 0 }, &wds_bind_mux_data_port_req_ei, {}, 0 }
#define WDS_BIND_MUX_DATA_PORT_RESP_NEW ({ \
	struct wds_bind_mux_data_port_resp *ptr = malloc(sizeof(struct wds_bind_mux_data_port_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x00a2; \
	ptr->ei = &wds_bind_mux_data_port_resp_ei; ptr })
#define WDS_BIND_MUX_DATA_PORT_RESP_INITIALIZER { { 2, 0, 0x00a2, 0 }, &wds_bind_mux_data_port_resp_ei, {} }
#define WDS_BIND_SUBSCRIPTION_REQ_NEW ({ \
	struct wds_bind_subscription_req *ptr = malloc(sizeof(struct wds_bind_subscription_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x00af; \
	ptr->ei = &wds_bind_subscription_req_ei; ptr })
#define WDS_BIND_SUBSCRIPTION_REQ_INITIALIZER { { 0, 0, 0x00af, 0 }, &wds_bind_subscription_req_ei, 0 }
#define WDS_BIND_SUBSCRIPTION_RESP_NEW ({ \
	struct wds_bind_subscription_resp *ptr = malloc(sizeof(struct wds_bind_subscription_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x00af; \
	ptr->ei = &wds_bind_subscription_resp_ei; ptr })
#define WDS_BIND_SUBSCRIPTION_RESP_INITIALIZER { { 2, 0, 0x00af, 0 }, &wds_bind_subscription_resp_ei, {} }

#endif

#include <errno.h>
#include <string.h>
#include "qmi_wds.h"

struct qmi_elem_info wds_ep_type_iface_id_ei[] = {
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct wds_ep_type_iface_id, ep_type),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct wds_ep_type_iface_id, iface_id),
	},
	{}
};

struct qmi_elem_info wds_pkt_srvc_status_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wds_pkt_srvc_status, connection_status),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wds_pkt_srvc_status, reconfiguration_required),
	},
	{}
};

struct qmi_elem_info wds_call_end_reason_ext_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct wds_call_end_reason_ext, call_end_reason_type),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct wds_call_end_reason_ext, call_end_reason),
	},
	{}
};

struct qmi_elem_info wds_start_network_interface_req_ei[] = {
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 20,
		.offset = offsetof(struct wds_start_network_interface_req, apn_name)
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 56,
		.offset = offsetof(struct wds_start_network_interface_req, apn_type_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 56,
		.offset = offsetof(struct wds_start_network_interface_req, apn_type),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 25,
		.offset = offsetof(struct wds_start_network_interface_req, ip_family_preference_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 25,
		.offset = offsetof(struct wds_start_network_interface_req, ip_family_preference),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 59,
		.offset = offsetof(struct wds_start_network_interface_req, ep_type_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct wds_ep_type_iface_id),
		.tlv_type = 59,
		.offset = offsetof(struct wds_start_network_interface_req, ep_type),
		.ei_array = wds_ep_type_iface_id_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 60,
		.offset = offsetof(struct wds_start_network_interface_req, bring_up_by_apn_name_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 60,
		.offset = offsetof(struct wds_start_network_interface_req, bring_up_by_apn_name),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 53,
		.offset = offsetof(struct wds_start_network_interface_req, call_type_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 53,
		.offset = offsetof(struct wds_start_network_interface_req, call_type),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 49,
		.offset = offsetof(struct wds_start_network_interface_req, profile_index_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 49,
		.offset = offsetof(struct wds_start_network_interface_req, profile_index),
	},
	{}
};

struct qmi_elem_info wds_start_network_interface_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct wds_start_network_interface_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 1,
		.offset = offsetof(struct wds_start_network_interface_resp, pkt_data_handle),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct wds_start_network_interface_resp, call_end_reason_valid),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 16,
		.offset = offsetof(struct wds_start_network_interface_resp, call_end_reason),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct wds_start_network_interface_resp, ext_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct wds_call_end_reason_ext),
		.tlv_type = 17,
		.offset = offsetof(struct wds_start_network_interface_resp, ext),
		.ei_array = wds_call_end_reason_ext_ei,
	},
	{}
};

struct qmi_elem_info wds_get_pkt_srvc_status_ind_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct wds_pkt_srvc_status),
		.tlv_type = 1,
		.offset = offsetof(struct wds_get_pkt_srvc_status_ind, status),
		.ei_array = wds_pkt_srvc_status_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct wds_get_pkt_srvc_status_ind, ip_family_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 18,
		.offset = offsetof(struct wds_get_pkt_srvc_status_ind, ip_family),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 19,
		.offset = offsetof(struct wds_get_pkt_srvc_status_ind, tech_name_valid),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 19,
		.offset = offsetof(struct wds_get_pkt_srvc_status_ind, tech_name),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 21,
		.offset = offsetof(struct wds_get_pkt_srvc_status_ind, xlat_capable_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 21,
		.offset = offsetof(struct wds_get_pkt_srvc_status_ind, xlat_capable),
	},
	{}
};

struct qmi_elem_info wds_get_current_settings_req_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct wds_get_current_settings_req, requested_settings_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 16,
		.offset = offsetof(struct wds_get_current_settings_req, requested_settings),
	},
	{}
};

struct qmi_elem_info wds_get_current_settings_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct wds_get_current_settings_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 30,
		.offset = offsetof(struct wds_get_current_settings_resp, ipv4_address_preference_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 30,
		.offset = offsetof(struct wds_get_current_settings_resp, ipv4_address_preference),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 32,
		.offset = offsetof(struct wds_get_current_settings_resp, ipv4_gateway_addr_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 32,
		.offset = offsetof(struct wds_get_current_settings_resp, ipv4_gateway_addr),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 33,
		.offset = offsetof(struct wds_get_current_settings_resp, ipv4_subnet_mask_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 33,
		.offset = offsetof(struct wds_get_current_settings_resp, ipv4_subnet_mask),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 41,
		.offset = offsetof(struct wds_get_current_settings_resp, mtu_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 41,
		.offset = offsetof(struct wds_get_current_settings_resp, mtu),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 43,
		.offset = offsetof(struct wds_get_current_settings_resp, ip_family_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 43,
		.offset = offsetof(struct wds_get_current_settings_resp, ip_family),
	},
	{}
};

struct qmi_elem_info wds_bind_mux_data_port_req_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct wds_bind_mux_data_port_req, ep_id_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct wds_ep_type_iface_id),
		.tlv_type = 16,
		.offset = offsetof(struct wds_bind_mux_data_port_req, ep_id),
		.ei_array = wds_ep_type_iface_id_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct wds_bind_mux_data_port_req, mux_id_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 17,
		.offset = offsetof(struct wds_bind_mux_data_port_req, mux_id),
	},
	{}
};

struct qmi_elem_info wds_bind_mux_data_port_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct wds_bind_mux_data_port_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{}
};

struct qmi_elem_info wds_bind_subscription_req_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 1,
		.offset = offsetof(struct wds_bind_subscription_req, subscription_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 1,
		.offset = offsetof(struct wds_bind_subscription_req, subscription),
	},
	{}
};

struct qmi_elem_info wds_bind_subscription_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct wds_bind_subscription_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{}
};


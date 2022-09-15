#include <errno.h>
#include <string.h>
#include "qmi_wda.h"

struct qmi_elem_info wda_ep_type_iface_id_ei[] = {
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct wda_ep_type_iface_id, ep_type),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct wda_ep_type_iface_id, iface_id),
	},
	{}
};

struct qmi_elem_info wda_set_data_format_req_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct wda_set_data_format_req, link_prot_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 17,
		.offset = offsetof(struct wda_set_data_format_req, link_prot),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct wda_set_data_format_req, ul_data_aggregation_protocol_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 18,
		.offset = offsetof(struct wda_set_data_format_req, ul_data_aggregation_protocol),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 19,
		.offset = offsetof(struct wda_set_data_format_req, dl_data_aggregation_protocol_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 19,
		.offset = offsetof(struct wda_set_data_format_req, dl_data_aggregation_protocol),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 21,
		.offset = offsetof(struct wda_set_data_format_req, dl_data_aggretation_max_datagrams_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 21,
		.offset = offsetof(struct wda_set_data_format_req, dl_data_aggretation_max_datagrams),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 22,
		.offset = offsetof(struct wda_set_data_format_req, dl_data_aggregation_max_size_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 22,
		.offset = offsetof(struct wda_set_data_format_req, dl_data_aggregation_max_size),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 23,
		.offset = offsetof(struct wda_set_data_format_req, ep_type_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct wda_ep_type_iface_id),
		.tlv_type = 23,
		.offset = offsetof(struct wda_set_data_format_req, ep_type),
		.ei_array = wda_ep_type_iface_id_ei,
	},
	{}
};

struct qmi_elem_info wda_set_data_format_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct wda_set_data_format_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{}
};


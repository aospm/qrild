#include <errno.h>
#include <string.h>
#include "qmi_dpm.h"

struct qmi_elem_info dpm_control_port_ei[] = {
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct dpm_control_port, ep_type),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct dpm_control_port, iface_id),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct dpm_control_port, consumer_pipe_num),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct dpm_control_port, producer_pipe_num),
	},
	{}
};

struct qmi_elem_info dpm_open_port_req_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct dpm_open_port_req, port_list_valid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 17,
		.offset = offsetof(struct dpm_open_port_req, port_list_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct dpm_control_port),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 17,
		.offset = offsetof(struct dpm_open_port_req, port_list),
		.ei_array = dpm_control_port_ei,
	},
	{}
};

struct qmi_elem_info dpm_open_port_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct dpm_qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct dpm_open_port_resp, res),
		.ei_array = dpm_qmi_response_type_v01_ei,
	},
	{}
};


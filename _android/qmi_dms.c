#include <errno.h>
#include <string.h>
#include "qmi_dms.h"

struct qmi_elem_info dms_ids_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct dms_ids, esn_len),
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.offset = offsetof(struct dms_ids, esn)
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct dms_ids, imei_len),
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.offset = offsetof(struct dms_ids, imei)
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct dms_ids, meid_len),
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.offset = offsetof(struct dms_ids, meid)
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct dms_ids, imei_ver_len),
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.offset = offsetof(struct dms_ids, imei_ver)
	},
	{}
};

struct qmi_elem_info dms_get_revision_req_ei[] = {
	{}
};

struct qmi_elem_info dms_get_revision_resp_ei[] = {
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 1,
		.offset = offsetof(struct dms_get_revision_resp, revision)
	},
	{}
};

struct qmi_elem_info dms_get_ids_req_ei[] = {
	{}
};

struct qmi_elem_info dms_get_ids_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct dms_get_ids_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 16,
		.offset = offsetof(struct dms_get_ids_resp, esn)
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 17,
		.offset = offsetof(struct dms_get_ids_resp, imei)
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 18,
		.offset = offsetof(struct dms_get_ids_resp, meid)
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 19,
		.offset = offsetof(struct dms_get_ids_resp, imei_ver)
	},
	{}
};

struct qmi_elem_info dms_get_operating_mode_req_ei[] = {
	{}
};

struct qmi_elem_info dms_get_operating_mode_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct dms_get_operating_mode_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 1,
		.offset = offsetof(struct dms_get_operating_mode_resp, mode),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct dms_get_operating_mode_resp, offline_reason_valid),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 16,
		.offset = offsetof(struct dms_get_operating_mode_resp, offline_reason),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 17,
		.offset = offsetof(struct dms_get_operating_mode_resp, hardware_restricted),
	},
	{}
};

struct qmi_elem_info dms_set_operating_mode_req_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 1,
		.offset = offsetof(struct dms_set_operating_mode_req, mode),
	},
	{}
};

struct qmi_elem_info dms_set_operating_mode_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct dms_set_operating_mode_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{}
};

struct qmi_elem_info dms_get_msisdn_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct dms_get_msisdn, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 1,
		.offset = offsetof(struct dms_get_msisdn, msisdn)
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 17,
		.offset = offsetof(struct dms_get_msisdn, imsi)
	},
	{}
};

struct qmi_elem_info dms_uim_get_imsi_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct dms_uim_get_imsi, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 1,
		.offset = offsetof(struct dms_uim_get_imsi, imsi)
	},
	{}
};


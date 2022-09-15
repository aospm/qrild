#include <errno.h>
#include <string.h>
#include "qmi_uim.h"

struct qmi_elem_info uim_card_status_cards_applications_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, type),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, state),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, personalization_state),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, personalization_feature),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, personalization_retries),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, personalization_unblock_retries),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, application_identifier_value_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, application_identifier_value),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, upin_replaces_pin1),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, pin1_state),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, pin1_retries),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, puk1_retries),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, pin2_state),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, pin2_retries),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards_applications, puk2_retries),
	},
	{}
};

struct qmi_elem_info uim_card_status_cards_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards, card_state),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards, upin_state),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards, upin_retries),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards, upuk_retries),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards, error_code),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status_cards, applications_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 255,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(struct uim_card_status_cards),
		.offset = offsetof(struct uim_card_status_cards, applications),
		.ei_array = &uim_card_status_cards_applications_ei,
	},
	{}
};

struct qmi_elem_info uim_card_status_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_card_status, index_gw_primary),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_card_status, index_1x_primary),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_card_status, index_gw_secondary),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_card_status, index_1x_secondary),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_status, cards_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 255,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(struct uim_card_status),
		.offset = offsetof(struct uim_card_status, cards),
		.ei_array = &uim_card_status_cards_ei,
	},
	{}
};

struct qmi_elem_info uim_provisioning_session_change_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_provisioning_session_change, session_type),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_provisioning_session_change, activate),
	},
	{}
};

struct qmi_elem_info uim_provisioning_session_application_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_provisioning_session_application, slot),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_provisioning_session_application, application_identifier_value_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_provisioning_session_application, application_identifier_value),
	},
	{}
};

struct qmi_elem_info uim_physical_slot_state_slots_ei[] = {
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct uim_physical_slot_state_slots, card_state),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct uim_physical_slot_state_slots, slot_state),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_physical_slot_state_slots, logical_slot),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_physical_slot_state_slots, iccid_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_physical_slot_state_slots, iccid),
	},
	{}
};

struct qmi_elem_info uim_physical_slot_state_ei[] = {
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_physical_slot_state, slots_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 255,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(struct uim_physical_slot_state),
		.offset = offsetof(struct uim_physical_slot_state, slots),
		.ei_array = &uim_physical_slot_state_slots_ei,
	},
	{}
};

struct qmi_elem_info uim_physical_slot_info_slots_ei[] = {
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct uim_physical_slot_info_slots, card_protocol),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_physical_slot_info_slots, valid_applications),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_physical_slot_info_slots, atr_value_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_physical_slot_info_slots, atr_value),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_physical_slot_info_slots, is_euicc),
	},
	{}
};

struct qmi_elem_info uim_physical_slot_info_ei[] = {
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_physical_slot_info, slots_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 255,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(struct uim_physical_slot_info),
		.offset = offsetof(struct uim_physical_slot_info, slots),
		.ei_array = &uim_physical_slot_info_slots_ei,
	},
	{}
};

struct qmi_elem_info uim_session_t_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_session_t, type),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_session_t, aid_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_session_t, aid),
	},
	{}
};

struct qmi_elem_info uim_file_t_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_file_t, file_id),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_file_t, path_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_file_t, path),
	},
	{}
};

struct qmi_elem_info uim_read_info_t_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_read_info_t, offset),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_read_info_t, len),
	},
	{}
};

struct qmi_elem_info uim_card_res_t_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_res_t, sw1),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_card_res_t, sw2),
	},
	{}
};

struct qmi_elem_info uim_file_attrs_t_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_file_attrs_t, file_size),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_file_attrs_t, file_id),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_file_attrs_t, file_type),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_file_attrs_t, record_size),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_file_attrs_t, record_count),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_file_attrs_t, read_sec_attr_logic),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_file_attrs_t, read_sec_attrs),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_file_attrs_t, write_sec_attr_logic),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_file_attrs_t, write_sec_attrs),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_file_attrs_t, inc_sec_attr_logic),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_file_attrs_t, inc_sec_attrs),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_file_attrs_t, deactivate_sec_attr_logic),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_file_attrs_t, deactivate_sec_attrs),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_file_attrs_t, activate_sec_attr_logic),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_file_attrs_t, activate_sec_attrs),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_file_attrs_t, raw_data_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_file_attrs_t, raw_data),
	},
	{}
};

struct qmi_elem_info uim_refresh_ev_t_files_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_refresh_ev_t_files, id),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_refresh_ev_t_files, path_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_refresh_ev_t_files, path),
	},
	{}
};

struct qmi_elem_info uim_refresh_ev_t_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_refresh_ev_t, stage),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_refresh_ev_t, mode),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_refresh_ev_t, session_type),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_refresh_ev_t, aid_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct uim_refresh_ev_t, aid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct uim_refresh_ev_t, files_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 255,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(struct uim_refresh_ev_t),
		.offset = offsetof(struct uim_refresh_ev_t, files),
		.ei_array = &uim_refresh_ev_t_files_ei,
	},
	{}
};

struct qmi_elem_info uim_get_card_status_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct uim_get_card_status_resp, result),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct uim_get_card_status_resp, status_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_card_status),
		.tlv_type = 16,
		.offset = offsetof(struct uim_get_card_status_resp, status),
		.ei_array = uim_card_status_ei,
	},
	{}
};

struct qmi_elem_info uim_change_provisioning_session_req_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 1,
		.offset = offsetof(struct uim_change_provisioning_session_req, session_change_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_provisioning_session_change),
		.tlv_type = 1,
		.offset = offsetof(struct uim_change_provisioning_session_req, session_change),
		.ei_array = uim_provisioning_session_change_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct uim_change_provisioning_session_req, application_information_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_provisioning_session_application),
		.tlv_type = 16,
		.offset = offsetof(struct uim_change_provisioning_session_req, application_information),
		.ei_array = uim_provisioning_session_application_ei,
	},
	{}
};

struct qmi_elem_info uim_change_provisioning_session_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct uim_change_provisioning_session_resp, result),
		.ei_array = qmi_response_type_v01_ei,
	},
	{}
};

struct qmi_elem_info uim_icc_open_logical_channel_req_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 1,
		.offset = offsetof(struct uim_icc_open_logical_channel_req, slot),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct uim_icc_open_logical_channel_req, application_id_valid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 16,
		.offset = offsetof(struct uim_icc_open_logical_channel_req, application_id_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 32,
		.elem_size = sizeof(uint8_t),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 16,
		.offset = offsetof(struct uim_icc_open_logical_channel_req, application_id),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct uim_icc_open_logical_channel_req, fileControlInfo_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 17,
		.offset = offsetof(struct uim_icc_open_logical_channel_req, fileControlInfo),
	},
	{}
};

struct qmi_elem_info uim_icc_open_logical_channel_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct uim_icc_open_logical_channel_resp, result),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct uim_icc_open_logical_channel_resp, channel_id_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 16,
		.offset = offsetof(struct uim_icc_open_logical_channel_resp, channel_id),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct uim_icc_open_logical_channel_resp, card_result_valid),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 17,
		.offset = offsetof(struct uim_icc_open_logical_channel_resp, card_result),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct uim_icc_open_logical_channel_resp, select_response_valid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 18,
		.offset = offsetof(struct uim_icc_open_logical_channel_resp, select_response_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 255,
		.elem_size = sizeof(uint8_t),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 18,
		.offset = offsetof(struct uim_icc_open_logical_channel_resp, select_response),
	},
	{}
};

struct qmi_elem_info uim_get_slot_status_req_ei[] = {
	{}
};

struct qmi_elem_info uim_get_slot_status_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct uim_get_slot_status_resp, result),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct uim_get_slot_status_resp, slot_state_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_physical_slot_state),
		.tlv_type = 16,
		.offset = offsetof(struct uim_get_slot_status_resp, slot_state),
		.ei_array = uim_physical_slot_state_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct uim_get_slot_status_resp, slot_info_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_physical_slot_info),
		.tlv_type = 17,
		.offset = offsetof(struct uim_get_slot_status_resp, slot_info),
		.ei_array = uim_physical_slot_info_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct uim_get_slot_status_resp, eid_info_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 32,
		.elem_size = sizeof(uint8_t),
		.array_type = STATIC_ARRAY,
		.tlv_type = 18,
		.offset = offsetof(struct uim_get_slot_status_resp, eid_info),
	},
	{}
};

struct qmi_elem_info uim_get_slot_status_ind_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_physical_slot_state),
		.tlv_type = 16,
		.offset = offsetof(struct uim_get_slot_status_ind, slot_state),
		.ei_array = uim_physical_slot_state_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct uim_get_slot_status_ind, slot_info_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_physical_slot_info),
		.tlv_type = 17,
		.offset = offsetof(struct uim_get_slot_status_ind, slot_info),
		.ei_array = uim_physical_slot_info_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct uim_get_slot_status_ind, eid_info_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 32,
		.elem_size = sizeof(uint8_t),
		.array_type = STATIC_ARRAY,
		.tlv_type = 18,
		.offset = offsetof(struct uim_get_slot_status_ind, eid_info),
	},
	{}
};

struct qmi_elem_info uim_read_transparent_req_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_session_t),
		.tlv_type = 1,
		.offset = offsetof(struct uim_read_transparent_req, session),
		.ei_array = uim_session_t_ei,
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_file_t),
		.tlv_type = 2,
		.offset = offsetof(struct uim_read_transparent_req, file),
		.ei_array = uim_file_t_ei,
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_read_info_t),
		.tlv_type = 3,
		.offset = offsetof(struct uim_read_transparent_req, read_info),
		.ei_array = uim_read_info_t_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct uim_read_transparent_req, resp_in_ind_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 16,
		.offset = offsetof(struct uim_read_transparent_req, resp_in_ind),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct uim_read_transparent_req, encrypt_data_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 17,
		.offset = offsetof(struct uim_read_transparent_req, encrypt_data),
	},
	{}
};

struct qmi_elem_info uim_read_transparent_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct uim_read_transparent_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct uim_read_transparent_resp, card_res_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_card_res_t),
		.tlv_type = 16,
		.offset = offsetof(struct uim_read_transparent_resp, card_res),
		.ei_array = uim_card_res_t_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct uim_read_transparent_resp, read_result_valid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 17,
		.offset = offsetof(struct uim_read_transparent_resp, read_result_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 2,
		.elem_size = sizeof(uint8_t),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 17,
		.offset = offsetof(struct uim_read_transparent_resp, read_result),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct uim_read_transparent_resp, resp_in_ind_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 18,
		.offset = offsetof(struct uim_read_transparent_resp, resp_in_ind),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 19,
		.offset = offsetof(struct uim_read_transparent_resp, encrypted_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 19,
		.offset = offsetof(struct uim_read_transparent_resp, encrypted),
	},
	{}
};

struct qmi_elem_info uim_read_record_req_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_session_t),
		.tlv_type = 1,
		.offset = offsetof(struct uim_read_record_req, session),
		.ei_array = uim_session_t_ei,
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_file_t),
		.tlv_type = 2,
		.offset = offsetof(struct uim_read_record_req, file),
		.ei_array = uim_file_t_ei,
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_read_info_t),
		.tlv_type = 3,
		.offset = offsetof(struct uim_read_record_req, read_info),
		.ei_array = uim_read_info_t_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct uim_read_record_req, last_record_valid),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 16,
		.offset = offsetof(struct uim_read_record_req, last_record),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct uim_read_record_req, resp_in_ind_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 17,
		.offset = offsetof(struct uim_read_record_req, resp_in_ind),
	},
	{}
};

struct qmi_elem_info uim_read_record_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct uim_read_record_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct uim_read_record_resp, card_res_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_card_res_t),
		.tlv_type = 16,
		.offset = offsetof(struct uim_read_record_resp, card_res),
		.ei_array = uim_card_res_t_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct uim_read_record_resp, read_result_valid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 17,
		.offset = offsetof(struct uim_read_record_resp, read_result_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 2,
		.elem_size = sizeof(uint8_t),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 17,
		.offset = offsetof(struct uim_read_record_resp, read_result),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct uim_read_record_resp, additional_read_result_valid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 18,
		.offset = offsetof(struct uim_read_record_resp, additional_read_result_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 2,
		.elem_size = sizeof(uint8_t),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 18,
		.offset = offsetof(struct uim_read_record_resp, additional_read_result),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 19,
		.offset = offsetof(struct uim_read_record_resp, resp_in_ind_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 19,
		.offset = offsetof(struct uim_read_record_resp, resp_in_ind),
	},
	{}
};

struct qmi_elem_info uim_get_file_attrs_req_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_session_t),
		.tlv_type = 1,
		.offset = offsetof(struct uim_get_file_attrs_req, session),
		.ei_array = uim_session_t_ei,
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_file_t),
		.tlv_type = 2,
		.offset = offsetof(struct uim_get_file_attrs_req, file),
		.ei_array = uim_file_t_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct uim_get_file_attrs_req, resp_in_ind_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 17,
		.offset = offsetof(struct uim_get_file_attrs_req, resp_in_ind),
	},
	{}
};

struct qmi_elem_info uim_get_file_attrs_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct uim_get_file_attrs_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct uim_get_file_attrs_resp, card_res_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_card_res_t),
		.tlv_type = 16,
		.offset = offsetof(struct uim_get_file_attrs_resp, card_res),
		.ei_array = uim_card_res_t_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct uim_get_file_attrs_resp, file_attrs_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_file_attrs_t),
		.tlv_type = 17,
		.offset = offsetof(struct uim_get_file_attrs_resp, file_attrs),
		.ei_array = uim_file_attrs_t_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct uim_get_file_attrs_resp, resp_in_ind_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 18,
		.offset = offsetof(struct uim_get_file_attrs_resp, resp_in_ind),
	},
	{}
};

struct qmi_elem_info uim_refresh_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct uim_refresh_ev_t),
		.tlv_type = 16,
		.offset = offsetof(struct uim_refresh, event),
		.ei_array = uim_refresh_ev_t_ei,
	},
	{}
};


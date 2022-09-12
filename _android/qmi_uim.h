#ifndef __QMI_UIM_H__
#define __QMI_UIM_H__

#include <stdint.h>
#include <stdbool.h>

#include "libqrtr.h"

extern struct qmi_elem_info uim_get_card_status_resp_ei[];
extern struct qmi_elem_info uim_change_provisioning_session_req_ei[];
extern struct qmi_elem_info uim_change_provisioning_session_resp_ei[];
extern struct qmi_elem_info uim_icc_open_logical_channel_req_ei[];
extern struct qmi_elem_info uim_icc_open_logical_channel_resp_ei[];
extern struct qmi_elem_info uim_get_slot_status_req_ei[];
extern struct qmi_elem_info uim_get_slot_status_resp_ei[];
extern struct qmi_elem_info uim_get_slot_status_ind_ei[];
extern struct qmi_elem_info uim_read_transparent_req_ei[];
extern struct qmi_elem_info uim_read_transparent_resp_ei[];
extern struct qmi_elem_info uim_read_record_req_ei[];
extern struct qmi_elem_info uim_read_record_resp_ei[];
extern struct qmi_elem_info uim_get_file_attrs_req_ei[];
extern struct qmi_elem_info uim_get_file_attrs_resp_ei[];
extern struct qmi_elem_info uim_refresh_ei[];

#define QMI_UIM_GET_CARD_STATUS 47
#define QMI_UIM_CHANGE_PROVISIONING_SESSION 56
#define QMI_UIM_GET_SLOT_STATUS 71
#define QMI_UIM_SLOT_STATUS_IND 72
#define QMI_UIM_SESSION_TYPE_PRIMARY_GW_PROVISIONING 0
#define QMI_UIM_CARD_STATE_ABSENT 0
#define QMI_UIM_CARD_STATE_PRESENT 1
#define QMI_UIM_CARD_STATE_ERROR 2
#define QMI_UIM_PHYSICAL_CARD_STATE_UNKNOWN 0
#define QMI_UIM_PHYSICAL_CARD_STATE_ABSENT 1
#define QMI_UIM_PHYSICAL_CARD_STATE_PRESENT 2
#define QMI_UIM_CARD_APPLICATION_STATE_UNKNOWN 0
#define QMI_UIM_CARD_APPLICATION_STATE_DETECTED 1
#define QMI_UIM_CARD_APPLICATION_STATE_PIN1_OR_UPIN_PIN_REQUIRED 2
#define QMI_UIM_CARD_APPLICATION_STATE_PUK1_OR_UPIN_PUK_REQUIRED 3
#define QMI_UIM_CARD_APPLICATION_STATE_CHECK_PERSONALIZATION_STATE 4
#define QMI_UIM_CARD_APPLICATION_STATE_PIN1_BLOCKED 5
#define QMI_UIM_CARD_APPLICATION_STATE_ILLEGAL 6
#define QMI_UIM_CARD_APPLICATION_STATE_READY 7
#define QMI_UIM_FILE_TYPE_TRANSPARENT 0
#define QMI_UIM_FILE_TYPE_CYCLIC 1
#define QMI_UIM_FILE_TYPE_LINEAR_FIXED 2
#define QMI_UIM_FILE_TYPE_DEDICATED_FILE 3
#define QMI_UIM_FILE_TYPE_MASTER_FILE 4

struct uim_card_status_cards_applications {
	uint8_t type;
	uint8_t state;
	uint8_t personalization_state;
	uint8_t personalization_feature;
	uint8_t personalization_retries;
	uint8_t personalization_unblock_retries;
	uint8_t application_identifier_value_len;
	uint8_t *application_identifier_value;
	uint8_t upin_replaces_pin1;
	uint8_t pin1_state;
	uint8_t pin1_retries;
	uint8_t puk1_retries;
	uint8_t pin2_state;
	uint8_t pin2_retries;
	uint8_t puk2_retries;
};

struct uim_card_status_cards {
	uint8_t card_state;
	uint8_t upin_state;
	uint8_t upin_retries;
	uint8_t upuk_retries;
	uint8_t error_code;
	uint8_t applications_len;
	struct uim_card_status_cards_applications *applications;
};

struct uim_card_status {
	uint16_t index_gw_primary;
	uint16_t index_1x_primary;
	uint16_t index_gw_secondary;
	uint16_t index_1x_secondary;
	uint8_t cards_len;
	struct uim_card_status_cards *cards;
};

struct uim_provisioning_session_change {
	uint8_t session_type;
	uint8_t activate;
};

struct uim_provisioning_session_application {
	uint8_t slot;
	uint8_t application_identifier_value_len;
	uint8_t *application_identifier_value;
};

struct uim_physical_slot_state_slots {
	uint32_t card_state;
	uint32_t slot_state;
	uint8_t logical_slot;
	uint8_t iccid_len;
	uint8_t *iccid;
};

struct uim_physical_slot_state {
	uint8_t slots_len;
	struct uim_physical_slot_state_slots *slots;
};

struct uim_physical_slot_info_slots {
	uint32_t card_protocol;
	uint8_t valid_applications;
	uint8_t atr_value_len;
	uint8_t *atr_value;
	uint8_t is_euicc;
};

struct uim_physical_slot_info {
	uint8_t slots_len;
	struct uim_physical_slot_info_slots *slots;
};

struct uim_session_t {
	uint8_t type;
	uint8_t aid_len;
	uint8_t *aid;
};

struct uim_file_t {
	uint16_t file_id;
	uint8_t path_len;
	uint8_t *path;
};

struct uim_read_info_t {
	uint16_t offset;
	uint16_t len;
};

struct uim_card_res_t {
	uint8_t sw1;
	uint8_t sw2;
};

struct uim_file_attrs_t {
	uint16_t file_size;
	uint16_t file_id;
	uint8_t file_type;
	uint16_t record_size;
	uint16_t record_count;
	uint8_t read_sec_attr_logic;
	uint16_t read_sec_attrs;
	uint8_t write_sec_attr_logic;
	uint16_t write_sec_attrs;
	uint8_t inc_sec_attr_logic;
	uint16_t inc_sec_attrs;
	uint8_t deactivate_sec_attr_logic;
	uint16_t deactivate_sec_attrs;
	uint8_t activate_sec_attr_logic;
	uint16_t activate_sec_attrs;
	uint16_t raw_data_len;
	uint8_t *raw_data;
};

struct uim_refresh_ev_t_files {
	uint16_t id;
	uint8_t path_len;
	uint8_t *path;
};

struct uim_refresh_ev_t {
	uint8_t stage;
	uint8_t mode;
	uint8_t session_type;
	uint8_t aid_len;
	uint8_t *aid;
	uint16_t files_len;
	struct uim_refresh_ev_t_files *files;
};

struct uim_get_card_status_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct uim_qmi_response_type_v01 result;
	bool status_valid;
	struct uim_card_status status;
};

struct uim_change_provisioning_session_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	bool session_change_valid;
	struct uim_provisioning_session_change session_change;
	bool application_information_valid;
	struct uim_provisioning_session_application application_information;
};

struct uim_change_provisioning_session_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct uim_qmi_response_type_v01 result;
};

struct uim_icc_open_logical_channel_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	uint8_t slot;
	bool application_id_valid;
	uint32_t application_id_len;
	uint8_t application_id[32];
	bool fileControlInfo_valid;
	uint8_t fileControlInfo;
};

struct uim_icc_open_logical_channel_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct uim_qmi_response_type_v01 result;
	bool channel_id_valid;
	uint8_t channel_id;
	bool card_result_valid;
	uint16_t card_result;
	bool select_response_valid;
	uint32_t select_response_len;
	uint8_t select_response[255];
};

struct uim_get_slot_status_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
};

struct uim_get_slot_status_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct uim_qmi_response_type_v01 result;
	bool slot_state_valid;
	struct uim_physical_slot_state slot_state;
	bool slot_info_valid;
	struct uim_physical_slot_info slot_info;
	bool eid_info_valid;
	uint32_t eid_info_len;
	uint8_t eid_info[32];
};

struct uim_get_slot_status_ind {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct uim_physical_slot_state slot_state;
	bool slot_info_valid;
	struct uim_physical_slot_info slot_info;
	bool eid_info_valid;
	uint32_t eid_info_len;
	uint8_t eid_info[32];
};

struct uim_read_transparent_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct uim_session_t session;
	struct uim_file_t file;
	struct uim_read_info_t read_info;
	bool resp_in_ind_valid;
	uint32_t resp_in_ind;
	bool encrypt_data_valid;
	uint8_t encrypt_data;
};

struct uim_read_transparent_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct uim_qmi_response_type_v01 res;
	bool card_res_valid;
	struct uim_card_res_t card_res;
	bool read_result_valid;
	uint32_t read_result_len;
	uint8_t read_result[2];
	bool resp_in_ind_valid;
	uint32_t resp_in_ind;
	bool encrypted_valid;
	uint8_t encrypted;
};

struct uim_read_record_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct uim_session_t session;
	struct uim_file_t file;
	struct uim_read_info_t read_info;
	bool last_record_valid;
	uint16_t last_record;
	bool resp_in_ind_valid;
	uint32_t resp_in_ind;
};

struct uim_read_record_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct uim_qmi_response_type_v01 res;
	bool card_res_valid;
	struct uim_card_res_t card_res;
	bool read_result_valid;
	uint32_t read_result_len;
	uint8_t read_result[2];
	bool additional_read_result_valid;
	uint32_t additional_read_result_len;
	uint8_t additional_read_result[2];
	bool resp_in_ind_valid;
	uint32_t resp_in_ind;
};

struct uim_get_file_attrs_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct uim_session_t session;
	struct uim_file_t file;
	bool resp_in_ind_valid;
	uint32_t resp_in_ind;
};

struct uim_get_file_attrs_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct uim_qmi_response_type_v01 res;
	bool card_res_valid;
	struct uim_card_res_t card_res;
	bool file_attrs_valid;
	struct uim_file_attrs_t file_attrs;
	bool resp_in_ind_valid;
	uint32_t resp_in_ind;
};

struct uim_refresh {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct uim_refresh_ev_t event;
};

#define UIM_GET_CARD_STATUS_RESP_NEW ({ \
	struct uim_get_card_status_resp *ptr = malloc(sizeof(struct uim_get_card_status_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x002f; \
	ptr->ei = &uim_get_card_status_resp_ei; ptr })
#define UIM_GET_CARD_STATUS_RESP_INITIALIZER { { 2, 0, 0x002f, 0 }, &uim_get_card_status_resp_ei, {}, {} }
#define UIM_CHANGE_PROVISIONING_SESSION_REQ_NEW ({ \
	struct uim_change_provisioning_session_req *ptr = malloc(sizeof(struct uim_change_provisioning_session_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x0038; \
	ptr->ei = &uim_change_provisioning_session_req_ei; ptr })
#define UIM_CHANGE_PROVISIONING_SESSION_REQ_INITIALIZER { { 0, 0, 0x0038, 0 }, &uim_change_provisioning_session_req_ei, {}, {} }
#define UIM_CHANGE_PROVISIONING_SESSION_RESP_NEW ({ \
	struct uim_change_provisioning_session_resp *ptr = malloc(sizeof(struct uim_change_provisioning_session_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0038; \
	ptr->ei = &uim_change_provisioning_session_resp_ei; ptr })
#define UIM_CHANGE_PROVISIONING_SESSION_RESP_INITIALIZER { { 2, 0, 0x0038, 0 }, &uim_change_provisioning_session_resp_ei, {} }
#define UIM_ICC_OPEN_LOGICAL_CHANNEL_REQ_NEW ({ \
	struct uim_icc_open_logical_channel_req *ptr = malloc(sizeof(struct uim_icc_open_logical_channel_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x0042; \
	ptr->ei = &uim_icc_open_logical_channel_req_ei; ptr })
#define UIM_ICC_OPEN_LOGICAL_CHANNEL_REQ_INITIALIZER { { 0, 0, 0x0042, 0 }, &uim_icc_open_logical_channel_req_ei, 0, 0, 0 }
#define UIM_ICC_OPEN_LOGICAL_CHANNEL_RESP_NEW ({ \
	struct uim_icc_open_logical_channel_resp *ptr = malloc(sizeof(struct uim_icc_open_logical_channel_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0042; \
	ptr->ei = &uim_icc_open_logical_channel_resp_ei; ptr })
#define UIM_ICC_OPEN_LOGICAL_CHANNEL_RESP_INITIALIZER { { 2, 0, 0x0042, 0 }, &uim_icc_open_logical_channel_resp_ei, {}, 0, 0, 0 }
#define UIM_GET_SLOT_STATUS_REQ_NEW ({ \
	struct uim_get_slot_status_req *ptr = malloc(sizeof(struct uim_get_slot_status_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x0047; \
	ptr->ei = &uim_get_slot_status_req_ei; ptr })
#define UIM_GET_SLOT_STATUS_REQ_INITIALIZER { { 0, 0, 0x0047, 0 }, &uim_get_slot_status_req_ei }
#define UIM_GET_SLOT_STATUS_RESP_NEW ({ \
	struct uim_get_slot_status_resp *ptr = malloc(sizeof(struct uim_get_slot_status_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0047; \
	ptr->ei = &uim_get_slot_status_resp_ei; ptr })
#define UIM_GET_SLOT_STATUS_RESP_INITIALIZER { { 2, 0, 0x0047, 0 }, &uim_get_slot_status_resp_ei, {}, {}, {}, 0 }
#define UIM_GET_SLOT_STATUS_IND_NEW ({ \
	struct uim_get_slot_status_ind *ptr = malloc(sizeof(struct uim_get_slot_status_ind)); \
	ptr->qmi_header->type = 4; ptr->qmi_header->msg_id = 0x0048; \
	ptr->ei = &uim_get_slot_status_ind_ei; ptr })
#define UIM_GET_SLOT_STATUS_IND_INITIALIZER { { 4, 0, 0x0048, 0 }, &uim_get_slot_status_ind_ei, {}, {}, 0 }
#define UIM_READ_TRANSPARENT_REQ_NEW ({ \
	struct uim_read_transparent_req *ptr = malloc(sizeof(struct uim_read_transparent_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x0020; \
	ptr->ei = &uim_read_transparent_req_ei; ptr })
#define UIM_READ_TRANSPARENT_REQ_INITIALIZER { { 0, 0, 0x0020, 0 }, &uim_read_transparent_req_ei, {}, {}, {}, 0, 0 }
#define UIM_READ_TRANSPARENT_RESP_NEW ({ \
	struct uim_read_transparent_resp *ptr = malloc(sizeof(struct uim_read_transparent_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0020; \
	ptr->ei = &uim_read_transparent_resp_ei; ptr })
#define UIM_READ_TRANSPARENT_RESP_INITIALIZER { { 2, 0, 0x0020, 0 }, &uim_read_transparent_resp_ei, {}, {}, 0, 0, 0 }
#define UIM_READ_RECORD_REQ_NEW ({ \
	struct uim_read_record_req *ptr = malloc(sizeof(struct uim_read_record_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x0021; \
	ptr->ei = &uim_read_record_req_ei; ptr })
#define UIM_READ_RECORD_REQ_INITIALIZER { { 0, 0, 0x0021, 0 }, &uim_read_record_req_ei, {}, {}, {}, 0, 0 }
#define UIM_READ_RECORD_RESP_NEW ({ \
	struct uim_read_record_resp *ptr = malloc(sizeof(struct uim_read_record_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0021; \
	ptr->ei = &uim_read_record_resp_ei; ptr })
#define UIM_READ_RECORD_RESP_INITIALIZER { { 2, 0, 0x0021, 0 }, &uim_read_record_resp_ei, {}, {}, 0, 0, 0 }
#define UIM_GET_FILE_ATTRS_REQ_NEW ({ \
	struct uim_get_file_attrs_req *ptr = malloc(sizeof(struct uim_get_file_attrs_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x0024; \
	ptr->ei = &uim_get_file_attrs_req_ei; ptr })
#define UIM_GET_FILE_ATTRS_REQ_INITIALIZER { { 0, 0, 0x0024, 0 }, &uim_get_file_attrs_req_ei, {}, {}, 0 }
#define UIM_GET_FILE_ATTRS_RESP_NEW ({ \
	struct uim_get_file_attrs_resp *ptr = malloc(sizeof(struct uim_get_file_attrs_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0024; \
	ptr->ei = &uim_get_file_attrs_resp_ei; ptr })
#define UIM_GET_FILE_ATTRS_RESP_INITIALIZER { { 2, 0, 0x0024, 0 }, &uim_get_file_attrs_resp_ei, {}, {}, {}, 0 }
#define UIM_REFRESH_NEW ({ \
	struct uim_refresh *ptr = malloc(sizeof(struct uim_refresh)); \
	ptr->qmi_header->type = 4; ptr->qmi_header->msg_id = 0x0033; \
	ptr->ei = &uim_refresh_ei; ptr })
#define UIM_REFRESH_INITIALIZER { { 4, 0, 0x0033, 0 }, &uim_refresh_ei, {} }

#endif

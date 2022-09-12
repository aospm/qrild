#ifndef __QMI_DMS_H__
#define __QMI_DMS_H__

#include <stdint.h>
#include <stdbool.h>

#include "libqrtr.h"

extern struct qmi_elem_info dms_get_revision_req_ei[];
extern struct qmi_elem_info dms_get_revision_resp_ei[];
extern struct qmi_elem_info dms_get_ids_req_ei[];
extern struct qmi_elem_info dms_get_ids_resp_ei[];
extern struct qmi_elem_info dms_get_operating_mode_req_ei[];
extern struct qmi_elem_info dms_get_operating_mode_resp_ei[];
extern struct qmi_elem_info dms_set_operating_mode_req_ei[];
extern struct qmi_elem_info dms_set_operating_mode_resp_ei[];
extern struct qmi_elem_info dms_get_msisdn_ei[];
extern struct qmi_elem_info dms_uim_get_imsi_ei[];

#define QMI_DMS_GET_REVISION 35
#define QMI_DMS_GET_MSISDN 36
#define QMI_DMS_GET_IDS 37
#define QMI_DMS_GET_OPERATING_MODE 45
#define QMI_DMS_SET_OPERATING_MODE 46
#define QMI_DMS_UIM_GET_IMSI 67
#define QMI_DMS_OPERATING_MODE_ONLINE 0
#define QMI_DMS_OPERATING_MODE_LOW_POWER 1
#define QMI_DMS_OPERATING_MODE_FACTORY_TEST 2
#define QMI_DMS_OPERATING_MODE_OFFLINE 3
#define QMI_DMS_OPERATING_MODE_RESET 4
#define QMI_DMS_OPERATING_MODE_SHUTTING_DOWN 5
#define QMI_DMS_OPERATING_MODE_PERSISTENT_LOW_POWER 6
#define QMI_DMS_OPERATING_MODE_MODE_ONLY_LOW_POWER 7
#define QMI_DMS_OPERATING_MODE_UNKNOWN 255

struct dms_ids {
	uint16_t esn_len;
	uint32_t esn_len;
	char esn[256];
	uint16_t imei_len;
	uint32_t imei_len;
	char imei[256];
	uint16_t meid_len;
	uint32_t meid_len;
	char meid[256];
	uint16_t imei_ver_len;
	uint32_t imei_ver_len;
	char imei_ver[256];
};

struct dms_get_revision_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
};

struct dms_get_revision_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	uint32_t revision_len;
	char revision[256];
};

struct dms_get_ids_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
};

struct dms_get_ids_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct dms_qmi_response_type_v01 res;
	uint32_t esn_len;
	char esn[256];
	uint32_t imei_len;
	char imei[256];
	uint32_t meid_len;
	char meid[256];
	uint32_t imei_ver_len;
	char imei_ver[256];
};

struct dms_get_operating_mode_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
};

struct dms_get_operating_mode_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct dms_qmi_response_type_v01 res;
	uint8_t mode;
	bool offline_reason_valid;
	uint16_t offline_reason;
	uint8_t hardware_restricted;
};

struct dms_set_operating_mode_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	uint8_t mode;
};

struct dms_set_operating_mode_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct dms_qmi_response_type_v01 res;
};

struct dms_get_msisdn {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct dms_qmi_response_type_v01 res;
	uint32_t msisdn_len;
	char msisdn[256];
	uint32_t imsi_len;
	char imsi[256];
};

struct dms_uim_get_imsi {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct dms_qmi_response_type_v01 res;
	uint32_t imsi_len;
	char imsi[256];
};

#define DMS_GET_REVISION_REQ_NEW ({ \
	struct dms_get_revision_req *ptr = malloc(sizeof(struct dms_get_revision_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x0023; \
	ptr->ei = &dms_get_revision_req_ei; ptr })
#define DMS_GET_REVISION_REQ_INITIALIZER { { 0, 0, 0x0023, 0 }, &dms_get_revision_req_ei }
#define DMS_GET_REVISION_RESP_NEW ({ \
	struct dms_get_revision_resp *ptr = malloc(sizeof(struct dms_get_revision_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0023; \
	ptr->ei = &dms_get_revision_resp_ei; ptr })
#define DMS_GET_REVISION_RESP_INITIALIZER { { 2, 0, 0x0023, 0 }, &dms_get_revision_resp_ei, 0, NULL }
#define DMS_GET_IDS_REQ_NEW ({ \
	struct dms_get_ids_req *ptr = malloc(sizeof(struct dms_get_ids_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x0025; \
	ptr->ei = &dms_get_ids_req_ei; ptr })
#define DMS_GET_IDS_REQ_INITIALIZER { { 0, 0, 0x0025, 0 }, &dms_get_ids_req_ei }
#define DMS_GET_IDS_RESP_NEW ({ \
	struct dms_get_ids_resp *ptr = malloc(sizeof(struct dms_get_ids_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0025; \
	ptr->ei = &dms_get_ids_resp_ei; ptr })
#define DMS_GET_IDS_RESP_INITIALIZER { { 2, 0, 0x0025, 0 }, &dms_get_ids_resp_ei, {}, 0, NULL, 0, NULL, 0, NULL, 0, NULL }
#define DMS_GET_OPERATING_MODE_REQ_NEW ({ \
	struct dms_get_operating_mode_req *ptr = malloc(sizeof(struct dms_get_operating_mode_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x002d; \
	ptr->ei = &dms_get_operating_mode_req_ei; ptr })
#define DMS_GET_OPERATING_MODE_REQ_INITIALIZER { { 0, 0, 0x002d, 0 }, &dms_get_operating_mode_req_ei }
#define DMS_GET_OPERATING_MODE_RESP_NEW ({ \
	struct dms_get_operating_mode_resp *ptr = malloc(sizeof(struct dms_get_operating_mode_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x002d; \
	ptr->ei = &dms_get_operating_mode_resp_ei; ptr })
#define DMS_GET_OPERATING_MODE_RESP_INITIALIZER { { 2, 0, 0x002d, 0 }, &dms_get_operating_mode_resp_ei, {}, 0, 0, 0 }
#define DMS_SET_OPERATING_MODE_REQ_NEW ({ \
	struct dms_set_operating_mode_req *ptr = malloc(sizeof(struct dms_set_operating_mode_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x002e; \
	ptr->ei = &dms_set_operating_mode_req_ei; ptr })
#define DMS_SET_OPERATING_MODE_REQ_INITIALIZER { { 0, 0, 0x002e, 0 }, &dms_set_operating_mode_req_ei, 0 }
#define DMS_SET_OPERATING_MODE_RESP_NEW ({ \
	struct dms_set_operating_mode_resp *ptr = malloc(sizeof(struct dms_set_operating_mode_resp)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x002e; \
	ptr->ei = &dms_set_operating_mode_resp_ei; ptr })
#define DMS_SET_OPERATING_MODE_RESP_INITIALIZER { { 0, 0, 0x002e, 0 }, &dms_set_operating_mode_resp_ei, {} }
#define DMS_GET_MSISDN_NEW ({ \
	struct dms_get_msisdn *ptr = malloc(sizeof(struct dms_get_msisdn)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0024; \
	ptr->ei = &dms_get_msisdn_ei; ptr })
#define DMS_GET_MSISDN_INITIALIZER { { 2, 0, 0x0024, 0 }, &dms_get_msisdn_ei, {}, 0, NULL, 0, NULL }
#define DMS_UIM_GET_IMSI_NEW ({ \
	struct dms_uim_get_imsi *ptr = malloc(sizeof(struct dms_uim_get_imsi)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0043; \
	ptr->ei = &dms_uim_get_imsi_ei; ptr })
#define DMS_UIM_GET_IMSI_INITIALIZER { { 2, 0, 0x0043, 0 }, &dms_uim_get_imsi_ei, {}, 0, NULL }

#endif

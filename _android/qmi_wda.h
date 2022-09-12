#ifndef __QMI_WDA_H__
#define __QMI_WDA_H__

#include <stdint.h>
#include <stdbool.h>

#include "libqrtr.h"

extern struct qmi_elem_info wda_set_data_format_req_ei[];
extern struct qmi_elem_info wda_set_data_format_resp_ei[];

#define QMI_WDA_SERVICE 26
#define QMI_WDA_SET_DATA_FORMAT 32

struct wda_ep_type_iface_id {
	uint32_t ep_type;
	uint32_t iface_id;
};

struct wda_set_data_format_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	bool link_prot_valid;
	uint32_t link_prot;
	bool ul_data_aggregation_protocol_valid;
	uint32_t ul_data_aggregation_protocol;
	bool dl_data_aggregation_protocol_valid;
	uint32_t dl_data_aggregation_protocol;
	bool dl_data_aggretation_max_datagrams_valid;
	uint32_t dl_data_aggretation_max_datagrams;
	bool dl_data_aggregation_max_size_valid;
	uint32_t dl_data_aggregation_max_size;
	bool ep_type_valid;
	struct wda_ep_type_iface_id ep_type;
};

struct wda_set_data_format_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct wda_qmi_response_type_v01 res;
};

#define WDA_SET_DATA_FORMAT_REQ_NEW ({ \
	struct wda_set_data_format_req *ptr = malloc(sizeof(struct wda_set_data_format_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x0020; \
	ptr->ei = &wda_set_data_format_req_ei; ptr })
#define WDA_SET_DATA_FORMAT_REQ_INITIALIZER { { 0, 0, 0x0020, 0 }, &wda_set_data_format_req_ei, 0, 0, 0, 0, 0, {} }
#define WDA_SET_DATA_FORMAT_RESP_NEW ({ \
	struct wda_set_data_format_resp *ptr = malloc(sizeof(struct wda_set_data_format_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0020; \
	ptr->ei = &wda_set_data_format_resp_ei; ptr })
#define WDA_SET_DATA_FORMAT_RESP_INITIALIZER { { 2, 0, 0x0020, 0 }, &wda_set_data_format_resp_ei, {} }

#endif

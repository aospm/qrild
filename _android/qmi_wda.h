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

struct wda_set_data_format_req { // 0x0020
	struct qmi_message_header header;
	bool link_prot_valid;
	uint32_t link_prot;  // 0x11
	bool ul_data_aggregation_protocol_valid;
	uint32_t ul_data_aggregation_protocol;  // 0x12
	bool dl_data_aggregation_protocol_valid;
	uint32_t dl_data_aggregation_protocol;  // 0x13
	bool dl_data_aggretation_max_datagrams_valid;
	uint32_t dl_data_aggretation_max_datagrams;  // 0x15
	bool dl_data_aggregation_max_size_valid;
	uint32_t dl_data_aggregation_max_size;  // 0x16
	bool ep_type_valid;
	struct wda_ep_type_iface_id ep_type;  // 0x17
};

struct wda_set_data_format_resp { // 0x0020
	struct qmi_message_header header;
	struct qmi_response_type_v01 res;  // 0x02
};

#define WDA_SET_DATA_FORMAT_REQ_NEW ({ \
	struct wda_set_data_format_req *ptr = malloc(sizeof(struct wda_set_data_format_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x0020; \
	ptr->ei = &wda_set_data_format_req_ei; ptr })
#define WDA_SET_DATA_FORMAT_REQ_INITIALIZER { { 0, 0, 0x0020, 0 }, &wda_set_data_format_req_ei, "set_data_format_req", 0, 0, 0, 0, 0, {} }
#define WDA_SET_DATA_FORMAT_RESP_NEW ({ \
	struct wda_set_data_format_resp *ptr = malloc(sizeof(struct wda_set_data_format_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0020; \
	ptr->ei = &wda_set_data_format_resp_ei; ptr })
#define WDA_SET_DATA_FORMAT_RESP_INITIALIZER { { 2, 0, 0x0020, 0 }, &wda_set_data_format_resp_ei, "set_data_format_resp", {} }

#endif

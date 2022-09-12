#ifndef __QMI_DPM_H__
#define __QMI_DPM_H__

#include <stdint.h>
#include <stdbool.h>

#include "libqrtr.h"

extern struct qmi_elem_info dpm_open_port_req_ei[];
extern struct qmi_elem_info dpm_open_port_resp_ei[];

#define QMI_DPM_SERVICE 47
#define QMI_DPM_OPEN_PORT 32

struct dpm_control_port {
	uint32_t ep_type;
	uint32_t iface_id;
	uint32_t consumer_pipe_num;
	uint32_t producer_pipe_num;
};

struct dpm_open_port_req {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	bool port_list_valid;
	uint32_t port_list_len;
	struct dpm_control_port port_list[1];
};

struct dpm_open_port_resp {
	struct qmi_header qmi_header;
	struct qmi_elem_info **ei;
	struct dpm_qmi_response_type_v01 res;
};

#define DPM_OPEN_PORT_REQ_NEW ({ \
	struct dpm_open_port_req *ptr = malloc(sizeof(struct dpm_open_port_req)); \
	ptr->qmi_header->type = 0; ptr->qmi_header->msg_id = 0x0020; \
	ptr->ei = &dpm_open_port_req_ei; ptr })
#define DPM_OPEN_PORT_REQ_INITIALIZER { { 0, 0, 0x0020, 0 }, &dpm_open_port_req_ei, {} }
#define DPM_OPEN_PORT_RESP_NEW ({ \
	struct dpm_open_port_resp *ptr = malloc(sizeof(struct dpm_open_port_resp)); \
	ptr->qmi_header->type = 2; ptr->qmi_header->msg_id = 0x0020; \
	ptr->ei = &dpm_open_port_resp_ei; ptr })
#define DPM_OPEN_PORT_RESP_INITIALIZER { { 2, 0, 0x0020, 0 }, &dpm_open_port_resp_ei, {} }

#endif

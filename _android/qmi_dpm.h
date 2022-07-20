#ifndef __QMI_DPM_H__
#define __QMI_DPM_H__

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <libqrtr.h>

#define get_next(_type, _sz) ({ \
	void* buf = ptr + len; \
	len += _sz; \
	if (len > buf_sz) goto err_wrong_len; \
	*(_type*)buf; \
})

#define QMI_DPM_SERVICE 47
#define QMI_DPM_OPEN_PORT 32

struct dpm_control_port {
	uint32_t ep_type;
	uint32_t iface_id;
	uint32_t consumer_pipe_num;
	uint32_t producer_pipe_num;
};

struct dpm_open_port_req;
struct dpm_open_port_resp;

/*
 * dpm_open_port_req message
 */
struct dpm_open_port_req *dpm_open_port_req_alloc(unsigned txn);
struct dpm_open_port_req *dpm_open_port_req_parse(void *buf, size_t len);
void *dpm_open_port_req_encode(struct dpm_open_port_req *open_port_req, size_t *len);
void dpm_open_port_req_free(struct dpm_open_port_req *open_port_req);

int dpm_open_port_req_set_port_list(struct dpm_open_port_req *open_port_req, struct dpm_control_port *val, size_t count);
struct dpm_control_port *dpm_open_port_req_get_port_list(struct dpm_open_port_req *open_port_req, size_t *count);

/*
 * dpm_open_port_resp message
 */
struct dpm_open_port_resp *dpm_open_port_resp_alloc(unsigned txn);
struct dpm_open_port_resp *dpm_open_port_resp_parse(void *buf, size_t len);
void *dpm_open_port_resp_encode(struct dpm_open_port_resp *open_port_resp, size_t *len);
void dpm_open_port_resp_free(struct dpm_open_port_resp *open_port_resp);

#endif

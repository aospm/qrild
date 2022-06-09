#ifndef __QMI_DPM_H__
#define __QMI_DPM_H__

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define get_next(_type, _sz) ({ \
	void* buf = ptr + len; \
	len += _sz; \
	if (len > buf_sz) goto err_wrong_len; \
	*(_type*)buf; \
})

struct qmi_tlv;

struct qmi_tlv *qmi_tlv_init(unsigned txn, unsigned msg_id, unsigned type);
struct qmi_tlv *qmi_tlv_init_ctl(unsigned txn, unsigned msg_id, unsigned type);
struct qmi_tlv *qmi_tlv_decode(void *buf, size_t len, unsigned *txn, unsigned type);
struct qmi_tlv *qmi_tlv_decode_ctl(void *buf, size_t len, unsigned *txn, unsigned type);
void *qmi_tlv_encode(struct qmi_tlv *tlv, size_t *len);
void *qmi_tlv_encode_ctl(struct qmi_tlv *tlv, size_t *len);
void qmi_tlv_free(struct qmi_tlv *tlv);

void *qmi_tlv_get(struct qmi_tlv *tlv, unsigned id, size_t *len);
void *qmi_tlv_get_array(struct qmi_tlv *tlv, unsigned id, unsigned len_size, size_t *len, size_t *size);
int qmi_tlv_set(struct qmi_tlv *tlv, unsigned id, void *buf, size_t len);
int qmi_tlv_set_array(struct qmi_tlv *tlv, unsigned id, unsigned len_size, void *buf, size_t len, size_t size);

#define QMI_DPM_SERVICE 47
#define QMI_DPM_OPEN_PORT 32

struct dpm_qmi_result {
	uint16_t result;
	uint16_t error;
};

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
struct dpm_open_port_req *dpm_open_port_req_parse(void *buf, size_t len, unsigned *txn);
void *dpm_open_port_req_encode(struct dpm_open_port_req *open_port_req, size_t *len);
void dpm_open_port_req_free(struct dpm_open_port_req *open_port_req);

int dpm_open_port_req_set_port_list(struct dpm_open_port_req *open_port_req, struct dpm_control_port *val, size_t count);
struct dpm_control_port *dpm_open_port_req_get_port_list(struct dpm_open_port_req *open_port_req, size_t *count);

/*
 * dpm_open_port_resp message
 */
struct dpm_open_port_resp *dpm_open_port_resp_alloc(unsigned txn);
struct dpm_open_port_resp *dpm_open_port_resp_parse(void *buf, size_t len, unsigned *txn);
void *dpm_open_port_resp_encode(struct dpm_open_port_resp *open_port_resp, size_t *len);
void dpm_open_port_resp_free(struct dpm_open_port_resp *open_port_resp);

int dpm_open_port_resp_set_r(struct dpm_open_port_resp *open_port_resp, struct dpm_qmi_result *val);
struct dpm_qmi_result *dpm_open_port_resp_get_r(struct dpm_open_port_resp *open_port_resp);

#endif

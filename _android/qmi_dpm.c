#include <errno.h>
#include <string.h>
#include "qmi_dpm.h"

struct dpm_open_port_req *dpm_open_port_req_alloc(unsigned txn)
{
	return (struct dpm_open_port_req*)qmi_tlv_init(txn, 32, 0);
}

struct dpm_open_port_req *dpm_open_port_req_parse(void *buf, size_t len)
{
	return (struct dpm_open_port_req*)qmi_tlv_decode(buf, len);
}

void *dpm_open_port_req_encode(struct dpm_open_port_req *open_port_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)open_port_req, len);
}

void dpm_open_port_req_free(struct dpm_open_port_req *open_port_req)
{
	qmi_tlv_free((struct qmi_tlv*)open_port_req);
}

int dpm_open_port_req_set_port_list(struct dpm_open_port_req *open_port_req, struct dpm_control_port *val, size_t count)
{
	return qmi_tlv_set_array((struct qmi_tlv*)open_port_req, 17, 1, val, count, sizeof(struct dpm_control_port));
}

struct dpm_control_port *dpm_open_port_req_get_port_list(struct dpm_open_port_req *open_port_req, size_t *count)
{
	size_t size;
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)open_port_req, 17, 1, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(struct dpm_control_port))
		return NULL;

	*count = len;
	return ptr;
}

struct dpm_open_port_resp *dpm_open_port_resp_alloc(unsigned txn)
{
	return (struct dpm_open_port_resp*)qmi_tlv_init(txn, 32, 2);
}

struct dpm_open_port_resp *dpm_open_port_resp_parse(void *buf, size_t len)
{
	return (struct dpm_open_port_resp*)qmi_tlv_decode(buf, len);
}

void *dpm_open_port_resp_encode(struct dpm_open_port_resp *open_port_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)open_port_resp, len);
}

void dpm_open_port_resp_free(struct dpm_open_port_resp *open_port_resp)
{
	qmi_tlv_free((struct qmi_tlv*)open_port_resp);
}


#include <errno.h>
#include <string.h>
#include "qmi_dpm.h"

struct dpm_open_port_req *dpm_open_port_req_alloc(unsigned txn)
{
	return (struct dpm_open_port_req*)qmi_tlv_init(txn, 32, 0);
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

struct dpm_open_port_resp *dpm_open_port_resp_parse(void *buf, size_t len)
{
	return (struct dpm_open_port_resp*)qmi_tlv_decode(buf, len);
}

void dpm_open_port_resp_getall(struct dpm_open_port_resp *open_port_resp, struct dpm_open_port_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = qmi_tlv_get((struct qmi_tlv*)open_port_resp, 2, NULL);
}

void dpm_open_port_resp_free(struct dpm_open_port_resp *open_port_resp)
{
	qmi_tlv_free((struct qmi_tlv*)open_port_resp);
}


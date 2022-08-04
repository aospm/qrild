#include <errno.h>
#include <string.h>
#include "qmi_dpm.h"

const struct qmi_tlv_msg_name dpm_msg_name_map[2] = {
	{ .msg_id = 32, .msg_name = "dpm_open_port_req" },
	{ .msg_id = 32, .msg_name = "dpm_open_port_resp" },
};

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

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)open_port_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
}

void dpm_open_port_resp_data_free(struct dpm_open_port_resp_data *data)
{

		free(data->res);
}

void dpm_open_port_resp_free(struct dpm_open_port_resp *open_port_resp)
{
	qmi_tlv_free((struct qmi_tlv*)open_port_resp);
}


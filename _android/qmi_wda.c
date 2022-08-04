#include <errno.h>
#include <string.h>
#include "qmi_wda.h"

const struct qmi_tlv_msg_name wda_msg_name_map[2] = {
	{ .msg_id = 32, .msg_name = "wda_set_data_format_req" },
	{ .msg_id = 32, .msg_name = "wda_set_data_format_resp" },
};

struct wda_set_data_format_req *wda_set_data_format_req_alloc(unsigned txn)
{
	return (struct wda_set_data_format_req*)qmi_tlv_init(txn, 32, 0);
}

void *wda_set_data_format_req_encode(struct wda_set_data_format_req *set_data_format_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)set_data_format_req, len);
}

void wda_set_data_format_req_free(struct wda_set_data_format_req *set_data_format_req)
{
	qmi_tlv_free((struct qmi_tlv*)set_data_format_req);
}

int wda_set_data_format_req_set_link_prot(struct wda_set_data_format_req *set_data_format_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_data_format_req, 17, &val, sizeof(uint32_t));
}

int wda_set_data_format_req_set_ul_data_aggregation_protocol(struct wda_set_data_format_req *set_data_format_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_data_format_req, 18, &val, sizeof(uint32_t));
}

int wda_set_data_format_req_set_dl_data_aggregation_protocol(struct wda_set_data_format_req *set_data_format_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_data_format_req, 19, &val, sizeof(uint32_t));
}

int wda_set_data_format_req_set_dl_data_aggretation_max_datagrams(struct wda_set_data_format_req *set_data_format_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_data_format_req, 21, &val, sizeof(uint32_t));
}

int wda_set_data_format_req_set_dl_data_aggregation_max_size(struct wda_set_data_format_req *set_data_format_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_data_format_req, 22, &val, sizeof(uint32_t));
}

int wda_set_data_format_req_set_ep_type(struct wda_set_data_format_req *set_data_format_req, struct wda_ep_type_iface_id *val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_data_format_req, 23, val, sizeof(struct wda_ep_type_iface_id));
}

struct wda_set_data_format_resp *wda_set_data_format_resp_parse(void *buf, size_t len)
{
	return (struct wda_set_data_format_resp*)qmi_tlv_decode(buf, len);
}

void wda_set_data_format_resp_getall(struct wda_set_data_format_resp *set_data_format_resp, struct wda_set_data_format_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)set_data_format_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
}

void wda_set_data_format_resp_data_free(struct wda_set_data_format_resp_data *data)
{

		free(data->res);
}

void wda_set_data_format_resp_free(struct wda_set_data_format_resp *set_data_format_resp)
{
	qmi_tlv_free((struct qmi_tlv*)set_data_format_resp);
}


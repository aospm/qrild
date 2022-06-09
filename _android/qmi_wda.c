#include <errno.h>
#include <string.h>
#include "qmi_wda.h"

struct wda_set_data_format_req *wda_set_data_format_req_alloc(unsigned txn)
{
	return (struct wda_set_data_format_req*)qmi_tlv_init(txn, 32, 0);
}

struct wda_set_data_format_req *wda_set_data_format_req_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct wda_set_data_format_req*)qmi_tlv_decode(buf, len, txn, 0);
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

int wda_set_data_format_req_get_link_prot(struct wda_set_data_format_req *set_data_format_req, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)set_data_format_req, 17, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

int wda_set_data_format_req_set_ul_data_aggregation_protocol(struct wda_set_data_format_req *set_data_format_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_data_format_req, 18, &val, sizeof(uint32_t));
}

int wda_set_data_format_req_get_ul_data_aggregation_protocol(struct wda_set_data_format_req *set_data_format_req, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)set_data_format_req, 18, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

int wda_set_data_format_req_set_dl_data_aggregation_protocol(struct wda_set_data_format_req *set_data_format_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_data_format_req, 19, &val, sizeof(uint32_t));
}

int wda_set_data_format_req_get_dl_data_aggregation_protocol(struct wda_set_data_format_req *set_data_format_req, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)set_data_format_req, 19, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

int wda_set_data_format_req_set_dl_data_aggretation_max_datagrams(struct wda_set_data_format_req *set_data_format_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_data_format_req, 21, &val, sizeof(uint32_t));
}

int wda_set_data_format_req_get_dl_data_aggretation_max_datagrams(struct wda_set_data_format_req *set_data_format_req, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)set_data_format_req, 21, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

int wda_set_data_format_req_set_dl_data_aggregation_max_size(struct wda_set_data_format_req *set_data_format_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_data_format_req, 22, &val, sizeof(uint32_t));
}

int wda_set_data_format_req_get_dl_data_aggregation_max_size(struct wda_set_data_format_req *set_data_format_req, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)set_data_format_req, 22, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

int wda_set_data_format_req_set_ep_type(struct wda_set_data_format_req *set_data_format_req, struct wda_ep_type_iface_id *val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_data_format_req, 23, val, sizeof(struct wda_ep_type_iface_id));
}

struct wda_ep_type_iface_id *wda_set_data_format_req_get_ep_type(struct wda_set_data_format_req *set_data_format_req)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)set_data_format_req, 23, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct wda_ep_type_iface_id))
		return NULL;

	return ptr;
}

struct wda_set_data_format_resp *wda_set_data_format_resp_alloc(unsigned txn)
{
	return (struct wda_set_data_format_resp*)qmi_tlv_init(txn, 32, 2);
}

struct wda_set_data_format_resp *wda_set_data_format_resp_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct wda_set_data_format_resp*)qmi_tlv_decode(buf, len, txn, 2);
}

void *wda_set_data_format_resp_encode(struct wda_set_data_format_resp *set_data_format_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)set_data_format_resp, len);
}

void wda_set_data_format_resp_free(struct wda_set_data_format_resp *set_data_format_resp)
{
	qmi_tlv_free((struct qmi_tlv*)set_data_format_resp);
}

int wda_set_data_format_resp_set_r(struct wda_set_data_format_resp *set_data_format_resp, struct wda_qmi_result *val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_data_format_resp, 2, val, sizeof(struct wda_qmi_result));
}

struct wda_qmi_result *wda_set_data_format_resp_get_r(struct wda_set_data_format_resp *set_data_format_resp)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)set_data_format_resp, 2, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct wda_qmi_result))
		return NULL;

	return ptr;
}


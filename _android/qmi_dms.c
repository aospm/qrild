#include <errno.h>
#include <string.h>
#include "qmi_dms.h"

struct dms_get_operating_mode_req *dms_get_operating_mode_req_alloc(unsigned txn)
{
	return (struct dms_get_operating_mode_req*)qmi_tlv_init(txn, 45, 0);
}

struct dms_get_operating_mode_req *dms_get_operating_mode_req_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct dms_get_operating_mode_req*)qmi_tlv_decode(buf, len, txn, 0);
}

void *dms_get_operating_mode_req_encode(struct dms_get_operating_mode_req *get_operating_mode_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_operating_mode_req, len);
}

void dms_get_operating_mode_req_free(struct dms_get_operating_mode_req *get_operating_mode_req)
{
	qmi_tlv_free((struct qmi_tlv*)get_operating_mode_req);
}

struct dms_get_operating_mode_resp *dms_get_operating_mode_resp_alloc(unsigned txn)
{
	return (struct dms_get_operating_mode_resp*)qmi_tlv_init(txn, 45, 2);
}

struct dms_get_operating_mode_resp *dms_get_operating_mode_resp_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct dms_get_operating_mode_resp*)qmi_tlv_decode(buf, len, txn, 2);
}

void *dms_get_operating_mode_resp_encode(struct dms_get_operating_mode_resp *get_operating_mode_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_operating_mode_resp, len);
}

void dms_get_operating_mode_resp_free(struct dms_get_operating_mode_resp *get_operating_mode_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_operating_mode_resp);
}

int dms_get_operating_mode_resp_set_res(struct dms_get_operating_mode_resp *get_operating_mode_resp, struct dms_qmi_result *val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_operating_mode_resp, 2, val, sizeof(struct dms_qmi_result));
}

struct dms_qmi_result *dms_get_operating_mode_resp_get_res(struct dms_get_operating_mode_resp *get_operating_mode_resp)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_operating_mode_resp, 2, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct dms_qmi_result))
		return NULL;

	return ptr;
}

int dms_get_operating_mode_resp_set_mode(struct dms_get_operating_mode_resp *get_operating_mode_resp, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_operating_mode_resp, 1, &val, sizeof(uint8_t));
}

int dms_get_operating_mode_resp_get_mode(struct dms_get_operating_mode_resp *get_operating_mode_resp, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_operating_mode_resp, 1, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int dms_get_operating_mode_resp_set_offline_reason(struct dms_get_operating_mode_resp *get_operating_mode_resp, uint16_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_operating_mode_resp, 16, &val, sizeof(uint16_t));
}

int dms_get_operating_mode_resp_get_offline_reason(struct dms_get_operating_mode_resp *get_operating_mode_resp, uint16_t *val)
{
	uint16_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_operating_mode_resp, 16, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint16_t))
		return -EINVAL;

	*val = *(uint16_t*)ptr;
	return 0;
}

int dms_get_operating_mode_resp_set_hardware_restricted(struct dms_get_operating_mode_resp *get_operating_mode_resp, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_operating_mode_resp, 17, &val, sizeof(uint8_t));
}

int dms_get_operating_mode_resp_get_hardware_restricted(struct dms_get_operating_mode_resp *get_operating_mode_resp, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_operating_mode_resp, 17, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

struct dms_set_operating_mode_req *dms_set_operating_mode_req_alloc(unsigned txn)
{
	return (struct dms_set_operating_mode_req*)qmi_tlv_init(txn, 46, 0);
}

struct dms_set_operating_mode_req *dms_set_operating_mode_req_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct dms_set_operating_mode_req*)qmi_tlv_decode(buf, len, txn, 0);
}

void *dms_set_operating_mode_req_encode(struct dms_set_operating_mode_req *set_operating_mode_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)set_operating_mode_req, len);
}

void dms_set_operating_mode_req_free(struct dms_set_operating_mode_req *set_operating_mode_req)
{
	qmi_tlv_free((struct qmi_tlv*)set_operating_mode_req);
}

int dms_set_operating_mode_req_set_mode(struct dms_set_operating_mode_req *set_operating_mode_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_operating_mode_req, 1, &val, sizeof(uint8_t));
}

int dms_set_operating_mode_req_get_mode(struct dms_set_operating_mode_req *set_operating_mode_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)set_operating_mode_req, 1, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

struct dms_set_operating_mode_resp *dms_set_operating_mode_resp_alloc(unsigned txn)
{
	return (struct dms_set_operating_mode_resp*)qmi_tlv_init(txn, 46, 0);
}

struct dms_set_operating_mode_resp *dms_set_operating_mode_resp_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct dms_set_operating_mode_resp*)qmi_tlv_decode(buf, len, txn, 0);
}

void *dms_set_operating_mode_resp_encode(struct dms_set_operating_mode_resp *set_operating_mode_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)set_operating_mode_resp, len);
}

void dms_set_operating_mode_resp_free(struct dms_set_operating_mode_resp *set_operating_mode_resp)
{
	qmi_tlv_free((struct qmi_tlv*)set_operating_mode_resp);
}

int dms_set_operating_mode_resp_set_res(struct dms_set_operating_mode_resp *set_operating_mode_resp, struct dms_qmi_result *val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_operating_mode_resp, 2, val, sizeof(struct dms_qmi_result));
}

struct dms_qmi_result *dms_set_operating_mode_resp_get_res(struct dms_set_operating_mode_resp *set_operating_mode_resp)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)set_operating_mode_resp, 2, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct dms_qmi_result))
		return NULL;

	return ptr;
}


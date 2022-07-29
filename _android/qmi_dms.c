#include <errno.h>
#include <string.h>
#include "qmi_dms.h"

struct dms_get_revision_req *dms_get_revision_req_alloc(unsigned txn)
{
	return (struct dms_get_revision_req*)qmi_tlv_init(txn, 35, 0);
}

void *dms_get_revision_req_encode(struct dms_get_revision_req *get_revision_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_revision_req, len);
}

void dms_get_revision_req_free(struct dms_get_revision_req *get_revision_req)
{
	qmi_tlv_free((struct qmi_tlv*)get_revision_req);
}

struct dms_get_revision_resp *dms_get_revision_resp_parse(void *buf, size_t len)
{
	return (struct dms_get_revision_resp*)qmi_tlv_decode(buf, len);
}

void dms_get_revision_resp_getall(struct dms_get_revision_resp *get_revision_resp, struct dms_get_revision_resp_data *data)
{
	int rc;
	(void)rc;

	data->revision = dms_get_revision_resp_get_revision(get_revision_resp);
}

void dms_get_revision_resp_free(struct dms_get_revision_resp *get_revision_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_revision_resp);
}

char *dms_get_revision_resp_get_revision(struct dms_get_revision_resp *get_revision_resp)
{
	char *ptr = NULL, *out;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_revision_resp, 1, &len);
	if (!ptr)
		return NULL;

	if (!ptr[len-1]) {
		out = malloc(len);
		memcpy(out, ptr, len);
	} else {
		out = malloc(len + 1);
		memcpy(out, ptr, len);
		out[len] = '\0';
	}

	return out;
}

struct dms_get_ids_req *dms_get_ids_req_alloc(unsigned txn)
{
	return (struct dms_get_ids_req*)qmi_tlv_init(txn, 37, 0);
}

void *dms_get_ids_req_encode(struct dms_get_ids_req *get_ids_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_ids_req, len);
}

void dms_get_ids_req_free(struct dms_get_ids_req *get_ids_req)
{
	qmi_tlv_free((struct qmi_tlv*)get_ids_req);
}

struct dms_get_ids_resp *dms_get_ids_resp_parse(void *buf, size_t len)
{
	return (struct dms_get_ids_resp*)qmi_tlv_decode(buf, len);
}

void dms_get_ids_resp_getall(struct dms_get_ids_resp *get_ids_resp, struct dms_get_ids_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = qmi_tlv_get((struct qmi_tlv*)get_ids_resp, 2, NULL);
	data->esn = dms_get_ids_resp_get_esn(get_ids_resp);
	data->esn_valid = !!data->esn;
	data->imei = dms_get_ids_resp_get_imei(get_ids_resp);
	data->imei_valid = !!data->imei;
	data->meid = dms_get_ids_resp_get_meid(get_ids_resp);
	data->meid_valid = !!data->meid;
	data->imei_ver = dms_get_ids_resp_get_imei_ver(get_ids_resp);
	data->imei_ver_valid = !!data->imei_ver;
}

void dms_get_ids_resp_free(struct dms_get_ids_resp *get_ids_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_ids_resp);
}

char *dms_get_ids_resp_get_esn(struct dms_get_ids_resp *get_ids_resp)
{
	char *ptr = NULL, *out;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_ids_resp, 16, &len);
	if (!ptr)
		return NULL;

	if (!ptr[len-1]) {
		out = malloc(len);
		memcpy(out, ptr, len);
	} else {
		out = malloc(len + 1);
		memcpy(out, ptr, len);
		out[len] = '\0';
	}

	return out;
}

char *dms_get_ids_resp_get_imei(struct dms_get_ids_resp *get_ids_resp)
{
	char *ptr = NULL, *out;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_ids_resp, 17, &len);
	if (!ptr)
		return NULL;

	if (!ptr[len-1]) {
		out = malloc(len);
		memcpy(out, ptr, len);
	} else {
		out = malloc(len + 1);
		memcpy(out, ptr, len);
		out[len] = '\0';
	}

	return out;
}

char *dms_get_ids_resp_get_meid(struct dms_get_ids_resp *get_ids_resp)
{
	char *ptr = NULL, *out;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_ids_resp, 18, &len);
	if (!ptr)
		return NULL;

	if (!ptr[len-1]) {
		out = malloc(len);
		memcpy(out, ptr, len);
	} else {
		out = malloc(len + 1);
		memcpy(out, ptr, len);
		out[len] = '\0';
	}

	return out;
}

char *dms_get_ids_resp_get_imei_ver(struct dms_get_ids_resp *get_ids_resp)
{
	char *ptr = NULL, *out;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_ids_resp, 19, &len);
	if (!ptr)
		return NULL;

	if (!ptr[len-1]) {
		out = malloc(len);
		memcpy(out, ptr, len);
	} else {
		out = malloc(len + 1);
		memcpy(out, ptr, len);
		out[len] = '\0';
	}

	return out;
}

struct dms_get_operating_mode_req *dms_get_operating_mode_req_alloc(unsigned txn)
{
	return (struct dms_get_operating_mode_req*)qmi_tlv_init(txn, 45, 0);
}

void *dms_get_operating_mode_req_encode(struct dms_get_operating_mode_req *get_operating_mode_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_operating_mode_req, len);
}

void dms_get_operating_mode_req_free(struct dms_get_operating_mode_req *get_operating_mode_req)
{
	qmi_tlv_free((struct qmi_tlv*)get_operating_mode_req);
}

struct dms_get_operating_mode_resp *dms_get_operating_mode_resp_parse(void *buf, size_t len)
{
	return (struct dms_get_operating_mode_resp*)qmi_tlv_decode(buf, len);
}

void dms_get_operating_mode_resp_getall(struct dms_get_operating_mode_resp *get_operating_mode_resp, struct dms_get_operating_mode_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = qmi_tlv_get((struct qmi_tlv*)get_operating_mode_resp, 2, NULL);
	rc = dms_get_operating_mode_resp_get_mode(get_operating_mode_resp, &data->mode);
	rc = dms_get_operating_mode_resp_get_offline_reason(get_operating_mode_resp, &data->offline_reason);
	data->offline_reason_valid = rc >= 0;
	rc = dms_get_operating_mode_resp_get_hardware_restricted(get_operating_mode_resp, &data->hardware_restricted);
}

void dms_get_operating_mode_resp_free(struct dms_get_operating_mode_resp *get_operating_mode_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_operating_mode_resp);
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

struct dms_set_operating_mode_resp *dms_set_operating_mode_resp_alloc(unsigned txn)
{
	return (struct dms_set_operating_mode_resp*)qmi_tlv_init(txn, 46, 0);
}

void *dms_set_operating_mode_resp_encode(struct dms_set_operating_mode_resp *set_operating_mode_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)set_operating_mode_resp, len);
}

void dms_set_operating_mode_resp_free(struct dms_set_operating_mode_resp *set_operating_mode_resp)
{
	qmi_tlv_free((struct qmi_tlv*)set_operating_mode_resp);
}


#include <errno.h>
#include <string.h>
#include "qmi_nas.h"

struct nas_register_indications_req *nas_register_indications_req_alloc(unsigned txn)
{
	return (struct nas_register_indications_req*)qmi_tlv_init(txn, 3, 0);
}

struct nas_register_indications_req *nas_register_indications_req_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct nas_register_indications_req*)qmi_tlv_decode(buf, len, txn, 0);
}

void *nas_register_indications_req_encode(struct nas_register_indications_req *register_indications_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)register_indications_req, len);
}

void nas_register_indications_req_free(struct nas_register_indications_req *register_indications_req)
{
	qmi_tlv_free((struct qmi_tlv*)register_indications_req);
}

int nas_register_indications_req_set_system_selection_preference(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 16, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_system_selection_preference(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 16, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_ddtm_events(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 18, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_ddtm_events(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 18, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_serving_system_events(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 19, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_serving_system_events(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 19, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_dual_standby_preference(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 20, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_dual_standby_preference(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 20, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_subscription_info(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 21, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_subscription_info(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 21, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_network_time(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 23, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_network_time(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 23, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_system_info(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 24, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_system_info(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 24, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_signal_info(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 25, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_signal_info(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 25, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_error_rate(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 26, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_error_rate(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 26, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_hdr_new_uati_assigned(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 27, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_hdr_new_uati_assigned(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 27, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_hdr_session_closed(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 28, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_hdr_session_closed(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 28, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_managed_roaming(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 29, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_managed_roaming(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 29, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_current_plmn_name(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 30, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_current_plmn_name(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 30, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_embms_status(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 31, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_embms_status(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 31, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_rf_band_information(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 32, &val, sizeof(uint8_t));
}

int nas_register_indications_req_get_rf_band_information(struct nas_register_indications_req *register_indications_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 32, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int nas_register_indications_req_set_network_reject_information(struct nas_register_indications_req *register_indications_req, struct nas_network_reject_info *val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 33, val, sizeof(struct nas_network_reject_info));
}

struct nas_network_reject_info *nas_register_indications_req_get_network_reject_information(struct nas_register_indications_req *register_indications_req)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)register_indications_req, 33, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct nas_network_reject_info))
		return NULL;

	return ptr;
}

struct nas_get_signal_strength_req *nas_get_signal_strength_req_alloc(unsigned txn)
{
	return (struct nas_get_signal_strength_req*)qmi_tlv_init(txn, 32, 0);
}

struct nas_get_signal_strength_req *nas_get_signal_strength_req_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct nas_get_signal_strength_req*)qmi_tlv_decode(buf, len, txn, 0);
}

void *nas_get_signal_strength_req_encode(struct nas_get_signal_strength_req *get_signal_strength_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_signal_strength_req, len);
}

void nas_get_signal_strength_req_free(struct nas_get_signal_strength_req *get_signal_strength_req)
{
	qmi_tlv_free((struct qmi_tlv*)get_signal_strength_req);
}

int nas_get_signal_strength_req_set_mask(struct nas_get_signal_strength_req *get_signal_strength_req, uint16_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_signal_strength_req, 16, &val, sizeof(uint16_t));
}

int nas_get_signal_strength_req_get_mask(struct nas_get_signal_strength_req *get_signal_strength_req, uint16_t *val)
{
	uint16_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_strength_req, 16, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint16_t))
		return -EINVAL;

	*val = *(uint16_t*)ptr;
	return 0;
}

struct nas_get_signal_strength_resp *nas_get_signal_strength_resp_alloc(unsigned txn)
{
	return (struct nas_get_signal_strength_resp*)qmi_tlv_init(txn, 45, 2);
}

struct nas_get_signal_strength_resp *nas_get_signal_strength_resp_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct nas_get_signal_strength_resp*)qmi_tlv_decode(buf, len, txn, 2);
}

void *nas_get_signal_strength_resp_encode(struct nas_get_signal_strength_resp *get_signal_strength_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_signal_strength_resp, len);
}

void nas_get_signal_strength_resp_free(struct nas_get_signal_strength_resp *get_signal_strength_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_signal_strength_resp);
}

int nas_get_signal_strength_resp_set_res(struct nas_get_signal_strength_resp *get_signal_strength_resp, struct nas_qmi_result *val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_signal_strength_resp, 2, val, sizeof(struct nas_qmi_result));
}

struct nas_qmi_result *nas_get_signal_strength_resp_get_res(struct nas_get_signal_strength_resp *get_signal_strength_resp)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_strength_resp, 2, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct nas_qmi_result))
		return NULL;

	return ptr;
}

int nas_get_signal_strength_resp_set_lte_snr(struct nas_get_signal_strength_resp *get_signal_strength_resp, int16_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_signal_strength_resp, 23, &val, sizeof(int16_t));
}

int nas_get_signal_strength_resp_get_lte_snr(struct nas_get_signal_strength_resp *get_signal_strength_resp, int16_t *val)
{
	int16_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_strength_resp, 23, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(int16_t))
		return -EINVAL;

	*val = *(int16_t*)ptr;
	return 0;
}

int nas_get_signal_strength_resp_set_lte_rsrp(struct nas_get_signal_strength_resp *get_signal_strength_resp, int16_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_signal_strength_resp, 24, &val, sizeof(int16_t));
}

int nas_get_signal_strength_resp_get_lte_rsrp(struct nas_get_signal_strength_resp *get_signal_strength_resp, int16_t *val)
{
	int16_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_strength_resp, 24, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(int16_t))
		return -EINVAL;

	*val = *(int16_t*)ptr;
	return 0;
}

int nas_get_signal_strength_resp_set_strength(struct nas_get_signal_strength_resp *get_signal_strength_resp, struct nas_signal_strength *val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_signal_strength_resp, 1, val, sizeof(struct nas_signal_strength));
}

struct nas_signal_strength *nas_get_signal_strength_resp_get_strength(struct nas_get_signal_strength_resp *get_signal_strength_resp)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_strength_resp, 1, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct nas_signal_strength))
		return NULL;

	return ptr;
}

int nas_get_signal_strength_resp_set_strength_list(struct nas_get_signal_strength_resp *get_signal_strength_resp, struct nas_signal_strength_list *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->interfaces_n;
	len += 1;
	for(size_t i = 0; i < val->interfaces_n; i++) {
		*((int8_t*)(ptr + len)) = val->interfaces[i].strength;
		len += 1;
		*((int8_t*)(ptr + len)) = val->interfaces[i].interface;
		len += 1;
	}
	rc = qmi_tlv_set((struct qmi_tlv*)get_signal_strength_resp, 16, ptr, len);
	free(ptr);
	return rc;
}

struct nas_signal_strength_list *nas_get_signal_strength_resp_get_strength_list(struct nas_get_signal_strength_resp *get_signal_strength_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_signal_strength_list *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_strength_resp, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_signal_strength_list));
	out->interfaces_n = get_next(uint8_t, 1);
	size_t interfaces_sz = sizeof(struct signal_strength_list_interfaces);
	out->interfaces = malloc(interfaces_sz * out->interfaces_n);
	for(size_t i = 0; i < out->interfaces_n; i++) {
		out->interfaces[i].strength = get_next(int8_t, 1);
		out->interfaces[i].interface = get_next(int8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_set_operating_mode_req *nas_set_operating_mode_req_alloc(unsigned txn)
{
	return (struct nas_set_operating_mode_req*)qmi_tlv_init(txn, 46, 0);
}

struct nas_set_operating_mode_req *nas_set_operating_mode_req_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct nas_set_operating_mode_req*)qmi_tlv_decode(buf, len, txn, 0);
}

void *nas_set_operating_mode_req_encode(struct nas_set_operating_mode_req *set_operating_mode_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)set_operating_mode_req, len);
}

void nas_set_operating_mode_req_free(struct nas_set_operating_mode_req *set_operating_mode_req)
{
	qmi_tlv_free((struct qmi_tlv*)set_operating_mode_req);
}

int nas_set_operating_mode_req_set_mode(struct nas_set_operating_mode_req *set_operating_mode_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_operating_mode_req, 1, &val, sizeof(uint8_t));
}

int nas_set_operating_mode_req_get_mode(struct nas_set_operating_mode_req *set_operating_mode_req, uint8_t *val)
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

struct nas_set_operating_mode_resp *nas_set_operating_mode_resp_alloc(unsigned txn)
{
	return (struct nas_set_operating_mode_resp*)qmi_tlv_init(txn, 46, 0);
}

struct nas_set_operating_mode_resp *nas_set_operating_mode_resp_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct nas_set_operating_mode_resp*)qmi_tlv_decode(buf, len, txn, 0);
}

void *nas_set_operating_mode_resp_encode(struct nas_set_operating_mode_resp *set_operating_mode_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)set_operating_mode_resp, len);
}

void nas_set_operating_mode_resp_free(struct nas_set_operating_mode_resp *set_operating_mode_resp)
{
	qmi_tlv_free((struct qmi_tlv*)set_operating_mode_resp);
}

int nas_set_operating_mode_resp_set_res(struct nas_set_operating_mode_resp *set_operating_mode_resp, struct nas_qmi_result *val)
{
	return qmi_tlv_set((struct qmi_tlv*)set_operating_mode_resp, 2, val, sizeof(struct nas_qmi_result));
}

struct nas_qmi_result *nas_set_operating_mode_resp_get_res(struct nas_set_operating_mode_resp *set_operating_mode_resp)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)set_operating_mode_resp, 2, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct nas_qmi_result))
		return NULL;

	return ptr;
}


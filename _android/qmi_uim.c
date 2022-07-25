#include <errno.h>
#include <string.h>
#include "qmi_uim.h"

struct uim_get_card_status_req *uim_get_card_status_req_alloc(unsigned txn)
{
	return (struct uim_get_card_status_req*)qmi_tlv_init(txn, 47, 0);
}

struct uim_get_card_status_req *uim_get_card_status_req_parse(void *buf, size_t len)
{
	return (struct uim_get_card_status_req*)qmi_tlv_decode(buf, len);
}

void *uim_get_card_status_req_encode(struct uim_get_card_status_req *get_card_status_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_card_status_req, len);
}

void uim_get_card_status_req_free(struct uim_get_card_status_req *get_card_status_req)
{
	qmi_tlv_free((struct qmi_tlv*)get_card_status_req);
}

struct uim_get_card_status_resp *uim_get_card_status_resp_alloc(unsigned txn)
{
	return (struct uim_get_card_status_resp*)qmi_tlv_init(txn, 47, 2);
}

struct uim_get_card_status_resp *uim_get_card_status_resp_parse(void *buf, size_t len)
{
	return (struct uim_get_card_status_resp*)qmi_tlv_decode(buf, len);
}

void *uim_get_card_status_resp_encode(struct uim_get_card_status_resp *get_card_status_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_card_status_resp, len);
}

void uim_get_card_status_resp_free(struct uim_get_card_status_resp *get_card_status_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_card_status_resp);
}

int uim_get_card_status_resp_set_status(struct uim_get_card_status_resp *get_card_status_resp, struct uim_card_status *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint16_t*)(ptr + len)) = val->index_gw_primary;
	len += 2;
	*((uint16_t*)(ptr + len)) = val->index_1x_primary;
	len += 2;
	*((uint16_t*)(ptr + len)) = val->index_gw_secondary;
	len += 2;
	*((uint16_t*)(ptr + len)) = val->index_1x_secondary;
	len += 2;
	*((uint8_t*)(ptr + len)) = val->cards_n;
	len += 1;
	for(size_t i = 0; i < val->cards_n; i++) {
		*((uint8_t*)(ptr + len)) = val->cards[i].card_state;
		len += 1;
		*((uint8_t*)(ptr + len)) = val->cards[i].upin_state;
		len += 1;
		*((uint8_t*)(ptr + len)) = val->cards[i].upin_retries;
		len += 1;
		*((uint8_t*)(ptr + len)) = val->cards[i].upuk_retries;
		len += 1;
		*((uint8_t*)(ptr + len)) = val->cards[i].error_code;
		len += 1;
		*((uint8_t*)(ptr + len)) = val->cards[i].applications_n;
		len += 1;
		for(size_t ii = 0; ii < val->cards[i].applications_n; ii++) {
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].type;
			len += 1;
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].state;
			len += 1;
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].personalization_state;
			len += 1;
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].personalization_feature;
			len += 1;
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].personalization_retries;
			len += 1;
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].personalization_unblock_retries;
			len += 1;
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].application_identifier_value_n;
			len += 1;
			for(size_t iii = 0; iii < val->cards[i].applications[ii].application_identifier_value_n; iii++) {
				*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].application_identifier_value[iii];
				len += 1;
			}
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].upin_replaces_pin1;
			len += 1;
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].pin1_state;
			len += 1;
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].pin1_retries;
			len += 1;
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].puk1_retries;
			len += 1;
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].pin2_state;
			len += 1;
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].pin2_retries;
			len += 1;
			*((uint8_t*)(ptr + len)) = val->cards[i].applications[ii].puk2_retries;
			len += 1;
		}
	}
	rc = qmi_tlv_set((struct qmi_tlv*)get_card_status_resp, 16, ptr, len);
	free(ptr);
	return rc;
}

struct uim_card_status *uim_get_card_status_resp_get_status(struct uim_get_card_status_resp *get_card_status_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct uim_card_status *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_card_status_resp, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct uim_card_status));
	out->index_gw_primary = get_next(uint16_t, 2);
	out->index_1x_primary = get_next(uint16_t, 2);
	out->index_gw_secondary = get_next(uint16_t, 2);
	out->index_1x_secondary = get_next(uint16_t, 2);
	out->cards_n = get_next(uint8_t, 1);
	size_t cards_sz = sizeof(struct card_status_cards);
	out->cards = malloc(cards_sz * out->cards_n);
	for(size_t i = 0; i < out->cards_n; i++) {
		out->cards[i].card_state = get_next(uint8_t, 1);
		out->cards[i].upin_state = get_next(uint8_t, 1);
		out->cards[i].upin_retries = get_next(uint8_t, 1);
		out->cards[i].upuk_retries = get_next(uint8_t, 1);
		out->cards[i].error_code = get_next(uint8_t, 1);
		out->cards[i].applications_n = get_next(uint8_t, 1);
		size_t applications_sz = sizeof(struct card_status_cards_applications);
		out->cards[i].applications = malloc(applications_sz * out->cards[i].applications_n);
		for(size_t ii = 0; ii < out->cards[i].applications_n; ii++) {
			out->cards[i].applications[ii].type = get_next(uint8_t, 1);
			out->cards[i].applications[ii].state = get_next(uint8_t, 1);
			out->cards[i].applications[ii].personalization_state = get_next(uint8_t, 1);
			out->cards[i].applications[ii].personalization_feature = get_next(uint8_t, 1);
			out->cards[i].applications[ii].personalization_retries = get_next(uint8_t, 1);
			out->cards[i].applications[ii].personalization_unblock_retries = get_next(uint8_t, 1);
			out->cards[i].applications[ii].application_identifier_value_n = get_next(uint8_t, 1);
			size_t application_identifier_value_sz = 1;
			out->cards[i].applications[ii].application_identifier_value = malloc(application_identifier_value_sz * out->cards[i].applications[ii].application_identifier_value_n);
			for(size_t iii = 0; iii < out->cards[i].applications[ii].application_identifier_value_n; iii++) {
				out->cards[i].applications[ii].application_identifier_value[iii] = get_next(uint8_t, 1);
			}
			out->cards[i].applications[ii].upin_replaces_pin1 = get_next(uint8_t, 1);
			out->cards[i].applications[ii].pin1_state = get_next(uint8_t, 1);
			out->cards[i].applications[ii].pin1_retries = get_next(uint8_t, 1);
			out->cards[i].applications[ii].puk1_retries = get_next(uint8_t, 1);
			out->cards[i].applications[ii].pin2_state = get_next(uint8_t, 1);
			out->cards[i].applications[ii].pin2_retries = get_next(uint8_t, 1);
			out->cards[i].applications[ii].puk2_retries = get_next(uint8_t, 1);
		}
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct uim_change_provisioning_session_req *uim_change_provisioning_session_req_alloc(unsigned txn)
{
	return (struct uim_change_provisioning_session_req*)qmi_tlv_init(txn, 56, 0);
}

struct uim_change_provisioning_session_req *uim_change_provisioning_session_req_parse(void *buf, size_t len)
{
	return (struct uim_change_provisioning_session_req*)qmi_tlv_decode(buf, len);
}

void *uim_change_provisioning_session_req_encode(struct uim_change_provisioning_session_req *change_provisioning_session_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)change_provisioning_session_req, len);
}

void uim_change_provisioning_session_req_free(struct uim_change_provisioning_session_req *change_provisioning_session_req)
{
	qmi_tlv_free((struct qmi_tlv*)change_provisioning_session_req);
}

int uim_change_provisioning_session_req_set_session_change(struct uim_change_provisioning_session_req *change_provisioning_session_req, struct uim_provisioning_session_change *val)
{
	return qmi_tlv_set((struct qmi_tlv*)change_provisioning_session_req, 1, val, sizeof(struct uim_provisioning_session_change));
}

struct uim_provisioning_session_change *uim_change_provisioning_session_req_get_session_change(struct uim_change_provisioning_session_req *change_provisioning_session_req)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)change_provisioning_session_req, 1, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct uim_provisioning_session_change))
		return NULL;

	return ptr;
}

int uim_change_provisioning_session_req_set_application_information(struct uim_change_provisioning_session_req *change_provisioning_session_req, struct uim_provisioning_session_application *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->slot;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->application_identifier_value_n;
	len += 1;
	for(size_t i = 0; i < val->application_identifier_value_n; i++) {
		*((uint8_t*)(ptr + len)) = val->application_identifier_value[i];
		len += 1;
	}
	rc = qmi_tlv_set((struct qmi_tlv*)change_provisioning_session_req, 16, ptr, len);
	free(ptr);
	return rc;
}

struct uim_provisioning_session_application *uim_change_provisioning_session_req_get_application_information(struct uim_change_provisioning_session_req *change_provisioning_session_req)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct uim_provisioning_session_application *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)change_provisioning_session_req, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct uim_provisioning_session_application));
	out->slot = get_next(uint8_t, 1);
	out->application_identifier_value_n = get_next(uint8_t, 1);
	size_t application_identifier_value_sz = 1;
	out->application_identifier_value = malloc(application_identifier_value_sz * out->application_identifier_value_n);
	for(size_t i = 0; i < out->application_identifier_value_n; i++) {
		out->application_identifier_value[i] = get_next(uint8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct uim_change_provisioning_session_resp *uim_change_provisioning_session_resp_alloc(unsigned txn)
{
	return (struct uim_change_provisioning_session_resp*)qmi_tlv_init(txn, 56, 2);
}

struct uim_change_provisioning_session_resp *uim_change_provisioning_session_resp_parse(void *buf, size_t len)
{
	return (struct uim_change_provisioning_session_resp*)qmi_tlv_decode(buf, len);
}

void *uim_change_provisioning_session_resp_encode(struct uim_change_provisioning_session_resp *change_provisioning_session_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)change_provisioning_session_resp, len);
}

void uim_change_provisioning_session_resp_free(struct uim_change_provisioning_session_resp *change_provisioning_session_resp)
{
	qmi_tlv_free((struct qmi_tlv*)change_provisioning_session_resp);
}

struct uim_get_slot_status_req *uim_get_slot_status_req_alloc(unsigned txn)
{
	return (struct uim_get_slot_status_req*)qmi_tlv_init(txn, 71, 0);
}

struct uim_get_slot_status_req *uim_get_slot_status_req_parse(void *buf, size_t len)
{
	return (struct uim_get_slot_status_req*)qmi_tlv_decode(buf, len);
}

void *uim_get_slot_status_req_encode(struct uim_get_slot_status_req *get_slot_status_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_slot_status_req, len);
}

void uim_get_slot_status_req_free(struct uim_get_slot_status_req *get_slot_status_req)
{
	qmi_tlv_free((struct qmi_tlv*)get_slot_status_req);
}

struct uim_get_slot_status_resp *uim_get_slot_status_resp_alloc(unsigned txn)
{
	return (struct uim_get_slot_status_resp*)qmi_tlv_init(txn, 71, 2);
}

struct uim_get_slot_status_resp *uim_get_slot_status_resp_parse(void *buf, size_t len)
{
	return (struct uim_get_slot_status_resp*)qmi_tlv_decode(buf, len);
}

void *uim_get_slot_status_resp_encode(struct uim_get_slot_status_resp *get_slot_status_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_slot_status_resp, len);
}

void uim_get_slot_status_resp_free(struct uim_get_slot_status_resp *get_slot_status_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_slot_status_resp);
}

int uim_get_slot_status_resp_set_slot_state(struct uim_get_slot_status_resp *get_slot_status_resp, struct uim_physical_slot_state *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->slots_n;
	len += 1;
	for(size_t i = 0; i < val->slots_n; i++) {
		*((uint32_t*)(ptr + len)) = val->slots[i].card_state;
		len += 4;
		*((uint32_t*)(ptr + len)) = val->slots[i].slot_state;
		len += 4;
		*((uint8_t*)(ptr + len)) = val->slots[i].logical_slot;
		len += 1;
		*((uint8_t*)(ptr + len)) = val->slots[i].iccid_n;
		len += 1;
		for(size_t ii = 0; ii < val->slots[i].iccid_n; ii++) {
			*((uint8_t*)(ptr + len)) = val->slots[i].iccid[ii];
			len += 1;
		}
	}
	rc = qmi_tlv_set((struct qmi_tlv*)get_slot_status_resp, 16, ptr, len);
	free(ptr);
	return rc;
}

struct uim_physical_slot_state *uim_get_slot_status_resp_get_slot_state(struct uim_get_slot_status_resp *get_slot_status_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct uim_physical_slot_state *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_slot_status_resp, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct uim_physical_slot_state));
	out->slots_n = get_next(uint8_t, 1);
	size_t slots_sz = sizeof(struct physical_slot_state_slots);
	out->slots = malloc(slots_sz * out->slots_n);
	for(size_t i = 0; i < out->slots_n; i++) {
		out->slots[i].card_state = get_next(uint32_t, 4);
		out->slots[i].slot_state = get_next(uint32_t, 4);
		out->slots[i].logical_slot = get_next(uint8_t, 1);
		out->slots[i].iccid_n = get_next(uint8_t, 1);
		size_t iccid_sz = 1;
		out->slots[i].iccid = malloc(iccid_sz * out->slots[i].iccid_n);
		for(size_t ii = 0; ii < out->slots[i].iccid_n; ii++) {
			out->slots[i].iccid[ii] = get_next(uint8_t, 1);
		}
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int uim_get_slot_status_resp_set_slot_info(struct uim_get_slot_status_resp *get_slot_status_resp, struct uim_physical_slot_info *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->slots_n;
	len += 1;
	for(size_t i = 0; i < val->slots_n; i++) {
		*((uint32_t*)(ptr + len)) = val->slots[i].card_protocol;
		len += 4;
		*((uint8_t*)(ptr + len)) = val->slots[i].valid_applications;
		len += 1;
		*((uint8_t*)(ptr + len)) = val->slots[i].atr_value_n;
		len += 1;
		for(size_t ii = 0; ii < val->slots[i].atr_value_n; ii++) {
			*((uint8_t*)(ptr + len)) = val->slots[i].atr_value[ii];
			len += 1;
		}
		*((uint8_t*)(ptr + len)) = val->slots[i].is_euicc;
		len += 1;
	}
	rc = qmi_tlv_set((struct qmi_tlv*)get_slot_status_resp, 17, ptr, len);
	free(ptr);
	return rc;
}

struct uim_physical_slot_info *uim_get_slot_status_resp_get_slot_info(struct uim_get_slot_status_resp *get_slot_status_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct uim_physical_slot_info *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_slot_status_resp, 17, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct uim_physical_slot_info));
	out->slots_n = get_next(uint8_t, 1);
	size_t slots_sz = sizeof(struct physical_slot_info_slots);
	out->slots = malloc(slots_sz * out->slots_n);
	for(size_t i = 0; i < out->slots_n; i++) {
		out->slots[i].card_protocol = get_next(uint32_t, 4);
		out->slots[i].valid_applications = get_next(uint8_t, 1);
		out->slots[i].atr_value_n = get_next(uint8_t, 1);
		size_t atr_value_sz = 1;
		out->slots[i].atr_value = malloc(atr_value_sz * out->slots[i].atr_value_n);
		for(size_t ii = 0; ii < out->slots[i].atr_value_n; ii++) {
			out->slots[i].atr_value[ii] = get_next(uint8_t, 1);
		}
		out->slots[i].is_euicc = get_next(uint8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int uim_get_slot_status_resp_set_eid_info(struct uim_get_slot_status_resp *get_slot_status_resp, uint8_t *val, size_t count)
{
	return qmi_tlv_set_array((struct qmi_tlv*)get_slot_status_resp, 18, 1, val, count, sizeof(uint8_t));
}

uint8_t *uim_get_slot_status_resp_get_eid_info(struct uim_get_slot_status_resp *get_slot_status_resp, size_t *count)
{
	uint8_t *ptr;
	size_t size;
	size_t len;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_slot_status_resp, 18, 1, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(uint8_t))
		return NULL;

	*count = len;
	return ptr;
}

struct uim_get_slot_status_ind *uim_get_slot_status_ind_alloc(unsigned txn)
{
	return (struct uim_get_slot_status_ind*)qmi_tlv_init(txn, 72, 4);
}

struct uim_get_slot_status_ind *uim_get_slot_status_ind_parse(void *buf, size_t len)
{
	return (struct uim_get_slot_status_ind*)qmi_tlv_decode(buf, len);
}

void *uim_get_slot_status_ind_encode(struct uim_get_slot_status_ind *get_slot_status_ind, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_slot_status_ind, len);
}

void uim_get_slot_status_ind_free(struct uim_get_slot_status_ind *get_slot_status_ind)
{
	qmi_tlv_free((struct qmi_tlv*)get_slot_status_ind);
}

int uim_get_slot_status_ind_set_slot_state(struct uim_get_slot_status_ind *get_slot_status_ind, struct uim_physical_slot_state *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->slots_n;
	len += 1;
	for(size_t i = 0; i < val->slots_n; i++) {
		*((uint32_t*)(ptr + len)) = val->slots[i].card_state;
		len += 4;
		*((uint32_t*)(ptr + len)) = val->slots[i].slot_state;
		len += 4;
		*((uint8_t*)(ptr + len)) = val->slots[i].logical_slot;
		len += 1;
		*((uint8_t*)(ptr + len)) = val->slots[i].iccid_n;
		len += 1;
		for(size_t ii = 0; ii < val->slots[i].iccid_n; ii++) {
			*((uint8_t*)(ptr + len)) = val->slots[i].iccid[ii];
			len += 1;
		}
	}
	rc = qmi_tlv_set((struct qmi_tlv*)get_slot_status_ind, 16, ptr, len);
	free(ptr);
	return rc;
}

struct uim_physical_slot_state *uim_get_slot_status_ind_get_slot_state(struct uim_get_slot_status_ind *get_slot_status_ind)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct uim_physical_slot_state *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_slot_status_ind, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct uim_physical_slot_state));
	out->slots_n = get_next(uint8_t, 1);
	size_t slots_sz = sizeof(struct physical_slot_state_slots);
	out->slots = malloc(slots_sz * out->slots_n);
	for(size_t i = 0; i < out->slots_n; i++) {
		out->slots[i].card_state = get_next(uint32_t, 4);
		out->slots[i].slot_state = get_next(uint32_t, 4);
		out->slots[i].logical_slot = get_next(uint8_t, 1);
		out->slots[i].iccid_n = get_next(uint8_t, 1);
		size_t iccid_sz = 1;
		out->slots[i].iccid = malloc(iccid_sz * out->slots[i].iccid_n);
		for(size_t ii = 0; ii < out->slots[i].iccid_n; ii++) {
			out->slots[i].iccid[ii] = get_next(uint8_t, 1);
		}
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int uim_get_slot_status_ind_set_slot_info(struct uim_get_slot_status_ind *get_slot_status_ind, struct uim_physical_slot_info *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->slots_n;
	len += 1;
	for(size_t i = 0; i < val->slots_n; i++) {
		*((uint32_t*)(ptr + len)) = val->slots[i].card_protocol;
		len += 4;
		*((uint8_t*)(ptr + len)) = val->slots[i].valid_applications;
		len += 1;
		*((uint8_t*)(ptr + len)) = val->slots[i].atr_value_n;
		len += 1;
		for(size_t ii = 0; ii < val->slots[i].atr_value_n; ii++) {
			*((uint8_t*)(ptr + len)) = val->slots[i].atr_value[ii];
			len += 1;
		}
		*((uint8_t*)(ptr + len)) = val->slots[i].is_euicc;
		len += 1;
	}
	rc = qmi_tlv_set((struct qmi_tlv*)get_slot_status_ind, 17, ptr, len);
	free(ptr);
	return rc;
}

struct uim_physical_slot_info *uim_get_slot_status_ind_get_slot_info(struct uim_get_slot_status_ind *get_slot_status_ind)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct uim_physical_slot_info *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_slot_status_ind, 17, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct uim_physical_slot_info));
	out->slots_n = get_next(uint8_t, 1);
	size_t slots_sz = sizeof(struct physical_slot_info_slots);
	out->slots = malloc(slots_sz * out->slots_n);
	for(size_t i = 0; i < out->slots_n; i++) {
		out->slots[i].card_protocol = get_next(uint32_t, 4);
		out->slots[i].valid_applications = get_next(uint8_t, 1);
		out->slots[i].atr_value_n = get_next(uint8_t, 1);
		size_t atr_value_sz = 1;
		out->slots[i].atr_value = malloc(atr_value_sz * out->slots[i].atr_value_n);
		for(size_t ii = 0; ii < out->slots[i].atr_value_n; ii++) {
			out->slots[i].atr_value[ii] = get_next(uint8_t, 1);
		}
		out->slots[i].is_euicc = get_next(uint8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int uim_get_slot_status_ind_set_eid_info(struct uim_get_slot_status_ind *get_slot_status_ind, uint8_t *val, size_t count)
{
	return qmi_tlv_set_array((struct qmi_tlv*)get_slot_status_ind, 18, 1, val, count, sizeof(uint8_t));
}

uint8_t *uim_get_slot_status_ind_get_eid_info(struct uim_get_slot_status_ind *get_slot_status_ind, size_t *count)
{
	uint8_t *ptr;
	size_t size;
	size_t len;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_slot_status_ind, 18, 1, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(uint8_t))
		return NULL;

	*count = len;
	return ptr;
}


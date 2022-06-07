#include <errno.h>
#include <string.h>
#include "qmi_uim.h"

struct uim_get_card_status_req *uim_get_card_status_req_alloc(unsigned txn)
{
	return (struct uim_get_card_status_req*)qmi_tlv_init(txn, 47, 0);
}

struct uim_get_card_status_req *uim_get_card_status_req_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct uim_get_card_status_req*)qmi_tlv_decode(buf, len, txn, 0);
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

struct uim_get_card_status_resp *uim_get_card_status_resp_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct uim_get_card_status_resp*)qmi_tlv_decode(buf, len, txn, 2);
}

void *uim_get_card_status_resp_encode(struct uim_get_card_status_resp *get_card_status_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_card_status_resp, len);
}

void uim_get_card_status_resp_free(struct uim_get_card_status_resp *get_card_status_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_card_status_resp);
}

int uim_get_card_status_resp_set_result(struct uim_get_card_status_resp *get_card_status_resp, struct uim_qmi_result *val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_card_status_resp, 2, val, sizeof(struct uim_qmi_result));
}

struct uim_qmi_result *uim_get_card_status_resp_get_result(struct uim_get_card_status_resp *get_card_status_resp)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_card_status_resp, 2, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct uim_qmi_result))
		return NULL;

	return ptr;
}

int uim_get_card_status_resp_set_status(struct uim_get_card_status_resp *get_card_status_resp, struct uim_card_status *val)
{
	/* This is broken for now (doesn't serialise ptr members) */
	return qmi_tlv_set((struct qmi_tlv*)get_card_status_resp, 16, val, sizeof(struct uim_card_status));
}

struct uim_card_status *uim_get_card_status_resp_get_status(struct uim_get_card_status_resp *get_card_status_resp)
{
	size_t len = 0, buf_sz, amt;
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
	fprintf(stderr, "%s: expected at least %u bytes but got %u\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}


#include <errno.h>
#include <string.h>
#include "qmi_uim.h"

const struct qmi_tlv_msg_name uim_msg_name_map[14] = {
	{ .msg_id = 47, .msg_name = "uim_get_card_status_resp" },
	{ .msg_id = 56, .msg_name = "uim_change_provisioning_session_req" },
	{ .msg_id = 56, .msg_name = "uim_change_provisioning_session_resp" },
	{ .msg_id = 66, .msg_name = "uim_icc_open_logical_channel_req" },
	{ .msg_id = 66, .msg_name = "uim_icc_open_logical_channel_resp" },
	{ .msg_id = 71, .msg_name = "uim_get_slot_status_req" },
	{ .msg_id = 71, .msg_name = "uim_get_slot_status_resp" },
	{ .msg_id = 72, .msg_name = "uim_get_slot_status_ind" },
	{ .msg_id = 32, .msg_name = "uim_read_transparent_req" },
	{ .msg_id = 32, .msg_name = "uim_read_transparent_resp" },
	{ .msg_id = 33, .msg_name = "uim_read_record_req" },
	{ .msg_id = 33, .msg_name = "uim_read_record_resp" },
	{ .msg_id = 36, .msg_name = "uim_get_file_attrs_req" },
	{ .msg_id = 36, .msg_name = "uim_get_file_attrs_resp" },
};

struct uim_get_card_status_resp *uim_get_card_status_resp_parse(void *buf, size_t len)
{
	return (struct uim_get_card_status_resp*)qmi_tlv_decode(buf, len);
}

void uim_get_card_status_resp_getall(struct uim_get_card_status_resp *get_card_status_resp, struct uim_get_card_status_resp_data *data)
{
	int rc;
	(void)rc;

	data->result = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->result, qmi_tlv_get((struct qmi_tlv*)get_card_status_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
	data->status = uim_get_card_status_resp_get_status(get_card_status_resp);
	data->status_valid = !!data->status;
}

void uim_get_card_status_resp_data_free(struct uim_get_card_status_resp_data *data)
{

		free(data->result);
	if(data->status_valid) {
		uim_card_status_free(data->status);
		free(data->status);
	}
}

void uim_get_card_status_resp_free(struct uim_get_card_status_resp *get_card_status_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_card_status_resp);
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
	out->cards = malloc(1 + cards_sz * out->cards_n);
	for(size_t i = 0; i < out->cards_n; i++) {
		out->cards[i].card_state = get_next(uint8_t, 1);
		out->cards[i].upin_state = get_next(uint8_t, 1);
		out->cards[i].upin_retries = get_next(uint8_t, 1);
		out->cards[i].upuk_retries = get_next(uint8_t, 1);
		out->cards[i].error_code = get_next(uint8_t, 1);
		out->cards[i].applications_n = get_next(uint8_t, 1);
		size_t applications_sz = sizeof(struct card_status_cards_applications);
		out->cards[i].applications = malloc(1 + applications_sz * out->cards[i].applications_n);
		for(size_t ii = 0; ii < out->cards[i].applications_n; ii++) {
			out->cards[i].applications[ii].type = get_next(uint8_t, 1);
			out->cards[i].applications[ii].state = get_next(uint8_t, 1);
			out->cards[i].applications[ii].personalization_state = get_next(uint8_t, 1);
			out->cards[i].applications[ii].personalization_feature = get_next(uint8_t, 1);
			out->cards[i].applications[ii].personalization_retries = get_next(uint8_t, 1);
			out->cards[i].applications[ii].personalization_unblock_retries = get_next(uint8_t, 1);
			out->cards[i].applications[ii].application_identifier_value_n = get_next(uint8_t, 1);
			size_t application_identifier_value_sz = 1;
			out->cards[i].applications[ii].application_identifier_value = malloc(1 + application_identifier_value_sz * out->cards[i].applications[ii].application_identifier_value_n);
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
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->session_type;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->activate;
	len += 1;
	rc = qmi_tlv_set((struct qmi_tlv*)change_provisioning_session_req, 1, ptr, len);
	free(ptr);
	return rc;
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

struct uim_change_provisioning_session_resp *uim_change_provisioning_session_resp_parse(void *buf, size_t len)
{
	return (struct uim_change_provisioning_session_resp*)qmi_tlv_decode(buf, len);
}

void uim_change_provisioning_session_resp_getall(struct uim_change_provisioning_session_resp *change_provisioning_session_resp, struct uim_change_provisioning_session_resp_data *data)
{
	int rc;
	(void)rc;

	data->result = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->result, qmi_tlv_get((struct qmi_tlv*)change_provisioning_session_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
}

void uim_change_provisioning_session_resp_data_free(struct uim_change_provisioning_session_resp_data *data)
{

		free(data->result);
}

void uim_change_provisioning_session_resp_free(struct uim_change_provisioning_session_resp *change_provisioning_session_resp)
{
	qmi_tlv_free((struct qmi_tlv*)change_provisioning_session_resp);
}

struct uim_icc_open_logical_channel_req *uim_icc_open_logical_channel_req_alloc(unsigned txn)
{
	return (struct uim_icc_open_logical_channel_req*)qmi_tlv_init(txn, 66, 0);
}

void *uim_icc_open_logical_channel_req_encode(struct uim_icc_open_logical_channel_req *icc_open_logical_channel_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)icc_open_logical_channel_req, len);
}

void uim_icc_open_logical_channel_req_free(struct uim_icc_open_logical_channel_req *icc_open_logical_channel_req)
{
	qmi_tlv_free((struct qmi_tlv*)icc_open_logical_channel_req);
}

int uim_icc_open_logical_channel_req_set_slot(struct uim_icc_open_logical_channel_req *icc_open_logical_channel_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)icc_open_logical_channel_req, 1, &val, sizeof(uint8_t));
}

int uim_icc_open_logical_channel_req_set_application_id(struct uim_icc_open_logical_channel_req *icc_open_logical_channel_req, uint8_t *val, size_t count)
{
	return qmi_tlv_set_array((struct qmi_tlv*)icc_open_logical_channel_req, 16, 1, val, count, sizeof(uint8_t));
}

int uim_icc_open_logical_channel_req_set_fileControlInfo(struct uim_icc_open_logical_channel_req *icc_open_logical_channel_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)icc_open_logical_channel_req, 17, &val, sizeof(uint8_t));
}

struct uim_icc_open_logical_channel_resp *uim_icc_open_logical_channel_resp_parse(void *buf, size_t len)
{
	return (struct uim_icc_open_logical_channel_resp*)qmi_tlv_decode(buf, len);
}

void uim_icc_open_logical_channel_resp_getall(struct uim_icc_open_logical_channel_resp *icc_open_logical_channel_resp, struct uim_icc_open_logical_channel_resp_data *data)
{
	int rc;
	(void)rc;

	data->result = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->result, qmi_tlv_get((struct qmi_tlv*)icc_open_logical_channel_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
	rc = uim_icc_open_logical_channel_resp_get_channel_id(icc_open_logical_channel_resp, &data->channel_id);
	data->channel_id_valid = rc >= 0;
	rc = uim_icc_open_logical_channel_resp_get_card_result(icc_open_logical_channel_resp, &data->card_result);
	data->card_result_valid = rc >= 0;
	data->select_response = uim_icc_open_logical_channel_resp_get_select_response(icc_open_logical_channel_resp, &data->select_response_n);
	data->select_response_valid = !!data->select_response_n;
}

void uim_icc_open_logical_channel_resp_data_free(struct uim_icc_open_logical_channel_resp_data *data)
{

		free(data->result);
	if(data->select_response_valid) {
		free(data->select_response);
	}
}

void uim_icc_open_logical_channel_resp_free(struct uim_icc_open_logical_channel_resp *icc_open_logical_channel_resp)
{
	qmi_tlv_free((struct qmi_tlv*)icc_open_logical_channel_resp);
}

int uim_icc_open_logical_channel_resp_get_channel_id(struct uim_icc_open_logical_channel_resp *icc_open_logical_channel_resp, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)icc_open_logical_channel_resp, 16, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int uim_icc_open_logical_channel_resp_get_card_result(struct uim_icc_open_logical_channel_resp *icc_open_logical_channel_resp, uint16_t *val)
{
	uint16_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)icc_open_logical_channel_resp, 17, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint16_t))
		return -EINVAL;

	*val = *(uint16_t*)ptr;
	return 0;
}

uint8_t *uim_icc_open_logical_channel_resp_get_select_response(struct uim_icc_open_logical_channel_resp *icc_open_logical_channel_resp, size_t *count)
{
	uint8_t *ptr, *out;
	size_t size;
	size_t len;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)icc_open_logical_channel_resp, 18, 1, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(uint8_t))
		return NULL;

	out = malloc(len);
	memcpy(out, ptr, len);

	*count = len;
	return out;
}

struct uim_get_slot_status_req *uim_get_slot_status_req_alloc(unsigned txn)
{
	return (struct uim_get_slot_status_req*)qmi_tlv_init(txn, 71, 0);
}

void *uim_get_slot_status_req_encode(struct uim_get_slot_status_req *get_slot_status_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_slot_status_req, len);
}

void uim_get_slot_status_req_free(struct uim_get_slot_status_req *get_slot_status_req)
{
	qmi_tlv_free((struct qmi_tlv*)get_slot_status_req);
}

struct uim_get_slot_status_resp *uim_get_slot_status_resp_parse(void *buf, size_t len)
{
	return (struct uim_get_slot_status_resp*)qmi_tlv_decode(buf, len);
}

void uim_get_slot_status_resp_getall(struct uim_get_slot_status_resp *get_slot_status_resp, struct uim_get_slot_status_resp_data *data)
{
	int rc;
	(void)rc;

	data->result = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->result, qmi_tlv_get((struct qmi_tlv*)get_slot_status_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
	data->slot_state = uim_get_slot_status_resp_get_slot_state(get_slot_status_resp);
	data->slot_state_valid = !!data->slot_state;
	data->slot_info = uim_get_slot_status_resp_get_slot_info(get_slot_status_resp);
	data->slot_info_valid = !!data->slot_info;
	data->eid_info = uim_get_slot_status_resp_get_eid_info(get_slot_status_resp, &data->eid_info_n);
	data->eid_info_valid = !!data->eid_info_n;
}

void uim_get_slot_status_resp_data_free(struct uim_get_slot_status_resp_data *data)
{

		free(data->result);
	if(data->slot_state_valid) {
		uim_physical_slot_state_free(data->slot_state);
		free(data->slot_state);
	}
	if(data->slot_info_valid) {
		uim_physical_slot_info_free(data->slot_info);
		free(data->slot_info);
	}
	if(data->eid_info_valid) {
		free(data->eid_info);
	}
}

void uim_get_slot_status_resp_free(struct uim_get_slot_status_resp *get_slot_status_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_slot_status_resp);
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
	out->slots = malloc(1 + slots_sz * out->slots_n);
	for(size_t i = 0; i < out->slots_n; i++) {
		out->slots[i].card_state = get_next(uint32_t, 4);
		out->slots[i].slot_state = get_next(uint32_t, 4);
		out->slots[i].logical_slot = get_next(uint8_t, 1);
		out->slots[i].iccid_n = get_next(uint8_t, 1);
		size_t iccid_sz = 1;
		out->slots[i].iccid = malloc(1 + iccid_sz * out->slots[i].iccid_n);
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
	out->slots = malloc(1 + slots_sz * out->slots_n);
	for(size_t i = 0; i < out->slots_n; i++) {
		out->slots[i].card_protocol = get_next(uint32_t, 4);
		out->slots[i].valid_applications = get_next(uint8_t, 1);
		out->slots[i].atr_value_n = get_next(uint8_t, 1);
		size_t atr_value_sz = 1;
		out->slots[i].atr_value = malloc(1 + atr_value_sz * out->slots[i].atr_value_n);
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

uint8_t *uim_get_slot_status_resp_get_eid_info(struct uim_get_slot_status_resp *get_slot_status_resp, size_t *count)
{
	uint8_t *ptr, *out;
	size_t size;
	size_t len;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_slot_status_resp, 18, 1, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(uint8_t))
		return NULL;

	out = malloc(len);
	memcpy(out, ptr, len);

	*count = len;
	return out;
}

struct uim_get_slot_status_ind *uim_get_slot_status_ind_alloc(unsigned txn)
{
	return (struct uim_get_slot_status_ind*)qmi_tlv_init(txn, 72, 4);
}

void *uim_get_slot_status_ind_encode(struct uim_get_slot_status_ind *get_slot_status_ind, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_slot_status_ind, len);
}

struct uim_get_slot_status_ind *uim_get_slot_status_ind_parse(void *buf, size_t len)
{
	return (struct uim_get_slot_status_ind*)qmi_tlv_decode(buf, len);
}

void uim_get_slot_status_ind_getall(struct uim_get_slot_status_ind *get_slot_status_ind, struct uim_get_slot_status_ind_data *data)
{
	int rc;
	(void)rc;

	data->slot_state = uim_get_slot_status_ind_get_slot_state(get_slot_status_ind);
	data->slot_info = uim_get_slot_status_ind_get_slot_info(get_slot_status_ind);
	data->slot_info_valid = !!data->slot_info;
	data->eid_info = uim_get_slot_status_ind_get_eid_info(get_slot_status_ind, &data->eid_info_n);
	data->eid_info_valid = !!data->eid_info_n;
}

void uim_get_slot_status_ind_data_free(struct uim_get_slot_status_ind_data *data)
{

		uim_physical_slot_state_free(data->slot_state);
		free(data->slot_state);
	if(data->slot_info_valid) {
		uim_physical_slot_info_free(data->slot_info);
		free(data->slot_info);
	}
	if(data->eid_info_valid) {
		free(data->eid_info);
	}
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
	out->slots = malloc(1 + slots_sz * out->slots_n);
	for(size_t i = 0; i < out->slots_n; i++) {
		out->slots[i].card_state = get_next(uint32_t, 4);
		out->slots[i].slot_state = get_next(uint32_t, 4);
		out->slots[i].logical_slot = get_next(uint8_t, 1);
		out->slots[i].iccid_n = get_next(uint8_t, 1);
		size_t iccid_sz = 1;
		out->slots[i].iccid = malloc(1 + iccid_sz * out->slots[i].iccid_n);
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
	out->slots = malloc(1 + slots_sz * out->slots_n);
	for(size_t i = 0; i < out->slots_n; i++) {
		out->slots[i].card_protocol = get_next(uint32_t, 4);
		out->slots[i].valid_applications = get_next(uint8_t, 1);
		out->slots[i].atr_value_n = get_next(uint8_t, 1);
		size_t atr_value_sz = 1;
		out->slots[i].atr_value = malloc(1 + atr_value_sz * out->slots[i].atr_value_n);
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
	uint8_t *ptr, *out;
	size_t size;
	size_t len;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_slot_status_ind, 18, 1, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(uint8_t))
		return NULL;

	out = malloc(len);
	memcpy(out, ptr, len);

	*count = len;
	return out;
}

struct uim_read_transparent_req *uim_read_transparent_req_alloc(unsigned txn)
{
	return (struct uim_read_transparent_req*)qmi_tlv_init(txn, 32, 0);
}

void *uim_read_transparent_req_encode(struct uim_read_transparent_req *read_transparent_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)read_transparent_req, len);
}

void uim_read_transparent_req_free(struct uim_read_transparent_req *read_transparent_req)
{
	qmi_tlv_free((struct qmi_tlv*)read_transparent_req);
}

int uim_read_transparent_req_set_session(struct uim_read_transparent_req *read_transparent_req, struct uim_session_t *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->type;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->aid_n;
	len += 1;
	for(size_t i = 0; i < val->aid_n; i++) {
		*((uint8_t*)(ptr + len)) = val->aid[i];
		len += 1;
	}
	rc = qmi_tlv_set((struct qmi_tlv*)read_transparent_req, 1, ptr, len);
	free(ptr);
	return rc;
}

int uim_read_transparent_req_set_file(struct uim_read_transparent_req *read_transparent_req, struct uim_file_t *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint16_t*)(ptr + len)) = val->file_id;
	len += 2;
	*((uint8_t*)(ptr + len)) = val->path_n;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->path;
	len += 1;
	rc = qmi_tlv_set((struct qmi_tlv*)read_transparent_req, 2, ptr, len);
	free(ptr);
	return rc;
}

int uim_read_transparent_req_set_read_info(struct uim_read_transparent_req *read_transparent_req, struct uim_read_info_t *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint16_t*)(ptr + len)) = val->offset;
	len += 2;
	*((uint16_t*)(ptr + len)) = val->len;
	len += 2;
	rc = qmi_tlv_set((struct qmi_tlv*)read_transparent_req, 3, ptr, len);
	free(ptr);
	return rc;
}

int uim_read_transparent_req_set_resp_in_ind(struct uim_read_transparent_req *read_transparent_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)read_transparent_req, 16, &val, sizeof(uint32_t));
}

int uim_read_transparent_req_set_encrypt_data(struct uim_read_transparent_req *read_transparent_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)read_transparent_req, 17, &val, sizeof(uint8_t));
}

struct uim_read_transparent_resp *uim_read_transparent_resp_parse(void *buf, size_t len)
{
	return (struct uim_read_transparent_resp*)qmi_tlv_decode(buf, len);
}

void uim_read_transparent_resp_getall(struct uim_read_transparent_resp *read_transparent_resp, struct uim_read_transparent_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)read_transparent_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
	data->card_res = uim_read_transparent_resp_get_card_res(read_transparent_resp);
	data->card_res_valid = !!data->card_res;
	data->read_result = uim_read_transparent_resp_get_read_result(read_transparent_resp, &data->read_result_n);
	data->read_result_valid = !!data->read_result_n;
	rc = uim_read_transparent_resp_get_resp_in_ind(read_transparent_resp, &data->resp_in_ind);
	data->resp_in_ind_valid = rc >= 0;
	rc = uim_read_transparent_resp_get_encrypted(read_transparent_resp, &data->encrypted);
	data->encrypted_valid = rc >= 0;
}

void uim_read_transparent_resp_data_free(struct uim_read_transparent_resp_data *data)
{

		free(data->res);
	if(data->card_res_valid) {
		free(data->card_res);
	}
	if(data->read_result_valid) {
		free(data->read_result);
	}
}

void uim_read_transparent_resp_free(struct uim_read_transparent_resp *read_transparent_resp)
{
	qmi_tlv_free((struct qmi_tlv*)read_transparent_resp);
}

struct uim_card_res_t *uim_read_transparent_resp_get_card_res(struct uim_read_transparent_resp *read_transparent_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct uim_card_res_t *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)read_transparent_resp, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct uim_card_res_t));
	out->sw1 = get_next(uint8_t, 1);
	out->sw2 = get_next(uint8_t, 1);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

uint8_t *uim_read_transparent_resp_get_read_result(struct uim_read_transparent_resp *read_transparent_resp, size_t *count)
{
	uint8_t *ptr, *out;
	size_t size;
	size_t len;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)read_transparent_resp, 17, 1, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(uint8_t))
		return NULL;

	out = malloc(len);
	memcpy(out, ptr, len);

	*count = len;
	return out;
}

int uim_read_transparent_resp_get_resp_in_ind(struct uim_read_transparent_resp *read_transparent_resp, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)read_transparent_resp, 18, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

int uim_read_transparent_resp_get_encrypted(struct uim_read_transparent_resp *read_transparent_resp, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)read_transparent_resp, 19, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

struct uim_read_record_req *uim_read_record_req_alloc(unsigned txn)
{
	return (struct uim_read_record_req*)qmi_tlv_init(txn, 33, 0);
}

void *uim_read_record_req_encode(struct uim_read_record_req *read_record_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)read_record_req, len);
}

void uim_read_record_req_free(struct uim_read_record_req *read_record_req)
{
	qmi_tlv_free((struct qmi_tlv*)read_record_req);
}

int uim_read_record_req_set_session(struct uim_read_record_req *read_record_req, struct uim_session_t *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->type;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->aid_n;
	len += 1;
	for(size_t i = 0; i < val->aid_n; i++) {
		*((uint8_t*)(ptr + len)) = val->aid[i];
		len += 1;
	}
	rc = qmi_tlv_set((struct qmi_tlv*)read_record_req, 1, ptr, len);
	free(ptr);
	return rc;
}

int uim_read_record_req_set_file(struct uim_read_record_req *read_record_req, struct uim_file_t *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint16_t*)(ptr + len)) = val->file_id;
	len += 2;
	*((uint8_t*)(ptr + len)) = val->path_n;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->path;
	len += 1;
	rc = qmi_tlv_set((struct qmi_tlv*)read_record_req, 2, ptr, len);
	free(ptr);
	return rc;
}

int uim_read_record_req_set_read_info(struct uim_read_record_req *read_record_req, struct uim_read_info_t *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint16_t*)(ptr + len)) = val->offset;
	len += 2;
	*((uint16_t*)(ptr + len)) = val->len;
	len += 2;
	rc = qmi_tlv_set((struct qmi_tlv*)read_record_req, 3, ptr, len);
	free(ptr);
	return rc;
}

int uim_read_record_req_set_last_record(struct uim_read_record_req *read_record_req, uint16_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)read_record_req, 16, &val, sizeof(uint16_t));
}

int uim_read_record_req_set_resp_in_ind(struct uim_read_record_req *read_record_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)read_record_req, 17, &val, sizeof(uint32_t));
}

struct uim_read_record_resp *uim_read_record_resp_parse(void *buf, size_t len)
{
	return (struct uim_read_record_resp*)qmi_tlv_decode(buf, len);
}

void uim_read_record_resp_getall(struct uim_read_record_resp *read_record_resp, struct uim_read_record_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)read_record_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
	data->card_res = uim_read_record_resp_get_card_res(read_record_resp);
	data->card_res_valid = !!data->card_res;
	data->read_result = uim_read_record_resp_get_read_result(read_record_resp, &data->read_result_n);
	data->read_result_valid = !!data->read_result_n;
	data->additional_read_result = uim_read_record_resp_get_additional_read_result(read_record_resp, &data->additional_read_result_n);
	data->additional_read_result_valid = !!data->additional_read_result_n;
	rc = uim_read_record_resp_get_resp_in_ind(read_record_resp, &data->resp_in_ind);
	data->resp_in_ind_valid = rc >= 0;
}

void uim_read_record_resp_data_free(struct uim_read_record_resp_data *data)
{

		free(data->res);
	if(data->card_res_valid) {
		free(data->card_res);
	}
	if(data->read_result_valid) {
		free(data->read_result);
	}
	if(data->additional_read_result_valid) {
		free(data->additional_read_result);
	}
}

void uim_read_record_resp_free(struct uim_read_record_resp *read_record_resp)
{
	qmi_tlv_free((struct qmi_tlv*)read_record_resp);
}

struct uim_card_res_t *uim_read_record_resp_get_card_res(struct uim_read_record_resp *read_record_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct uim_card_res_t *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)read_record_resp, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct uim_card_res_t));
	out->sw1 = get_next(uint8_t, 1);
	out->sw2 = get_next(uint8_t, 1);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

uint8_t *uim_read_record_resp_get_read_result(struct uim_read_record_resp *read_record_resp, size_t *count)
{
	uint8_t *ptr, *out;
	size_t size;
	size_t len;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)read_record_resp, 17, 1, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(uint8_t))
		return NULL;

	out = malloc(len);
	memcpy(out, ptr, len);

	*count = len;
	return out;
}

uint8_t *uim_read_record_resp_get_additional_read_result(struct uim_read_record_resp *read_record_resp, size_t *count)
{
	uint8_t *ptr, *out;
	size_t size;
	size_t len;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)read_record_resp, 18, 1, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(uint8_t))
		return NULL;

	out = malloc(len);
	memcpy(out, ptr, len);

	*count = len;
	return out;
}

int uim_read_record_resp_get_resp_in_ind(struct uim_read_record_resp *read_record_resp, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)read_record_resp, 19, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

struct uim_get_file_attrs_req *uim_get_file_attrs_req_alloc(unsigned txn)
{
	return (struct uim_get_file_attrs_req*)qmi_tlv_init(txn, 36, 0);
}

void *uim_get_file_attrs_req_encode(struct uim_get_file_attrs_req *get_file_attrs_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_file_attrs_req, len);
}

void uim_get_file_attrs_req_free(struct uim_get_file_attrs_req *get_file_attrs_req)
{
	qmi_tlv_free((struct qmi_tlv*)get_file_attrs_req);
}

int uim_get_file_attrs_req_set_session(struct uim_get_file_attrs_req *get_file_attrs_req, struct uim_session_t *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->type;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->aid_n;
	len += 1;
	for(size_t i = 0; i < val->aid_n; i++) {
		*((uint8_t*)(ptr + len)) = val->aid[i];
		len += 1;
	}
	rc = qmi_tlv_set((struct qmi_tlv*)get_file_attrs_req, 1, ptr, len);
	free(ptr);
	return rc;
}

int uim_get_file_attrs_req_set_file(struct uim_get_file_attrs_req *get_file_attrs_req, struct uim_file_t *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint16_t*)(ptr + len)) = val->file_id;
	len += 2;
	*((uint8_t*)(ptr + len)) = val->path_n;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->path;
	len += 1;
	rc = qmi_tlv_set((struct qmi_tlv*)get_file_attrs_req, 2, ptr, len);
	free(ptr);
	return rc;
}

int uim_get_file_attrs_req_set_resp_in_ind(struct uim_get_file_attrs_req *get_file_attrs_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_file_attrs_req, 17, &val, sizeof(uint32_t));
}

struct uim_get_file_attrs_resp *uim_get_file_attrs_resp_parse(void *buf, size_t len)
{
	return (struct uim_get_file_attrs_resp*)qmi_tlv_decode(buf, len);
}

void uim_get_file_attrs_resp_getall(struct uim_get_file_attrs_resp *get_file_attrs_resp, struct uim_get_file_attrs_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)get_file_attrs_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
	data->card_res = uim_get_file_attrs_resp_get_card_res(get_file_attrs_resp);
	data->card_res_valid = !!data->card_res;
	data->file_attrs = uim_get_file_attrs_resp_get_file_attrs(get_file_attrs_resp);
	data->file_attrs_valid = !!data->file_attrs;
	rc = uim_get_file_attrs_resp_get_resp_in_ind(get_file_attrs_resp, &data->resp_in_ind);
	data->resp_in_ind_valid = rc >= 0;
}

void uim_get_file_attrs_resp_data_free(struct uim_get_file_attrs_resp_data *data)
{

		free(data->res);
	if(data->card_res_valid) {
		free(data->card_res);
	}
	if(data->file_attrs_valid) {
		uim_file_attrs_t_free(data->file_attrs);
		free(data->file_attrs);
	}
}

void uim_get_file_attrs_resp_free(struct uim_get_file_attrs_resp *get_file_attrs_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_file_attrs_resp);
}

struct uim_card_res_t *uim_get_file_attrs_resp_get_card_res(struct uim_get_file_attrs_resp *get_file_attrs_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct uim_card_res_t *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_file_attrs_resp, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct uim_card_res_t));
	out->sw1 = get_next(uint8_t, 1);
	out->sw2 = get_next(uint8_t, 1);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct uim_file_attrs_t *uim_get_file_attrs_resp_get_file_attrs(struct uim_get_file_attrs_resp *get_file_attrs_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct uim_file_attrs_t *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_file_attrs_resp, 17, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct uim_file_attrs_t));
	out->file_size = get_next(uint16_t, 2);
	out->file_id = get_next(uint16_t, 2);
	out->file_type = get_next(uint8_t, 1);
	out->record_size = get_next(uint16_t, 2);
	out->record_count = get_next(uint16_t, 2);
	out->read_sec_attr_logic = get_next(uint8_t, 1);
	out->read_sec_attrs = get_next(uint16_t, 2);
	out->write_sec_attr_logic = get_next(uint8_t, 1);
	out->write_sec_attrs = get_next(uint16_t, 2);
	out->inc_sec_attr_logic = get_next(uint8_t, 1);
	out->inc_sec_attrs = get_next(uint16_t, 2);
	out->deactivate_sec_attr_logic = get_next(uint8_t, 1);
	out->deactivate_sec_attrs = get_next(uint16_t, 2);
	out->activate_sec_attr_logic = get_next(uint8_t, 1);
	out->activate_sec_attrs = get_next(uint16_t, 2);
	out->raw_data_n = get_next(uint16_t, 2);
	size_t raw_data_sz = 1;
	out->raw_data = malloc(1 + raw_data_sz * out->raw_data_n);
	for(size_t i = 0; i < out->raw_data_n; i++) {
		out->raw_data[i] = get_next(uint8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int uim_get_file_attrs_resp_get_resp_in_ind(struct uim_get_file_attrs_resp *get_file_attrs_resp, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_file_attrs_resp, 18, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

void uim_card_status_free(struct uim_card_status *val)
{
	for(size_t i = 0; i < val->cards_n; i++) {
		for(size_t ii = 0; ii < val->cards[i].applications_n; ii++) {
			if(val->cards[i].applications[ii].application_identifier_value)
				free(val->cards[i].applications[ii].application_identifier_value);
		}
		if(val->cards[i].applications)
			free(val->cards[i].applications);
	}
	if(val->cards)
		free(val->cards);

}

void uim_provisioning_session_application_free(struct uim_provisioning_session_application *val)
{
	if(val->application_identifier_value)
		free(val->application_identifier_value);

}

void uim_physical_slot_state_free(struct uim_physical_slot_state *val)
{
	for(size_t i = 0; i < val->slots_n; i++) {
		if(val->slots[i].iccid)
			free(val->slots[i].iccid);
	}
	if(val->slots)
		free(val->slots);

}

void uim_physical_slot_info_free(struct uim_physical_slot_info *val)
{
	for(size_t i = 0; i < val->slots_n; i++) {
		if(val->slots[i].atr_value)
			free(val->slots[i].atr_value);
	}
	if(val->slots)
		free(val->slots);

}

void uim_session_t_free(struct uim_session_t *val)
{
	if(val->aid)
		free(val->aid);

}

void uim_file_attrs_t_free(struct uim_file_attrs_t *val)
{
	if(val->raw_data)
		free(val->raw_data);

}


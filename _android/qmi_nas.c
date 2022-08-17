#include <errno.h>
#include <string.h>
#include "qmi_nas.h"

const struct qmi_tlv_msg_name nas_msg_name_map[18] = {
	{ .msg_id = 3, .msg_name = "nas_register_indications_req" },
	{ .msg_id = 32, .msg_name = "nas_get_signal_strength_req" },
	{ .msg_id = 32, .msg_name = "nas_get_signal_strength_resp" },
	{ .msg_id = 34, .msg_name = "nas_initiate_network_register" },
	{ .msg_id = 36, .msg_name = "nas_serving_system_resp" },
	{ .msg_id = 36, .msg_name = "nas_serving_system_ind" },
	{ .msg_id = 46, .msg_name = "nas_set_operating_mode_req" },
	{ .msg_id = 46, .msg_name = "nas_set_operating_mode_resp" },
	{ .msg_id = 51, .msg_name = "nas_set_system_prefs" },
	{ .msg_id = 52, .msg_name = "nas_get_system_prefs" },
	{ .msg_id = 57, .msg_name = "nas_get_operator_name_resp" },
	{ .msg_id = 58, .msg_name = "nas_operator_name_ind" },
	{ .msg_id = 67, .msg_name = "nas_get_cell_loc_info" },
	{ .msg_id = 68, .msg_name = "nas_get_plmn_name_req" },
	{ .msg_id = 68, .msg_name = "nas_get_plmn_name_resp" },
	{ .msg_id = 79, .msg_name = "nas_get_signal_info" },
	{ .msg_id = 81, .msg_name = "nas_signal_info_ind" },
	{ .msg_id = 172, .msg_name = "nas_get_lte_cphy_ca_info_resp" },
};

struct nas_register_indications_req *nas_register_indications_req_alloc(unsigned txn)
{
	return (struct nas_register_indications_req*)qmi_tlv_init(txn, 3, 0);
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

int nas_register_indications_req_set_ddtm_events(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 18, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_serving_system_events(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 19, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_dual_standby_preference(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 20, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_subscription_info(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 21, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_network_time(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 23, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_system_info(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 24, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_signal_info(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 25, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_error_rate(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 26, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_hdr_new_uati_assigned(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 27, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_hdr_session_closed(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 28, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_managed_roaming(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 29, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_current_plmn_name(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 30, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_embms_status(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 31, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_rf_band_information(struct nas_register_indications_req *register_indications_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 32, &val, sizeof(uint8_t));
}

int nas_register_indications_req_set_network_reject_information(struct nas_register_indications_req *register_indications_req, struct nas_network_reject_info *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->enable_network_reject_indications;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->suppress_system_info_indications;
	len += 1;
	rc = qmi_tlv_set((struct qmi_tlv*)register_indications_req, 33, ptr, len);
	free(ptr);
	return rc;
}

struct nas_get_signal_strength_req *nas_get_signal_strength_req_alloc(unsigned txn)
{
	return (struct nas_get_signal_strength_req*)qmi_tlv_init(txn, 32, 0);
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

struct nas_get_signal_strength_resp *nas_get_signal_strength_resp_parse(void *buf, size_t len)
{
	return (struct nas_get_signal_strength_resp*)qmi_tlv_decode(buf, len);
}

void nas_get_signal_strength_resp_getall(struct nas_get_signal_strength_resp *get_signal_strength_resp, struct nas_get_signal_strength_resp_data *data)
{
	int rc;
	(void)rc;

	data->strength = nas_get_signal_strength_resp_get_strength(get_signal_strength_resp);
	data->strength_valid = !!data->strength;
	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)get_signal_strength_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
	data->strength_list = nas_get_signal_strength_resp_get_strength_list(get_signal_strength_resp, &data->strength_list_n);
	data->strength_list_valid = !!data->strength_list;
	data->rssi_list = nas_get_signal_strength_resp_get_rssi_list(get_signal_strength_resp, &data->rssi_list_n);
	data->rssi_list_valid = !!data->rssi_list;
	data->ecio_list = nas_get_signal_strength_resp_get_ecio_list(get_signal_strength_resp, &data->ecio_list_n);
	data->ecio_list_valid = !!data->ecio_list;
	rc = nas_get_signal_strength_resp_get_io(get_signal_strength_resp, &data->io);
	data->io_valid = rc >= 0;
	rc = nas_get_signal_strength_resp_get_sinr(get_signal_strength_resp, &data->sinr);
	data->sinr_valid = rc >= 0;
	data->err_rate_list = nas_get_signal_strength_resp_get_err_rate_list(get_signal_strength_resp, &data->err_rate_list_n);
	data->err_rate_list_valid = !!data->err_rate_list;
	data->rsrq = nas_get_signal_strength_resp_get_rsrq(get_signal_strength_resp);
	data->rsrq_valid = !!data->rsrq;
	rc = nas_get_signal_strength_resp_get_lte_snr(get_signal_strength_resp, &data->lte_snr);
	data->lte_snr_valid = rc >= 0;
	rc = nas_get_signal_strength_resp_get_lte_rsrp(get_signal_strength_resp, &data->lte_rsrp);
	data->lte_rsrp_valid = rc >= 0;
}

void nas_get_signal_strength_resp_data_free(struct nas_get_signal_strength_resp_data *data)
{

	if(data->strength_valid) {
		free(data->strength);
	}
		free(data->res);
	if(data->strength_list_valid) {
		free(data->strength_list);
	}
	if(data->rssi_list_valid) {
		free(data->rssi_list);
	}
	if(data->ecio_list_valid) {
		free(data->ecio_list);
	}
	if(data->err_rate_list_valid) {
		free(data->err_rate_list);
	}
	if(data->rsrq_valid) {
		free(data->rsrq);
	}
}

void nas_get_signal_strength_resp_free(struct nas_get_signal_strength_resp *get_signal_strength_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_signal_strength_resp);
}

struct nas_signal_strength *nas_get_signal_strength_resp_get_strength(struct nas_get_signal_strength_resp *get_signal_strength_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_signal_strength *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_strength_resp, 1, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_signal_strength));
	out->strength = get_next(int8_t, 1);
	out->interface = get_next(int8_t, 1);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_signal_strength *nas_get_signal_strength_resp_get_strength_list(struct nas_get_signal_strength_resp *get_signal_strength_resp, size_t *count)
{
	size_t size;
	size_t len;
	void *ptr, *out;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_signal_strength_resp, 16, 2, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(struct nas_signal_strength))
		return NULL;

	*count = len;
	out = malloc(len);
	memcpy(out, ptr, len);
	return out;
}

struct nas_ss_value *nas_get_signal_strength_resp_get_rssi_list(struct nas_get_signal_strength_resp *get_signal_strength_resp, size_t *count)
{
	size_t size;
	size_t len;
	void *ptr, *out;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_signal_strength_resp, 17, 2, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(struct nas_ss_value))
		return NULL;

	*count = len;
	out = malloc(len);
	memcpy(out, ptr, len);
	return out;
}

struct nas_ss_value *nas_get_signal_strength_resp_get_ecio_list(struct nas_get_signal_strength_resp *get_signal_strength_resp, size_t *count)
{
	size_t size;
	size_t len;
	void *ptr, *out;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_signal_strength_resp, 18, 2, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(struct nas_ss_value))
		return NULL;

	*count = len;
	out = malloc(len);
	memcpy(out, ptr, len);
	return out;
}

int nas_get_signal_strength_resp_get_io(struct nas_get_signal_strength_resp *get_signal_strength_resp, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_strength_resp, 19, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

int nas_get_signal_strength_resp_get_sinr(struct nas_get_signal_strength_resp *get_signal_strength_resp, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_strength_resp, 20, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

struct nas_ss_value *nas_get_signal_strength_resp_get_err_rate_list(struct nas_get_signal_strength_resp *get_signal_strength_resp, size_t *count)
{
	size_t size;
	size_t len;
	void *ptr, *out;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_signal_strength_resp, 21, 2, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(struct nas_ss_value))
		return NULL;

	*count = len;
	out = malloc(len);
	memcpy(out, ptr, len);
	return out;
}

struct nas_ss_value *nas_get_signal_strength_resp_get_rsrq(struct nas_get_signal_strength_resp *get_signal_strength_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_ss_value *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_strength_resp, 22, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_ss_value));
	out->val = get_next(uint8_t, 1);
	out->interface = get_next(int8_t, 1);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
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

struct nas_initiate_network_register *nas_initiate_network_register_alloc(unsigned txn)
{
	return (struct nas_initiate_network_register*)qmi_tlv_init(txn, 34, 0);
}

void *nas_initiate_network_register_encode(struct nas_initiate_network_register *initiate_network_register, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)initiate_network_register, len);
}

void nas_initiate_network_register_free(struct nas_initiate_network_register *initiate_network_register)
{
	qmi_tlv_free((struct qmi_tlv*)initiate_network_register);
}

int nas_initiate_network_register_set_action(struct nas_initiate_network_register *initiate_network_register, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)initiate_network_register, 1, &val, sizeof(uint8_t));
}

struct nas_serving_system_resp *nas_serving_system_resp_parse(void *buf, size_t len)
{
	return (struct nas_serving_system_resp*)qmi_tlv_decode(buf, len);
}

void nas_serving_system_resp_getall(struct nas_serving_system_resp *serving_system_resp, struct nas_serving_system_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)serving_system_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
	data->system = nas_serving_system_resp_get_system(serving_system_resp);
	data->system_valid = !!data->system;
	data->data_service_cap = nas_serving_system_resp_get_data_service_cap(serving_system_resp, &data->data_service_cap_n);
	data->data_service_cap_valid = !!data->data_service_cap_n;
	data->plmn = nas_serving_system_resp_get_plmn(serving_system_resp);
	data->plmn_valid = !!data->plmn;
	rc = nas_serving_system_resp_get_lac(serving_system_resp, &data->lac);
	data->lac_valid = rc >= 0;
	rc = nas_serving_system_resp_get_cid(serving_system_resp, &data->cid);
	data->cid_valid = rc >= 0;
	data->status = nas_serving_system_resp_get_status(serving_system_resp);
	data->status_valid = !!data->status;
}

void nas_serving_system_resp_data_free(struct nas_serving_system_resp_data *data)
{

		free(data->res);
	if(data->system_valid) {
		nas_serving_system_free(data->system);
		free(data->system);
	}
	if(data->data_service_cap_valid) {
		free(data->data_service_cap);
	}
	if(data->plmn_valid) {
		nas_current_plmn_free(data->plmn);
		free(data->plmn);
	}
	if(data->status_valid) {
		free(data->status);
	}
}

void nas_serving_system_resp_free(struct nas_serving_system_resp *serving_system_resp)
{
	qmi_tlv_free((struct qmi_tlv*)serving_system_resp);
}

struct nas_serving_system *nas_serving_system_resp_get_system(struct nas_serving_system_resp *serving_system_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_serving_system *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)serving_system_resp, 1, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_serving_system));
	out->registration_state = get_next(uint8_t, 1);
	out->cs_attach_state = get_next(uint8_t, 1);
	out->ps_attach_state = get_next(uint8_t, 1);
	out->selected_network = get_next(uint8_t, 1);
	out->radio_interfaces_n = get_next(uint8_t, 1);
	size_t radio_interfaces_sz = 1;
	out->radio_interfaces = malloc(1 + radio_interfaces_sz * out->radio_interfaces_n);
	for(size_t i = 0; i < out->radio_interfaces_n; i++) {
		out->radio_interfaces[i] = get_next(uint8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

uint8_t *nas_serving_system_resp_get_data_service_cap(struct nas_serving_system_resp *serving_system_resp, size_t *count)
{
	uint8_t *ptr, *out;
	size_t size;
	size_t len;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)serving_system_resp, 17, 1, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(uint8_t))
		return NULL;

	out = malloc(len);
	memcpy(out, ptr, len);

	*count = len;
	return out;
}

struct nas_current_plmn *nas_serving_system_resp_get_plmn(struct nas_serving_system_resp *serving_system_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_current_plmn *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)serving_system_resp, 18, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_current_plmn));
	out->mcc = get_next(uint16_t, 2);
	out->mnc = get_next(uint16_t, 2);
	out->description = malloc(strlen(ptr + len) + 1);
	strcpy(out->description, ptr + len); len += strlen(ptr + len);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_serving_system_resp_get_lac(struct nas_serving_system_resp *serving_system_resp, uint16_t *val)
{
	uint16_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)serving_system_resp, 29, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint16_t))
		return -EINVAL;

	*val = *(uint16_t*)ptr;
	return 0;
}

int nas_serving_system_resp_get_cid(struct nas_serving_system_resp *serving_system_resp, uint16_t *val)
{
	uint16_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)serving_system_resp, 30, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint16_t))
		return -EINVAL;

	*val = *(uint16_t*)ptr;
	return 0;
}

struct nas_service_status *nas_serving_system_resp_get_status(struct nas_serving_system_resp *serving_system_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_service_status *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)serving_system_resp, 34, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_service_status));
	out->status = get_next(uint8_t, 1);
	out->capability = get_next(uint8_t, 1);
	out->hdr_status = get_next(uint8_t, 1);
	out->hdr_hybrid = get_next(uint8_t, 1);
	out->forbidden = get_next(uint8_t, 1);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_serving_system_ind *nas_serving_system_ind_alloc(unsigned txn)
{
	return (struct nas_serving_system_ind*)qmi_tlv_init(txn, 36, 4);
}

void *nas_serving_system_ind_encode(struct nas_serving_system_ind *serving_system_ind, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)serving_system_ind, len);
}

struct nas_serving_system_ind *nas_serving_system_ind_parse(void *buf, size_t len)
{
	return (struct nas_serving_system_ind*)qmi_tlv_decode(buf, len);
}

void nas_serving_system_ind_getall(struct nas_serving_system_ind *serving_system_ind, struct nas_serving_system_ind_data *data)
{
	int rc;
	(void)rc;

	data->system = nas_serving_system_ind_get_system(serving_system_ind);
	data->system_valid = !!data->system;
	data->data_service_cap = nas_serving_system_ind_get_data_service_cap(serving_system_ind, &data->data_service_cap_n);
	data->data_service_cap_valid = !!data->data_service_cap_n;
	data->plmn = nas_serving_system_ind_get_plmn(serving_system_ind);
	data->plmn_valid = !!data->plmn;
	rc = nas_serving_system_ind_get_lac(serving_system_ind, &data->lac);
	data->lac_valid = rc >= 0;
	rc = nas_serving_system_ind_get_cid(serving_system_ind, &data->cid);
	data->cid_valid = rc >= 0;
	data->status = nas_serving_system_ind_get_status(serving_system_ind);
	data->status_valid = !!data->status;
}

void nas_serving_system_ind_data_free(struct nas_serving_system_ind_data *data)
{

	if(data->system_valid) {
		nas_serving_system_free(data->system);
		free(data->system);
	}
	if(data->data_service_cap_valid) {
		free(data->data_service_cap);
	}
	if(data->plmn_valid) {
		nas_current_plmn_free(data->plmn);
		free(data->plmn);
	}
	if(data->status_valid) {
		free(data->status);
	}
}

void nas_serving_system_ind_free(struct nas_serving_system_ind *serving_system_ind)
{
	qmi_tlv_free((struct qmi_tlv*)serving_system_ind);
}

int nas_serving_system_ind_set_system(struct nas_serving_system_ind *serving_system_ind, struct nas_serving_system *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->registration_state;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->cs_attach_state;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->ps_attach_state;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->selected_network;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->radio_interfaces_n;
	len += 1;
	for(size_t i = 0; i < val->radio_interfaces_n; i++) {
		*((uint8_t*)(ptr + len)) = val->radio_interfaces[i];
		len += 1;
	}
	rc = qmi_tlv_set((struct qmi_tlv*)serving_system_ind, 1, ptr, len);
	free(ptr);
	return rc;
}

struct nas_serving_system *nas_serving_system_ind_get_system(struct nas_serving_system_ind *serving_system_ind)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_serving_system *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)serving_system_ind, 1, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_serving_system));
	out->registration_state = get_next(uint8_t, 1);
	out->cs_attach_state = get_next(uint8_t, 1);
	out->ps_attach_state = get_next(uint8_t, 1);
	out->selected_network = get_next(uint8_t, 1);
	out->radio_interfaces_n = get_next(uint8_t, 1);
	size_t radio_interfaces_sz = 1;
	out->radio_interfaces = malloc(1 + radio_interfaces_sz * out->radio_interfaces_n);
	for(size_t i = 0; i < out->radio_interfaces_n; i++) {
		out->radio_interfaces[i] = get_next(uint8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_serving_system_ind_set_data_service_cap(struct nas_serving_system_ind *serving_system_ind, uint8_t *val, size_t count)
{
	return qmi_tlv_set_array((struct qmi_tlv*)serving_system_ind, 17, 1, val, count, sizeof(uint8_t));
}

uint8_t *nas_serving_system_ind_get_data_service_cap(struct nas_serving_system_ind *serving_system_ind, size_t *count)
{
	uint8_t *ptr, *out;
	size_t size;
	size_t len;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)serving_system_ind, 17, 1, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(uint8_t))
		return NULL;

	out = malloc(len);
	memcpy(out, ptr, len);

	*count = len;
	return out;
}

int nas_serving_system_ind_set_plmn(struct nas_serving_system_ind *serving_system_ind, struct nas_current_plmn *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint16_t*)(ptr + len)) = val->mcc;
	len += 2;
	*((uint16_t*)(ptr + len)) = val->mnc;
	len += 2;
	strcpy(ptr + len, val->description);
	len += strlen(val->description);
	rc = qmi_tlv_set((struct qmi_tlv*)serving_system_ind, 18, ptr, len);
	free(ptr);
	return rc;
}

struct nas_current_plmn *nas_serving_system_ind_get_plmn(struct nas_serving_system_ind *serving_system_ind)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_current_plmn *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)serving_system_ind, 18, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_current_plmn));
	out->mcc = get_next(uint16_t, 2);
	out->mnc = get_next(uint16_t, 2);
	out->description = malloc(strlen(ptr + len) + 1);
	strcpy(out->description, ptr + len); len += strlen(ptr + len);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_serving_system_ind_set_lac(struct nas_serving_system_ind *serving_system_ind, uint16_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)serving_system_ind, 29, &val, sizeof(uint16_t));
}

int nas_serving_system_ind_get_lac(struct nas_serving_system_ind *serving_system_ind, uint16_t *val)
{
	uint16_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)serving_system_ind, 29, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint16_t))
		return -EINVAL;

	*val = *(uint16_t*)ptr;
	return 0;
}

int nas_serving_system_ind_set_cid(struct nas_serving_system_ind *serving_system_ind, uint16_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)serving_system_ind, 30, &val, sizeof(uint16_t));
}

int nas_serving_system_ind_get_cid(struct nas_serving_system_ind *serving_system_ind, uint16_t *val)
{
	uint16_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)serving_system_ind, 30, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint16_t))
		return -EINVAL;

	*val = *(uint16_t*)ptr;
	return 0;
}

int nas_serving_system_ind_set_status(struct nas_serving_system_ind *serving_system_ind, struct nas_service_status *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->status;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->capability;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->hdr_status;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->hdr_hybrid;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->forbidden;
	len += 1;
	rc = qmi_tlv_set((struct qmi_tlv*)serving_system_ind, 34, ptr, len);
	free(ptr);
	return rc;
}

struct nas_service_status *nas_serving_system_ind_get_status(struct nas_serving_system_ind *serving_system_ind)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_service_status *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)serving_system_ind, 34, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_service_status));
	out->status = get_next(uint8_t, 1);
	out->capability = get_next(uint8_t, 1);
	out->hdr_status = get_next(uint8_t, 1);
	out->hdr_hybrid = get_next(uint8_t, 1);
	out->forbidden = get_next(uint8_t, 1);

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

struct nas_set_operating_mode_resp *nas_set_operating_mode_resp_alloc(unsigned txn)
{
	return (struct nas_set_operating_mode_resp*)qmi_tlv_init(txn, 46, 0);
}

void *nas_set_operating_mode_resp_encode(struct nas_set_operating_mode_resp *set_operating_mode_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)set_operating_mode_resp, len);
}

void nas_set_operating_mode_resp_free(struct nas_set_operating_mode_resp *set_operating_mode_resp)
{
	qmi_tlv_free((struct qmi_tlv*)set_operating_mode_resp);
}

struct nas_set_system_prefs *nas_set_system_prefs_alloc(unsigned txn)
{
	return (struct nas_set_system_prefs*)qmi_tlv_init(txn, 51, 0);
}

void *nas_set_system_prefs_encode(struct nas_set_system_prefs *set_system_prefs, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)set_system_prefs, len);
}

void nas_set_system_prefs_free(struct nas_set_system_prefs *set_system_prefs)
{
	qmi_tlv_free((struct qmi_tlv*)set_system_prefs);
}

int nas_set_system_prefs_set_network_selection(struct nas_set_system_prefs *set_system_prefs, struct nas_network_selection_pref *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->mode;
	len += 1;
	*((uint16_t*)(ptr + len)) = val->mcc;
	len += 2;
	*((uint16_t*)(ptr + len)) = val->mnc;
	len += 2;
	rc = qmi_tlv_set((struct qmi_tlv*)set_system_prefs, 22, ptr, len);
	free(ptr);
	return rc;
}

struct nas_get_system_prefs *nas_get_system_prefs_parse(void *buf, size_t len)
{
	return (struct nas_get_system_prefs*)qmi_tlv_decode(buf, len);
}

void nas_get_system_prefs_getall(struct nas_get_system_prefs *get_system_prefs, struct nas_get_system_prefs_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)get_system_prefs, 2, NULL), sizeof(struct qmi_response_type_v01));
	rc = nas_get_system_prefs_get_network_selection(get_system_prefs, &data->network_selection);
	data->network_selection_valid = rc >= 0;
}

void nas_get_system_prefs_data_free(struct nas_get_system_prefs_data *data)
{

		free(data->res);
}

void nas_get_system_prefs_free(struct nas_get_system_prefs *get_system_prefs)
{
	qmi_tlv_free((struct qmi_tlv*)get_system_prefs);
}

int nas_get_system_prefs_get_network_selection(struct nas_get_system_prefs *get_system_prefs, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_system_prefs, 22, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

struct nas_get_operator_name_resp *nas_get_operator_name_resp_parse(void *buf, size_t len)
{
	return (struct nas_get_operator_name_resp*)qmi_tlv_decode(buf, len);
}

void nas_get_operator_name_resp_getall(struct nas_get_operator_name_resp *get_operator_name_resp, struct nas_get_operator_name_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)get_operator_name_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
	data->provider_name = nas_get_operator_name_resp_get_provider_name(get_operator_name_resp);
	data->provider_name_valid = !!data->provider_name;
	data->operator_plmns = nas_get_operator_name_resp_get_operator_plmns(get_operator_name_resp);
	data->operator_plmns_valid = !!data->operator_plmns;
	data->operator_plmn_names = nas_get_operator_name_resp_get_operator_plmn_names(get_operator_name_resp);
	data->operator_plmn_names_valid = !!data->operator_plmn_names;
	data->operator_string_name = nas_get_operator_name_resp_get_operator_string_name(get_operator_name_resp);
	data->operator_string_name_valid = !!data->operator_string_name;
	data->nitz_info = nas_get_operator_name_resp_get_nitz_info(get_operator_name_resp);
	data->nitz_info_valid = !!data->nitz_info;
}

void nas_get_operator_name_resp_data_free(struct nas_get_operator_name_resp_data *data)
{

		free(data->res);
	if(data->provider_name_valid) {
		nas_service_provider_name_free(data->provider_name);
		free(data->provider_name);
	}
	if(data->operator_plmns_valid) {
		nas_operator_plmn_arr_free(data->operator_plmns);
		free(data->operator_plmns);
	}
	if(data->operator_plmn_names_valid) {
		nas_operator_plmn_name_arr_free(data->operator_plmn_names);
		free(data->operator_plmn_names);
	}
	if(data->operator_string_name_valid) {
		free(data->operator_string_name);
	}
	if(data->nitz_info_valid) {
		nas_operator_plmn_name_free(data->nitz_info);
		free(data->nitz_info);
	}
}

void nas_get_operator_name_resp_free(struct nas_get_operator_name_resp *get_operator_name_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_operator_name_resp);
}

struct nas_service_provider_name *nas_get_operator_name_resp_get_provider_name(struct nas_get_operator_name_resp *get_operator_name_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_service_provider_name *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_operator_name_resp, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_service_provider_name));
	out->display_condition = get_next(uint8_t, 1);
	out->name = malloc(strlen(ptr + len) + 1);
	strcpy(out->name, ptr + len); len += strlen(ptr + len);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_operator_plmn_arr *nas_get_operator_name_resp_get_operator_plmns(struct nas_get_operator_name_resp *get_operator_name_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_operator_plmn_arr *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_operator_name_resp, 17, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_operator_plmn_arr));
	out->operators_n = get_next(uint16_t, 2);
	size_t operators_sz = sizeof(struct operator_plmn_arr_operators);
	out->operators = malloc(1 + operators_sz * out->operators_n);
	for(size_t i = 0; i < out->operators_n; i++) {
		memcpy(&out->operators[i].mcc, ptr + len, 3 * 1);
		len += 3 * 1;
		memcpy(&out->operators[i].mnc, ptr + len, 3 * 1);
		len += 3 * 1;
		out->operators[i].lac1 = get_next(uint16_t, 2);
		out->operators[i].lac2 = get_next(uint16_t, 2);
		out->operators[i].name_record_indicator = get_next(uint8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_operator_plmn_name_arr *nas_get_operator_name_resp_get_operator_plmn_names(struct nas_get_operator_name_resp *get_operator_name_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_operator_plmn_name_arr *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_operator_name_resp, 18, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_operator_plmn_name_arr));
	out->operators_n = get_next(uint8_t, 1);
	size_t operators_sz = sizeof(struct operator_plmn_name_arr_operators);
	out->operators = malloc(1 + operators_sz * out->operators_n);
	for(size_t i = 0; i < out->operators_n; i++) {
		out->operators[i].name_encoding = get_next(uint8_t, 1);
		out->operators[i].short_country_initials = get_next(uint8_t, 1);
		out->operators[i].long_name_spare_bits = get_next(uint8_t, 1);
		out->operators[i].short_name_spare_bits = get_next(uint8_t, 1);
		out->operators[i].long_name_n = get_next(uint8_t, 1);
		size_t long_name_sz = 1;
		out->operators[i].long_name = malloc(1 + long_name_sz * out->operators[i].long_name_n);
		for(size_t ii = 0; ii < out->operators[i].long_name_n; ii++) {
			out->operators[i].long_name[ii] = get_next(uint8_t, 1);
		}
		out->operators[i].short_name_n = get_next(uint8_t, 1);
		size_t short_name_sz = 1;
		out->operators[i].short_name = malloc(1 + short_name_sz * out->operators[i].short_name_n);
		for(size_t ii = 0; ii < out->operators[i].short_name_n; ii++) {
			out->operators[i].short_name[ii] = get_next(uint8_t, 1);
		}
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

char *nas_get_operator_name_resp_get_operator_string_name(struct nas_get_operator_name_resp *get_operator_name_resp)
{
	char *ptr = NULL, *out;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_operator_name_resp, 19, &len);
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

struct nas_operator_plmn_name *nas_get_operator_name_resp_get_nitz_info(struct nas_get_operator_name_resp *get_operator_name_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_operator_plmn_name *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_operator_name_resp, 20, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_operator_plmn_name));
	out->name_encoding = get_next(uint8_t, 1);
	out->short_country_initials = get_next(uint8_t, 1);
	out->long_name_spare_bits = get_next(uint8_t, 1);
	out->short_name_spare_bits = get_next(uint8_t, 1);
	out->long_name_n = get_next(uint8_t, 1);
	size_t long_name_sz = 1;
	out->long_name = malloc(1 + long_name_sz * out->long_name_n);
	for(size_t i = 0; i < out->long_name_n; i++) {
		out->long_name[i] = get_next(uint8_t, 1);
	}
	out->short_name_n = get_next(uint8_t, 1);
	size_t short_name_sz = 1;
	out->short_name = malloc(1 + short_name_sz * out->short_name_n);
	for(size_t i = 0; i < out->short_name_n; i++) {
		out->short_name[i] = get_next(uint8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_operator_name_ind *nas_operator_name_ind_alloc(unsigned txn)
{
	return (struct nas_operator_name_ind*)qmi_tlv_init(txn, 58, 4);
}

void *nas_operator_name_ind_encode(struct nas_operator_name_ind *operator_name_ind, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)operator_name_ind, len);
}

struct nas_operator_name_ind *nas_operator_name_ind_parse(void *buf, size_t len)
{
	return (struct nas_operator_name_ind*)qmi_tlv_decode(buf, len);
}

void nas_operator_name_ind_getall(struct nas_operator_name_ind *operator_name_ind, struct nas_operator_name_ind_data *data)
{
	int rc;
	(void)rc;

	data->provider_name = nas_operator_name_ind_get_provider_name(operator_name_ind);
	data->provider_name_valid = !!data->provider_name;
	data->operator_plmns = nas_operator_name_ind_get_operator_plmns(operator_name_ind);
	data->operator_plmns_valid = !!data->operator_plmns;
	data->operator_plmn_names = nas_operator_name_ind_get_operator_plmn_names(operator_name_ind);
	data->operator_plmn_names_valid = !!data->operator_plmn_names;
	data->operator_string_name = nas_operator_name_ind_get_operator_string_name(operator_name_ind);
	data->operator_string_name_valid = !!data->operator_string_name;
	data->nitz_info = nas_operator_name_ind_get_nitz_info(operator_name_ind);
	data->nitz_info_valid = !!data->nitz_info;
}

void nas_operator_name_ind_data_free(struct nas_operator_name_ind_data *data)
{

	if(data->provider_name_valid) {
		nas_service_provider_name_free(data->provider_name);
		free(data->provider_name);
	}
	if(data->operator_plmns_valid) {
		nas_operator_plmn_arr_free(data->operator_plmns);
		free(data->operator_plmns);
	}
	if(data->operator_plmn_names_valid) {
		nas_operator_plmn_name_arr_free(data->operator_plmn_names);
		free(data->operator_plmn_names);
	}
	if(data->operator_string_name_valid) {
		free(data->operator_string_name);
	}
	if(data->nitz_info_valid) {
		nas_operator_plmn_name_free(data->nitz_info);
		free(data->nitz_info);
	}
}

void nas_operator_name_ind_free(struct nas_operator_name_ind *operator_name_ind)
{
	qmi_tlv_free((struct qmi_tlv*)operator_name_ind);
}

int nas_operator_name_ind_set_provider_name(struct nas_operator_name_ind *operator_name_ind, struct nas_service_provider_name *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->display_condition;
	len += 1;
	strcpy(ptr + len, val->name);
	len += strlen(val->name);
	rc = qmi_tlv_set((struct qmi_tlv*)operator_name_ind, 16, ptr, len);
	free(ptr);
	return rc;
}

struct nas_service_provider_name *nas_operator_name_ind_get_provider_name(struct nas_operator_name_ind *operator_name_ind)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_service_provider_name *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)operator_name_ind, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_service_provider_name));
	out->display_condition = get_next(uint8_t, 1);
	out->name = malloc(strlen(ptr + len) + 1);
	strcpy(out->name, ptr + len); len += strlen(ptr + len);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_operator_name_ind_set_operator_plmns(struct nas_operator_name_ind *operator_name_ind, struct nas_operator_plmn_arr *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint16_t*)(ptr + len)) = val->operators_n;
	len += 2;
	for(size_t i = 0; i < val->operators_n; i++) {
		memcpy(ptr + len, &val->operators[i].mcc, 3 * 1);
		len += 3 * 1;
		memcpy(ptr + len, &val->operators[i].mnc, 3 * 1);
		len += 3 * 1;
		*((uint16_t*)(ptr + len)) = val->operators[i].lac1;
		len += 2;
		*((uint16_t*)(ptr + len)) = val->operators[i].lac2;
		len += 2;
		*((uint8_t*)(ptr + len)) = val->operators[i].name_record_indicator;
		len += 1;
	}
	rc = qmi_tlv_set((struct qmi_tlv*)operator_name_ind, 17, ptr, len);
	free(ptr);
	return rc;
}

struct nas_operator_plmn_arr *nas_operator_name_ind_get_operator_plmns(struct nas_operator_name_ind *operator_name_ind)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_operator_plmn_arr *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)operator_name_ind, 17, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_operator_plmn_arr));
	out->operators_n = get_next(uint16_t, 2);
	size_t operators_sz = sizeof(struct operator_plmn_arr_operators);
	out->operators = malloc(1 + operators_sz * out->operators_n);
	for(size_t i = 0; i < out->operators_n; i++) {
		memcpy(&out->operators[i].mcc, ptr + len, 3 * 1);
		len += 3 * 1;
		memcpy(&out->operators[i].mnc, ptr + len, 3 * 1);
		len += 3 * 1;
		out->operators[i].lac1 = get_next(uint16_t, 2);
		out->operators[i].lac2 = get_next(uint16_t, 2);
		out->operators[i].name_record_indicator = get_next(uint8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_operator_name_ind_set_operator_plmn_names(struct nas_operator_name_ind *operator_name_ind, struct nas_operator_plmn_name_arr *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->operators_n;
	len += 1;
	for(size_t i = 0; i < val->operators_n; i++) {
		*((uint8_t*)(ptr + len)) = val->operators[i].name_encoding;
		len += 1;
		*((uint8_t*)(ptr + len)) = val->operators[i].short_country_initials;
		len += 1;
		*((uint8_t*)(ptr + len)) = val->operators[i].long_name_spare_bits;
		len += 1;
		*((uint8_t*)(ptr + len)) = val->operators[i].short_name_spare_bits;
		len += 1;
		*((uint8_t*)(ptr + len)) = val->operators[i].long_name_n;
		len += 1;
		for(size_t ii = 0; ii < val->operators[i].long_name_n; ii++) {
			*((uint8_t*)(ptr + len)) = val->operators[i].long_name[ii];
			len += 1;
		}
		*((uint8_t*)(ptr + len)) = val->operators[i].short_name_n;
		len += 1;
		for(size_t ii = 0; ii < val->operators[i].short_name_n; ii++) {
			*((uint8_t*)(ptr + len)) = val->operators[i].short_name[ii];
			len += 1;
		}
	}
	rc = qmi_tlv_set((struct qmi_tlv*)operator_name_ind, 18, ptr, len);
	free(ptr);
	return rc;
}

struct nas_operator_plmn_name_arr *nas_operator_name_ind_get_operator_plmn_names(struct nas_operator_name_ind *operator_name_ind)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_operator_plmn_name_arr *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)operator_name_ind, 18, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_operator_plmn_name_arr));
	out->operators_n = get_next(uint8_t, 1);
	size_t operators_sz = sizeof(struct operator_plmn_name_arr_operators);
	out->operators = malloc(1 + operators_sz * out->operators_n);
	for(size_t i = 0; i < out->operators_n; i++) {
		out->operators[i].name_encoding = get_next(uint8_t, 1);
		out->operators[i].short_country_initials = get_next(uint8_t, 1);
		out->operators[i].long_name_spare_bits = get_next(uint8_t, 1);
		out->operators[i].short_name_spare_bits = get_next(uint8_t, 1);
		out->operators[i].long_name_n = get_next(uint8_t, 1);
		size_t long_name_sz = 1;
		out->operators[i].long_name = malloc(1 + long_name_sz * out->operators[i].long_name_n);
		for(size_t ii = 0; ii < out->operators[i].long_name_n; ii++) {
			out->operators[i].long_name[ii] = get_next(uint8_t, 1);
		}
		out->operators[i].short_name_n = get_next(uint8_t, 1);
		size_t short_name_sz = 1;
		out->operators[i].short_name = malloc(1 + short_name_sz * out->operators[i].short_name_n);
		for(size_t ii = 0; ii < out->operators[i].short_name_n; ii++) {
			out->operators[i].short_name[ii] = get_next(uint8_t, 1);
		}
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_operator_name_ind_set_operator_string_name(struct nas_operator_name_ind *operator_name_ind, char *buf, size_t len)
{
	return qmi_tlv_set((struct qmi_tlv*)operator_name_ind, 19, buf, len);
}

char *nas_operator_name_ind_get_operator_string_name(struct nas_operator_name_ind *operator_name_ind)
{
	char *ptr = NULL, *out;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)operator_name_ind, 19, &len);
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

int nas_operator_name_ind_set_nitz_info(struct nas_operator_name_ind *operator_name_ind, struct nas_operator_plmn_name *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint8_t*)(ptr + len)) = val->name_encoding;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->short_country_initials;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->long_name_spare_bits;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->short_name_spare_bits;
	len += 1;
	*((uint8_t*)(ptr + len)) = val->long_name_n;
	len += 1;
	for(size_t i = 0; i < val->long_name_n; i++) {
		*((uint8_t*)(ptr + len)) = val->long_name[i];
		len += 1;
	}
	*((uint8_t*)(ptr + len)) = val->short_name_n;
	len += 1;
	for(size_t i = 0; i < val->short_name_n; i++) {
		*((uint8_t*)(ptr + len)) = val->short_name[i];
		len += 1;
	}
	rc = qmi_tlv_set((struct qmi_tlv*)operator_name_ind, 20, ptr, len);
	free(ptr);
	return rc;
}

struct nas_operator_plmn_name *nas_operator_name_ind_get_nitz_info(struct nas_operator_name_ind *operator_name_ind)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_operator_plmn_name *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)operator_name_ind, 20, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_operator_plmn_name));
	out->name_encoding = get_next(uint8_t, 1);
	out->short_country_initials = get_next(uint8_t, 1);
	out->long_name_spare_bits = get_next(uint8_t, 1);
	out->short_name_spare_bits = get_next(uint8_t, 1);
	out->long_name_n = get_next(uint8_t, 1);
	size_t long_name_sz = 1;
	out->long_name = malloc(1 + long_name_sz * out->long_name_n);
	for(size_t i = 0; i < out->long_name_n; i++) {
		out->long_name[i] = get_next(uint8_t, 1);
	}
	out->short_name_n = get_next(uint8_t, 1);
	size_t short_name_sz = 1;
	out->short_name = malloc(1 + short_name_sz * out->short_name_n);
	for(size_t i = 0; i < out->short_name_n; i++) {
		out->short_name[i] = get_next(uint8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_get_cell_loc_info *nas_get_cell_loc_info_parse(void *buf, size_t len)
{
	return (struct nas_get_cell_loc_info*)qmi_tlv_decode(buf, len);
}

void nas_get_cell_loc_info_getall(struct nas_get_cell_loc_info *get_cell_loc_info, struct nas_get_cell_loc_info_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)get_cell_loc_info, 2, NULL), sizeof(struct qmi_response_type_v01));
	data->geran = nas_get_cell_loc_info_get_geran(get_cell_loc_info);
	data->geran_valid = !!data->geran;
	data->umts = nas_get_cell_loc_info_get_umts(get_cell_loc_info);
	data->umts_valid = !!data->umts;
	data->cdma = nas_get_cell_loc_info_get_cdma(get_cell_loc_info);
	data->cdma_valid = !!data->cdma;
	data->intra_lte = nas_get_cell_loc_info_get_intra_lte(get_cell_loc_info);
	data->intra_lte_valid = !!data->intra_lte;
}

void nas_get_cell_loc_info_data_free(struct nas_get_cell_loc_info_data *data)
{

		free(data->res);
	if(data->geran_valid) {
		nas_geran_info_free(data->geran);
		free(data->geran);
	}
	if(data->umts_valid) {
		nas_umts_info_free(data->umts);
		free(data->umts);
	}
	if(data->cdma_valid) {
		free(data->cdma);
	}
	if(data->intra_lte_valid) {
		nas_intrafreq_lte_info_free(data->intra_lte);
		free(data->intra_lte);
	}
}

void nas_get_cell_loc_info_free(struct nas_get_cell_loc_info *get_cell_loc_info)
{
	qmi_tlv_free((struct qmi_tlv*)get_cell_loc_info);
}

struct nas_geran_info *nas_get_cell_loc_info_get_geran(struct nas_get_cell_loc_info *get_cell_loc_info)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_geran_info *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_cell_loc_info, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_geran_info));
	out->cell_id = get_next(uint32_t, 4);
	memcpy(&out->plmn, ptr + len, 3 * 1);
	len += 3 * 1;
	out->lac = get_next(uint16_t, 2);
	out->abs_channel_num = get_next(uint16_t, 2);
	out->bsic = get_next(uint8_t, 1);
	out->timing_advance = get_next(uint32_t, 4);
	out->rx_level = get_next(uint16_t, 2);
	out->cells_n = get_next(uint8_t, 1);
	size_t cells_sz = sizeof(struct geran_info_cells);
	out->cells = malloc(1 + cells_sz * out->cells_n);
	for(size_t i = 0; i < out->cells_n; i++) {
		out->cells[i].cell_id = get_next(uint32_t, 4);
		memcpy(&out->cells[i].plmn, ptr + len, 3 * 1);
		len += 3 * 1;
		out->cells[i].lac = get_next(uint16_t, 2);
		out->cells[i].abs_channel_num = get_next(uint16_t, 2);
		out->cells[i].bsic = get_next(uint8_t, 1);
		out->cells[i].rx_level = get_next(uint16_t, 2);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_umts_info *nas_get_cell_loc_info_get_umts(struct nas_get_cell_loc_info *get_cell_loc_info)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_umts_info *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_cell_loc_info, 17, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_umts_info));
	out->cell_id = get_next(uint16_t, 2);
	memcpy(&out->plmn, ptr + len, 3 * 1);
	len += 3 * 1;
	out->lac = get_next(uint16_t, 2);
	out->abs_channel_num = get_next(uint16_t, 2);
	out->psc = get_next(uint16_t, 2);
	out->rscp = get_next(int16_t, 2);
	out->ecio = get_next(int16_t, 2);
	out->cells_n = get_next(uint8_t, 1);
	size_t cells_sz = sizeof(struct umts_info_cells);
	out->cells = malloc(1 + cells_sz * out->cells_n);
	for(size_t i = 0; i < out->cells_n; i++) {
		out->cells[i].abs_channel_num = get_next(uint16_t, 2);
		out->cells[i].psc = get_next(uint16_t, 2);
		out->cells[i].rscp = get_next(int16_t, 2);
		out->cells[i].ecio = get_next(int16_t, 2);
	}
	out->gerans_n = get_next(uint8_t, 1);
	size_t gerans_sz = sizeof(struct umts_info_cells_gerans);
	out->gerans = malloc(1 + gerans_sz * out->gerans_n);
	for(size_t i = 0; i < out->gerans_n; i++) {
		out->gerans[i].abs_channel_num = get_next(uint16_t, 2);
		out->gerans[i].network_color_code = get_next(uint8_t, 1);
		out->gerans[i].base_station_color_code = get_next(uint8_t, 1);
		out->gerans[i].rssi = get_next(int8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_cdma_info *nas_get_cell_loc_info_get_cdma(struct nas_get_cell_loc_info *get_cell_loc_info)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_cdma_info *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_cell_loc_info, 18, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_cdma_info));
	out->system_id = get_next(uint16_t, 2);
	out->network_id = get_next(uint16_t, 2);
	out->bsid = get_next(uint16_t, 2);
	out->reference_pn = get_next(uint16_t, 2);
	out->latitude = get_next(uint32_t, 4);
	out->longitude = get_next(uint32_t, 4);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_intrafreq_lte_info *nas_get_cell_loc_info_get_intra_lte(struct nas_get_cell_loc_info *get_cell_loc_info)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_intrafreq_lte_info *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_cell_loc_info, 19, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_intrafreq_lte_info));
	out->ue_idle = get_next(uint8_t, 1);
	memcpy(&out->plmn, ptr + len, 3 * 1);
	len += 3 * 1;
	out->tac = get_next(uint16_t, 2);
	out->global_cell_id = get_next(uint32_t, 4);
	out->abs_channel_num = get_next(uint16_t, 2);
	out->serving_cell_id = get_next(uint16_t, 2);
	out->crp = get_next(uint8_t, 1);
	out->s_non_intra_search_threshold = get_next(uint8_t, 1);
	out->serving_cell_low_threshold = get_next(uint8_t, 1);
	out->s_intra_search_threshold = get_next(uint8_t, 1);
	out->cells_n = get_next(uint8_t, 1);
	size_t cells_sz = sizeof(struct intrafreq_lte_info_cells);
	out->cells = malloc(1 + cells_sz * out->cells_n);
	for(size_t i = 0; i < out->cells_n; i++) {
		out->cells[i].pci = get_next(uint16_t, 2);
		out->cells[i].rsrq = get_next(int16_t, 2);
		out->cells[i].rsrp = get_next(int16_t, 2);
		out->cells[i].rssi = get_next(int16_t, 2);
		out->cells[i].rx_level = get_next(int16_t, 2);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_get_plmn_name_req *nas_get_plmn_name_req_alloc(unsigned txn)
{
	return (struct nas_get_plmn_name_req*)qmi_tlv_init(txn, 68, 0);
}

void *nas_get_plmn_name_req_encode(struct nas_get_plmn_name_req *get_plmn_name_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_plmn_name_req, len);
}

void nas_get_plmn_name_req_free(struct nas_get_plmn_name_req *get_plmn_name_req)
{
	qmi_tlv_free((struct qmi_tlv*)get_plmn_name_req);
}

int nas_get_plmn_name_req_set_plmn(struct nas_get_plmn_name_req *get_plmn_name_req, struct nas_plmn_id *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((uint16_t*)(ptr + len)) = val->mcc;
	len += 2;
	*((uint16_t*)(ptr + len)) = val->mnc;
	len += 2;
	rc = qmi_tlv_set((struct qmi_tlv*)get_plmn_name_req, 1, ptr, len);
	free(ptr);
	return rc;
}

int nas_get_plmn_name_req_set_send_all_info(struct nas_get_plmn_name_req *get_plmn_name_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_plmn_name_req, 22, &val, sizeof(uint8_t));
}

struct nas_get_plmn_name_resp *nas_get_plmn_name_resp_parse(void *buf, size_t len)
{
	return (struct nas_get_plmn_name_resp*)qmi_tlv_decode(buf, len);
}

void nas_get_plmn_name_resp_getall(struct nas_get_plmn_name_resp *get_plmn_name_resp, struct nas_get_plmn_name_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)get_plmn_name_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
	data->plmn_name = nas_get_plmn_name_resp_get_plmn_name(get_plmn_name_resp);
	data->plmn_name_valid = !!data->plmn_name;
}

void nas_get_plmn_name_resp_data_free(struct nas_get_plmn_name_resp_data *data)
{

		free(data->res);
	if(data->plmn_name_valid) {
		nas_eons_plmn_name_free(data->plmn_name);
		free(data->plmn_name);
	}
}

void nas_get_plmn_name_resp_free(struct nas_get_plmn_name_resp *get_plmn_name_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_plmn_name_resp);
}

struct nas_eons_plmn_name *nas_get_plmn_name_resp_get_plmn_name(struct nas_get_plmn_name_resp *get_plmn_name_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_eons_plmn_name *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_plmn_name_resp, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_eons_plmn_name));
	out->sp_name_encoding = get_next(uint8_t, 1);
	out->sp_name_n = get_next(uint8_t, 1);
	size_t sp_name_sz = 1;
	out->sp_name = malloc(1 + sp_name_sz * out->sp_name_n);
	for(size_t i = 0; i < out->sp_name_n; i++) {
		out->sp_name[i] = get_next(uint8_t, 1);
	}
	out->short_name_encoding = get_next(uint8_t, 1);
	out->short_name_country_initials = get_next(uint8_t, 1);
	out->short_name_spare_bits = get_next(uint8_t, 1);
	out->short_name_n = get_next(uint8_t, 1);
	size_t short_name_sz = 1;
	out->short_name = malloc(1 + short_name_sz * out->short_name_n);
	for(size_t i = 0; i < out->short_name_n; i++) {
		out->short_name[i] = get_next(uint8_t, 1);
	}
	out->long_name_encoding = get_next(uint8_t, 1);
	out->long_name_country_initials = get_next(uint8_t, 1);
	out->long_name_spare_bits = get_next(uint8_t, 1);
	out->long_name_n = get_next(uint8_t, 1);
	size_t long_name_sz = 1;
	out->long_name = malloc(1 + long_name_sz * out->long_name_n);
	for(size_t i = 0; i < out->long_name_n; i++) {
		out->long_name[i] = get_next(uint8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_get_signal_info *nas_get_signal_info_parse(void *buf, size_t len)
{
	return (struct nas_get_signal_info*)qmi_tlv_decode(buf, len);
}

void nas_get_signal_info_getall(struct nas_get_signal_info *get_signal_info, struct nas_get_signal_info_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)get_signal_info, 2, NULL), sizeof(struct qmi_response_type_v01));
	data->cdma = nas_get_signal_info_get_cdma(get_signal_info);
	data->cdma_valid = !!data->cdma;
	data->hdr = nas_get_signal_info_get_hdr(get_signal_info);
	data->hdr_valid = !!data->hdr;
	rc = nas_get_signal_info_get_gsm(get_signal_info, &data->gsm);
	data->gsm_valid = rc >= 0;
	data->wcdma = nas_get_signal_info_get_wcdma(get_signal_info);
	data->wcdma_valid = !!data->wcdma;
	data->lte = nas_get_signal_info_get_lte(get_signal_info);
	data->lte_valid = !!data->lte;
	rc = nas_get_signal_info_get_tdma(get_signal_info, &data->tdma);
	data->tdma_valid = rc >= 0;
	data->tdma_ext = nas_get_signal_info_get_tdma_ext(get_signal_info);
	data->tdma_ext_valid = !!data->tdma_ext;
}

void nas_get_signal_info_data_free(struct nas_get_signal_info_data *data)
{

		free(data->res);
	if(data->cdma_valid) {
		free(data->cdma);
	}
	if(data->hdr_valid) {
		free(data->hdr);
	}
	if(data->wcdma_valid) {
		free(data->wcdma);
	}
	if(data->lte_valid) {
		free(data->lte);
	}
	if(data->tdma_ext_valid) {
		free(data->tdma_ext);
	}
}

void nas_get_signal_info_free(struct nas_get_signal_info *get_signal_info)
{
	qmi_tlv_free((struct qmi_tlv*)get_signal_info);
}

struct nas_ss_cdma *nas_get_signal_info_get_cdma(struct nas_get_signal_info *get_signal_info)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_ss_cdma *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_info, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_ss_cdma));
	out->rssi = get_next(int8_t, 1);
	out->ecio = get_next(int16_t, 2);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_ss_hdr *nas_get_signal_info_get_hdr(struct nas_get_signal_info *get_signal_info)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_ss_hdr *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_info, 17, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_ss_hdr));
	out->rssi = get_next(int8_t, 1);
	out->ecio = get_next(int16_t, 2);
	out->sinr = get_next(uint8_t, 1);
	out->io = get_next(int32_t, 4);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_get_signal_info_get_gsm(struct nas_get_signal_info *get_signal_info, int8_t *val)
{
	int8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_info, 18, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(int8_t))
		return -EINVAL;

	*val = *(int8_t*)ptr;
	return 0;
}

struct nas_ss_wcdma *nas_get_signal_info_get_wcdma(struct nas_get_signal_info *get_signal_info)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_ss_wcdma *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_info, 19, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_ss_wcdma));
	out->rssi = get_next(int8_t, 1);
	out->ecio = get_next(int16_t, 2);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_ss_lte *nas_get_signal_info_get_lte(struct nas_get_signal_info *get_signal_info)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_ss_lte *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_info, 20, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_ss_lte));
	out->rssi = get_next(int8_t, 1);
	out->rsrq = get_next(int8_t, 1);
	out->rsrp = get_next(int16_t, 2);
	out->snr = get_next(int16_t, 2);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_get_signal_info_get_tdma(struct nas_get_signal_info *get_signal_info, int8_t *val)
{
	int8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_info, 21, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(int8_t))
		return -EINVAL;

	*val = *(int8_t*)ptr;
	return 0;
}

struct nas_ss_tdma_ext *nas_get_signal_info_get_tdma_ext(struct nas_get_signal_info *get_signal_info)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_ss_tdma_ext *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_info, 22, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_ss_tdma_ext));
	out->rssi = get_next(uint32_t, 4);
	out->rscp = get_next(int32_t, 4);
	out->ecio = get_next(int32_t, 4);
	out->sinr = get_next(int32_t, 4);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_signal_info_ind *nas_signal_info_ind_alloc(unsigned txn)
{
	return (struct nas_signal_info_ind*)qmi_tlv_init(txn, 81, 4);
}

void *nas_signal_info_ind_encode(struct nas_signal_info_ind *signal_info_ind, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)signal_info_ind, len);
}

struct nas_signal_info_ind *nas_signal_info_ind_parse(void *buf, size_t len)
{
	return (struct nas_signal_info_ind*)qmi_tlv_decode(buf, len);
}

void nas_signal_info_ind_getall(struct nas_signal_info_ind *signal_info_ind, struct nas_signal_info_ind_data *data)
{
	int rc;
	(void)rc;

	data->cdma = nas_signal_info_ind_get_cdma(signal_info_ind);
	data->cdma_valid = !!data->cdma;
	data->hdr = nas_signal_info_ind_get_hdr(signal_info_ind);
	data->hdr_valid = !!data->hdr;
	rc = nas_signal_info_ind_get_gsm(signal_info_ind, &data->gsm);
	data->gsm_valid = rc >= 0;
	data->wcdma = nas_signal_info_ind_get_wcdma(signal_info_ind);
	data->wcdma_valid = !!data->wcdma;
	data->lte = nas_signal_info_ind_get_lte(signal_info_ind);
	data->lte_valid = !!data->lte;
	rc = nas_signal_info_ind_get_tdma(signal_info_ind, &data->tdma);
	data->tdma_valid = rc >= 0;
}

void nas_signal_info_ind_data_free(struct nas_signal_info_ind_data *data)
{

	if(data->cdma_valid) {
		free(data->cdma);
	}
	if(data->hdr_valid) {
		free(data->hdr);
	}
	if(data->wcdma_valid) {
		free(data->wcdma);
	}
	if(data->lte_valid) {
		free(data->lte);
	}
}

void nas_signal_info_ind_free(struct nas_signal_info_ind *signal_info_ind)
{
	qmi_tlv_free((struct qmi_tlv*)signal_info_ind);
}

int nas_signal_info_ind_set_cdma(struct nas_signal_info_ind *signal_info_ind, struct nas_ss_cdma *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((int8_t*)(ptr + len)) = val->rssi;
	len += 1;
	*((int16_t*)(ptr + len)) = val->ecio;
	len += 2;
	rc = qmi_tlv_set((struct qmi_tlv*)signal_info_ind, 16, ptr, len);
	free(ptr);
	return rc;
}

struct nas_ss_cdma *nas_signal_info_ind_get_cdma(struct nas_signal_info_ind *signal_info_ind)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_ss_cdma *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)signal_info_ind, 16, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_ss_cdma));
	out->rssi = get_next(int8_t, 1);
	out->ecio = get_next(int16_t, 2);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_signal_info_ind_set_hdr(struct nas_signal_info_ind *signal_info_ind, struct nas_ss_hdr *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((int8_t*)(ptr + len)) = val->rssi;
	len += 1;
	*((int16_t*)(ptr + len)) = val->ecio;
	len += 2;
	*((uint8_t*)(ptr + len)) = val->sinr;
	len += 1;
	*((int32_t*)(ptr + len)) = val->io;
	len += 4;
	rc = qmi_tlv_set((struct qmi_tlv*)signal_info_ind, 17, ptr, len);
	free(ptr);
	return rc;
}

struct nas_ss_hdr *nas_signal_info_ind_get_hdr(struct nas_signal_info_ind *signal_info_ind)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_ss_hdr *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)signal_info_ind, 17, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_ss_hdr));
	out->rssi = get_next(int8_t, 1);
	out->ecio = get_next(int16_t, 2);
	out->sinr = get_next(uint8_t, 1);
	out->io = get_next(int32_t, 4);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_signal_info_ind_set_gsm(struct nas_signal_info_ind *signal_info_ind, int8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)signal_info_ind, 18, &val, sizeof(int8_t));
}

int nas_signal_info_ind_get_gsm(struct nas_signal_info_ind *signal_info_ind, int8_t *val)
{
	int8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)signal_info_ind, 18, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(int8_t))
		return -EINVAL;

	*val = *(int8_t*)ptr;
	return 0;
}

int nas_signal_info_ind_set_wcdma(struct nas_signal_info_ind *signal_info_ind, struct nas_ss_wcdma *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((int8_t*)(ptr + len)) = val->rssi;
	len += 1;
	*((int16_t*)(ptr + len)) = val->ecio;
	len += 2;
	rc = qmi_tlv_set((struct qmi_tlv*)signal_info_ind, 19, ptr, len);
	free(ptr);
	return rc;
}

struct nas_ss_wcdma *nas_signal_info_ind_get_wcdma(struct nas_signal_info_ind *signal_info_ind)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_ss_wcdma *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)signal_info_ind, 19, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_ss_wcdma));
	out->rssi = get_next(int8_t, 1);
	out->ecio = get_next(int16_t, 2);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_signal_info_ind_set_lte(struct nas_signal_info_ind *signal_info_ind, struct nas_ss_lte *val)
{
	size_t len = 0;
	int rc;
	// FIXME: use realloc dynamically instead
	void *ptr = malloc(1024);
	memset(ptr, 0, 1024);
	*((int8_t*)(ptr + len)) = val->rssi;
	len += 1;
	*((int8_t*)(ptr + len)) = val->rsrq;
	len += 1;
	*((int16_t*)(ptr + len)) = val->rsrp;
	len += 2;
	*((int16_t*)(ptr + len)) = val->snr;
	len += 2;
	rc = qmi_tlv_set((struct qmi_tlv*)signal_info_ind, 20, ptr, len);
	free(ptr);
	return rc;
}

struct nas_ss_lte *nas_signal_info_ind_get_lte(struct nas_signal_info_ind *signal_info_ind)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_ss_lte *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)signal_info_ind, 20, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_ss_lte));
	out->rssi = get_next(int8_t, 1);
	out->rsrq = get_next(int8_t, 1);
	out->rsrp = get_next(int16_t, 2);
	out->snr = get_next(int16_t, 2);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_signal_info_ind_set_tdma(struct nas_signal_info_ind *signal_info_ind, int8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)signal_info_ind, 21, &val, sizeof(int8_t));
}

int nas_signal_info_ind_get_tdma(struct nas_signal_info_ind *signal_info_ind, int8_t *val)
{
	int8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)signal_info_ind, 21, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(int8_t))
		return -EINVAL;

	*val = *(int8_t*)ptr;
	return 0;
}

struct nas_get_lte_cphy_ca_info_resp *nas_get_lte_cphy_ca_info_resp_parse(void *buf, size_t len)
{
	return (struct nas_get_lte_cphy_ca_info_resp*)qmi_tlv_decode(buf, len);
}

void nas_get_lte_cphy_ca_info_resp_getall(struct nas_get_lte_cphy_ca_info_resp *get_lte_cphy_ca_info_resp, struct nas_get_lte_cphy_ca_info_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)get_lte_cphy_ca_info_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
	rc = nas_get_lte_cphy_ca_info_resp_get_dl_bandwidth(get_lte_cphy_ca_info_resp, &data->dl_bandwidth);
	data->dl_bandwidth_valid = rc >= 0;
	data->phy_scell_info = nas_get_lte_cphy_ca_info_resp_get_phy_scell_info(get_lte_cphy_ca_info_resp);
	data->phy_scell_info_valid = !!data->phy_scell_info;
}

void nas_get_lte_cphy_ca_info_resp_data_free(struct nas_get_lte_cphy_ca_info_resp_data *data)
{

		free(data->res);
	if(data->phy_scell_info_valid) {
		free(data->phy_scell_info);
	}
}

void nas_get_lte_cphy_ca_info_resp_free(struct nas_get_lte_cphy_ca_info_resp *get_lte_cphy_ca_info_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_lte_cphy_ca_info_resp);
}

int nas_get_lte_cphy_ca_info_resp_get_dl_bandwidth(struct nas_get_lte_cphy_ca_info_resp *get_lte_cphy_ca_info_resp, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_lte_cphy_ca_info_resp, 17, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

struct nas_lte_cphy_agg_scell *nas_get_lte_cphy_ca_info_resp_get_phy_scell_info(struct nas_get_lte_cphy_ca_info_resp *get_lte_cphy_ca_info_resp)
{
	size_t len = 0, buf_sz;
	uint8_t *ptr;
	struct nas_lte_cphy_agg_scell *out;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_lte_cphy_ca_info_resp, 18, &buf_sz);
	if (!ptr)
		return NULL;

	out = malloc(sizeof(struct nas_lte_cphy_agg_scell));
	out->pci = get_next(uint16_t, 2);
	out->rx_chan = get_next(uint16_t, 2);
	out->dl_bandwidth = get_next(uint32_t, 4);
	out->lte_band = get_next(uint16_t, 2);
	out->state = get_next(uint32_t, 4);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

void nas_serving_system_free(struct nas_serving_system *val)
{
	if(val->radio_interfaces)
		free(val->radio_interfaces);

}

void nas_current_plmn_free(struct nas_current_plmn *val)
{
	if(val->description)
		free(val->description);

}

void nas_service_provider_name_free(struct nas_service_provider_name *val)
{
	if(val->name)
		free(val->name);

}

void nas_operator_plmn_arr_free(struct nas_operator_plmn_arr *val)
{
	for(size_t i = 0; i < val->operators_n; i++) {
	}
	if(val->operators)
		free(val->operators);

}

void nas_operator_plmn_name_free(struct nas_operator_plmn_name *val)
{
	if(val->long_name)
		free(val->long_name);
	if(val->short_name)
		free(val->short_name);

}

void nas_operator_plmn_name_arr_free(struct nas_operator_plmn_name_arr *val)
{
	for(size_t i = 0; i < val->operators_n; i++) {
		if(val->operators[i].long_name)
			free(val->operators[i].long_name);
		if(val->operators[i].short_name)
			free(val->operators[i].short_name);
	}
	if(val->operators)
		free(val->operators);

}

void nas_geran_info_free(struct nas_geran_info *val)
{
	for(size_t i = 0; i < val->cells_n; i++) {
	}
	if(val->cells)
		free(val->cells);

}

void nas_umts_info_free(struct nas_umts_info *val)
{
	for(size_t i = 0; i < val->cells_n; i++) {
	}
	if(val->cells)
		free(val->cells);
	if(val->gerans)
		free(val->gerans);

}

void nas_intrafreq_lte_info_free(struct nas_intrafreq_lte_info *val)
{
	for(size_t i = 0; i < val->cells_n; i++) {
	}
	if(val->cells)
		free(val->cells);

}

void nas_eons_plmn_name_free(struct nas_eons_plmn_name *val)
{
	if(val->sp_name)
		free(val->sp_name);
	if(val->short_name)
		free(val->short_name);
	if(val->long_name)
		free(val->long_name);

}


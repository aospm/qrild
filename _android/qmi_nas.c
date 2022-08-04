#include <errno.h>
#include <string.h>
#include "qmi_nas.h"

const struct qmi_tlv_msg_name nas_msg_name_map[9] = {
	{ .msg_id = 3, .msg_name = "nas_register_indications_req" },
	{ .msg_id = 32, .msg_name = "nas_get_signal_strength_req" },
	{ .msg_id = 32, .msg_name = "nas_get_signal_strength_resp" },
	{ .msg_id = 36, .msg_name = "nas_serving_system_ind" },
	{ .msg_id = 46, .msg_name = "nas_set_operating_mode_req" },
	{ .msg_id = 46, .msg_name = "nas_set_operating_mode_resp" },
	{ .msg_id = 57, .msg_name = "nas_get_operator_name_resp" },
	{ .msg_id = 67, .msg_name = "nas_get_cell_loc_info" },
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
	return qmi_tlv_set((struct qmi_tlv*)register_indications_req, 33, val, sizeof(struct nas_network_reject_info));
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
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_strength_resp, 1, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct nas_signal_strength))
		return NULL;

	return ptr;
}

struct nas_signal_strength *nas_get_signal_strength_resp_get_strength_list(struct nas_get_signal_strength_resp *get_signal_strength_resp, size_t *count)
{
	size_t size;
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_signal_strength_resp, 16, 16, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(struct nas_signal_strength))
		return NULL;

	*count = len;
	return ptr;
}

struct nas_ss_value *nas_get_signal_strength_resp_get_rssi_list(struct nas_get_signal_strength_resp *get_signal_strength_resp, size_t *count)
{
	size_t size;
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_signal_strength_resp, 17, 16, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(struct nas_ss_value))
		return NULL;

	*count = len;
	return ptr;
}

struct nas_ss_value *nas_get_signal_strength_resp_get_ecio_list(struct nas_get_signal_strength_resp *get_signal_strength_resp, size_t *count)
{
	size_t size;
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_signal_strength_resp, 18, 16, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(struct nas_ss_value))
		return NULL;

	*count = len;
	return ptr;
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
	void *ptr;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_signal_strength_resp, 21, 16, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(struct nas_ss_value))
		return NULL;

	*count = len;
	return ptr;
}

struct nas_ss_value *nas_get_signal_strength_resp_get_rsrq(struct nas_get_signal_strength_resp *get_signal_strength_resp)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_signal_strength_resp, 22, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct nas_ss_value))
		return NULL;

	return ptr;
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
	rc = nas_serving_system_ind_get_data_service_cap(serving_system_ind, &data->data_service_cap);
	data->data_service_cap_valid = rc >= 0;
	data->plmn = nas_serving_system_ind_get_plmn(serving_system_ind);
	data->plmn_valid = !!data->plmn;
	data->status = nas_serving_system_ind_get_status(serving_system_ind);
	data->status_valid = !!data->status;
}

void nas_serving_system_ind_data_free(struct nas_serving_system_ind_data *data)
{

	if(data->system_valid) {
		nas_serving_system_free(data->system);
		free(data->system);
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
	out->radio_interfaces = malloc(radio_interfaces_sz * out->radio_interfaces_n);
	for(size_t i = 0; i < out->radio_interfaces_n; i++) {
		out->radio_interfaces[i] = get_next(uint8_t, 1);
	}

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_serving_system_ind_set_data_service_cap(struct nas_serving_system_ind *serving_system_ind, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)serving_system_ind, 17, &val, sizeof(uint8_t));
}

int nas_serving_system_ind_get_data_service_cap(struct nas_serving_system_ind *serving_system_ind, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)serving_system_ind, 17, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
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
	out->description = malloc(strlen(ptr + len));
	strcpy(out->description, ptr + len); len += strlen(ptr + len);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

int nas_serving_system_ind_set_status(struct nas_serving_system_ind *serving_system_ind, struct nas_service_status *val)
{
	return qmi_tlv_set((struct qmi_tlv*)serving_system_ind, 34, val, sizeof(struct nas_service_status));
}

struct nas_service_status *nas_serving_system_ind_get_status(struct nas_serving_system_ind *serving_system_ind)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)serving_system_ind, 34, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct nas_service_status))
		return NULL;

	return ptr;
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
	data->operator_plmn_list = nas_get_operator_name_resp_get_operator_plmn_list(get_operator_name_resp, &data->operator_plmn_list_n);
	data->operator_plmn_list_valid = !!data->operator_plmn_list;
	data->operator_plmn_names = nas_get_operator_name_resp_get_operator_plmn_names(get_operator_name_resp, &data->operator_plmn_names_n);
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
	if(data->operator_plmn_list_valid) {
		free(data->operator_plmn_list);
	}
	if(data->operator_plmn_names_valid) {
		nas_operator_plmn_name_free(data->operator_plmn_names);
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
	out->name = malloc(strlen(ptr + len));
	strcpy(out->name, ptr + len); len += strlen(ptr + len);

	return out;

err_wrong_len:
	printf("%s: expected at least %zu bytes but got %zu\n", __func__, len, buf_sz);
	free(out);
	return NULL;
}

struct nas_operator_plmn *nas_get_operator_name_resp_get_operator_plmn_list(struct nas_get_operator_name_resp *get_operator_name_resp, size_t *count)
{
	size_t size;
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_operator_name_resp, 17, 64, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(struct nas_operator_plmn))
		return NULL;

	*count = len;
	return ptr;
}

struct nas_operator_plmn_name *nas_get_operator_name_resp_get_operator_plmn_names(struct nas_get_operator_name_resp *get_operator_name_resp, size_t *count)
{
	size_t size;
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get_array((struct qmi_tlv*)get_operator_name_resp, 18, 64, &len, &size);
	if (!ptr)
		return NULL;

	if (size != sizeof(struct nas_operator_plmn_name))
		return NULL;

	*count = len;
	return ptr;
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
	out->long_name = malloc(long_name_sz * out->long_name_n);
	for(size_t i = 0; i < out->long_name_n; i++) {
		out->long_name[i] = get_next(uint8_t, 1);
	}
	out->short_name_n = get_next(uint8_t, 1);
	size_t short_name_sz = 1;
	out->short_name = malloc(short_name_sz * out->short_name_n);
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

void nas_get_cell_loc_info_free(struct nas_get_cell_loc_info *get_cell_loc_info)
{
	qmi_tlv_free((struct qmi_tlv*)get_cell_loc_info);
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
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_lte_cphy_ca_info_resp, 18, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct nas_lte_cphy_agg_scell))
		return NULL;

	return ptr;
}

void nas_serving_system_free(struct nas_serving_system *val)
{
	free(val->radio_interfaces);

}

void nas_current_plmn_free(struct nas_current_plmn *val)
{
	free(val->description);

}

void nas_service_provider_name_free(struct nas_service_provider_name *val)
{
	free(val->name);

}

void nas_operator_plmn_name_free(struct nas_operator_plmn_name *val)
{
	free(val->long_name);
	free(val->short_name);

}


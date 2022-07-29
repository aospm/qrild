#include <errno.h>
#include <string.h>
#include "qmi_nas.h"

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
	*((char **)(ptr + len)) = val->description;
	len += -1;
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
	out->description = get_next(char *, strlen(ptr) + 1);

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

struct nas_get_signal_strength_resp *nas_get_signal_strength_resp_parse(void *buf, size_t len)
{
	return (struct nas_get_signal_strength_resp*)qmi_tlv_decode(buf, len);
}

void nas_get_signal_strength_resp_getall(struct nas_get_signal_strength_resp *get_signal_strength_resp, struct nas_get_signal_strength_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = qmi_tlv_get((struct qmi_tlv*)get_signal_strength_resp, 2, NULL);
	rc = nas_get_signal_strength_resp_get_lte_snr(get_signal_strength_resp, &data->lte_snr);
	rc = nas_get_signal_strength_resp_get_lte_rsrp(get_signal_strength_resp, &data->lte_rsrp);
	data->strength = nas_get_signal_strength_resp_get_strength(get_signal_strength_resp);
	data->strength_list = nas_get_signal_strength_resp_get_strength_list(get_signal_strength_resp);
}

void nas_get_signal_strength_resp_free(struct nas_get_signal_strength_resp *get_signal_strength_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_signal_strength_resp);
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

struct nas_get_lte_cphy_ca_info_resp *nas_get_lte_cphy_ca_info_resp_parse(void *buf, size_t len)
{
	return (struct nas_get_lte_cphy_ca_info_resp*)qmi_tlv_decode(buf, len);
}

void nas_get_lte_cphy_ca_info_resp_getall(struct nas_get_lte_cphy_ca_info_resp *get_lte_cphy_ca_info_resp, struct nas_get_lte_cphy_ca_info_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = qmi_tlv_get((struct qmi_tlv*)get_lte_cphy_ca_info_resp, 2, NULL);
	rc = nas_get_lte_cphy_ca_info_resp_get_dl_bandwidth(get_lte_cphy_ca_info_resp, &data->dl_bandwidth);
	data->dl_bandwidth_valid = rc >= 0;
	data->phy_scell_info = nas_get_lte_cphy_ca_info_resp_get_phy_scell_info(get_lte_cphy_ca_info_resp);
	data->phy_scell_info_valid = !!data->phy_scell_info;
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


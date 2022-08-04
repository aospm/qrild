#include <errno.h>
#include <string.h>
#include "qmi_wds.h"

const struct qmi_tlv_msg_name wds_msg_name_map[9] = {
	{ .msg_id = 32, .msg_name = "wds_start_network_interface_req" },
	{ .msg_id = 32, .msg_name = "wds_start_network_interface_resp" },
	{ .msg_id = 34, .msg_name = "wds_get_pkt_srvc_status_ind" },
	{ .msg_id = 45, .msg_name = "wds_get_current_settings_req" },
	{ .msg_id = 45, .msg_name = "wds_get_current_settings_resp" },
	{ .msg_id = 162, .msg_name = "wds_bind_mux_data_port_req" },
	{ .msg_id = 162, .msg_name = "wds_bind_mux_data_port_resp" },
	{ .msg_id = 175, .msg_name = "wds_bind_subscription_req" },
	{ .msg_id = 175, .msg_name = "wds_bind_subscription_resp" },
};

struct wds_start_network_interface_req *wds_start_network_interface_req_alloc(unsigned txn)
{
	return (struct wds_start_network_interface_req*)qmi_tlv_init(txn, 32, 0);
}

void *wds_start_network_interface_req_encode(struct wds_start_network_interface_req *start_network_interface_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)start_network_interface_req, len);
}

void wds_start_network_interface_req_free(struct wds_start_network_interface_req *start_network_interface_req)
{
	qmi_tlv_free((struct qmi_tlv*)start_network_interface_req);
}

int wds_start_network_interface_req_set_apn_name(struct wds_start_network_interface_req *start_network_interface_req, char *buf, size_t len)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_req, 20, buf, len);
}

int wds_start_network_interface_req_set_apn_type(struct wds_start_network_interface_req *start_network_interface_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_req, 56, &val, sizeof(uint32_t));
}

int wds_start_network_interface_req_set_ip_family_preference(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_req, 25, &val, sizeof(uint8_t));
}

int wds_start_network_interface_req_set_ep_type(struct wds_start_network_interface_req *start_network_interface_req, struct wds_ep_type_iface_id *val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_req, 59, val, sizeof(struct wds_ep_type_iface_id));
}

int wds_start_network_interface_req_set_bring_up_by_apn_name(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_req, 60, &val, sizeof(uint8_t));
}

int wds_start_network_interface_req_set_call_type(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_req, 53, &val, sizeof(uint8_t));
}

int wds_start_network_interface_req_set_profile_index(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_req, 49, &val, sizeof(uint8_t));
}

struct wds_start_network_interface_resp *wds_start_network_interface_resp_parse(void *buf, size_t len)
{
	return (struct wds_start_network_interface_resp*)qmi_tlv_decode(buf, len);
}

void wds_start_network_interface_resp_getall(struct wds_start_network_interface_resp *start_network_interface_resp, struct wds_start_network_interface_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)start_network_interface_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
	rc = wds_start_network_interface_resp_get_pkt_data_handle(start_network_interface_resp, &data->pkt_data_handle);
	rc = wds_start_network_interface_resp_get_call_end_reason(start_network_interface_resp, &data->call_end_reason);
	data->call_end_reason_valid = rc >= 0;
	data->ext = wds_start_network_interface_resp_get_ext(start_network_interface_resp);
	data->ext_valid = !!data->ext;
}

void wds_start_network_interface_resp_data_free(struct wds_start_network_interface_resp_data *data)
{

		free(data->res);
	if(data->ext_valid) {
		free(data->ext);
	}
}

void wds_start_network_interface_resp_free(struct wds_start_network_interface_resp *start_network_interface_resp)
{
	qmi_tlv_free((struct qmi_tlv*)start_network_interface_resp);
}

int wds_start_network_interface_resp_get_pkt_data_handle(struct wds_start_network_interface_resp *start_network_interface_resp, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)start_network_interface_resp, 1, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

int wds_start_network_interface_resp_get_call_end_reason(struct wds_start_network_interface_resp *start_network_interface_resp, uint16_t *val)
{
	uint16_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)start_network_interface_resp, 16, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint16_t))
		return -EINVAL;

	*val = *(uint16_t*)ptr;
	return 0;
}

struct wds_call_end_reason_ext *wds_start_network_interface_resp_get_ext(struct wds_start_network_interface_resp *start_network_interface_resp)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)start_network_interface_resp, 17, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct wds_call_end_reason_ext))
		return NULL;

	return ptr;
}

struct wds_get_pkt_srvc_status_ind *wds_get_pkt_srvc_status_ind_alloc(unsigned txn)
{
	return (struct wds_get_pkt_srvc_status_ind*)qmi_tlv_init(txn, 34, 4);
}

void *wds_get_pkt_srvc_status_ind_encode(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_pkt_srvc_status_ind, len);
}

struct wds_get_pkt_srvc_status_ind *wds_get_pkt_srvc_status_ind_parse(void *buf, size_t len)
{
	return (struct wds_get_pkt_srvc_status_ind*)qmi_tlv_decode(buf, len);
}

void wds_get_pkt_srvc_status_ind_getall(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, struct wds_get_pkt_srvc_status_ind_data *data)
{
	int rc;
	(void)rc;

	data->status = wds_get_pkt_srvc_status_ind_get_status(get_pkt_srvc_status_ind);
	rc = wds_get_pkt_srvc_status_ind_get_ip_family(get_pkt_srvc_status_ind, &data->ip_family);
	data->ip_family_valid = rc >= 0;
	rc = wds_get_pkt_srvc_status_ind_get_tech_name(get_pkt_srvc_status_ind, &data->tech_name);
	data->tech_name_valid = rc >= 0;
	rc = wds_get_pkt_srvc_status_ind_get_xlat_capable(get_pkt_srvc_status_ind, &data->xlat_capable);
	data->xlat_capable_valid = rc >= 0;
}

void wds_get_pkt_srvc_status_ind_data_free(struct wds_get_pkt_srvc_status_ind_data *data)
{

		free(data->status);
}

void wds_get_pkt_srvc_status_ind_free(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind)
{
	qmi_tlv_free((struct qmi_tlv*)get_pkt_srvc_status_ind);
}

int wds_get_pkt_srvc_status_ind_set_status(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, struct wds_pkt_srvc_status *val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_pkt_srvc_status_ind, 1, val, sizeof(struct wds_pkt_srvc_status));
}

struct wds_pkt_srvc_status *wds_get_pkt_srvc_status_ind_get_status(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_pkt_srvc_status_ind, 1, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct wds_pkt_srvc_status))
		return NULL;

	return ptr;
}

int wds_get_pkt_srvc_status_ind_set_ip_family(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_pkt_srvc_status_ind, 18, &val, sizeof(uint8_t));
}

int wds_get_pkt_srvc_status_ind_get_ip_family(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_pkt_srvc_status_ind, 18, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int wds_get_pkt_srvc_status_ind_set_tech_name(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint16_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_pkt_srvc_status_ind, 19, &val, sizeof(uint16_t));
}

int wds_get_pkt_srvc_status_ind_get_tech_name(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint16_t *val)
{
	uint16_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_pkt_srvc_status_ind, 19, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint16_t))
		return -EINVAL;

	*val = *(uint16_t*)ptr;
	return 0;
}

int wds_get_pkt_srvc_status_ind_set_xlat_capable(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_pkt_srvc_status_ind, 21, &val, sizeof(uint8_t));
}

int wds_get_pkt_srvc_status_ind_get_xlat_capable(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_pkt_srvc_status_ind, 21, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

struct wds_get_current_settings_req *wds_get_current_settings_req_alloc(unsigned txn)
{
	return (struct wds_get_current_settings_req*)qmi_tlv_init(txn, 45, 0);
}

void *wds_get_current_settings_req_encode(struct wds_get_current_settings_req *get_current_settings_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_current_settings_req, len);
}

void wds_get_current_settings_req_free(struct wds_get_current_settings_req *get_current_settings_req)
{
	qmi_tlv_free((struct qmi_tlv*)get_current_settings_req);
}

int wds_get_current_settings_req_set_requested_settings(struct wds_get_current_settings_req *get_current_settings_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_current_settings_req, 16, &val, sizeof(uint32_t));
}

struct wds_get_current_settings_resp *wds_get_current_settings_resp_parse(void *buf, size_t len)
{
	return (struct wds_get_current_settings_resp*)qmi_tlv_decode(buf, len);
}

void wds_get_current_settings_resp_getall(struct wds_get_current_settings_resp *get_current_settings_resp, struct wds_get_current_settings_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)get_current_settings_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
	rc = wds_get_current_settings_resp_get_ipv4_address_preference(get_current_settings_resp, &data->ipv4_address_preference);
	data->ipv4_address_preference_valid = rc >= 0;
	rc = wds_get_current_settings_resp_get_ipv4_gateway_addr(get_current_settings_resp, &data->ipv4_gateway_addr);
	data->ipv4_gateway_addr_valid = rc >= 0;
	rc = wds_get_current_settings_resp_get_ipv4_subnet_mask(get_current_settings_resp, &data->ipv4_subnet_mask);
	data->ipv4_subnet_mask_valid = rc >= 0;
	rc = wds_get_current_settings_resp_get_mtu(get_current_settings_resp, &data->mtu);
	data->mtu_valid = rc >= 0;
	rc = wds_get_current_settings_resp_get_ip_family(get_current_settings_resp, &data->ip_family);
	data->ip_family_valid = rc >= 0;
}

void wds_get_current_settings_resp_data_free(struct wds_get_current_settings_resp_data *data)
{

		free(data->res);
}

void wds_get_current_settings_resp_free(struct wds_get_current_settings_resp *get_current_settings_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_current_settings_resp);
}

int wds_get_current_settings_resp_get_ipv4_address_preference(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_current_settings_resp, 30, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

int wds_get_current_settings_resp_get_ipv4_gateway_addr(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_current_settings_resp, 32, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

int wds_get_current_settings_resp_get_ipv4_subnet_mask(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_current_settings_resp, 33, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

int wds_get_current_settings_resp_get_mtu(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_current_settings_resp, 41, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

int wds_get_current_settings_resp_get_ip_family(struct wds_get_current_settings_resp *get_current_settings_resp, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_current_settings_resp, 43, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

struct wds_bind_mux_data_port_req *wds_bind_mux_data_port_req_alloc(unsigned txn)
{
	return (struct wds_bind_mux_data_port_req*)qmi_tlv_init(txn, 162, 0);
}

void *wds_bind_mux_data_port_req_encode(struct wds_bind_mux_data_port_req *bind_mux_data_port_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)bind_mux_data_port_req, len);
}

void wds_bind_mux_data_port_req_free(struct wds_bind_mux_data_port_req *bind_mux_data_port_req)
{
	qmi_tlv_free((struct qmi_tlv*)bind_mux_data_port_req);
}

int wds_bind_mux_data_port_req_set_ep_id(struct wds_bind_mux_data_port_req *bind_mux_data_port_req, struct wds_ep_type_iface_id *val)
{
	return qmi_tlv_set((struct qmi_tlv*)bind_mux_data_port_req, 16, val, sizeof(struct wds_ep_type_iface_id));
}

int wds_bind_mux_data_port_req_set_mux_id(struct wds_bind_mux_data_port_req *bind_mux_data_port_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)bind_mux_data_port_req, 17, &val, sizeof(uint8_t));
}

struct wds_bind_mux_data_port_resp *wds_bind_mux_data_port_resp_parse(void *buf, size_t len)
{
	return (struct wds_bind_mux_data_port_resp*)qmi_tlv_decode(buf, len);
}

void wds_bind_mux_data_port_resp_getall(struct wds_bind_mux_data_port_resp *bind_mux_data_port_resp, struct wds_bind_mux_data_port_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)bind_mux_data_port_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
}

void wds_bind_mux_data_port_resp_data_free(struct wds_bind_mux_data_port_resp_data *data)
{

		free(data->res);
}

void wds_bind_mux_data_port_resp_free(struct wds_bind_mux_data_port_resp *bind_mux_data_port_resp)
{
	qmi_tlv_free((struct qmi_tlv*)bind_mux_data_port_resp);
}

struct wds_bind_subscription_req *wds_bind_subscription_req_alloc(unsigned txn)
{
	return (struct wds_bind_subscription_req*)qmi_tlv_init(txn, 175, 0);
}

void *wds_bind_subscription_req_encode(struct wds_bind_subscription_req *bind_subscription_req, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)bind_subscription_req, len);
}

void wds_bind_subscription_req_free(struct wds_bind_subscription_req *bind_subscription_req)
{
	qmi_tlv_free((struct qmi_tlv*)bind_subscription_req);
}

int wds_bind_subscription_req_set_subscription(struct wds_bind_subscription_req *bind_subscription_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)bind_subscription_req, 1, &val, sizeof(uint32_t));
}

struct wds_bind_subscription_resp *wds_bind_subscription_resp_parse(void *buf, size_t len)
{
	return (struct wds_bind_subscription_resp*)qmi_tlv_decode(buf, len);
}

void wds_bind_subscription_resp_getall(struct wds_bind_subscription_resp *bind_subscription_resp, struct wds_bind_subscription_resp_data *data)
{
	int rc;
	(void)rc;

	data->res = malloc(sizeof(struct qmi_response_type_v01));
	memcpy(data->res, qmi_tlv_get((struct qmi_tlv*)bind_subscription_resp, 2, NULL), sizeof(struct qmi_response_type_v01));
}

void wds_bind_subscription_resp_data_free(struct wds_bind_subscription_resp_data *data)
{

		free(data->res);
}

void wds_bind_subscription_resp_free(struct wds_bind_subscription_resp *bind_subscription_resp)
{
	qmi_tlv_free((struct qmi_tlv*)bind_subscription_resp);
}


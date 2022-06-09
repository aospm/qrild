#include <errno.h>
#include <string.h>
#include "qmi_wds.h"

struct wds_start_network_interface_req *wds_start_network_interface_req_alloc(unsigned txn)
{
	return (struct wds_start_network_interface_req*)qmi_tlv_init(txn, 32, 0);
}

struct wds_start_network_interface_req *wds_start_network_interface_req_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct wds_start_network_interface_req*)qmi_tlv_decode(buf, len, txn, 0);
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

int wds_start_network_interface_req_get_apn_name(struct wds_start_network_interface_req *start_network_interface_req, char *buf, size_t buflen)
{
	size_t len;
	char *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)start_network_interface_req, 20, &len);
	if (!ptr)
		return -ENOENT;

	if (len >= buflen)
		return -ENOMEM;

	memcpy(buf, ptr, len);
	buf[len] = '\0';
	return len;
}

int wds_start_network_interface_req_set_apn_type(struct wds_start_network_interface_req *start_network_interface_req, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_req, 56, &val, sizeof(uint32_t));
}

int wds_start_network_interface_req_get_apn_type(struct wds_start_network_interface_req *start_network_interface_req, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)start_network_interface_req, 56, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

int wds_start_network_interface_req_set_ip_family_preference(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_req, 25, &val, sizeof(uint8_t));
}

int wds_start_network_interface_req_get_ip_family_preference(struct wds_start_network_interface_req *start_network_interface_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)start_network_interface_req, 25, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int wds_start_network_interface_req_set_ep_type(struct wds_start_network_interface_req *start_network_interface_req, struct wds_ep_type_iface_id *val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_req, 59, val, sizeof(struct wds_ep_type_iface_id));
}

struct wds_ep_type_iface_id *wds_start_network_interface_req_get_ep_type(struct wds_start_network_interface_req *start_network_interface_req)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)start_network_interface_req, 59, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct wds_ep_type_iface_id))
		return NULL;

	return ptr;
}

int wds_start_network_interface_req_set_bring_up_by_apn_name(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_req, 60, &val, sizeof(uint8_t));
}

int wds_start_network_interface_req_get_bring_up_by_apn_name(struct wds_start_network_interface_req *start_network_interface_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)start_network_interface_req, 60, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int wds_start_network_interface_req_set_call_type(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_req, 53, &val, sizeof(uint8_t));
}

int wds_start_network_interface_req_get_call_type(struct wds_start_network_interface_req *start_network_interface_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)start_network_interface_req, 53, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

int wds_start_network_interface_req_set_profile_index(struct wds_start_network_interface_req *start_network_interface_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_req, 49, &val, sizeof(uint8_t));
}

int wds_start_network_interface_req_get_profile_index(struct wds_start_network_interface_req *start_network_interface_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)start_network_interface_req, 49, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

struct wds_start_network_interface_resp *wds_start_network_interface_resp_alloc(unsigned txn)
{
	return (struct wds_start_network_interface_resp*)qmi_tlv_init(txn, 32, 2);
}

struct wds_start_network_interface_resp *wds_start_network_interface_resp_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct wds_start_network_interface_resp*)qmi_tlv_decode(buf, len, txn, 2);
}

void *wds_start_network_interface_resp_encode(struct wds_start_network_interface_resp *start_network_interface_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)start_network_interface_resp, len);
}

void wds_start_network_interface_resp_free(struct wds_start_network_interface_resp *start_network_interface_resp)
{
	qmi_tlv_free((struct qmi_tlv*)start_network_interface_resp);
}

int wds_start_network_interface_resp_set_r(struct wds_start_network_interface_resp *start_network_interface_resp, struct wds_qmi_result *val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_resp, 2, val, sizeof(struct wds_qmi_result));
}

struct wds_qmi_result *wds_start_network_interface_resp_get_r(struct wds_start_network_interface_resp *start_network_interface_resp)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)start_network_interface_resp, 2, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct wds_qmi_result))
		return NULL;

	return ptr;
}

int wds_start_network_interface_resp_set_pkt_data_handle(struct wds_start_network_interface_resp *start_network_interface_resp, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_resp, 1, &val, sizeof(uint32_t));
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

int wds_start_network_interface_resp_set_call_end_reason(struct wds_start_network_interface_resp *start_network_interface_resp, uint16_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_resp, 16, &val, sizeof(uint16_t));
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

int wds_start_network_interface_resp_set_ext(struct wds_start_network_interface_resp *start_network_interface_resp, struct wds_call_end_reason_ext *val)
{
	return qmi_tlv_set((struct qmi_tlv*)start_network_interface_resp, 17, val, sizeof(struct wds_call_end_reason_ext));
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

struct wds_get_pkt_srvc_status_ind *wds_get_pkt_srvc_status_ind_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct wds_get_pkt_srvc_status_ind*)qmi_tlv_decode(buf, len, txn, 4);
}

void *wds_get_pkt_srvc_status_ind_encode(struct wds_get_pkt_srvc_status_ind *get_pkt_srvc_status_ind, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_pkt_srvc_status_ind, len);
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

struct wds_get_current_settings_req *wds_get_current_settings_req_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct wds_get_current_settings_req*)qmi_tlv_decode(buf, len, txn, 0);
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

int wds_get_current_settings_req_get_requested_settings(struct wds_get_current_settings_req *get_current_settings_req, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_current_settings_req, 16, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

struct wds_get_current_settings_resp *wds_get_current_settings_resp_alloc(unsigned txn)
{
	return (struct wds_get_current_settings_resp*)qmi_tlv_init(txn, 45, 2);
}

struct wds_get_current_settings_resp *wds_get_current_settings_resp_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct wds_get_current_settings_resp*)qmi_tlv_decode(buf, len, txn, 2);
}

void *wds_get_current_settings_resp_encode(struct wds_get_current_settings_resp *get_current_settings_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)get_current_settings_resp, len);
}

void wds_get_current_settings_resp_free(struct wds_get_current_settings_resp *get_current_settings_resp)
{
	qmi_tlv_free((struct qmi_tlv*)get_current_settings_resp);
}

int wds_get_current_settings_resp_set_r(struct wds_get_current_settings_resp *get_current_settings_resp, struct wds_qmi_result *val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_current_settings_resp, 2, val, sizeof(struct wds_qmi_result));
}

struct wds_qmi_result *wds_get_current_settings_resp_get_r(struct wds_get_current_settings_resp *get_current_settings_resp)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)get_current_settings_resp, 2, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct wds_qmi_result))
		return NULL;

	return ptr;
}

int wds_get_current_settings_resp_set_ipv4_address_preference(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_current_settings_resp, 30, &val, sizeof(uint32_t));
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

int wds_get_current_settings_resp_set_ipv4_gateway_addr(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_current_settings_resp, 32, &val, sizeof(uint32_t));
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

int wds_get_current_settings_resp_set_ipv4_subnet_mask(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_current_settings_resp, 33, &val, sizeof(uint32_t));
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

int wds_get_current_settings_resp_set_mtu(struct wds_get_current_settings_resp *get_current_settings_resp, uint32_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_current_settings_resp, 41, &val, sizeof(uint32_t));
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

int wds_get_current_settings_resp_set_ip_family(struct wds_get_current_settings_resp *get_current_settings_resp, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)get_current_settings_resp, 43, &val, sizeof(uint8_t));
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

struct wds_bind_mux_data_port_req *wds_bind_mux_data_port_req_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct wds_bind_mux_data_port_req*)qmi_tlv_decode(buf, len, txn, 0);
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

struct wds_ep_type_iface_id *wds_bind_mux_data_port_req_get_ep_id(struct wds_bind_mux_data_port_req *bind_mux_data_port_req)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)bind_mux_data_port_req, 16, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct wds_ep_type_iface_id))
		return NULL;

	return ptr;
}

int wds_bind_mux_data_port_req_set_mux_id(struct wds_bind_mux_data_port_req *bind_mux_data_port_req, uint8_t val)
{
	return qmi_tlv_set((struct qmi_tlv*)bind_mux_data_port_req, 17, &val, sizeof(uint8_t));
}

int wds_bind_mux_data_port_req_get_mux_id(struct wds_bind_mux_data_port_req *bind_mux_data_port_req, uint8_t *val)
{
	uint8_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)bind_mux_data_port_req, 17, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint8_t))
		return -EINVAL;

	*val = *(uint8_t*)ptr;
	return 0;
}

struct wds_bind_mux_data_port_resp *wds_bind_mux_data_port_resp_alloc(unsigned txn)
{
	return (struct wds_bind_mux_data_port_resp*)qmi_tlv_init(txn, 162, 2);
}

struct wds_bind_mux_data_port_resp *wds_bind_mux_data_port_resp_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct wds_bind_mux_data_port_resp*)qmi_tlv_decode(buf, len, txn, 2);
}

void *wds_bind_mux_data_port_resp_encode(struct wds_bind_mux_data_port_resp *bind_mux_data_port_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)bind_mux_data_port_resp, len);
}

void wds_bind_mux_data_port_resp_free(struct wds_bind_mux_data_port_resp *bind_mux_data_port_resp)
{
	qmi_tlv_free((struct qmi_tlv*)bind_mux_data_port_resp);
}

int wds_bind_mux_data_port_resp_set_r(struct wds_bind_mux_data_port_resp *bind_mux_data_port_resp, struct wds_qmi_result *val)
{
	return qmi_tlv_set((struct qmi_tlv*)bind_mux_data_port_resp, 2, val, sizeof(struct wds_qmi_result));
}

struct wds_qmi_result *wds_bind_mux_data_port_resp_get_r(struct wds_bind_mux_data_port_resp *bind_mux_data_port_resp)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)bind_mux_data_port_resp, 2, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct wds_qmi_result))
		return NULL;

	return ptr;
}

struct wds_bind_subscription_req *wds_bind_subscription_req_alloc(unsigned txn)
{
	return (struct wds_bind_subscription_req*)qmi_tlv_init(txn, 175, 0);
}

struct wds_bind_subscription_req *wds_bind_subscription_req_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct wds_bind_subscription_req*)qmi_tlv_decode(buf, len, txn, 0);
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

int wds_bind_subscription_req_get_subscription(struct wds_bind_subscription_req *bind_subscription_req, uint32_t *val)
{
	uint32_t *ptr;
	size_t len;

	ptr = qmi_tlv_get((struct qmi_tlv*)bind_subscription_req, 1, &len);
	if (!ptr)
		return -ENOENT;

	if (len != sizeof(uint32_t))
		return -EINVAL;

	*val = *(uint32_t*)ptr;
	return 0;
}

struct wds_bind_subscription_resp *wds_bind_subscription_resp_alloc(unsigned txn)
{
	return (struct wds_bind_subscription_resp*)qmi_tlv_init(txn, 175, 2);
}

struct wds_bind_subscription_resp *wds_bind_subscription_resp_parse(void *buf, size_t len, unsigned *txn)
{
	return (struct wds_bind_subscription_resp*)qmi_tlv_decode(buf, len, txn, 2);
}

void *wds_bind_subscription_resp_encode(struct wds_bind_subscription_resp *bind_subscription_resp, size_t *len)
{
	return qmi_tlv_encode((struct qmi_tlv*)bind_subscription_resp, len);
}

void wds_bind_subscription_resp_free(struct wds_bind_subscription_resp *bind_subscription_resp)
{
	qmi_tlv_free((struct qmi_tlv*)bind_subscription_resp);
}

int wds_bind_subscription_resp_set_r(struct wds_bind_subscription_resp *bind_subscription_resp, struct wds_qmi_result *val)
{
	return qmi_tlv_set((struct qmi_tlv*)bind_subscription_resp, 2, val, sizeof(struct wds_qmi_result));
}

struct wds_qmi_result *wds_bind_subscription_resp_get_r(struct wds_bind_subscription_resp *bind_subscription_resp)
{
	size_t len;
	void *ptr;

	ptr = qmi_tlv_get((struct qmi_tlv*)bind_subscription_resp, 2, &len);
	if (!ptr)
		return NULL;

	if (len != sizeof(struct wds_qmi_result))
		return NULL;

	return ptr;
}


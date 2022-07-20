#ifndef __QMI_WDA_H__
#define __QMI_WDA_H__

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <libqrtr.h>

#define get_next(_type, _sz) ({ \
	void* buf = ptr + len; \
	len += _sz; \
	if (len > buf_sz) goto err_wrong_len; \
	*(_type*)buf; \
})

#define QMI_WDA_SERVICE 26
#define QMI_WDA_SET_DATA_FORMAT 32

struct wda_ep_type_iface_id {
	uint32_t ep_type;
	uint32_t iface_id;
};

struct wda_set_data_format_req;
struct wda_set_data_format_resp;

/*
 * wda_set_data_format_req message
 */
struct wda_set_data_format_req *wda_set_data_format_req_alloc(unsigned txn);
struct wda_set_data_format_req *wda_set_data_format_req_parse(void *buf, size_t len);
void *wda_set_data_format_req_encode(struct wda_set_data_format_req *set_data_format_req, size_t *len);
void wda_set_data_format_req_free(struct wda_set_data_format_req *set_data_format_req);

int wda_set_data_format_req_set_link_prot(struct wda_set_data_format_req *set_data_format_req, uint32_t val);
int wda_set_data_format_req_get_link_prot(struct wda_set_data_format_req *set_data_format_req, uint32_t *val);

int wda_set_data_format_req_set_ul_data_aggregation_protocol(struct wda_set_data_format_req *set_data_format_req, uint32_t val);
int wda_set_data_format_req_get_ul_data_aggregation_protocol(struct wda_set_data_format_req *set_data_format_req, uint32_t *val);

int wda_set_data_format_req_set_dl_data_aggregation_protocol(struct wda_set_data_format_req *set_data_format_req, uint32_t val);
int wda_set_data_format_req_get_dl_data_aggregation_protocol(struct wda_set_data_format_req *set_data_format_req, uint32_t *val);

int wda_set_data_format_req_set_dl_data_aggretation_max_datagrams(struct wda_set_data_format_req *set_data_format_req, uint32_t val);
int wda_set_data_format_req_get_dl_data_aggretation_max_datagrams(struct wda_set_data_format_req *set_data_format_req, uint32_t *val);

int wda_set_data_format_req_set_dl_data_aggregation_max_size(struct wda_set_data_format_req *set_data_format_req, uint32_t val);
int wda_set_data_format_req_get_dl_data_aggregation_max_size(struct wda_set_data_format_req *set_data_format_req, uint32_t *val);

int wda_set_data_format_req_set_ep_type(struct wda_set_data_format_req *set_data_format_req, struct wda_ep_type_iface_id *val);
struct wda_ep_type_iface_id *wda_set_data_format_req_get_ep_type(struct wda_set_data_format_req *set_data_format_req);

/*
 * wda_set_data_format_resp message
 */
struct wda_set_data_format_resp *wda_set_data_format_resp_alloc(unsigned txn);
struct wda_set_data_format_resp *wda_set_data_format_resp_parse(void *buf, size_t len);
void *wda_set_data_format_resp_encode(struct wda_set_data_format_resp *set_data_format_resp, size_t *len);
void wda_set_data_format_resp_free(struct wda_set_data_format_resp *set_data_format_resp);

#endif

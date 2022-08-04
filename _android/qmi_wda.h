#ifndef __QMI_WDA_H__
#define __QMI_WDA_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <libqrtr.h>

#ifdef __cplusplus
extern "C" {
#endif

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


#define QMI_NUM_MESSAGES_WDA 2
extern const struct qmi_tlv_msg_name wda_msg_name_map[2];

/*
 * wda_set_data_format_req message
 */
struct wda_set_data_format_req *wda_set_data_format_req_alloc(unsigned txn);
void *wda_set_data_format_req_encode(struct wda_set_data_format_req *set_data_format_req, size_t *len);
void wda_set_data_format_req_free(struct wda_set_data_format_req *set_data_format_req);

int wda_set_data_format_req_set_link_prot(struct wda_set_data_format_req *set_data_format_req, uint32_t val);
int wda_set_data_format_req_set_ul_data_aggregation_protocol(struct wda_set_data_format_req *set_data_format_req, uint32_t val);
int wda_set_data_format_req_set_dl_data_aggregation_protocol(struct wda_set_data_format_req *set_data_format_req, uint32_t val);
int wda_set_data_format_req_set_dl_data_aggretation_max_datagrams(struct wda_set_data_format_req *set_data_format_req, uint32_t val);
int wda_set_data_format_req_set_dl_data_aggregation_max_size(struct wda_set_data_format_req *set_data_format_req, uint32_t val);
int wda_set_data_format_req_set_ep_type(struct wda_set_data_format_req *set_data_format_req, struct wda_ep_type_iface_id *val);

/*
 * wda_set_data_format_resp message
 */

struct wda_set_data_format_resp_data {
	struct qmi_response_type_v01 *res;
};

struct wda_set_data_format_resp *wda_set_data_format_resp_parse(void *buf, size_t len);
void wda_set_data_format_resp_getall(struct wda_set_data_format_resp *set_data_format_resp, struct wda_set_data_format_resp_data *data);
void wda_set_data_format_resp_data_free(struct wda_set_data_format_resp_data *data);
void wda_set_data_format_resp_free(struct wda_set_data_format_resp *set_data_format_resp);

#ifdef __cplusplus
}
#endif

#endif

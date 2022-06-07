#ifndef __QMI_UIM_H__
#define __QMI_UIM_H__

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#define get_next(_type, _sz) ({ \
	void* buf = ptr + len; \
	len += _sz; \
	if (len > buf_sz) goto err_wrong_len; \
	*(_type*)buf; \
})

struct qmi_tlv;

struct qmi_tlv *qmi_tlv_init(unsigned txn, unsigned msg_id, unsigned type);
struct qmi_tlv *qmi_tlv_init_ctl(unsigned txn, unsigned msg_id, unsigned type);
struct qmi_tlv *qmi_tlv_decode(void *buf, size_t len, unsigned *txn, unsigned type);
struct qmi_tlv *qmi_tlv_decode_ctl(void *buf, size_t len, unsigned *txn, unsigned type);
void *qmi_tlv_encode(struct qmi_tlv *tlv, size_t *len);
void *qmi_tlv_encode_ctl(struct qmi_tlv *tlv, size_t *len);
void qmi_tlv_free(struct qmi_tlv *tlv);

void *qmi_tlv_get(struct qmi_tlv *tlv, unsigned id, size_t *len);
void *qmi_tlv_get_array(struct qmi_tlv *tlv, unsigned id, unsigned len_size, size_t *len, size_t *size);
int qmi_tlv_set(struct qmi_tlv *tlv, unsigned id, void *buf, size_t len);
int qmi_tlv_set_array(struct qmi_tlv *tlv, unsigned id, unsigned len_size, void *buf, size_t len, size_t size);

#define QMI_RESULT_SUCCESS 0
#define QMI_RESULT_FAILURE 1
#define QMI_UIM_GET_CARD_STATUS 47

struct uim_qmi_result {
	uint16_t result;
	uint16_t error;
};

struct uim_card_status {
	uint16_t index_gw_primary;
	uint16_t index_1x_primary;
	uint16_t index_gw_secondary;
	uint16_t index_1x_secondary;
	uint8_t cards_n;
	struct card_status_cards {
		uint8_t card_state;
		uint8_t upin_state;
		uint8_t upin_retries;
		uint8_t upuk_retries;
		uint8_t error_code;
		uint8_t applications_n;
		struct card_status_cards_applications {
			uint8_t type;
			uint8_t state;
			uint8_t personalization_state;
			uint8_t personalization_feature;
			uint8_t personalization_retries;
			uint8_t personalization_unblock_retries;
			uint8_t application_identifier_value_n;
			uint8_t *application_identifier_value;
			uint8_t upin_replaces_pin1;
			uint8_t pin1_state;
			uint8_t pin1_retries;
			uint8_t puk1_retries;
			uint8_t pin2_state;
			uint8_t pin2_retries;
			uint8_t puk2_retries;
		} *applications;
	} *cards;
};

struct uim_get_card_status_req;
struct uim_get_card_status_resp;

/*
 * uim_get_card_status_req message
 */
struct uim_get_card_status_req *uim_get_card_status_req_alloc(unsigned txn);
struct uim_get_card_status_req *uim_get_card_status_req_parse(void *buf, size_t len, unsigned *txn);
void *uim_get_card_status_req_encode(struct uim_get_card_status_req *get_card_status_req, size_t *len);
void uim_get_card_status_req_free(struct uim_get_card_status_req *get_card_status_req);

/*
 * uim_get_card_status_resp message
 */
struct uim_get_card_status_resp *uim_get_card_status_resp_alloc(unsigned txn);
struct uim_get_card_status_resp *uim_get_card_status_resp_parse(void *buf, size_t len, unsigned *txn);
void *uim_get_card_status_resp_encode(struct uim_get_card_status_resp *get_card_status_resp, size_t *len);
void uim_get_card_status_resp_free(struct uim_get_card_status_resp *get_card_status_resp);

int uim_get_card_status_resp_set_result(struct uim_get_card_status_resp *get_card_status_resp, struct uim_qmi_result *val);
struct uim_qmi_result *uim_get_card_status_resp_get_result(struct uim_get_card_status_resp *get_card_status_resp);

int uim_get_card_status_resp_set_status(struct uim_get_card_status_resp *get_card_status_resp, struct uim_card_status *val);
struct uim_card_status *uim_get_card_status_resp_get_status(struct uim_get_card_status_resp *get_card_status_resp);

#endif

#ifndef __QMI_UIM_H__
#define __QMI_UIM_H__

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

#define QMI_UIM_GET_CARD_STATUS 47
#define QMI_UIM_CHANGE_PROVISIONING_SESSION 56
#define QMI_UIM_SESSION_TYPE_PRIMARY_GW_PROVISIONING 0

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

struct uim_provisioning_session_change {
	uint8_t session_type;
	uint8_t activate;
};

struct uim_provisioning_session_application {
	uint8_t slot;
	uint8_t application_identifier_value_n;
	uint8_t *application_identifier_value;
};

struct uim_get_card_status_req;
struct uim_get_card_status_resp;
struct uim_change_provisioning_session_req;
struct uim_change_provisioning_session_resp;

/*
 * uim_get_card_status_req message
 */
struct uim_get_card_status_req *uim_get_card_status_req_alloc(unsigned txn);
struct uim_get_card_status_req *uim_get_card_status_req_parse(void *buf, size_t len);
void *uim_get_card_status_req_encode(struct uim_get_card_status_req *get_card_status_req, size_t *len);
void uim_get_card_status_req_free(struct uim_get_card_status_req *get_card_status_req);

/*
 * uim_get_card_status_resp message
 */
struct uim_get_card_status_resp *uim_get_card_status_resp_alloc(unsigned txn);
struct uim_get_card_status_resp *uim_get_card_status_resp_parse(void *buf, size_t len);
void *uim_get_card_status_resp_encode(struct uim_get_card_status_resp *get_card_status_resp, size_t *len);
void uim_get_card_status_resp_free(struct uim_get_card_status_resp *get_card_status_resp);

int uim_get_card_status_resp_set_status(struct uim_get_card_status_resp *get_card_status_resp, struct uim_card_status *val);
struct uim_card_status *uim_get_card_status_resp_get_status(struct uim_get_card_status_resp *get_card_status_resp);

/*
 * uim_change_provisioning_session_req message
 */
struct uim_change_provisioning_session_req *uim_change_provisioning_session_req_alloc(unsigned txn);
struct uim_change_provisioning_session_req *uim_change_provisioning_session_req_parse(void *buf, size_t len);
void *uim_change_provisioning_session_req_encode(struct uim_change_provisioning_session_req *change_provisioning_session_req, size_t *len);
void uim_change_provisioning_session_req_free(struct uim_change_provisioning_session_req *change_provisioning_session_req);

int uim_change_provisioning_session_req_set_session_change(struct uim_change_provisioning_session_req *change_provisioning_session_req, struct uim_provisioning_session_change *val);
struct uim_provisioning_session_change *uim_change_provisioning_session_req_get_session_change(struct uim_change_provisioning_session_req *change_provisioning_session_req);

int uim_change_provisioning_session_req_set_application_information(struct uim_change_provisioning_session_req *change_provisioning_session_req, struct uim_provisioning_session_application *val);
struct uim_provisioning_session_application *uim_change_provisioning_session_req_get_application_information(struct uim_change_provisioning_session_req *change_provisioning_session_req);

/*
 * uim_change_provisioning_session_resp message
 */
struct uim_change_provisioning_session_resp *uim_change_provisioning_session_resp_alloc(unsigned txn);
struct uim_change_provisioning_session_resp *uim_change_provisioning_session_resp_parse(void *buf, size_t len);
void *uim_change_provisioning_session_resp_encode(struct uim_change_provisioning_session_resp *change_provisioning_session_resp, size_t *len);
void uim_change_provisioning_session_resp_free(struct uim_change_provisioning_session_resp *change_provisioning_session_resp);

#endif

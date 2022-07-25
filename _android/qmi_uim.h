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
#define QMI_UIM_GET_SLOT_STATUS 71
#define QMI_UIM_SLOT_STATUS_IND 72
#define QMI_UIM_SESSION_TYPE_PRIMARY_GW_PROVISIONING 0
#define QMI_UIM_CARD_STATE_ABSENT 0
#define QMI_UIM_CARD_STATE_PRESENT 1
#define QMI_UIM_CARD_STATE_ERROR 2
#define QMI_UIM_CARD_STATE_RESTRICTED 4

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

struct uim_physical_slot_state {
	uint8_t slots_n;
	struct physical_slot_state_slots {
		uint32_t card_state;
		uint32_t slot_state;
		uint8_t logical_slot;
		uint8_t iccid_n;
		uint8_t *iccid;
	} *slots;
};

struct uim_physical_slot_info {
	uint8_t slots_n;
	struct physical_slot_info_slots {
		uint32_t card_protocol;
		uint8_t valid_applications;
		uint8_t atr_value_n;
		uint8_t *atr_value;
		uint8_t is_euicc;
	} *slots;
};

struct uim_slot_status_msg {
	struct uim_physical_slot_state *state;
	struct uim_physical_slot_info *info;
	uint8_t eid_info_n;
	uint8_t *eid_info;
};

struct uim_get_card_status_req;
struct uim_get_card_status_resp;
struct uim_change_provisioning_session_req;
struct uim_change_provisioning_session_resp;
struct uim_get_slot_status_req;
struct uim_get_slot_status_resp;
struct uim_get_slot_status_ind;

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

/*
 * uim_get_slot_status_req message
 */
struct uim_get_slot_status_req *uim_get_slot_status_req_alloc(unsigned txn);
struct uim_get_slot_status_req *uim_get_slot_status_req_parse(void *buf, size_t len);
void *uim_get_slot_status_req_encode(struct uim_get_slot_status_req *get_slot_status_req, size_t *len);
void uim_get_slot_status_req_free(struct uim_get_slot_status_req *get_slot_status_req);

/*
 * uim_get_slot_status_resp message
 */
struct uim_get_slot_status_resp *uim_get_slot_status_resp_alloc(unsigned txn);
struct uim_get_slot_status_resp *uim_get_slot_status_resp_parse(void *buf, size_t len);
void *uim_get_slot_status_resp_encode(struct uim_get_slot_status_resp *get_slot_status_resp, size_t *len);
void uim_get_slot_status_resp_free(struct uim_get_slot_status_resp *get_slot_status_resp);

int uim_get_slot_status_resp_set_slot_state(struct uim_get_slot_status_resp *get_slot_status_resp, struct uim_physical_slot_state *val);
struct uim_physical_slot_state *uim_get_slot_status_resp_get_slot_state(struct uim_get_slot_status_resp *get_slot_status_resp);

int uim_get_slot_status_resp_set_slot_info(struct uim_get_slot_status_resp *get_slot_status_resp, struct uim_physical_slot_info *val);
struct uim_physical_slot_info *uim_get_slot_status_resp_get_slot_info(struct uim_get_slot_status_resp *get_slot_status_resp);

int uim_get_slot_status_resp_set_eid_info(struct uim_get_slot_status_resp *get_slot_status_resp, uint8_t *val, size_t count);
uint8_t *uim_get_slot_status_resp_get_eid_info(struct uim_get_slot_status_resp *get_slot_status_resp, size_t *count);

/*
 * uim_get_slot_status_ind message
 */
struct uim_get_slot_status_ind *uim_get_slot_status_ind_alloc(unsigned txn);
struct uim_get_slot_status_ind *uim_get_slot_status_ind_parse(void *buf, size_t len);
void *uim_get_slot_status_ind_encode(struct uim_get_slot_status_ind *get_slot_status_ind, size_t *len);
void uim_get_slot_status_ind_free(struct uim_get_slot_status_ind *get_slot_status_ind);

int uim_get_slot_status_ind_set_slot_state(struct uim_get_slot_status_ind *get_slot_status_ind, struct uim_physical_slot_state *val);
struct uim_physical_slot_state *uim_get_slot_status_ind_get_slot_state(struct uim_get_slot_status_ind *get_slot_status_ind);

int uim_get_slot_status_ind_set_slot_info(struct uim_get_slot_status_ind *get_slot_status_ind, struct uim_physical_slot_info *val);
struct uim_physical_slot_info *uim_get_slot_status_ind_get_slot_info(struct uim_get_slot_status_ind *get_slot_status_ind);

int uim_get_slot_status_ind_set_eid_info(struct uim_get_slot_status_ind *get_slot_status_ind, uint8_t *val, size_t count);
uint8_t *uim_get_slot_status_ind_get_eid_info(struct uim_get_slot_status_ind *get_slot_status_ind, size_t *count);

#endif

#ifndef __QMI_DMS_H__
#define __QMI_DMS_H__

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

#define QMI_DMS_GET_REVISION 35
#define QMI_DMS_GET_IDS 37
#define QMI_DMS_GET_OPERATING_MODE 45
#define QMI_DMS_SET_OPERATING_MODE 46
#define QMI_DMS_OPERATING_MODE_ONLINE 0
#define QMI_DMS_OPERATING_MODE_LOW_POWER 1
#define QMI_DMS_OPERATING_MODE_FACTORY_TEST 2
#define QMI_DMS_OPERATING_MODE_OFFLINE 3
#define QMI_DMS_OPERATING_MODE_RESET 4
#define QMI_DMS_OPERATING_MODE_SHUTTING_DOWN 5
#define QMI_DMS_OPERATING_MODE_PERSISTENT_LOW_POWER 6
#define QMI_DMS_OPERATING_MODE_MODE_ONLY_LOW_POWER 7
#define QMI_DMS_OPERATING_MODE_UNKNOWN 255

struct dms_ids {
	uint8_t esn_len;
	char * esn;
	uint8_t imei_len;
	char * imei;
	uint8_t meid_len;
	char * meid;
	uint8_t imei_ver_len;
	char * imei_ver;
};

struct dms_get_revision_req;
struct dms_get_revision_resp;
struct dms_get_ids_req;
struct dms_get_ids_resp;
struct dms_get_operating_mode_req;
struct dms_get_operating_mode_resp;
struct dms_set_operating_mode_req;
struct dms_set_operating_mode_resp;

/*
 * dms_get_revision_req message
 */
struct dms_get_revision_req *dms_get_revision_req_alloc(unsigned txn);
struct dms_get_revision_req *dms_get_revision_req_parse(void *buf, size_t len);
void *dms_get_revision_req_encode(struct dms_get_revision_req *get_revision_req, size_t *len);
void dms_get_revision_req_free(struct dms_get_revision_req *get_revision_req);

/*
 * dms_get_revision_resp message
 */
struct dms_get_revision_resp *dms_get_revision_resp_alloc(unsigned txn);
struct dms_get_revision_resp *dms_get_revision_resp_parse(void *buf, size_t len);
void *dms_get_revision_resp_encode(struct dms_get_revision_resp *get_revision_resp, size_t *len);
void dms_get_revision_resp_free(struct dms_get_revision_resp *get_revision_resp);

int dms_get_revision_resp_set_revision(struct dms_get_revision_resp *get_revision_resp, char *buf, size_t len);
int dms_get_revision_resp_get_revision(struct dms_get_revision_resp *get_revision_resp, char *buf, size_t buflen);

/*
 * dms_get_ids_req message
 */
struct dms_get_ids_req *dms_get_ids_req_alloc(unsigned txn);
struct dms_get_ids_req *dms_get_ids_req_parse(void *buf, size_t len);
void *dms_get_ids_req_encode(struct dms_get_ids_req *get_ids_req, size_t *len);
void dms_get_ids_req_free(struct dms_get_ids_req *get_ids_req);

/*
 * dms_get_ids_resp message
 */
struct dms_get_ids_resp *dms_get_ids_resp_alloc(unsigned txn);
struct dms_get_ids_resp *dms_get_ids_resp_parse(void *buf, size_t len);
void *dms_get_ids_resp_encode(struct dms_get_ids_resp *get_ids_resp, size_t *len);
void dms_get_ids_resp_free(struct dms_get_ids_resp *get_ids_resp);

int dms_get_ids_resp_set_esn(struct dms_get_ids_resp *get_ids_resp, char *buf, size_t len);
int dms_get_ids_resp_get_esn(struct dms_get_ids_resp *get_ids_resp, char *buf, size_t buflen);

int dms_get_ids_resp_set_imei(struct dms_get_ids_resp *get_ids_resp, char *buf, size_t len);
int dms_get_ids_resp_get_imei(struct dms_get_ids_resp *get_ids_resp, char *buf, size_t buflen);

int dms_get_ids_resp_set_meid(struct dms_get_ids_resp *get_ids_resp, char *buf, size_t len);
int dms_get_ids_resp_get_meid(struct dms_get_ids_resp *get_ids_resp, char *buf, size_t buflen);

int dms_get_ids_resp_set_imei_ver(struct dms_get_ids_resp *get_ids_resp, char *buf, size_t len);
int dms_get_ids_resp_get_imei_ver(struct dms_get_ids_resp *get_ids_resp, char *buf, size_t buflen);

/*
 * dms_get_operating_mode_req message
 */
struct dms_get_operating_mode_req *dms_get_operating_mode_req_alloc(unsigned txn);
struct dms_get_operating_mode_req *dms_get_operating_mode_req_parse(void *buf, size_t len);
void *dms_get_operating_mode_req_encode(struct dms_get_operating_mode_req *get_operating_mode_req, size_t *len);
void dms_get_operating_mode_req_free(struct dms_get_operating_mode_req *get_operating_mode_req);

/*
 * dms_get_operating_mode_resp message
 */
struct dms_get_operating_mode_resp *dms_get_operating_mode_resp_alloc(unsigned txn);
struct dms_get_operating_mode_resp *dms_get_operating_mode_resp_parse(void *buf, size_t len);
void *dms_get_operating_mode_resp_encode(struct dms_get_operating_mode_resp *get_operating_mode_resp, size_t *len);
void dms_get_operating_mode_resp_free(struct dms_get_operating_mode_resp *get_operating_mode_resp);

int dms_get_operating_mode_resp_set_mode(struct dms_get_operating_mode_resp *get_operating_mode_resp, uint8_t val);
int dms_get_operating_mode_resp_get_mode(struct dms_get_operating_mode_resp *get_operating_mode_resp, uint8_t *val);

int dms_get_operating_mode_resp_set_offline_reason(struct dms_get_operating_mode_resp *get_operating_mode_resp, uint16_t val);
int dms_get_operating_mode_resp_get_offline_reason(struct dms_get_operating_mode_resp *get_operating_mode_resp, uint16_t *val);

int dms_get_operating_mode_resp_set_hardware_restricted(struct dms_get_operating_mode_resp *get_operating_mode_resp, uint8_t val);
int dms_get_operating_mode_resp_get_hardware_restricted(struct dms_get_operating_mode_resp *get_operating_mode_resp, uint8_t *val);

/*
 * dms_set_operating_mode_req message
 */
struct dms_set_operating_mode_req *dms_set_operating_mode_req_alloc(unsigned txn);
struct dms_set_operating_mode_req *dms_set_operating_mode_req_parse(void *buf, size_t len);
void *dms_set_operating_mode_req_encode(struct dms_set_operating_mode_req *set_operating_mode_req, size_t *len);
void dms_set_operating_mode_req_free(struct dms_set_operating_mode_req *set_operating_mode_req);

int dms_set_operating_mode_req_set_mode(struct dms_set_operating_mode_req *set_operating_mode_req, uint8_t val);
int dms_set_operating_mode_req_get_mode(struct dms_set_operating_mode_req *set_operating_mode_req, uint8_t *val);

/*
 * dms_set_operating_mode_resp message
 */
struct dms_set_operating_mode_resp *dms_set_operating_mode_resp_alloc(unsigned txn);
struct dms_set_operating_mode_resp *dms_set_operating_mode_resp_parse(void *buf, size_t len);
void *dms_set_operating_mode_resp_encode(struct dms_set_operating_mode_resp *set_operating_mode_resp, size_t *len);
void dms_set_operating_mode_resp_free(struct dms_set_operating_mode_resp *set_operating_mode_resp);

#endif

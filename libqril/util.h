#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "libqrtr.h"
#include "timespec.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#ifndef gettid
#define gettid() ((pid_t)syscall(SYS_gettid))
#endif

struct enum_value {
	int value;
	const char *value_str;
	const char *name;
};

char to_hex(uint8_t ch);
void print_hex_dump(const char *prefix, const void *buf, size_t len);

#ifndef zalloc
#define zalloc(size) calloc(1, (size))
#endif

struct bytearray {
	size_t len;
	void* data;
};

struct bytearray *ba_init(size_t size);
void ba_set_size(struct bytearray *ba, size_t newsize);
void ba_free(struct bytearray *ba);

int msleep(long ms);

struct qmi_tlv {
	void *allocated;
	void *buf;
	size_t size;
	int error;
};

struct qmi_tlv_item {
	uint8_t key;
	uint16_t len;
	uint8_t data[];
} __attribute__((__packed__));

struct qmi_tlv_msg_name {
	int msg_id;
	const char *msg_name;
};

struct qmi_tlv *qmi_tlv_init(uint16_t txn, uint32_t msg_id, uint32_t msg_type);
void *qmi_tlv_encode(struct qmi_tlv *tlv, size_t *len);
struct qmi_tlv *qmi_tlv_decode(void *buf, size_t len);
void qmi_tlv_free(struct qmi_tlv *tlv);
void *qmi_tlv_get(struct qmi_tlv *tlv, uint8_t id, size_t *len);
void *qmi_tlv_get_array(struct qmi_tlv *tlv, uint8_t id, size_t len_size,
			size_t *len, size_t *size);
int qmi_tlv_set(struct qmi_tlv *tlv, uint8_t id, void *buf, size_t len);
int qmi_tlv_set_array(struct qmi_tlv *tlv, uint8_t id, size_t len_size,
		      void *buf, size_t len, size_t size);
struct qmi_response_type_v01 qmi_tlv_get_result(struct qmi_tlv *tlv);

void qmi_tlv_dump(struct qmi_tlv *tlv, int qmi_svc, const char *msg_name);
static inline int qmi_tlv_dump_buf(void *buf, size_t len, int qmi_svc, const char *msg_name) {
	struct qmi_tlv *tlv = qmi_tlv_decode(buf, len);
	if (!tlv)
		return -1;
	qmi_tlv_dump(tlv, qmi_svc, msg_name);
	qmi_tlv_free(tlv);

	return 0;
}

void time_now(struct timespec *ts);

#endif

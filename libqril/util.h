#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "libqrtr.h"

__BEGIN_DECLS

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

char to_hex(uint8_t ch);
void print_hex_dump(const char *prefix, const void *buf, size_t len);
uint8_t *bytes_from_hex_str(const char *str, size_t *out_len);
char *bytes_to_hex_string(uint8_t *bytes, size_t len);

#define zalloc(size) calloc(1, (size))

struct bytearray {
	size_t len;
	void* data;
};

struct bytearray *ba_init(size_t size);
void ba_set_size(struct bytearray *ba, size_t newsize);
void ba_free(struct bytearray *ba);

int msleep(long ms);

const char *qmi_tlv_msg_get_name(int qmi_svc, int msg_id);
void qmi_tlv_dump(struct qmi_tlv *tlv, int qmi_svc);
static inline int qmi_tlv_dump_buf(void *buf, size_t len, int qmi_svc) {
	struct qmi_tlv *tlv = qmi_tlv_decode(buf, len);
	if (!tlv)
		return -1;
	qmi_tlv_dump(tlv, qmi_svc);
	qmi_tlv_free(tlv);

	return 0;
}

void time_now(struct timespec *ts);

__END_DECLS
#endif

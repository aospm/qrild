#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdlib.h>
#include <string.h>

__BEGIN_DECLS

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

void print_hex_dump(const char *prefix, const void *buf, size_t len);

#define zalloc(size) calloc(1, (size))

struct bytearray {
	size_t len;
	void* data;
};

struct bytearray *ba_init(size_t size);
void ba_set_size(struct bytearray *ba, size_t newsize);
void ba_free(struct bytearray *ba);

int msleep(long ms);

__END_DECLS
#endif

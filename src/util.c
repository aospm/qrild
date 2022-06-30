#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#include "logging.h"
#include "libqrtr.h"

#include "util.h"
#include "qrild_msg.h"

static uint8_t to_hex(uint8_t ch)
{
	ch &= 0xf;
	return ch <= 9 ? '0' + ch : 'a' + ch - 10;
}

#define LINE_LENGTH 64

void print_hex_dump(const char *prefix, const void *buf, size_t len)
{
	const uint8_t *ptr = buf;
	size_t linelen;
	uint8_t ch;
	char line[LINE_LENGTH * 4 + 1];
	int li;
	int i;
	int j;

	// if (len < 0) {
	// 	LOGW("%s: len %zu less than 0", __func__, len);
	// 	return;
	// }

	if (prefix)
		printf("%s:\n", prefix);

	for (i = 0; i < len; i += LINE_LENGTH) {
		linelen = MIN(LINE_LENGTH, len - i);
		li = 0;

		for (j = 0; j < linelen; j++) {
			ch = ptr[i + j];
			line[li++] = to_hex(ch >> 4);
			line[li++] = to_hex(ch);
			line[li++] = j < linelen - 1 ? ':' : ' ';
		}

		// for (; j < LINE_LENGTH; j++) {
		// 	line[li++] = ' ';
		// 	line[li++] = ' ';
		// 	line[li++] = ' ';
		// }

		// for (j = 0; j < linelen; j++) {
		// 	ch = ptr[i + j];
		// 	line[li++] = isprint(ch) ? ch : '.';
		// }

		line[li] = '\0';

		printf("%s\n\n", line);
	}
}

struct bytearray *ba_init(size_t size) {
	struct bytearray *arr = zalloc(sizeof(struct bytearray));
	arr->len = size;
	arr->data = zalloc(4096);
	printf("Created array of %zu bytes\n", arr->len);

	return arr;
}

void ba_free(struct bytearray *ba) {
	free(ba->data);
	free(ba);
}

void ba_set_size(struct bytearray *ba, size_t newsize) {
	//size_t oldsize = ba->len;
	if (newsize > 4096) {
		printf("can't resize larger than 4096\n");
	}
	ba->len = newsize;
	return;
	// ba->data = realloc(ba->data, newsize);
	// ba->len = newsize;
	// printf("resized to %u\n", ba->len);

	// memset(ba->data + oldsize, 0, newsize - oldsize);
}

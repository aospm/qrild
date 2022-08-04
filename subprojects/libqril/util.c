#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

#include "libqrtr.h"

#include "qrild.h"
#include "q_log.h"
#include "util.h"
#include "qrild_msg.h"

#include "qmi_dms.h"
#include "qmi_dpm.h"
#include "qmi_nas.h"
#include "qmi_uim.h"
#include "qmi_wda.h"
#include "qmi_wds.h"

char to_hex(uint8_t ch)
{
	ch &= 0xf;
	return ch <= 9 ? '0' + ch : 'A' + ch - 10;
}

uint8_t *bytes_from_hex_str(const char *str, size_t *out_len)
{
	size_t b_len, len = strlen(str);
	uint8_t *out;
	int i, rc;

	if (len % 2)
		return NULL;

	b_len = len / 2;
	out = malloc(b_len);

	for (i = 0; i < b_len; i++) {
		rc = sscanf(str + i * 2, "%2hhx", &out[i]);
		if (rc < 0)
			return NULL;
	}

	if (out_len)
		*out_len = b_len;
	return out;
}

char *bytes_to_hex_string(uint8_t *bytes, size_t len)
{
	char *str = (char *)zalloc(len * 2 + 1);
	for (size_t i = 0; i < len; i++) {
		str[i * 2] = to_hex(bytes[i] >> 4);
		str[i * 2 + 1] = to_hex(bytes[i]);
	}

	return str;
}

#define LINE_LENGTH 32

void print_hex_dump(const char *prefix, const void *buf, size_t len)
{
	const uint8_t *ptr = buf;
	size_t linelen, buf_size;
	uint8_t ch;
	int i;
	int j;
	char *printbuf;
	FILE *fp = open_memstream(&printbuf, &buf_size);

	// if (len < 0) {
	// 	LOGW("%s: len %zu less than 0", __func__, len);
	// 	return;
	// }

	if (prefix)
		fprintf(fp, "%s:\n", prefix);

	for (i = 0; i < len; i += LINE_LENGTH) {
		linelen = MIN(LINE_LENGTH, len - i);

		for (j = 0; j < linelen; j++) {
			ch = ptr[i + j];
			fprintf(fp, "%c", to_hex(ch >> 4));
			fprintf(fp, "%c", to_hex(ch));
			fprintf(fp, "%c", j < linelen - 1 ? ':' : ' ');
		}

		// for (; j < LINE_LENGTH; j++) {
		// 	fprintf(fp, "%c", ' ');
		// 	fprintf(fp, "%c", ' ');
		// 	fprintf(fp, "%c", ' ');
		// }

		// for (j = 0; j < linelen; j++) {
		// 	ch = ptr[i + j];
		// 	fprintf(fp, "%c", isprint(ch) ? ch : '.');
		// }

		fprintf(fp, "\n");
	}

	fclose(fp);
	log_trace(printbuf);
	free(printbuf);
}

struct bytearray *ba_init(size_t size)
{
	struct bytearray *arr = zalloc(sizeof(struct bytearray));
	arr->len = size;
	arr->data = zalloc(4096);
	log_info("Created array of %zu bytes", arr->len);

	return arr;
}

void ba_free(struct bytearray *ba)
{
	free(ba->data);
	free(ba);
}

void ba_set_size(struct bytearray *ba, size_t newsize)
{
	//size_t oldsize = ba->len;
	if (newsize > 4096) {
		log_info("can't resize larger than 4096");
	}
	ba->len = newsize;
	return;
	// ba->data = realloc(ba->data, newsize);
	// ba->len = newsize;
	// log_info("resized to %u", ba->len);

	// memset(ba->data + oldsize, 0, newsize - oldsize);
}

int msleep(long ms)
{
	struct timespec ts;
	int ret;

	if (ms < 0) {
		errno = EINVAL;
		return -1;
	}

	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;

	do {
		ret = nanosleep(&ts, &ts);
	} while (ret && errno == EINTR);

	return ret;
}

const char *qmi_tlv_msg_get_name(int qmi_svc, int msg_id)
{
	struct qmi_tlv_msg_name *msg_name_map;
	size_t n_messages;
	int i;

	switch(qmi_svc) {
	case QMI_SERVICE_DMS:
		msg_name_map = &dms_msg_name_map[0];
		n_messages = QMI_NUM_MESSAGES_DMS;
		break;
	case QMI_SERVICE_DPM:
		msg_name_map = &dpm_msg_name_map[0];
		n_messages = QMI_NUM_MESSAGES_DPM;
		break;
	case QMI_SERVICE_NAS:
		msg_name_map = &nas_msg_name_map[0];
		n_messages = QMI_NUM_MESSAGES_NAS;
		break;
	case QMI_SERVICE_UIM:
		msg_name_map = &uim_msg_name_map[0];
		n_messages = QMI_NUM_MESSAGES_UIM;
		break;
	case QMI_SERVICE_WDA:
		msg_name_map = &wda_msg_name_map[0];
		n_messages = QMI_NUM_MESSAGES_WDA;
		break;
	case QMI_SERVICE_WDS:
		msg_name_map = &wds_msg_name_map[0];
		n_messages = QMI_NUM_MESSAGES_WDS;
		break;
	default:
		log_error("Can't find map for service: %d\n", qmi_svc);
		return NULL;
	}

	for(i = 0; i < n_messages; i++) {
		if (msg_name_map[i].msg_id == msg_id)
			return msg_name_map[i].msg_name;
	}

	log_warn("Couldn't find name of msg %d for service %d\n", msg_id, qmi_svc);

	return NULL;
}

void qmi_tlv_dump(struct qmi_tlv *tlv, int qmi_svc) {
	struct qmi_tlv_item *item;
	struct qmi_header *pkt;
	unsigned offset = sizeof(struct qmi_header);
	void *pkt_data;
	int i = 0, j, k;
	uint8_t ch;
	size_t linelen, buf_size;
	char *buf;
	char *msg_name;
	FILE *fp = open_memstream(&buf, &buf_size);

	pkt = tlv->buf;
	pkt_data = &pkt[0];

	msg_name = qmi_tlv_msg_get_name(qmi_svc, pkt->msg_id);

	fprintf(fp, "<<< QMI Message:\n");
	if (msg_name)
		fprintf(fp, "<<<    name    : %s\n",msg_name);
	fprintf(fp, "<<<    type    : %u\n", pkt->type);
	fprintf(fp, "<<<    msg_len : 0x%1$04x (%1$u)\n", pkt->msg_len);
	fprintf(fp, "<<<    msg_id  : 0x%1$04x (%1$u)\n", pkt->msg_id);
	fprintf(fp, "<<<    txn_id  : 0x%1$04x (%1$u)\n", pkt->txn_id);
	fprintf(fp, "<<< TLVs:");
	// I do not understand why this -1 is needed
	while (offset < tlv->size - 1) {
		item = pkt_data + offset;
		fprintf(fp, "<<< TLV %d: {id: 0x%02x, len: 0x%02x}\n", i, item->key, item->len);
		if (item->len > pkt->msg_len + sizeof(struct qmi_header) - offset) {
			log_trace("Invalid item length!");
			return;
		}
		for (j = 0; j < item->len; j += LINE_LENGTH) {
			linelen = MIN(LINE_LENGTH, item->len - j);

			for (k = 0; k < linelen; k++) {
				ch = item->data[j + k];
				fprintf(fp, "%c", to_hex(ch >> 4));
				fprintf(fp, "%c", to_hex(ch));
				fprintf(fp, "%c", k < linelen - 1 ? ':' : ' ');
			}

			for (; k < LINE_LENGTH; k++) {
				fprintf(fp, "%c", ' ');
				fprintf(fp, "%c", ' ');
				fprintf(fp, "%c", ' ');
			}

			for (k = 0; k < linelen; k++) {
				ch = item->data[j + k];
				fprintf(fp, "%c", isprint(ch) ? ch : '.');
			}

			fprintf(fp, "\n");
		}
		offset += sizeof(struct qmi_tlv_item) + item->len;
		i++;
	}

	fclose(fp);
	log_trace(buf);
	free(buf);
}

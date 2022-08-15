#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

#include "libqrtr.h"

#include "qrild.h"
#include "list.h"
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
	const struct qmi_tlv_msg_name *msg_name_map;
	size_t n_messages;
	int i;

	switch (qmi_svc) {
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
		return NULL;
	}

	for (i = 0; i < n_messages; i++) {
		if (msg_name_map[i].msg_id == msg_id)
			return msg_name_map[i].msg_name;
	}

	return NULL;
}

void qmi_tlv_dump(struct qmi_tlv *tlv, int qmi_svc)
{
	struct qmi_tlv_item *item;
	struct qmi_header *pkt;
	unsigned offset = sizeof(struct qmi_header);
	void *pkt_data;
	int i = 0, j, k;
	uint8_t ch;
	size_t linelen, buf_size;
	char *buf;
	const char *msg_name;
	FILE *fp = open_memstream(&buf, &buf_size);

	pkt = tlv->buf;
	pkt_data = &pkt[0];

	msg_name = qmi_tlv_msg_get_name(qmi_svc, pkt->msg_id);

	fprintf(fp, "<<< QMI Message:\n");
	if (msg_name)
		fprintf(fp, "<<<    name    : %s\n", msg_name);
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

void time_now(struct timespec *ts)
{
	clock_gettime(CLOCK_REALTIME, ts);
}

// FIXME: stick this lock debugging code somewhere else...
static unsigned long strhash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

struct qlock {
	struct list_head li;
	const char *file;
	const char *mtex;
	int line;
	unsigned long hash;
	int count;
	bool global;
	pid_t tid;
};

static struct list_head locks = LIST_INIT(locks);
static pthread_mutex_t locktrack_mtex = PTHREAD_MUTEX_INITIALIZER;

static struct qlock *lock_find_by_hash(unsigned long hash)
{
	static struct qlock *l;

	list_for_each_entry(l, &locks, li)
	{
		if (l->hash == hash)
			return l;
	}

	return NULL;
}

static struct qlock *lock_init(const char *mtex, const char *file, int line, pid_t tid,
			       unsigned long hash)
{
	struct qlock *l = zalloc(sizeof(struct qlock));
	list_append(&locks, &l->li);
	l->count = 1;
	l->hash = hash;
	l->mtex = mtex;
	l->file = file;
	l->line = line;
	l->tid = tid;
	l->global = false;

	return l;
}

static void track_lock(const char *mtex, uintptr_t addr, const char *file, const char *func,
		       int line, bool lock, bool trace)
{
	char buf[64];
	pid_t tid = gettid();
	unsigned long hash;
	struct qlock *l_global, *l;

	pthread_mutex_lock(&locktrack_mtex);

	sprintf(buf, "%s:%s:%s", mtex, file, func);
	hash = strhash((unsigned char *)&buf[0]);

	l = lock_find_by_hash(hash);
	l_global = lock_find_by_hash(addr);
	if (!l_global) {
		l_global = lock_init(mtex, file, line, tid, addr);
		l_global->global = true;
		log_error("TRACKLOCK: %s:%d %s() new global lock: %s (%lu)", l_global->file,
			  l_global->line, func, mtex, l_global->hash);
	}
	if (!lock) {
		if (!l) {
			log_error("TRACKLOCK: %s:%d %s() %s can't find lock to unlock!", file, line,
				  func, mtex);
			goto out;
		}
		if (trace)
			log_trace("TRACKLOCK: %s:%d %s() UNLOCK %s (%d) (global count: %d) (%lu)",
				  file, line, func, mtex, l->count, l_global->count, l->hash);
		l_global->count--;
		l->count--;
		goto out;
	}
	if (!l) {
		l = lock_init(mtex, file, line, tid, hash);
		log_error("TRACKLOCK: %s:%d %s() new lock: %s (%lu)", l->file, l->line, func, mtex,
			  l->hash);
		goto out;
	}
	if (trace)
		log_trace("TRACKLOCK: %s:%d %s() LOCK %s (%d) (global count: %d) (%lu)", file, line,
			  func, mtex, l->count, l_global->count, l->hash);
	l_global->count++;
	l->count++;

out:
	pthread_mutex_unlock(&locktrack_mtex);
}

int _q_thread_mutex_lock(pthread_mutex_t *m, const char *mtex, const char *file, const char *func,
			 int line)
{
	int rc;
	track_lock(mtex, (uintptr_t)m, file, func, line, true, true);
	rc = pthread_mutex_lock(m);
	log_error("TRACKLOCK: %s:%d %s() OBTAINED %s", file, line, func, mtex);

	// if (rc) {
	// 	log_error("TRACKLOCK: %s:%d %s() %s failed to lock! %d (%s)", file, line, func,
	// 		mtex, rc, strerror(rc));
	// 	pthread_mutex_lock(m);
	// }

	return rc;
}

int _q_thread_mutex_unlock(pthread_mutex_t *m, const char *mtex, const char *file, const char *func,
			   int line)
{
	int rc;
	track_lock(mtex, (uintptr_t)m, file, func, line, false, true);
	rc = pthread_mutex_unlock(m);

	return rc;
}

int _q_thread_cond_timedwait(pthread_cond_t *c, pthread_mutex_t *m, struct timespec *ts,
			     const char *mtex, const char *file, const char *func, int line)
{
	int rc;
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	rc = pthread_mutex_trylock(m);
	if (rc != EBUSY) {
		log_error("TRACKLOCK: %s:%d %s() TIMEDWAIT CALLED WITH UNLOCKED MUTEX %s", file,
			  line, func, mtex);
		while (true) {
			rc++;
		}
	}
	log_error("TRACKLOCK: %s:%d %s() TIMEDWAIT UNLOCK %s (trylock rc: %d (%s))", file, line,
		  func, mtex, rc, strerror(rc));
	log_debug(
		"TRACKLOCK: timespec now {tv_sec: %ld, tv_nsec: %ld}, timeout {tv_sec: %ld, tv_nsec: %ld}",
		now.tv_sec, now.tv_nsec, ts->tv_sec, ts->tv_nsec);
	track_lock(mtex, (uintptr_t)m, file, func, line, false, false);
	rc = pthread_cond_timedwait(c, m, ts);
	track_lock(mtex, (uintptr_t)m, file, func, line, true, false);
	log_error("TRACKLOCK: %s:%d %s() TIMEDWAIT LOCK %s (%d)", file, line, func, mtex, rc);

	return rc;
}

int _q_thread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m, const char *mtex, const char *file,
			const char *func, int line)
{
	int rc;
	rc = pthread_mutex_trylock(m);
	if (rc != EBUSY) {
		log_error("TRACKLOCK: %s:%d %s() WAIT CALLED WITH UNLOCKED MUTEX %s", file, line,
			  func, mtex);
		while (true) {
			rc++;
		}
	}
	log_error("TRACKLOCK: %s:%d %s() WAIT UNLOCK %s (trylock rc: %d (%s))", file, line, func,
		  mtex, rc, strerror(rc));
	track_lock(mtex, (uintptr_t)m, file, func, line, false, false);
	rc = pthread_cond_wait(c, m);
	track_lock(mtex, (uintptr_t)m, file, func, line, true, false);
	log_error("TRACKLOCK: %s:%d %s() WAIT LOCK %s (%d)", file, line, func, mtex, rc);

	return rc;
}

void _q_thread_dump_locks()
{
	static struct qlock *l;
	pthread_mutex_lock(&locktrack_mtex);
	log_info("TRACKLOCK: LOCK DUMP");
	list_for_each_entry(l, &locks, li)
	{
		if (l->global)
			log_info("\t%s: GLOBAL count: %d, tid: %d (%lu)", l->mtex, l->count, l->tid,
				 l->hash);
		else
			log_info("\t%s: %s:%d count: %d, tid: %d (%lu)", l->mtex, l->file, l->line,
				 l->count, l->tid, l->hash);
	}
	pthread_mutex_unlock(&locktrack_mtex);
}

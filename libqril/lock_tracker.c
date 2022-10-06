/*
 * Copyright (C) 2022, Linaro Ltd.
 * Author: Caleb Connolly <caleb.connolly@linaro.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#ifndef ANDROID
#define _GNU_SOURCE
#endif
#include <unistd.h>
#include <pthread.h>

#include "libqril_private.h"

static struct list_head locks = LIST_INIT(locks);
static pthread_mutex_t locktrack_mtex = PTHREAD_MUTEX_INITIALIZER;

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
	const char *func;
	int line;
	unsigned long hash;
	int count;
	bool global;
	pid_t tid;
};

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

static struct qlock *lock_init(const char *mtex, const char *file, const char *func, int line,
			       pid_t tid, unsigned long hash)
{
	struct qlock *l = zalloc(sizeof(struct qlock));
	list_append(&locks, &l->li);
	l->count = 1;
	l->hash = hash;
	l->mtex = mtex;
	l->file = file;
	l->func = func;
	l->line = line;
	l->tid = tid;
	l->global = false;

	return l;
}

static unsigned long lock_gen_hash(const char *mtex, const char *file, const char *func)
{
	char buf[128];
	snprintf(buf, 128, "%s:%s:%s", mtex, file, func);
	return strhash((unsigned char *)&buf[0]);
}

static void track_lock(const char *mtex, uintptr_t addr, unsigned long hash, const char *file,
		       const char *func, int line, bool lock, bool trace)
{
	pid_t tid = gettid();

	struct qlock *l_global, *l;

	pthread_mutex_lock(&locktrack_mtex);

	l = lock_find_by_hash(hash);
	l_global = lock_find_by_hash(addr);

	if (lock && !l_global) {
		l_global = lock_init(mtex, file, func, line, tid, addr);
		l_global->global = true;
		log_info("TRACKLOCK: %s:%d %s() new global lock: %s (%lu)", l_global->file,
			 l_global->line, func, mtex, l_global->hash);
	}

	// New lock
	if (lock && !l) {
		l = lock_init(mtex, file, func, line, tid, hash);
		log_error("TRACKLOCK: %s:%d %s() new lock: %s (%lu)", l->file, l->line, func, mtex,
			  l->hash);
		goto out;
	}

	if (!l || !l_global) {
		log_error("TRACKLOCK: Couldn't find lock to update count!!! (%lu)", addr);
		pthread_mutex_unlock(&locktrack_mtex);
		goto out;
	}

	// if (trace)
	// 	log_trace("TRACKLOCK: %s:%d %s() %sLOCK %s (%d) (global count: %d) (%lu)", file,
	// 		  line, func, lock ? "" : "UN", mtex, l->count, l_global->count, l->hash);

out:
	pthread_mutex_unlock(&locktrack_mtex);
}

// Due to racing the counts can become larger than 1
// but should immediately decrement again.
static void update_count(uintptr_t addr, unsigned long hash, bool lock)
{
	struct qlock *l_global, *l;

	pthread_mutex_lock(&locktrack_mtex);

	l = lock_find_by_hash(hash);
	l_global = lock_find_by_hash(addr);

	if (!l || !l_global) {
		pthread_mutex_unlock(&locktrack_mtex);
		log_error("TRACKLOCK: Couldn't find lock to update count!!! (%lu)", addr);
		return;
	}

	if (lock) {
		l_global->count++;
		l->count++;
	} else {
		l_global->count--;
		l->count--;
	}

	pthread_mutex_unlock(&locktrack_mtex);

	log_trace("TRACKLOCK: %s:%d %s() %sLOCK %s (%d) (global count: %d) (%lu)", l->file, l->line,
		  l->func, lock ? "" : "UN", l->mtex, l->count, l_global->count, l->hash);
}

int _q_thread_mutex_lock(pthread_mutex_t *m, const char *mtex, const char *file, const char *func,
			 int line)
{
	int rc;
	unsigned long hash = lock_gen_hash(mtex, file, func);
	track_lock(mtex, (uintptr_t)m, hash, file, func, line, true, true);
	rc = pthread_mutex_lock(m);
	update_count((uintptr_t)m, hash, true);
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
	unsigned long hash = lock_gen_hash(mtex, file, func);
	track_lock(mtex, (uintptr_t)m, hash, file, func, line, false, true);
	rc = pthread_mutex_unlock(m);
	update_count((uintptr_t)m, hash, false);

	return rc;
}

int _q_thread_cond_timedwait(pthread_cond_t *c, pthread_mutex_t *m, struct timespec *ts,
			     const char *mtex, const char *file, const char *func, int line)
{
	int rc;
	struct timespec now;
	unsigned long hash = lock_gen_hash(mtex, file, func);
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
	track_lock(mtex, (uintptr_t)m, hash, file, func, line, false, false);
	update_count((uintptr_t)m, hash, false);
	rc = pthread_cond_timedwait(c, m, ts);
	track_lock(mtex, (uintptr_t)m, hash, file, func, line, true, false);
	update_count((uintptr_t)m, hash, true);
	log_error("TRACKLOCK: %s:%d %s() TIMEDWAIT LOCK %s (%d)", file, line, func, mtex, rc);

	return rc;
}

int _q_thread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m, const char *mtex, const char *file,
			const char *func, int line)
{
	int rc;
	unsigned long hash = lock_gen_hash(mtex, file, func);
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
	track_lock(mtex, (uintptr_t)m, hash, file, func, line, false, false);
	update_count((uintptr_t)m, hash, false);
	rc = pthread_cond_wait(c, m);
	track_lock(mtex, (uintptr_t)m, hash, file, func, line, true, false);
	update_count((uintptr_t)m, hash, true);
	log_error("TRACKLOCK: %s:%d %s() WAIT LOCK %s (%d)", file, line, func, mtex, rc);

	return rc;
}

void _q_thread_dump_locks()
{
	static struct qlock *l;
	size_t buf_size;
	char *buf;
	FILE *fp = open_memstream(&buf, &buf_size);

	pthread_mutex_lock(&locktrack_mtex);
	fprintf(fp, "TRACKLOCK: LOCK DUMP\n");
	fprintf(fp, "G | LOCK                     | FILE                             |"
		 " FUNCTION                             | COUNT |  THREAD  | HASH\n");
	list_for_each_entry(l, &locks, li)
	{
		if (l->global)
			fprintf(fp, "G | %24s |                                  |"
				 "                                      | %5d | %8d | %lu\n",
				l->mtex, l->count, l->tid, l->hash);
		else
			fprintf(fp, "  | %24s | %27s:%4d | %36s | %5d | %8d | %lu\n", l->mtex, l->file,
				 l->line, l->func, l->count, l->tid, l->hash);
	}
	pthread_mutex_unlock(&locktrack_mtex);

	fclose(fp);
	log_info(buf);
	free(buf);
}

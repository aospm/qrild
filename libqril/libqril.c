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
#include <errno.h>
#include <linux/qrtr.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>

#include <arpa/inet.h>

#include "q_log.h"
#include "workqueue_priv.h"
#include "util.h"
#include "libqril.h"
#include "libqril_events.h"
#include "libqril_private.h"

static enum modem_state modem_state;

static void q_log_lock(bool lock, void *data)
{
	static pthread_mutex_t print_mtex = PTHREAD_MUTEX_INITIALIZER;

	if (lock) {
		pthread_mutex_lock(&print_mtex);
	} else {
		pthread_mutex_unlock(&print_mtex);
	}
}

static void *_main_loop(void * _)
{
	while (true) {
		sleep(1);
	}

	return NULL;
}

void dump_state(int x) {
	messages_dump_pending();
	q_thread_dump_locks();
	q_workqueue_dump();
}

/****** Public API *******/

void libqril_init()
{
	pthread_t main_thread;
	struct sigaction action;

	log_set_level(QLOG_TRACE);
	log_set_lock(q_log_lock, NULL);

	q_workqueue_init();

	services_init();
	messages_init();

	memset(&action, 0, sizeof(action));
	action.sa_handler = dump_state;
	//sigaction(SIGTERM, &action, NULL);
	//sigaction(SIGINT, &action, NULL);
	sigaction(SIGHUP, &action, NULL);

	// Doesn't do much for now, but that might change
	if (pthread_create(&main_thread, NULL, _main_loop, NULL)) {
		log_error("Failed to create msg thread");
		abort();
	}

	return;
}

enum modem_state libqril_modem_state()
{
	return modem_state;
}

const char *libqril_strerror(int err)
{
	if (err < 0)
		return strerror(err);
	else
		return libqril_qmi_error_string(err);
}

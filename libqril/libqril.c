#include <errno.h>
#include <linux/qrtr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include <arpa/inet.h>

#include "q_log.h"
#include "util.h"
#include "libqril.h"
#include "libqril_events.h"

#include "libqril_private.h"

static struct libqril_state *state;
static int qrtr_sock;

static void q_log_lock(bool lock, void *data)
{
	struct rild_state *state = data;
	static pthread_mutex_t print_mtex = PTHREAD_MUTEX_INITIALIZER;

	if (lock) {
		pthread_mutex_lock(&print_mtex);
	} else {
		pthread_mutex_unlock(&print_mtex);
	}
}

static void *msg_loop(void * _)
{
	int rc;

	// Find all QRTR services
	qrild_qrtr_do_lookup(state);

	while (!state->exit) {
		rc = qrild_qrtr_send_queued(state);
		if (rc < 0) {
			log_error("[MSGLOOP] Failed to send queued messages! %d", rc);
			state->exit = true;
			break;
		}
		rc = qrtr_poll(qrtr_sock, 50);
		if (rc < 0 && errno == EINTR)
			continue;
		if (rc < 0)
			log_error("[MSGLOOP] poll() failed: %d (%s)", errno, strerror(errno));

		if (rc > 0)
			qrild_qrtr_recv(state);
	}

	log_info("[MSGLOOP] Quitting loop!");
	qrtr_close(qrtr_sock);

	return NULL;
}

static void *main_loop(void * _)
{
	while (true) {
		sleep(1);
	}

	return NULL;
}

struct wait_for_qmi_service_data {
	pthread_mutex_t mtex;
	pthread_cond_t cond;
	enum qmi_service service;
};

static void _on_service_new(void *_data, enum qmi_service service)
{
	struct wait_for_qmi_service_data *data = _data;

	if (service != data->service)
		return;
	
	q_thread_mutex_lock(&data->mtex);
	pthread_cond_broadcast(&data->cond);
	q_thread_mutex_unlock(&data->mtex);
}

void libqril_wait_for_qmi_service(enum qmi_service service)
{
	struct wait_for_qmi_service_data data;
	struct libqril_events handler = {
		.on_service_new = _on_service_new,
	};

	log_debug("Waiting for service %s", qmi_service_to_string(service, false));

	data.mtex = PTHREAD_MUTEX_INITIALIZER;
	data.cond = PTHREAD_COND_INITIALIZER;
	data.service = service;

	libqril_register_event_handlers(&handler, &data);

	q_thread_mutex_lock(&data.mtex);
	q_thread_cond_wait(&data.cond, &data.mtex);
	q_thread_mutex_unlock(&data.mtex);

	libqril_unregister_event_handlers_by_struct(&handler);
}

void libqril_init()
{
	int rc;
	pthread_t msg_thread;
	pthread_t main_thread;

	pthread_mutexattr_t mattr;
	pthread_condattr_t cattr;

	state = zalloc(sizeof(struct libqril_state));

	log_set_lock(q_log_lock, state);

	q_workqueue_init();

	list_init(&state->services);
	list_init(&state->pending_rx);
	list_init(&state->pending_tx);

	pthread_mutexattr_init(&mattr);
	pthread_condattr_init(&cattr);

	pthread_mutex_init(&state->services_mutex, &mattr);
	pthread_mutex_init(&state->msg_mutex, &mattr);
	pthread_cond_init(&state->msg_change, &cattr);
	pthread_cond_init(&state->pending_indications, &cattr);
	pthread_mutex_init(&state->connection_status_mutex, &mattr);
	pthread_cond_init(&state->connection_status_change, &cattr);

	qrtr_sock = qrtr_open(0);
	if (qrtr_sock < 0) {
		log_error("Failed to open QRTR socket: %d", qrtr_sock);
		abort();
	}

	if (pthread_create(&msg_thread, NULL, msg_loop, NULL)) {
		log_error("Failed to create msg thread");
		abort();
	}

	// Wait for the modem to be discovered
	libqril_wait_for_qmi_service(QMI_SERVICE_DMS);

	if (pthread_create(&main_thread, NULL, main_loop, NULL)) {
		log_error("Failed to create msg thread");
		abort();
	}

	return;
}

enum modem_state libqril_modem_state()
{
	return state->modem_state;
}

int libqril_modem_activate()
{
	else if (state->modem_state != STATE_OFFLINE)
		return -EINVAL;
}

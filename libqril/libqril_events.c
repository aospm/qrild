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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>

#include <arpa/inet.h>

#include "libqril_private.h"
#include "timespec.h"

static pthread_mutex_t events_mutex = PTHREAD_MUTEX_INITIALIZER;
static struct list_head event_handlers = LIST_INIT(event_handlers);

static void _process_event(void *_event);

struct ev_handler {
	struct list_head li;
	struct libqril_events h;
	long handlers_id;
	void *data;
};

const char *event_type_name[] = {
	[EV_MODEM_STATE_CHANGE] = "EV_MODEM_STATE_CHANGE",
	[EV_QMI_INDICATION] = "EV_QMI_INDICATION",
	[EV_SERVICE_DISCOVERY_DONE] = "EV_SERVICE_DISCOVERY_DONE",
	[EV_SERVICE_NEW] = "EV_SERVICE_NEW",
	[EV_SERVICE_GOODBYE] = "EV_SERVICE_GOODBYE",
};

struct ev_type {
	struct list_head li;
	enum libqril_event_type type;
	struct timespec timestamp;
	struct q_work work;
	union {
		enum modem_state newstate; // EV_MODEM_STATE_CHANGE
		struct qmi_header *ind; // EV_QMI_INDICATION
		enum qmi_service service; // EV_SERVICE_NEW, EV_SERVICE_GOODBYE
	};
};

static struct ev_type *_ev_type_new(enum libqril_event_type type)
{
	struct ev_type *e = zalloc(sizeof(struct ev_type));
	e->type = type;
	e->work.data = e;
	e->work.func = _process_event;
	e->timestamp = timespec_now();

	return e;
}

/**
 * @brief if a client on_qmi_indication() callback returns true
 * then we need to update the pointer to the new buffer and preallocate
 * a new pointer for the next client.
 * The client is then responsible for free'ing the buffer, and we avoid dealing with
 * complicated pointer lifetimes.
 * 
 * We have to duplicate the buffer before calling the callback to avoid racing with
 * the client in case they free the buffer in another thread.
 *
 * @buf: Pointer to the buffer to pre-allocate
 * 
 * @returns a duplicate of @buf
 */
static struct qmi_header *_ind_buffer_dup(struct qmi_header *buf)
{
	struct qmi_header *newbuf = zalloc(buf->msg_len + sizeof(struct qmi_header));

	memcpy(newbuf, buf, buf->msg_len + sizeof(struct qmi_header));

	return newbuf;
}

static void _process_event(void *_event)
{
	struct ev_type *event = _event;
	struct ev_handler *handler;
	struct list_head *li, *bkup;
	long age = timespec_to_ms(timespec_sub(timespec_now(), event->timestamp));
	struct qmi_header *nextbuf;
	log_debug("[EVENTS] '%s', age: %ldms", event_type_name[event->type], age);

	if (event->type == EV_QMI_INDICATION)
		nextbuf = _ind_buffer_dup(event->ind);

	q_thread_mutex_lock(&events_mutex);
	list_for_each_safe(&event_handlers, li, bkup)
	{
		handler = list_entry(li, struct ev_handler, li);
		switch (event->type) {
		case EV_MODEM_STATE_CHANGE:
			if (handler->h.on_modem_state_change)
				handler->h.on_modem_state_change(handler->data, event->newstate);
			break;
		case EV_QMI_INDICATION:
			// FIXME:
			// clang-format off
			if (handler->h.on_qmi_indication &&
			    handler->h.on_qmi_indication(handler->data, event->ind,
			    event->ind->msg_len + sizeof(struct qmi_header))) {
				event->ind = nextbuf;
				nextbuf = _ind_buffer_dup(event->ind);
			}
			// clang-format on
			break;
		case EV_SERVICE_DISCOVERY_DONE:
			log_trace("Calling handler discovery done");
			if (handler->h.on_service_discovery_done)
				handler->h.on_service_discovery_done(handler->data);
		case EV_SERVICE_NEW:
			if (handler->h.on_service_new)
				handler->h.on_service_new(handler->data, event->service);
			break;
		case EV_SERVICE_GOODBYE:
			if (handler->h.on_service_goodbye)
				handler->h.on_service_goodbye(handler->data, event->service);
			break;
		default:
			log_error("[EVENTS] Invalid event type: %d", event->type);
			break;
		}
	}
	q_thread_mutex_unlock(&events_mutex);

	if (event->type == EV_QMI_INDICATION) {
		free(nextbuf);
		free(event->ind);
	}

	free(event);
}

/* Lock events_mutex before calling */
static struct ev_handler *_event_handlers_get_by_id(long hid)
{
	struct list_head *li, *bkup;
	struct ev_handler *entry;

	list_for_each_safe(&event_handlers, li, bkup)
	{
		entry = list_entry(li, struct ev_handler, li);
		if (entry->handlers_id == hid) {
			return entry;
		}
	}

	return NULL;
}

/******* Internal API *******/

void event_service_discovery_done()
{
	static bool called = false;
	struct ev_type *event;

	if (called) {
		log_warn("The service discovery event should only occur once!");
	}

	called = true;

	event = _ev_type_new(EV_SERVICE_DISCOVERY_DONE);

	q_work_schedule_now(&event->work);
	log_trace("Service discovery done!");
}

void event_new_modem_state_change(enum modem_state newstate)
{
	struct ev_type *event = _ev_type_new(EV_MODEM_STATE_CHANGE);
	event->newstate = newstate;

	q_work_schedule_now(&event->work);
}

void event_new_indication(struct qmi_header *ind)
{
	struct ev_type *event = _ev_type_new(EV_QMI_INDICATION);
	event->ind = ind;

	q_work_schedule_now(&event->work);
}

void event_service_new(enum qmi_service service)
{
	struct ev_type *event = _ev_type_new(EV_SERVICE_NEW);
	event->service = service;

	q_work_schedule_now(&event->work);
}

void event_service_goodbye(enum qmi_service service)
{
	struct ev_type *event = _ev_type_new(EV_SERVICE_GOODBYE);
	event->service = service;

	q_work_schedule_now(&event->work);
}

/******* Public API ********/

int libqril_register_event_handlers(struct libqril_events *handlers, void *data)
{
	struct ev_handler *entry = zalloc(sizeof(struct ev_handler));
	memcpy(&entry->h, handlers, sizeof(struct libqril_events));
	entry->handlers_id = libqril_event_handlers_get_id(handlers);

	log_trace("Registered new event handlers");

	q_thread_mutex_lock(&events_mutex);
	list_append(&event_handlers, &entry->li);
	q_thread_mutex_unlock(&events_mutex);

	return 0;
}

int libqril_event_handlers_unregister(unsigned long hid)
{
	struct ev_handler *entry;

	q_thread_mutex_lock(&events_mutex);
	entry = _event_handlers_get_by_id(hid);
	if (!entry) {
		q_thread_mutex_unlock(&events_mutex);
		return -ENOENT;
	}

	list_remove(&entry->li);
	free(entry);
	q_thread_mutex_unlock(&events_mutex);

	return 0;
}

unsigned long libqril_event_handlers_get_id(struct libqril_events *handlers)
{
	// Bite me
	return (uintptr_t)handlers;
}

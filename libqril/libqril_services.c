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

#include <arpa/inet.h>

#include <libqrtr.h>

#include "libqril.h"
#include "util.h"
#include "libqril_private.h"

static void _wait_service_discovery_done_on_done();

static pthread_mutex_t services_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t service_discovery_done = PTHREAD_COND_INITIALIZER;
static struct list_head services = LIST_INIT(services);

static struct libqril_events discovery_done_handler = {
	.on_service_discovery_done = _wait_service_discovery_done_on_done,
};

#define service_for_each(s) list_for_each_entry(s, &services, li)

const struct enum_value qmi_service_values[];

struct qmi_service_info {
	enum qmi_service type;
	uint16_t major;
	uint16_t minor;
	uint16_t node;
	uint16_t port;
	const char *name;
	struct list_head li;
};

struct wait_for_qmi_service_data {
	pthread_cond_t cond;
	enum qmi_service service;
};

struct qmi_service_info *_qmi_service_get(enum qmi_service type)
{
	struct qmi_service_info *service, *out = NULL;
	service_for_each(service) {
		if (service->type == type) {
			out = service;
			break;
		};
	}
	return out;
}

// FIXME: this is pretty ugly
void _log_service(struct qmi_service_info *info)
{
	static int count = 0;
	if (!info) {
		count = 0;
		return;
	}

	if (!count)
		log_debug("| Type | Node | Port | Major | Minor | Service Name");

	log_debug("| %4d | %4d | %5d | %4d  | %4d  | %s", info->type, info->node,
	     info->port, info->major, info->minor,
	     info->name ? info->name : "<unknown>");

	count++;
}

static void _wait_service_discovery_done_on_done(enum qmi_service service)
{
	q_thread_mutex_lock(&services_mutex);
	pthread_cond_broadcast(&service_discovery_done);
	q_thread_mutex_unlock(&services_mutex);
}

/***** Internal API *****/

int qmi_service_get(enum qmi_service type, int *port, int *node)
{
	q_thread_mutex_lock(&services_mutex);
	struct qmi_service_info *service = _qmi_service_get(type);

	if (!service) {
		q_thread_mutex_unlock(&services_mutex);
		return -ENOENT;
	}

	if (port)
		*port = service->port;
	if (node)
		*node = service->node;

	q_thread_mutex_unlock(&services_mutex);
	return 0;
}

int qmi_service_get_port(enum qmi_service type)
{
	int port;
	int rc = qmi_service_get(type, &port, NULL);
	return rc ?: port;
}

int qmi_service_get_node(enum qmi_service type)
{
	int node;
	int rc = qmi_service_get(type, NULL, &node);
	return rc ?: node;
}

int qmi_service_from_port(uint16_t port, enum qmi_service *type)
{
	struct qmi_service_info *service;
	q_thread_mutex_lock(&services_mutex);
	service_for_each(service) {
		if (service->port == port) {
			*type = service->type;
			q_thread_mutex_unlock(&services_mutex);
			return 0;
		}
	}

	q_thread_mutex_unlock(&services_mutex);
	return -ENOENT;
}

void qmi_service_new(struct qrtr_packet *pkt)
{
	struct qmi_service_info *service;
	// If the pkt is all empty that means all services have been
	// discovered
	if (!pkt->service && !pkt->node && !pkt->port && !pkt->instance) {
		log_trace("Got null service, firing service discovery done event");
		event_service_discovery_done();
		return;
	}

	service = zalloc(sizeof(struct qmi_service_info));

	service->type = pkt->service;
	service->node = pkt->node;
	service->port = pkt->port;
	service->major = pkt->instance & 0xff;
	service->minor = pkt->instance >> 8;
	service->name = libqril_qmi_service_name(service->type);

	_log_service(service);

	q_thread_mutex_lock(&services_mutex);
	list_append(&services, &service->li);
	event_service_new(service->type);
	q_thread_mutex_unlock(&services_mutex);
}

void qmi_service_goodbye(enum qmi_service type)
{
	struct qmi_service_info *service;

	q_thread_mutex_lock(&services_mutex);

	service = _qmi_service_get(type);
	if (!service)
		return;

	log_debug("Service shutdown: %s", service->name);

	list_remove(&service->li);
	q_thread_mutex_unlock(&services_mutex);
	free(service);

	event_service_goodbye(type);
}

void services_init()
{
	libqril_register_event_handlers(&discovery_done_handler, NULL);
}

/****** Public API *******/

const char *libqril_qmi_service_name(enum qmi_service service)
{
	const struct enum_value *v = &qmi_service_values[0];
	while (v->value_str) {
		if (v->value == service)
			return v->value_str;
		v++;
	}

	return "<UNKNOWN>";
}

void libqril_wait_for_service_discovery()
{
	log_debug("Waiting for services to be discovered");

	q_thread_mutex_lock(&services_mutex);
	while (q_thread_cond_wait(&service_discovery_done, &services_mutex));
	q_thread_mutex_unlock(&services_mutex);

	log_trace("Got service discovery done notification!");
}

int libqril_qmi_service_online(enum qmi_service service)
{
	return qmi_service_get(service, NULL, NULL);
}

/****** Debugging data *******/

const struct enum_value qmi_service_values[] = {
	{ QMI_SERVICE_UNKNOWN, "QMI_SERVICE_UNKNOWN", "unknown" },
	{ QMI_SERVICE_CTL, "QMI_SERVICE_CTL", "ctl" },
	{ QMI_SERVICE_WDS, "QMI_SERVICE_WDS", "wds" },
	{ QMI_SERVICE_DMS, "QMI_SERVICE_DMS", "dms" },
	{ QMI_SERVICE_NAS, "QMI_SERVICE_NAS", "nas" },
	{ QMI_SERVICE_QOS, "QMI_SERVICE_QOS", "qos" },
	{ QMI_SERVICE_WMS, "QMI_SERVICE_WMS", "wms" },
	{ QMI_SERVICE_PDS, "QMI_SERVICE_PDS", "pds" },
	{ QMI_SERVICE_AUTH, "QMI_SERVICE_AUTH", "auth" },
	{ QMI_SERVICE_AT, "QMI_SERVICE_AT", "at" },
	{ QMI_SERVICE_VOICE, "QMI_SERVICE_VOICE", "voice" },
	{ QMI_SERVICE_CAT2, "QMI_SERVICE_CAT2", "cat2" },
	{ QMI_SERVICE_UIM, "QMI_SERVICE_UIM", "uim" },
	{ QMI_SERVICE_PBM, "QMI_SERVICE_PBM", "pbm" },
	{ QMI_SERVICE_QCHAT, "QMI_SERVICE_QCHAT", "qchat" },
	{ QMI_SERVICE_RMTFS, "QMI_SERVICE_RMTFS", "rmtfs" },
	{ QMI_SERVICE_TEST, "QMI_SERVICE_TEST", "test" },
	{ QMI_SERVICE_LOC, "QMI_SERVICE_LOC", "loc" },
	{ QMI_SERVICE_SAR, "QMI_SERVICE_SAR", "sar" },
	{ QMI_SERVICE_IMS, "QMI_SERVICE_IMS", "ims" },
	{ QMI_SERVICE_ADC, "QMI_SERVICE_ADC", "adc" },
	{ QMI_SERVICE_CSD, "QMI_SERVICE_CSD", "csd" },
	{ QMI_SERVICE_MFS, "QMI_SERVICE_MFS", "mfs" },
	{ QMI_SERVICE_TIME, "QMI_SERVICE_TIME", "time" },
	{ QMI_SERVICE_TS, "QMI_SERVICE_TS", "ts" },
	{ QMI_SERVICE_TMD, "QMI_SERVICE_TMD", "tmd" },
	{ QMI_SERVICE_SAP, "QMI_SERVICE_SAP", "sap" },
	{ QMI_SERVICE_WDA, "QMI_SERVICE_WDA", "wda" },
	{ QMI_SERVICE_TSYNC, "QMI_SERVICE_TSYNC", "tsync" },
	{ QMI_SERVICE_RFSA, "QMI_SERVICE_RFSA", "rfsa" },
	{ QMI_SERVICE_CSVT, "QMI_SERVICE_CSVT", "csvt" },
	{ QMI_SERVICE_QCMAP, "QMI_SERVICE_QCMAP", "qcmap" },
	{ QMI_SERVICE_IMSP, "QMI_SERVICE_IMSP", "imsp" },
	{ QMI_SERVICE_IMSVT, "QMI_SERVICE_IMSVT", "imsvt" },
	{ QMI_SERVICE_IMSA, "QMI_SERVICE_IMSA", "imsa" },
	{ QMI_SERVICE_COEX, "QMI_SERVICE_COEX", "coex" },
	{ QMI_SERVICE_PDC, "QMI_SERVICE_PDC", "pdc" },
	{ QMI_SERVICE_STX, "QMI_SERVICE_STX", "stx" },
	{ QMI_SERVICE_BIT, "QMI_SERVICE_BIT", "bit" },
	{ QMI_SERVICE_IMSRTP, "QMI_SERVICE_IMSRTP", "imsrtp" },
	{ QMI_SERVICE_RFRPE, "QMI_SERVICE_RFRPE", "rfrpe" },
	{ QMI_SERVICE_DSD, "QMI_SERVICE_DSD", "dsd" },
	{ QMI_SERVICE_SSCTL, "QMI_SERVICE_SSCTL", "ssctl" },
	{ QMI_SERVICE_DPM, "QMI_SERVICE_DPM", "dpm" },
	{ QMI_SERVICE_CAT, "QMI_SERVICE_CAT", "cat" },
	{ QMI_SERVICE_RMS, "QMI_SERVICE_RMS", "rms" },
	{ QMI_SERVICE_OMA, "QMI_SERVICE_OMA", "oma" },
	{ QMI_SERVICE_FOTA, "QMI_SERVICE_FOTA", "fota" },
	{ QMI_SERVICE_GMS, "QMI_SERVICE_GMS", "gms" },
	{ QMI_SERVICE_GAS, "QMI_SERVICE_GAS", "gas" },
	{ 0, NULL, NULL }
};

#include <errno.h>
#include <linux/qrtr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include <arpa/inet.h>

#include "libqrtr.h"

#include "q_log.h"
#include "util.h"
#include "list.h"
#include "libqril.h"
#include "libqril_services.h"

#include "libqril_private.h"

static pthread_mutex_t services_mutex = PTHREAD_MUTEX_INITIALIZER;
static struct list_head services = LIST_INIT(services);

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

struct qmi_service_info *_qmi_service_get(enum qmi_service type)
{
	struct qmi_service_info *service, *out = NULL;
	list_for_each_entry(service, &services, li) {
		if (service->type == type) {
			out = service;
			break;
		};
	}
	return out;
}

/***** Internal API *****/

void qmi_service_get_port(enum qmi_service type)
{
	struct qmi_service_info *service = qmi_service_get(type);
	if (service)
		return service->port;
	return -ENOENT;
}

void qmi_service_new(struct qrtr_packet *pkt)
{
	struct qmi_service_info *service = zalloc(sizeof(struct qmi_service_info));

	service->type = pkt->service;
	service->node = pkt->node;
	service->port = pkt->port;
	service->major = pkt->instance & 0xff;
	service->minor = pkt->instance >> 8;
	service->name = qmi_service_get_name(service->type);

	log_debug("Found service: %s", service->name);
	q_thread_mutex_lock(&services_mutex);
	list_append(&services, &service->li);
	q_thread_mutex_unlock(&services_mutex);
}

void qmi_service_goodbye(enum qmi_service type)
{
	struct qmi_service_info *service;

	q_thread_mutex_lock(&services_mutex);

	service = qmi_service_get(type);
	if (!service)
		return;

	log_debug("Service shutdown: %s", service->name);
	list_remove(&service->li);
	q_thread_mutex_unlock(&services_mutex);
	free(service);
}

const char *qmi_service_get_name(enum qmi_service service)
{
	const struct enum_value *v = &qmi_service_values[0];
	while (v->value_str) {
		if (v->value == service)
			return v->value_str;
		v++;
	}

	return "<UNKNOWN>";
}

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

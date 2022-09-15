#ifndef __LIBQRIL_SERVICES_H__
#define __LIBQRIL_SERVICES_H__

#include "libqrtr.h"

#include "libqril_qmi.h"
#include "list.h"

struct qmi_service_info *qmi_service_get(enum qmi_service type);
void qmi_service_new(struct qrtr_packet *pkt);
void qmi_service_goodbye(enum qmi_service type);

const char *qmi_service_get_name(enum qmi_service service);

#endif
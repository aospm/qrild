#ifndef __LIBQRIL_SERVICES_H__
#define __LIBQRIL_SERVICES_H__

#include "libqrtr.h"

#include "libqril_qmi.h"
#include "list.h"

/**
 * @brief init services local state. Must be called
 * before \a messages_init()
 */
void services_init();

/**
 * @brief get the port and node for a QMI service
 * 
 * @type: The QMI service to get
 * @port: Port result
 * @node: Node result
 * 
 * @returns 0 if the service is online, -ENOENT otherwise
 */
int qmi_service_get(enum qmi_service type, int *port, int *node);

/**
 * @brief get the port for an online QMI service
 * 
 * @type: The QMI service to lookup (e.g. QMI_SERVICE_UIM)
 * 
 * @returns positive port on success, -ENOENT otherwise
 */
int qmi_service_get_port(enum qmi_service type);

/**
 * @brief get the node providing a QMI service
 * 
 * @type: The QMI service to lookup
 * 
 * @returns the node (e.g. 0 is modem) or -ENOENT
 * if the service is unavailable
 */
int qmi_service_get_node(enum qmi_service type);

/**
 * @brief get a service by port
 * 
 * @port: The port the service is on
 * @type: Service type to return
 * 
 * @returns 0 on success, -ENOENT if the service is offline
 */
int qmi_service_from_port(uint16_t port, enum qmi_service *type);

/**
 * @brief register a new service, called from message thread
 * 
 * @pkt: A qrtr_packet of type QRTR_TYPE_NEW_SERVER
 */
void qmi_service_new(struct qrtr_packet *pkt);

/**
 * @brief notify of a service going offline, called from message thread
 * 
 * @pkt: A qrtr_packet of type QRTR_TYPE_DEL_SERVER
 */
void qmi_service_goodbye(enum qmi_service type);

#endif
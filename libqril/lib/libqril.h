#ifndef __LIBQRIL_LIB_H__
#define __LIBQRIL_LIB_H__

#include "libqrtr.h"

#include "q_log.h"
#include "libqril_qmi.h"
#include "list.h"

__BEGIN_DECLS

enum modem_state {
	STATE_UNKNOWN = 0,
	STATE_OFFLINE,
	STATE_ERROR,
	STATE_AVAILABLE,
};

struct libqril_modem_info {
	char revision[1024];
	char esn[256];
	char imei[256];
	char meid[256];
	char imei_ver[256];
};

enum libqril_event_type {
	EV_MODEM_STATE_CHANGE = 0,
	EV_QMI_INDICATION,
	EV_SERVICE_NEW,
	EV_SERVICE_GOODBYE,
};

/**
 * @brief event callbacks the client can register to receive.
 * It is assumed that handler functions don't do extensive processing
 * These are called from a workqueue context
 */
struct libqril_events {
	/**
	 * @brief called when the modem state changes
	 * @data: client data
	 * @newstate: The new modem state
	 */
	void (*on_modem_state_change)(void *data, enum modem_state newstate);
	/**
	 * @brief called when a QMI indication is received from the modem
	 * @data: client data
	 * @indication: The QMI indication message, this can be decoded by calling
	 * qmi_decode_message2() with the appropriate message struct.
	 */
	void (*on_qmi_indication)(void *data, struct qmi_header *indication, size_t len);
	/**
	 * @brief: called when a new QMI service appears on QRTR
	 * @data: client data
	 * @service: The service which is now available
	 */
	void (*on_service_new)(void *data, enum qmi_service service);
	/**
	 * @brief: called when a QMI service closes on QRTR
	 * @data: client data
	 * @service: The service which is no longer available
	 */
	void (*on_service_goodbye)(void *data, enum qmi_service service);
};

/*
 * All functions return 0 on success, positive QMI_ERR
 * or < 0 on error
 */

/* Init messaging threads and register to modem */
void libqril_init();

/* Returns the current modem state */
enum modem_state libqril_modem_state();

/**
 * @brief: bring the modem online
 * 
 * Returns: 0 on success,
 * -EINVAL if the modem state isn't STATE_OFFLINE
 */
int libqril_modem_activate();

/**
 * @brief register event handlers
 *
 * @handlers: handlers to register
 * @data: context to pass to callback functions
 * 
 * @returns 0 on sucess, or -err
 */
int libqril_register_event_handlers(struct libqril_events *handlers, void *data);

/**
 * @brief get the unique ID for this handlers struct
 * irrelevant of if it has been registered.
 */
unsigned long libqril_event_handlers_get_id(struct libqril_events *handlers);

/**
 * @brief unregister event handlers
 * @hid: The ID of the handlers to unregister
 * get with libqril_event_handlers_get_id()
 * 
 * @returns 0 on success, -ENOENT if no handlers can be found for this ID
 */
int libqril_unregister_event_handlers(unsigned long hid);

#define libqril_unregister_event_handlers_by_struct(handlers)                                      \
	libqril_unregister_event_handlers(libqril_event_handlers_get_id(handlers))

/**
 * @brief block until the given QMI service is available.
 * returns immediately if the service is already online.
 */
void libqril_wait_for_qmi_service(enum qmi_service service);

typedef void (*qmi_message_handler_t)(struct qmi_message_header *);

/**
 * @brief Send a message synchronously and populate resp with the response
 * 
 * @msg: The header for the message to send
 * @resp: The response message
 * 
 * @returns 0 on success, positive QMI_ERR or negative err on failure
 */
int libqril_send_message_sync(struct qmi_message_header *msg, struct qmi_message_header *resp);

/**
 * @brief send a message and call cb asynchronously with the response.
 * Returns immediately.
 * 
 * @msg: The message to send
 * @resp: The message response struct
 * @cb: Callback function to process response
 * 
 * @returns 0 on success, negative err on failure
 */
int libqril_send_message_async(struct qmi_message_header *msg, struct qmi_message_header *resp,
	qmi_message_handler_t *cb);

/* This doesn't turn the modem on/off, but sets how it may operate */
int libqril_dms_get_operating_mode(enum QmiDmsOperatingMode *mode);
int libqril_dms_set_operating_mode(enum QmiDmsOperatingMode mode);

// FIXME: support more than 1 IMEI
/* Get info like the modem revision, IMEI, MEID and ESN */
int libqril_get_modem_info(struct libqril_modem_info *info);

int libqril_provision(char *application_id);

__END_DECLS

#endif

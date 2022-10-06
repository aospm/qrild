#ifndef __LIBQRIL_LIB_H__
#define __LIBQRIL_LIB_H__

#include "libqrtr.h"

#include "q_log.h"
#include "libqril_qmi.h"
#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

#define zalloc(size) calloc(1, (size))

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

	_EV_TYPE_MAX,
#define EV_TYPE_MAX (_EV_TYPE_MAX - 1)
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
	 * 
	 * NOTE: currently unused
	 */
	void (*on_modem_state_change)(void *data, enum modem_state newstate);
	/**
	 * @brief called when a QMI indication is received from the modem
	 * @service: The QMI service that sent the indication
	 * @data: client data
	 * @ind: The QMI indication message, this can be decoded by calling
	 * qmi_decode_message2() with the appropriate message struct.
	 * @len: The length of the QMI message in bytes.
	 * 
	 * See examples/network_indications.c for example usage
	 */
	void (*on_qmi_indication)(void *data, enum qmi_service service, struct qmi_header *ind,
				  size_t len);
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
 * get with \a libqril_event_handlers_get_id()
 * 
 * @returns 0 on success, -ENOENT if no handlers can be found for this ID
 */
int libqril_event_handlers_unregister(unsigned long hid);

#define libqril_event_handlers_unregister_by_struct(handlers)                                      \
	libqril_event_handlers_unregister(libqril_event_handlers_get_id(handlers))

/**
 * @brief wait until all available services are discovered
 */
void libqril_wait_for_service_discovery();

/**
 * @brief check if a QMI service is online
 * 
 * @service: The service to check
 * 
 * @returns 0 if the service is online, -ENOENT otherwise
 */
int libqril_qmi_service_online(enum qmi_service service);

typedef void (*qmi_message_handler_t)(void *data, struct qmi_message_header *msg);

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
 * @cb_data: Context to pass to the callback
 * @cb: Callback function to process response
 * 
 * @returns 0 on success, negative err on failure
 */
int libqril_send_message_async(struct qmi_message_header *msg, struct qmi_message_header *resp,
			       void *cb_data, qmi_message_handler_t cb);

/**
 * @brief send a "basic" QMI request message which doesn't contain a body
 * blocks until the response is received
 *
 * @service: The service to send the request to
 * @message_id: The ID of the message
 * @resp: Pointer to the response to populate
 */
int libqril_send_basic_request_sync(enum qmi_service service, uint16_t message_id,
				    struct qmi_message_header *resp);

/**
 * @brief send a basic request message and call cb asynchronously
 * with the response. Returns immediately.
 * 
 * @msg: The message to send
 * @resp: The message response struct
 * @cb_data: Context to pass to the callback
 * @cb: Callback function to process response
 * 
 * @returns 0 on success, negative err on failure
 */
int libqril_send_basic_request_async(enum qmi_service service, uint16_t message_id,
				     struct qmi_message_header *resp, void *cb_data,
				     qmi_message_handler_t cb);

/**
 * @brief send a QMI request message where the response
 * only contains the QMI result TLV ("ack")
 *
 * @service: The service to send the request to
 * @message_id: The ID of the message
 * @req: Pointer to the request message
 * 
 * @returns non-negative QMI_ERROR or negative errno
 */
int libqril_send_message_ack_sync(struct qmi_message_header *req);

/**
 * @brief send a message and call cb asynchronously
 * with the response TLV ("ack"). Returns immediately.
 * 
 * 
 * @msg: The message to send
 * @req: The request message struct
 * @cb_data: Context to pass to the callback
 * @cb: Callback function to process response
 * Use \a libqril_async_ack_get_error to get the QMI error
 * for the response
 * 
 * @returns 0 on success, negative err on failure
 * 
 * NOTE: untested
 */
int libqril_send_message_ack_async(struct qmi_message_header *req, void *cb_data,
				     qmi_message_handler_t cb);

/**
 * @brief send a basic QMI message and validate the basic response.
 * 
 * @service: The QMI service to send the message to
 * @message_id: The ID of the QMI message
 * 
 * @returns: non-negative QMI error or negative errno
 */
int libqril_send_message_basic_ack_sync(enum qmi_service service, uint16_t message_id);

/**
 * @brief: Get the QMI error for the response message @msg
 * only valid in the context of a callback handler for
 * \a libqril_send_message_ack_async
 * 
 * @msg: The QMI response message
 */
int libqril_async_ack_get_error(struct qmi_message_header *msg);

/**
 * @brief get the name of a QMI error
 * 
 * @err: The QMI error (enum qmi_error)
 * 
 * @returns the error string
 */
const char *libqril_qmi_error_string(int err);

/**
 * @brief return the QMI error string or C strerror
 * 
 * @err: either positive QMI error or negative errno
 * 
 * @returns: error string
 */
const char *libqril_strerror(int err);

/**
 * @brief get the name of a QMI service
 * 
 * @service: The service type to get the name of
 * 
 * @returns The service name
 */
const char *libqril_qmi_service_name(enum qmi_service service);

/**
 * @brief utility function to convert between raw bytes and ascii HEX
 */
uint8_t *bytes_from_hex_str(const char *str, size_t *out_len);
char *bytes_to_hex_string(uint8_t *bytes, size_t len);

/* This doesn't turn the modem on/off, but sets how it may operate */
int libqril_dms_get_operating_mode(enum QmiDmsOperatingMode *mode);
int libqril_dms_set_operating_mode(enum QmiDmsOperatingMode mode);

// FIXME: support more than 1 IMEI
/* Get info like the modem revision, IMEI, MEID and ESN */
int libqril_get_modem_info(struct libqril_modem_info *info);

int libqril_provision(char *application_id);

#ifdef __cplusplus
}
#endif

#endif

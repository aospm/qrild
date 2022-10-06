#ifndef __LIBQRIL_EVENTS_H__
#define __LIBQRIL_EVENTS_H__

#include "libqril_messages.h"

/**
 * @brief notify clients of a change in the modem state
 * 
 * @newstate: The new modem state
 */
void event_new_modem_state_change(enum modem_state newstate);

/**
 * @brief notify clients of a pending QMI indication from the modem
 * 
 * @service: The QMI service the message is for
 * @ind: The QMI indication message
 * @lt: The lifetime associated with the message, handed back to \a messages_free_ind_cb
 */
void event_new_indication(enum qmi_service service, struct qmi_header *ind,
        struct message_lifetime *lt);

/**
 * @brief notify clients of a new QMI service being discovered
 * 
 * @service: the new QMI service
 */
void event_service_new(enum qmi_service service);

/**
 * @brief Notify clients of a service shutting down
 * 
 * @service: The service which has shut down
 */
void event_service_goodbye(enum qmi_service service);

#endif
#ifndef __LIBQRIL_EVENTS_H__
#define __LIBQRIL_EVENTS_H__

/**
 * @brief notify clients of a change in the modem state
 * 
 * @newstate: The new modem state
 */
void event_new_modem_state_change(enum modem_state newstate);

/**
 * @brief notify clients of a pending QMI indication from the modem
 * 
 * @ind: The QMI indication message
 */
void event_new_indication(struct qmi_message_header *ind);

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
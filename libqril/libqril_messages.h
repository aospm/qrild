#ifndef __LIBQRIL_MESSAGES_H__
#define __LIBQRIL_MESSAGES_H__

#include <libqrtr.h>

void messages_init();
void messages_dump_pending();

struct message_lifetime;

// Used by libqril_events to free the lifetime associated with a qmi indication
// once all handlers have been called.
void messages_free_lifetime(struct message_lifetime *lt);

// Declared in libqril.h
//int libqril_send_message_sync(struct qmi_message_header *msg,
//			      struct qmi_message_header *resp)

#endif // __LIBQRIL_MESSAGES_H__
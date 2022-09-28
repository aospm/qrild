#ifndef __LIBQRIL_MESSAGES_H__
#define __LIBQRIL_MESSAGES_H__

void messages_init();
void messages_dump_pending();

// Declared in libqril.h
//int libqril_send_message_sync(struct qmi_message_header *msg,
//			      struct qmi_message_header *resp)

#endif // __LIBQRIL_MESSAGES_H__
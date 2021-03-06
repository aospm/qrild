#ifndef __QRILD_MSG_H__
#define __QRILD_MSG_H__

#include <stdbool.h>

#include "qrild.h"
#include "libqrtr.h"

#define TIMEOUT_DEFAULT 5000

__BEGIN_DECLS

void print_service(struct qmi_service_info *pkt);

uint16_t qrild_next_transaction_id();

int qrild_qrtr_send_queued(struct rild_state *state);
int qrild_qrtr_send_to_service(struct rild_state *state,
			       enum qmi_service svc_id, const void *data,
			       size_t sz, bool sync, int timeout_ms);
int qrild_msg_send_sync(struct rild_state *state, enum qmi_service svc_id,
			void *data, size_t sz, int timeout_ms,
			struct qrild_msg **resp);
int qrild_msg_send_async(struct rild_state *state,
				enum qmi_service svc_id, void *data, size_t sz);
int qrild_msg_send_resp_check(struct rild_state *state,
				     enum qmi_service svc_id, void *data,
				     size_t sz, int timeout_ms, struct qmi_response_type_v01 *res);
int qrild_qmi_send_basic_request_sync(struct rild_state *state, enum qmi_service svc_id, uint32_t msg_id, struct qrild_msg **resp);
int qrild_qmi_send_basic_request_async(struct rild_state *state, enum qmi_service svc_id, uint32_t msg_id);

bool qrild_qrtr_do_lookup(struct rild_state *state);
void qrild_qrtr_recv(struct rild_state *state);

struct qmi_response_type_v01 *qrild_qmi_get_result(struct qmi_tlv *tlv);
void qrild_qmi_result_print(struct qmi_response_type_v01 *res);

struct qrild_msg *qrild_msg_new(uint16_t txn, uint32_t msg_id,
	pthread_mutex_t *shared_mutex);
void qrild_msg_free(struct qrild_msg *msg);
void qrild_msg_free_locked(struct qrild_msg *msg);

struct qmi_service_info *qmi_service_get(struct list_head *list,
					 enum qmi_service svc);

struct qmi_service_info *qmi_service_from_port(struct list_head *list,
					 uint16_t port);

__END_DECLS

#endif

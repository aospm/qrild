#ifndef __QRILD_QRTR__
#define __QRILD_QRTR__

#include "qrild.h"
#include "qmi_tlv.h"
#include <stdbool.h>

#define TIMEOUT_DEFAULT 500

void print_service(struct qmi_service_info *pkt);

int qrild_qrtr_send_to_service(struct rild_state *state,
			       enum qmi_service svc_id, const void *data,
			       size_t sz, bool sync, int timeout_ms);
int qrild_msg_send_sync(struct rild_state *state, enum qmi_service svc_id,
			void *data, size_t sz, int timeout_ms,
			struct qrild_msg *resp);
inline int qrild_msg_send_async(struct rild_state *state,
				enum qmi_service svc_id, void *data, size_t sz);

inline int qrild_qmi_send_basic_request_sync(struct rild_state *state, enum qmi_service svc_id, uint32_t msg_id, struct qrild_msg *resp);
inline int qrild_qmi_send_basic_request_async(struct rild_state *state, enum qmi_service svc_id, uint32_t msg_id);

bool qrild_qrtr_do_lookup(struct rild_state *state);
void qrild_qrtr_recv(struct rild_state *state);

inline struct qmi_result *qrild_qmi_get_result(struct qmi_tlv *tlv);
inline void qrild_qmi_result_print(struct qmi_result *res);

struct qrild_msg *qrild_msg_new(uint16_t txn, uint32_t msg_id,
	pthread_mutex_t *shared_mutex);
void qrild_msg_free(struct qrild_msg *msg);

struct qmi_service_info *qmi_service_get(struct list_head *list,
					 enum qmi_service svc);

#endif

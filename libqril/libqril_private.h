#ifndef __LIBQRIL_PRIVATE_H__
#define __LIBQRIL_PRIVATE_H__

#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>

#include "libqril.h"
#include "libqril_events.h"
#include "libqril_services.h"
#include "libqril_messages.h"

#include "list.h"
#include "qmi_uim.h"

__BEGIN_DECLS

#define NUMARGS(...) (sizeof((int[]){ __VA_ARGS__ }) / sizeof(int))

struct enum_value {
	int value;
	const char *value_str;
	const char *name;
};

extern const struct enum_value qmi_error_names[];

struct rild_state;

struct libqril_state {
	enum modem_state modem_state;
	volatile bool exit;

	struct list_head pending_rx;
	struct list_head pending_tx;
	pthread_mutex_t msg_mutex;
	pthread_cond_t msg_change;
	// Broadcast when there are new pending QMI indications
	pthread_cond_t pending_indications;

	/* Mobile data connection */
	uint8_t connection_status;
	pthread_mutex_t connection_status_mutex;
	pthread_cond_t connection_status_change;

	uint32_t wds_pkt_data_handle;

	// Available QMI services
	struct list_head services;
	pthread_mutex_t services_mutex;
};



#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

/* Uncomment to enable mutex debugging */
//#define LOCKTRACKER 1

int _q_thread_mutex_lock(pthread_mutex_t* m, const char *mtex, const char *file, const char* func, int line);
int _q_thread_mutex_unlock(pthread_mutex_t* m, const char *mtex, const char *file, const char* func, int line);

int _q_thread_cond_timedwait(pthread_cond_t* c, pthread_mutex_t* m, struct timespec *ts, const char *mtex, const char *file, const char* func, int line);

int _q_thread_cond_wait(pthread_cond_t* c, pthread_mutex_t* m, const char *mtex, const char *file, const char* func, int line);

#ifdef LOCKTRACKER
#define q_thread_dump_locks() _q_thread_dump_locks()

#define q_thread_mutex_lock(m) \
	_q_thread_mutex_lock(m, #m, __FILENAME__, __FUNCTION__, __LINE__)

#define q_thread_mutex_unlock(m) \
	_q_thread_mutex_unlock(m, #m, __FILENAME__, __FUNCTION__, __LINE__)

#define q_thread_cond_timedwait(c, m, t) \
	_q_thread_cond_timedwait(c, m, t, #m, __FILENAME__, __FUNCTION__, __LINE__)

#define q_thread_cond_wait(c, m) \
	_q_thread_cond_wait(c, m, #m, __FILENAME__, __FUNCTION__, __LINE__)
#else
#define q_thread_dump_locks() do {} while(0)

#define q_thread_mutex_lock(m) pthread_mutex_lock(m)

#define q_thread_mutex_unlock(m) pthread_mutex_unlock(m)

#define q_thread_cond_timedwait(c, m, t) pthread_cond_timedwait(c, m, t)

#define q_thread_cond_wait(c, m) pthread_cond_wait(c, m)
#endif


/**
 * @brief block until the condition is true, assumes the condition was set up
 * like connection_status is above.
 * 
 * @obj: the object the condition is waiting on
 * @cond: the condition to wait on
 */
#define THREAD_WAIT(obj, cond)                                                 \
	({                                                                     \
		int rc;                                                        \
		struct timespec ts = { 0, 5000000 };                           \
		pthread_mutex_lock(&(obj)->cond##_mutex);                      \
		while (!(obj)->cond) {                                         \
			rc = pthread_cond_timedwait(&(obj)->cond##_change,     \
						    &(obj)->cond##_mutex,      \
						    &ts);                      \
		}                                                              \
		pthread_mutex_unlock(&(obj)->cond##_mutex);                    \
		rc;                                                            \
	})

/**
 * @brief Return if a service hasn't been discovered yet
 *
 * @_l: service list to search
 * @_s: enum qmi_service to find
 * @_r: return value to use if the service can't be found
 */
#define QMI_SERVICE_OR_RETURN(_l, _s, _r)                                      \
	if (!qmi_service_get((_l), _s))                                        \
	return _r

static inline struct libqril_message_lifetime *qmi_msg_get_by_txn(struct list_head *list, uint16_t txn)
{
	struct libqril_message_lifetime *msg;
	list_for_each_entry(msg, list, li) {
		if (msg->txn == txn)
			return msg;
	}
	return NULL;
}

__END_DECLS

#endif

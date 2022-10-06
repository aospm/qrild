#ifndef __LOCK_TRACKER_H__
#define __LOCK_TRACKER_H__

#include <pthread.h>

/* Uncomment to enable mutex debugging */
//#define LOCKTRACKER 1

#ifdef LOCKTRACKER

#ifndef __FILENAME__
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

int _q_thread_mutex_lock(pthread_mutex_t *m, const char *mtex, const char *file, const char *func,
			 int line);
int _q_thread_mutex_unlock(pthread_mutex_t *m, const char *mtex, const char *file, const char *func,
			   int line);

int _q_thread_cond_timedwait(pthread_cond_t *c, pthread_mutex_t *m, struct timespec *ts,
			     const char *mtex, const char *file, const char *func, int line);

int _q_thread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m, const char *mtex, const char *file,
			const char *func, int line);

void _q_thread_dump_locks();

#define q_thread_dump_locks()	 _q_thread_dump_locks()

#define q_thread_mutex_lock(m)	 _q_thread_mutex_lock(m, #m, __FILENAME__, __FUNCTION__, __LINE__)

#define q_thread_mutex_unlock(m) _q_thread_mutex_unlock(m, #m, __FILENAME__, __FUNCTION__, __LINE__)

#define q_thread_cond_timedwait(c, m, t)                                                           \
	_q_thread_cond_timedwait(c, m, t, #m, __FILENAME__, __FUNCTION__, __LINE__)

#define q_thread_cond_wait(c, m) _q_thread_cond_wait(c, m, #m, __FILENAME__, __FUNCTION__, __LINE__)

#else

#define q_thread_dump_locks()                                                                      \
	do {                                                                                       \
	} while (0)

#define q_thread_mutex_lock(m)		 pthread_mutex_lock(m)

#define q_thread_mutex_unlock(m)	 pthread_mutex_unlock(m)

#define q_thread_cond_timedwait(c, m, t) pthread_cond_timedwait(c, m, t)

#define q_thread_cond_wait(c, m)	 pthread_cond_wait(c, m)

#endif

#endif

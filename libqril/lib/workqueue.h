#ifndef __Q_WORKQUEUE_H__
#define __Q_WORKQUEUE_H__

#include <stdbool.h>
#include <unistd.h>

__BEGIN_DECLS

#define Q_WORK_N_THREADS 6

struct q_work {
	void *data;
	void (*func)(void *);
};

int q_work_schedule_delayed(struct q_work *work, int delay_ms);
static inline int q_work_schedule_now(struct q_work *work)
{
	return q_work_schedule_delayed(work, 0);
}

int q_threads_exitall();


__END_DECLS

#endif // __Q_WORKQUEUE_H__

#ifndef __Q_WORKQUEUE_H__
#define __Q_WORKQUEUE_H__

#include <stdbool.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

struct q_work {
	void *data;
	void (*func)(void *);
};

int q_work_schedule_delayed(struct q_work *work, int delay_ms);
static inline int q_work_schedule_now(struct q_work *work)
{
	return q_work_schedule_delayed(work, 0);
}

#ifdef __cplusplus
}
#endif

#endif // __Q_WORKQUEUE_H__

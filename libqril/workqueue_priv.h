#ifndef __Q_WORKQUEUE_PRIV_H__
#define __Q_WORKQUEUE_PRIV_H__

#include <stdbool.h>
#include <unistd.h>
#include "workqueue.h"

__BEGIN_DECLS

#define Q_WORK_N_THREADS 4

/**
 * @brief: Set up the workqueue, must be called once
 * before work items can be queued
 */
void q_workqueue_init();

int q_threads_exitall();


__END_DECLS

#endif // __Q_WORKQUEUE_PRIV_H__

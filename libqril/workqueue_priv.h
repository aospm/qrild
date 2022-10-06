#ifndef __Q_WORKQUEUE_PRIV_H__
#define __Q_WORKQUEUE_PRIV_H__

#include <stdbool.h>
#include <unistd.h>
#include "workqueue.h"

#ifdef __cplusplus
extern "C" {
#endif

#define Q_WORK_N_THREADS 6

/**
 * @brief: Set up the workqueue, must be called once
 * before work items can be queued
 */
void q_workqueue_init();

void q_workqueue_dump();

int q_threads_exitall();

#ifdef __cplusplus
}
#endif

#endif // __Q_WORKQUEUE_PRIV_H__

/*
 * Copyright (C) 2022, Linaro Ltd.
 * Author: Caleb Connolly <caleb.connolly@linaro.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#include "timespec.h"
#include "list.h"
#include "q_log.h"
#include "util.h"
#include "workqueue_priv.h"

static struct list_head delayed_tasks = LIST_INIT(delayed_tasks);
static struct list_head workqueue = LIST_INIT(workqueue);
static pthread_cond_t new_task = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t wq_mtex = PTHREAD_MUTEX_INITIALIZER;
static pthread_t workthreads[Q_WORK_N_THREADS+1];
static bool q_exit = false;

struct q_work_task {
	struct list_head li;
	struct q_work *work;
	struct timespec scheduled;
	struct timespec due;
};

static void *q_worker_scheduler(void *data) {
	int rc;
	struct timespec ts, now, tick;
	struct q_work_task *task;
	struct list_head *li, *bkup;
	bool new_tasks;
	(void)data;

	log_trace("Work scheduler starting...");

	while (!q_exit) {
		ts = timespec_from_ms(50);
		new_tasks = false;

		pthread_mutex_lock(&wq_mtex);
		now = timespec_now();
		tick = timespec_add(now, ts);
		do {
			rc = pthread_cond_timedwait(&new_task, &wq_mtex, &tick);
		} while (rc && errno == EINTR);
		
		list_for_each_safe(&delayed_tasks, li, bkup) {
			task = list_entry(li, struct q_work_task, li);
			if (timespec_lt(now, task->due)) {
				continue;
			}

			//log_trace("WORK: Adding task to wq: %zu", (uintptr_t)task);
			list_remove(&task->li);
			list_push(&workqueue, &task->li);
			new_tasks = true;
		}
		if (new_tasks)
			pthread_cond_broadcast(&new_task);
		pthread_mutex_unlock(&wq_mtex);
	}

	return NULL;
}

static void q_worker_process_task(struct q_work_task *task)
{
	struct q_work *work = task->work;
	//log_trace("WORK: Processing task");

	if (work->func)
		(work->func)(work->data);

	free(task);
}

static void *q_worker_thread(void* data)
{
	struct q_work_task *task;
	struct list_head *li;
	(void)data;

	pthread_mutex_lock(&wq_mtex);
	while (!q_exit) {
		pthread_cond_wait(&new_task, &wq_mtex);
		while (!list_empty(&workqueue)) {
			li = list_pop(&workqueue);
			pthread_mutex_unlock(&wq_mtex);
			task = list_entry(li, struct q_work_task, li);
			//log_trace("WORK: new task recv (%zu)", (uintptr_t)task);
			q_worker_process_task(task);
			pthread_mutex_lock(&wq_mtex);
		}
	}
	pthread_mutex_unlock(&wq_mtex);
	return NULL;
}

void q_workqueue_init()
{
	int i;

	for(i = 0; i < Q_WORK_N_THREADS; i++) {
		pthread_create(&workthreads[i], NULL, q_worker_thread, NULL);
	}

	pthread_create(&workthreads[Q_WORK_N_THREADS], NULL, q_worker_scheduler, NULL);
}

void q_workqueue_dump()
{
	struct q_work_task *task;
	struct list_head *li, *bkup;

	pthread_mutex_lock(&wq_mtex);

	log_info("WORKQUEUE SCHEDULED TASKS:");
	list_for_each_safe(&delayed_tasks, li, bkup) {
		task = list_entry(li, struct q_work_task, li);
		log_info("\t%32s: scheduled %ums ago, delay: %ums",
			task->work->name ?: "UNNAMED",
			timespec_to_ms(timespec_sub(timespec_now(), task->scheduled)),
			timespec_to_ms(timespec_sub(task->due, task->scheduled)));
	}

	log_info("WORKQUEUE ACTIVE TASKS:");
	list_for_each_safe(&workqueue, li, bkup) {
		task = list_entry(li, struct q_work_task, li);
		log_info("\t%32s: scheduled %ums ago, delay: %ums",
			task->work->name ?: "UNNAMED",
			timespec_to_ms(timespec_sub(timespec_now(), task->scheduled)),
			timespec_to_ms(timespec_sub(task->due, task->scheduled)));
	}


	pthread_mutex_unlock(&wq_mtex);
}

int q_work_schedule_delayed(struct q_work *work, int delay_ms)
{
	struct q_work_task *task = zalloc(sizeof(struct q_work_task));

	task->scheduled = timespec_now();
	task->work = work;

	pthread_mutex_lock(&wq_mtex);
	task->due = timespec_add(task->scheduled, timespec_from_ms(delay_ms));
	//log_trace("WORK: scheduling delayed task to run in %dms (%zu)", delay_ms, (uintptr_t)task);
	list_push(&delayed_tasks, &task->li);
	if (delay_ms < 5)
		pthread_cond_broadcast(&new_task);
	pthread_mutex_unlock(&wq_mtex);

	return 0;
}

int q_threads_exitall() {
	int i;
	q_exit = true;
	for(i = 0; i < Q_WORK_N_THREADS; i++) {
		pthread_join(workthreads[i], NULL);
	}

	return 0;
}

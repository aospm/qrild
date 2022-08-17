
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#include "timespec.h"
#include "list.h"
#include "q_log.h"
#include "util.h"
#include "workqueue.h"

static struct list_head delayed_tasks = LIST_INIT(delayed_tasks);
static struct list_head workqueue = LIST_INIT(workqueue);
static pthread_cond_t new_task = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t wq_mtex = PTHREAD_MUTEX_INITIALIZER;
static pthread_t workthreads[Q_WORK_N_THREADS+1];
static bool q_exit = false;

struct q_work_task {
	struct list_head li;
	struct q_work *work;
	struct timespec when;
};

static void *q_worker_scheduler(void *data) {
	int rc;
	struct timespec ts, now;
	struct q_work_task *task;
	struct list_head *li, *bkup;
	bool new_tasks;
	(void)data;

	while (!q_exit) {
		ts = timespec_from_ms(50);
		new_tasks = false;

		do {
			rc = nanosleep(&ts, &ts);
		} while (rc && errno == EINTR);

		pthread_mutex_lock(&wq_mtex);
		time_now(&now);
		list_for_each_safe(&delayed_tasks, li, bkup) {
			task = list_entry(li, struct q_work_task, li);
			if (timespec_gt(now, task->when))
				continue;
			
			log_trace("WORK: Adding task to wq: %zu", (uintptr_t)task);
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
	log_trace("WORK: Processing task");

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
		log_trace("WORK: new task recv!");
		while (!list_empty(&workqueue)) {
			li = list_pop(&workqueue);
			pthread_mutex_unlock(&wq_mtex);
			task = list_entry(li, struct q_work_task, li);
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

int q_work_schedule_delayed(struct q_work *work, int delay_ms)
{
	struct q_work_task *task = zalloc(sizeof(struct q_work_task));

	time_now(&task->when);
	task->work = work;

	pthread_mutex_lock(&wq_mtex);
	task->when = timespec_add(task->when, timespec_from_ms(delay_ms));
	log_info("WORK: scheduling delayed task to run in %dms", delay_ms);
	list_push(&delayed_tasks, &task->li);
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

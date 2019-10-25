#ifndef __TM_H__
#define __TM_H__
#include <stddef.h> /* size_t */

#include "uid.h" /* ilrd_uid_t */
#include "sched.h" /* sched_t */
#include "pq.h" /* pq_t */

typedef int (*task_cmp_func_t)(void*, void*);

typedef struct
{
	ilrd_uid_t handle_id;
	time_t execute_time; 	/* last time the function ran */
	size_t interval; 			/* defines how often a task will run */
	void *data;
	operation_func_t func; 	/* function pointer to the task */
} sched_task_t;

sched_task_t *TaskCreate(operation_func_t func, size_t interval_in_seconds, void *param);

sched_task_t *
TaskInit(sched_task_t *new_task, operation_func_t func, size_t interval_in_seconds, void *param);

sched_task_t *TaskGetCurrent(pq_t *q);

int TaskExecute(sched_task_t *task);

int TaskCmp(void *task_id, void *task);

void TaskDestroy(sched_task_t *task);

   #endif /* __TM_H__ */

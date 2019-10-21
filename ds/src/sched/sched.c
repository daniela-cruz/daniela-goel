#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

/* for sleep() portability: */
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "uid.h" /* ilrd_uid_t */
#include "pq.h" /* the below functions are priority queue based */
#include "sched.h" /* types and all functions below */

typedef enum sched_status_t {READY, WAITING, INACTIVE}; /*?*/

struct scheduler
{
    pq_t *queue; /* priority queue */
};

typedef struct
{
	ilrd_uid_t handle_id;
	time_t act_time; 				/* last time the function ran */
	size_t interval; 				/* defines how often a task will run */
	void *data;
	operation_func_t func; 	/* function pointer to the task */
} sched_task_t;

int SortingOperation(void *uid1, void *uid2, void *param);
sched_task_t *CreateTask(operation_func_t func, size_t interval_in_seconds, void *param);

sched_t *SchedCreate()
{
	sched_t *schedule = malloc(sizeof(*schedule));
	if (NULL == schedule)
	{
		return NULL;
	}
	
	schedule->queue = PQCreate((pq_is_before_t)SortingOperation, NULL);
	if (NULL == schedule->queue)
	{
		free(schedule);
		return NULL;
	}
	
	return schedule;
}

ilrd_uid_t 
SchedAddTask(sched_t *scheduler, operation_func_t func, size_t interval_in_seconds, void *param)
{
	sched_task_t *new_task = CreateTask(func, interval_in_seconds, param);
	ilrd_uid_t task_id = UIDCreate();
	
	assert(NULL != scheduler);
	if (NULL == new_task)
	{
		task_id.is_error = 1;
		return task_id;
	}

	new_task->handle_id = task_id;
	PQEnqueue(scheduler->queue, new_task);
	
	return task_id;
}

void SchedRemoveTask(sched_t *scheduler, ilrd_uid_t task)
{
	PQErase(scheduler->queue, (pq_is_match_t)SortingOperation, (void*)&task);
}

void SchedStop(sched_t *scheduler)
{
	sched_task_t *current_task = NULL;
	int no_sleep = 0;
	
	assert(NULL != scheduler);
	current_task = PQPeek(scheduler->queue);
	(no_sleep < *(int*)current_task->data) ? sleep(current_task->interval) : sleep(no_sleep);
	
	((sched_task_t *)PQPeek(scheduler->queue))->data = (void *)&no_sleep;
}

void SchedRun(sched_t *schedule)
{
	time_t curr_time = time(NULL);
	sched_task_t *curr_task = NULL;
	
	assert(NULL != schedule);
	
	while (SchedDestroy(schedule) != PQPeek(schedule->queue)->func(schedule))
	{
		for (; !PQIsEmpty(schedule->queue); PQDequeue(schedule->queue))
		{
			curr_time = time(NULL);
			curr_task = PQPeek(schedule->queue);
			
			if (curr_time >= (curr_task->act_time + curr_task->interval))
			{
				curr_task->func(curr_task->data);
				curr_task->act_time = curr_time;
				curr_task->data = curr_task->interval;
			}
			
			PQEnqueue(schedule->queue, curr_task);
		}
	}
	
	SchedDestroy(schedule);
}

void SchedDestroy(sched_t *scheduler)
{
	PQDestroy(scheduler->queue);
	free(scheduler); scheduler = NULL;
}

/*********INTERNAL FUNCTIONS*********/
int SortingOperation(void *uid1, void *uid2, void *param)
{
	int is_before = 0;
	
	(void)param;
	if (((time_t)((ilrd_uid_t)uid1).curr_time <= (time_t)((ilrd_uid_t)uid2).curr_time) &&
		((ilrd_uid_t)uid1.pid <= (ilrd_uid_t)uid2.pid) &&
		((ilrd_uid_t)uid1.counter < (ilrd_uid_t)uid2.counter))
	{
		is_before = 1;
	}
	
	return is_before;
}

sched_task_t *CreateTask(operation_func_t func, size_t interval_in_seconds, void *param)
{
	sched_task_t *new_task = malloc(sizeof(*new_task));
	
	if (NULL == new_task)
	{
		return NULL;
	}
	
	new_task->interval = interval_in_seconds;
	new_task->data = param;
	new_task->func = func;
	new_task->act_time = interval_in_seconds;
	
	return new_task;
}
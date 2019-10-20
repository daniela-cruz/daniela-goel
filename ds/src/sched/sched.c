#include <stddef.h> /* size_t */

#include "sched.h" /* types and all functions below */
#include "uid.h" /* ilrd_uid_t */
#include "pq.h" /* the below functions are priority queue based */

struct scheduler
{
    pq_t *queue; /* priority queue */
};

typedef struct task
{
	ilrd_uid_t handle_id;
	time_t act_time;
	size_t interval;
	void *data;
	operation_func_t func;
} task_t;

sl_is_before_t SortingOperation(void *uid1, void *uid2, void *param);

sched_t *SchedCreate()
{
	sched_t *schedule = malloc(sizeof(*schedule));
	if (NULL == schedule)
	{
		return NULL;
	}
	
	schedule->queue = PQCreate(SortingOperation, NULL);
	if (NULL == schedule->queue)
	{
		free(schedule);
		return NULL;
	}
	
	return schedule;
}

ilrd_uid_t 
SchedAddTask(sched_t *scheduler, handle_func func, size_t interval_in_seconds, void *param)
{
	task_t *new_task = malloc(sizeof(*new_task));
	ilrd_uid_t task_id = UIDCreate();
	
	assert(NULL != scheduler);
	if (NULL == new_task)
	{
		task_id->is_error = 1;
		return task_id;
	}
	
	new_task->handle_id = task_id;
	new_task->iterval = interval_in_seconds;
	new_task->data = param;
	new_task->func = func;
	new_task->act_time = interval_in_seconds;
	
	PQEnqueue(scheduler.queue, new_task);
	
	return task_id;
}

void SchedRemoveTask(sched_t *scheduler, const ilrd_uid_t *task);

void SchedStop(sched_t *scheduler);

void SchedRun(sched_t *schedule);

void SchedDestroy(sched_t *scheduler)
{
	PQDestroy(scheduler.queue);
	free(scheduler); scheduler = NULL;
}

/*********INTERNAL FUNCTIONS*********/
sl_is_before_t SortingOperation(void *uid1, void *uid2, void *param)
{
	(void)param;
	return 1 == UIDIsEqual((ilrd_uid_t *)uid1, (ilrd_uid_t *)uid2);
}

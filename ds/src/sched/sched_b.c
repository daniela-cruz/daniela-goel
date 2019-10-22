#include <stdlib.h> 			/* malloc, free */
#include <stddef.h> 		/* size_t */
#include <assert.h> 		/* assert */

/* for sleep() portability: */
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "sched.h" 			/* types and all functions below */
#include "uid.h" 				/* ilrd_uid_t */
#include "pq.h" 				/* the below functions are priority queue based */


struct scheduler
{
    pq_t *queue; 				/* priority queue */
	int should_i_sleep; 		/* zero when no need to call SchedStop and one when it's time to sleep*/
};

typedef struct
{
	ilrd_uid_t handle_id;
	time_t execute_time; 	/* last time the function ran */
	size_t interval; 			/* defines how often a task will run */
	void *data;
	operation_func_t func; 	/* function pointer to the task */
} sched_task_t;

static int CmpExeTime(void *task1, void *task2, void *param);
static sched_task_t *CreateTask(operation_func_t func, size_t interval_in_seconds, void *param);
static int IsSameUID(void *element_uid, void *task_uid);

sched_t *SchedCreate()
{
	sched_t *schedule = malloc(sizeof(*schedule));
	if (NULL == schedule)
	{
		return NULL;
	}
	
	schedule->queue = PQCreate((pq_is_before_t)CmpExeTime, "useless_param");
	if (NULL == schedule->queue)
	{
		free(schedule);
		return NULL;
	}
	
	schedule->should_i_sleep = 0;
	
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
	
	return new_task->handle_id;
}

void SchedRemoveTask(sched_t *scheduler, ilrd_uid_t *task_uid)
{
	PQErase(scheduler->queue, IsSameUID, task_uid);
}

void SchedStop(sched_t *scheduler)
{
	sched_task_t *current_task = NULL;
	int no_sleep = 0;
	
	assert(NULL != scheduler);
	current_task = PQPeek(scheduler->queue);
	(no_sleep < *(int*)current_task->data) ? sleep(current_task->interval) : sleep(no_sleep);
	
	*(int*)PQPeek(scheduler->queue) = no_sleep;
}

void SchedRun(sched_t *schedule)
{
	assert(NULL != schedule);
	
	while (0 == schedule->should_i_sleep)
	{
		time_t curr_time = time(NULL);
		sched_task_t *curr_task = PQPeek(schedule->queue);
		
		if (curr_time >= (curr_task->execute_time + curr_task->interval))
		{
			curr_task->func(curr_task->data);
			curr_task->execute_time = curr_time;
			*(size_t*)curr_task->data = curr_task->interval;
		}
		
		PQEnqueue(schedule->queue, curr_task);
	}
	
	SchedDestroy(schedule);
}

void SchedDestroy(sched_t *scheduler)
{
	PQDestroy(scheduler->queue);
	free(scheduler); scheduler = NULL;
}

/*********INTERNAL FUNCTIONS*********/
static int CmpExeTime(void *task1, void *task2, void *param)
{
	assert(NULL != task1);
	assert(NULL != task2);
	(void)param;
	
	return (int)((time_t)(((sched_task_t *)task1)->execute_time) - (time_t)(((sched_task_t *)task2)->execute_time));
}

static int IsSameUID(void *element_uid, void *task_uid)
{
	return UIDIsEqual(*(ilrd_uid_t*)element_uid, *(ilrd_uid_t*)task_uid);
}

static sched_task_t *CreateTask(operation_func_t func, size_t interval_in_seconds, void *param)
{
	ilrd_uid_t task_id = UIDCreate();
	sched_task_t *new_task = malloc(sizeof(*new_task));
	
	if (NULL == new_task)
	{
		return NULL;
	}
	
	if (UIDIsError(task_id))
	{
		free(new_task);
		return NULL;
	}
	
	new_task->handle_id = task_id;
	new_task->interval = interval_in_seconds;
	new_task->data = param;
	new_task->func = func;
	new_task->execute_time = interval_in_seconds;
	
	return new_task;
}

/***********************************
* 		DBUG FUNCTIONS 	*
***********************************/
 
 size_t PrintQueueSize(sched_t *scheduler)
{
	assert(NULL != scheduler);
	return PQCount(scheduler->queue);
}

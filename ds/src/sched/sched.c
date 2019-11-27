#include <stdlib.h> 			/* malloc, free */
#include <stddef.h> 			/* size_t */
#include <assert.h> 			/* assert */

/* for sleep() portability: */
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "sched.h" 				/* types and all functions below */
#include "uid.h" 						/* ilrd_uid_t */
#include "pq.h" 						/* the below functions are priority queue based */
#include "task_manager.h" 	/* sched_task_t */
#include "time_manager.h" 	/* TimeIsBefore, TimeDifference */

struct scheduler
{
    pq_t *queue; 				/* priority queue */
	int stop_me;
};

sched_t *SchedCreate()
{
	sched_t *new_scheduler = malloc(sizeof(*new_scheduler));
	
	if (NULL == new_scheduler)
	{
		return NULL;
	}
	
	new_scheduler->queue = PQCreate((pq_is_before_t)TimeIsBefore, NULL);
	if (NULL == new_scheduler->queue)
	{
		free(new_scheduler);
		return NULL;
	}
	
	new_scheduler->stop_me = 0;

	return new_scheduler;
}

ilrd_uid_t SchedAddTask(sched_t *scheduler, operation_func_t func, 
	size_t interval_in_seconds, void *param)
{
	sched_task_t *new_task = TaskCreate(func, interval_in_seconds, param);
	
	assert(NULL != scheduler);
	if (NULL == new_task)
	{
		return UIDError();
	}
	
	if (0 == PQEnqueue(scheduler->queue, new_task))
	{
		TaskDestroy(new_task);
		return UIDError();
	}
	
	scheduler->stop_me = 0;
	
	return new_task->handle_id;
}

void SchedRemoveTask(sched_t *scheduler, ilrd_uid_t *task_uid)
{
	assert(NULL != scheduler);
	if (1 != PQIsEmpty(scheduler->queue))
	{
		free(PQErase(scheduler->queue, (pq_is_match_t)TaskIsEqual, task_uid));
	}
}

void SchedStop(sched_t *scheduler)
{
	assert(NULL != scheduler);
	scheduler->stop_me = 1;
}

void SchedRun(sched_t *scheduler)
{
	assert(NULL != scheduler);
	
	for (; 1 != scheduler->stop_me;)
	{
		sched_task_t *curr_task = PQDequeue(scheduler->queue);
		int halt = TimeDifference(curr_task);
		
		if (0 >= halt)
		{
			halt = 0;
		}
		
		sleep(halt);
		if ((0 == TaskExecute(curr_task)) && (1 != scheduler->stop_me))
		{
			SchedAddTask(scheduler, curr_task->func, curr_task->interval, curr_task->data);
		}
		else
		{
			TaskDestroy(curr_task);
		}
	}
}

void SchedDestroy(sched_t *scheduler)
{
	assert(NULL != scheduler);
	
	for (; !PQIsEmpty(scheduler->queue); PQDequeue(scheduler->queue));
	
	PQDestroy(scheduler->queue);
	free(scheduler); scheduler = NULL;
}

/***********************************
* 		DBUG FUNCTIONS 	*
***********************************/
 
size_t PrintQueueSize(sched_t *scheduler)
{
	assert(NULL != scheduler);
	return PQCount(scheduler->queue);
}

size_t GetTaskInterval(sched_t *scheduler, ilrd_uid_t task_uid)
{
	sched_task_t *task = NULL;
	
	
	task = (sched_task_t *)PQPeek(scheduler->queue);
	return (size_t)(task->interval);
}

#include <stdio.h>
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
#include "task_manager.h" /* sched_task_t */

struct scheduler
{
    pq_t *queue; 				/* priority queue */
	int stop_me;
};

/***************TIME***********************/
int TimeIsBefore(void *task1, void *task2, void *param);
int TimeDifference(sched_task_t *task);
time_t TimeOfExe(sched_task_t *task);
void TimeExeUpdate(sched_task_t *task_running);
/*******************************************/

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

ilrd_uid_t 
SchedAddTask(sched_t *scheduler, operation_func_t func, size_t interval_in_seconds, void *param)
{
	sched_task_t *new_task = TaskCreate(func, interval_in_seconds, param);
	
	printf("task id is: %ld process id is: %d\n", new_task->handle_id.counter, new_task->handle_id.pid);
	
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
	
	printf("\nstop me value: %d\n", scheduler->stop_me);
	for (; 1 != scheduler->stop_me;)
	{
		int task_status = 0;
		sched_task_t *curr_task = PQDequeue(scheduler->queue);
		int halt = TimeDifference(curr_task);
		
		printf("Run current task - task id is: %ld process id is: %d\n", curr_task->handle_id.counter, curr_task->handle_id.pid);
		
		if (0 >= halt)
		{
			halt = 0;
		}
		
		printf("\nHalt is: %d\n", halt);
		
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
* 	INTERNAL FUNCTIONS 	*
***********************************/

/************TIME**********************/
void TimeExeUpdate(sched_task_t *task_running)
{
	assert(NULL != task_running);
	
	task_running->execute_time = time(NULL) + task_running->interval;
}

time_t TimeOfExe(sched_task_t *task)
{
	assert(NULL != task);
	
	return task->execute_time;
}

int TimeIsBefore(void *new_task, void *first_task, void *param)
{
	(void)param;
	
	return ((sched_task_t *)new_task)->execute_time < ((sched_task_t *)first_task)->execute_time;
}

int TimeDifference(sched_task_t *task)
{
	return (int)((int)task->execute_time - (int)time(NULL));
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

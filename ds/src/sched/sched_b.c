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
	int should_i_sleep; 		/* zero when no need to call SchedStop and one when it's time to sleep*/
	sched_task_t *task_running;
	int remove_me;
};

/*************TIME ******************/
int TimeCmp(void *task1, void *task2, void *param);
static void ForceSleep(time_t current_task_execution_time);
time_t TimeExeUpdate(sched_task_t *task_running);
time_t TimeOfExe(sched_task_t *task);

/**********IMPLEMENTATION************/
sched_t *SchedCreate()
{
	sched_t *schedule = malloc(sizeof(*schedule));
	if (NULL == schedule)
	{
		return NULL;
	}
	
	schedule->queue = PQCreate((pq_is_before_t)TimeCmp, "useless_param");
	if (NULL == schedule->queue)
	{
		free(schedule);
		return NULL;
	}
	
	schedule->should_i_sleep = 0;
	schedule->task_running = NULL;
	schedule->remove_me = 0;
	
	return schedule;
}

ilrd_uid_t 
SchedAddTask(sched_t *scheduler, operation_func_t func, size_t interval_in_seconds, void *param)
{
	sched_task_t *new_task = NULL;
	ilrd_uid_t task_id = UIDCreate();
	
	assert(NULL != scheduler);
	
	if (1 == UIDIsError(task_id))
	{
		return UIDError(task_id);
	}
	
	new_task = TaskCreate(func, interval_in_seconds, param);
	if ((NULL == new_task))
	{
		return UIDError(task_id);
	}
	
	new_task->handle_id = task_id;
	PQEnqueue(scheduler->queue, (sched_task_t *)new_task);
	
	return new_task->handle_id;
}

void SchedRemoveTask(sched_t *scheduler, ilrd_uid_t *task_uid)
{
	assert(NULL != scheduler);
	
	if ((NULL != scheduler->task_running) && 
		(UIDIsEqual(*task_uid, scheduler->task_running->handle_id)))
	{
		scheduler->remove_me = 1;
	}
	else
	{
		TaskDestroy(PQErase(scheduler->queue, (pq_is_match_t)TimeCmp, &task_uid));
	}
}

void SchedStop(sched_t *scheduler)
{
	assert(NULL != scheduler);
	scheduler->should_i_sleep = 1;
}

void SchedRun(sched_t *scheduler)
{
	void *task_to_dequeue = PQPeek(scheduler->queue);
	time_t current_task_execution_time = 0;
	
	assert(NULL != scheduler);
	
	for (;  (!scheduler->should_i_sleep) && (!PQIsEmpty(scheduler->queue)); )
	{
		task_to_dequeue = PQPeek(scheduler->queue);
		current_task_execution_time = TimeOfExe(task_to_dequeue);
		
		scheduler->task_running = task_to_dequeue;
		PQDequeue(scheduler->queue);
		ForceSleep(current_task_execution_time); 
		
		if (TaskExecute(scheduler->task_running) && (!scheduler->remove_me))
		{
			TimeExeUpdate(scheduler->task_running);
			
			if (0 != PQEnqueue(scheduler->queue, scheduler->task_running))
			{
				break;
			}
		}
		else
		{			
			TaskDestroy(scheduler->task_running);
			scheduler->remove_me = 0;
		}
		
		scheduler->task_running = NULL;
	}
	
	scheduler->should_i_sleep = 0; 
}

void SchedDestroy(sched_t *scheduler)
{
	/*while (!PQIsEmpty(scheduler->queue))
	{
		PQDequeue(scheduler->queue);
	}
	
	PQDestroy(scheduler->queue);
	free(scheduler); scheduler = NULL;*/
	
	assert(NULL != scheduler);
	
	while (!PQIsEmpty(scheduler->queue))
	{
		void *task_to_destroy = PQPeek(scheduler->queue);
		TaskDestroy(task_to_destroy);
		PQDequeue(scheduler->queue);
	}
	
	scheduler->remove_me = 1;
	
	/*SchedClear(scheduler);*/
	PQDestroy(scheduler->queue); scheduler->queue = NULL;
	free(scheduler->task_running); scheduler->task_running = NULL;
	free(scheduler); scheduler = NULL;
}

/***********************************
* 	INTERNAL FUNCTIONS 	*
***********************************/
static void ForceSleep(time_t current_task_execution_time)
{
	while (current_task_execution_time)
	{
		current_task_execution_time = sleep(current_task_execution_time - time(NULL));
	}
}

/************TIME**********************/
time_t TimeExeUpdate(sched_task_t *task_running)
{
	assert(NULL != task_running);
	
	task_running->execute_time = time(NULL) + task_running->interval;
	
	return task_running->execute_time;
}

time_t TimeOfExe(sched_task_t *task)
{
	return task->execute_time;
}

int TimeCmp(void *task1, void *task2, void *param)
{
	assert(NULL != task1);
	assert(NULL != task2);
	(void)param;
	
	return (int)((time_t)(((sched_task_t *)task1)->execute_time) - 
			(time_t)(((sched_task_t *)task2)->execute_time));
}

/***********************************
* 		DBUG FUNCTIONS 	*
***********************************/
 
 size_t PrintQueueSize(sched_t *scheduler)
{
	assert(NULL != scheduler);
	return PQCount(scheduler->queue);
}

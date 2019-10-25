#include <stdlib.h> /* malloc, free */
#include <time.h> /* time_t */
#include <assert.h> /* assert */

#include "task_manager.h" /* sched_task_t */
#include "dll.h" /* dll_iter_t */

sched_task_t *TaskCreate(operation_func_t func, size_t interval_in_seconds, void *param)
{
	sched_task_t *new_task = malloc(sizeof(*new_task));
	
	if (NULL == new_task)
	{
		return NULL;
	}
	
	return TaskInit(new_task, func, interval_in_seconds, param);
}

sched_task_t *
TaskInit(sched_task_t *new_task, operation_func_t func, size_t interval_in_seconds, void *param)
{
	ilrd_uid_t task_id = UIDCreate();
	
	assert(NULL != new_task);
	if (1 == UIDIsError(task_id))
	{
		return NULL;
	}
	
	new_task->handle_id = task_id;
	new_task->interval = interval_in_seconds;
	new_task->data = param;
	new_task->func = func;
	new_task->execute_time = time(NULL) + interval_in_seconds;
	
	return new_task;
}

sched_task_t *TaskGetCurrent(pq_t *q)
{
	sched_task_t *task = PQPeek(q);
	
	assert(NULL != q);
	return task;
}

int TaskExecute(sched_task_t *task)
{
	assert(NULL != task);
	
	return task->func(task->data);
}

int TaskIsEqual(void *task_id, void *curr_task, void *param)
{
	(void) param;
	
	return UIDIsEqual(*(ilrd_uid_t *)task_id, ((sched_task_t *)curr_task)->handle_id);
}

void TaskDestroy(sched_task_t *task)
{
	free(task); task = NULL;
}

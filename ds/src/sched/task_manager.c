#include <stdlib.h> /* malloc, free */
#include <time.h> /* time_t */
#include <assert.h> /* assert */

#include "task_manager.h" /* sched_task_t */
#include "pq.h" /* PQEnqueue, PQPeek */
#include "sl.h" /**/
#include "dll.h" /* dll_iter_t */
#include "uid.h" /* UIDIsEqual*/

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
	assert(NULL != new_task);
		
	new_task->interval = interval_in_seconds;
	new_task->data = param;
	new_task->func = func;
	new_task->execute_time = interval_in_seconds;
	
	return new_task;
}

int TaskExecute(sched_task_t *task)
{
	return FAILURE;
}

void TaskDestroy(sched_task_t *task)
{
	free(task);
}

/* for sleep() portability: */
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <assert.h> /* assert */

#include "time_manager.h"

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

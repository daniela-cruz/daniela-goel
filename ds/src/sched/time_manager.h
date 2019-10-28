#ifndef __TIME_MAN_H__
#define __TIME_MAN_H__
#include <time.h> /* time_t */

#include "task_manager.h"  /* sched_task_t */ 

int TimeIsBefore(void *task1, void *task2, void *param);

int TimeDifference(sched_task_t *task);

time_t TimeOfExe(sched_task_t *task);

void TimeExeUpdate(sched_task_t *task_running);

#endif /* __TIME_MAN_H__ */

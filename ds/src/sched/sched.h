#ifndef __SCHED_H__
#define __SCHED_H__
#include <stddef.h> /* size_t */

#include "uid.h" /* unique task id */

/*		function pointer to a callback function 
* 		of a task 													*/
typedef int (*operation_func_t)(void *);	

/*		the user will receive a pointer to new
 * 		scheduler whenever SchedCreate 
 * 		will be called 												*/
typedef struct scheduler sched_t;

/*		create a new scheduler. SchedDestroy
 * 		must be called in order to terminate
 * 		this program 												*/
sched_t *SchedCreate();

/*		add new task to scheduler. Note that 
 * 		new tasks will be ordered by time of 
 * 		add request. interval_in_seconds 
 * 		determines minimal interval between 
 * 		each task run time and func is the 
 * 		particular callback function to be 
 * 		executed by SchedRun								*/
ilrd_uid_t 
SchedAddTask(sched_t *scheduler, operation_func_t func, size_t interval_in_seconds, void *param);

/* 		remove entire task from schedule 					*/
void SchedRemoveTask(sched_t *scheduler, ilrd_uid_t *task_uid);

/*		if current task->data > 0, sleep will be
 * 		activated for data number of seconds 			*/
void SchedStop(sched_t *scheduler);

/*		run tasks in queue until SchedDestroy is 
 * 		called as one of the tasks. If it's (or due) 
 * 		time for a task to be called SchedRun 
 *		will execute it otherwise it will be ignored		*/
void SchedRun(sched_t *schedule);

/*		this function must be called when the user 
 * 		wishes to permanently stop SchedRun from 
 * 		running any longer. The scheduler must 
 * 		be destroyed to free up allocated memory		*/
void SchedDestroy(sched_t *scheduler);

#endif /*__SCHED_H__*/

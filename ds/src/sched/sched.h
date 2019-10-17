#ifndef __SCHED_H__
#define __SCHED_H__
#include <stddef.h> /* size_t */

#include "uid.h"

typedef int (*operation_func_t)(void *);	

typedef struct scheduler sched_t;

sched_t *SchedCreate();

uid_t SchedAdd(sched_t *scheduler, handle_func func, size_t interval_in_seconds, void *param);

void SchedRemove(sched_t *scheduler, uid_t task);

void SchedStop(sched_t *scheduler);

void SchedRun(sched_t *schedule);

void SchedDestroy(sched_t *scheduler);

#endif /*__SCHED_H__*/

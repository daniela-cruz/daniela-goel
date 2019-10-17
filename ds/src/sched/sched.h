#ifndef __SCHED_H__
#define __SCHED_H__
#include <stddef.h> /* size_t */

#include "uid.h"
#include "pq.h"

typedef int (*handle_func_t)(void *);	

typedef struct scheduler sched_t;

sched_t *SchedCreate();

uid_t SchedAdd(size_t period, sched_t *scheduler, handle_func func, void *param);

void SchedRemove(uid_t task, sched_t *scheduler);

void SchedStop(sched_t *scheduler);

void SchedRun(sched_t *schedule);

void SchedDestroy(sched_t *scheduler);

#endif /*__SCHED_H__*/

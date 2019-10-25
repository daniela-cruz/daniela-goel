#ifndef __TESTER_H__
#define __TESTER_H__

#include "sched.h"			/* sched */

/* indicates on number of tasks awaiting in queue */
size_t PrintQueueSize(sched_t *scheduler);

size_t GetTaskInterval(sched_t *scheduler, ilrd_uid_t);

#endif /*__TESTER_H__*/

/* 
 * Please save some time and copy this line: 
* gd sched_b.c sched.h sched_test.c task_manager.c uid.c uid.h tester.h ../dll/dll.c ../sl/sl.c ../pq/pq.c -I ../dll/ -I ../sl/ -I ../pq/
*/
#include <stdio.h> 	/* printf */
#include <stddef.h> 	/* size_t */

#include "sched.h" 	/* scheduler functions */
#include "tester.h" 		/* debug funcs */
#include "uid.h"		 	/* uid */

/*****************************************************************/
void PrintUID(ilrd_uid_t uid);
int PrintMsg(void* param);
int PrintMsg2(void* param);
int PrintMsg3(void* param);
int PrintMsg4(void* param);
int TestStop(void* sched);
int TestRemove(void* task_remove);
int TestAdd(void* task_add);

typedef struct
{
	sched_t* task_sched;
	ilrd_uid_t* task_uid;
}task_remove_t;

typedef struct
{
	sched_t* task_sched;
	size_t interval_in_sec;
	operation_func_t func;
	void* param;
	ilrd_uid_t* uid;
}task_add_t;

ilrd_uid_t uid_array[20];

/*******************/

int main()
{
	sched_t* sch = NULL;
	
	task_remove_t task_rem1;
	task_add_t task_add1;
	
	sch = SchedCreate();
	
	uid_array[0] = SchedAddTask(sch, TestStop, 25, sch);
	
	task_rem1.task_sched = sch;
	task_rem1.task_uid = &(uid_array[2]);
	uid_array[1] = SchedAddTask(sch, TestRemove, 8, &task_rem1);
	
	uid_array[2] = SchedAddTask(sch, PrintMsg, 3, NULL);
	uid_array[3] = SchedAddTask(sch, PrintMsg2, 2, NULL);
	uid_array[4] = SchedAddTask(sch, PrintMsg3, 4, NULL);
	uid_array[5] = SchedAddTask(sch, TestAdd, 18, sch);

	printf("no. of tasks in scheduler: %lu\n", PrintQueueSize(sch));
	SchedRun(sch);
	
	
	SchedDestroy(sch);
	
	return 0;
}

/*******************/

int PrintMsg(void* param)
{
	(void)param;
	printf("Yo sup 3\n");
	
	return 1;
}

int PrintMsg2(void* param)
{
	(void)param;
	printf("Wee 2\n");
	
	return 1;
}

int PrintMsg3(void* param)
{
	(void)param;
	printf("AAAh 4\n");
	
	return 1;
}

int PrintMsg4(void* param)
{
	(void)param;
	printf("Yo yo yo\n");
	
	return 1;
}

/*******************/

int TestRemove(void* task_remove)
{
	task_remove_t* task = ((task_remove_t*)task_remove);
	
	sched_t* sched = ((sched_t*)task->task_sched);
	ilrd_uid_t* uid = ((ilrd_uid_t*)task->task_uid);
	
	printf("removing task which prints: Yo sup\n");
	SchedRemoveTask(sched, uid);
	
	return 0;
}

int TestAdd(void* sched)
{

	printf("adding a task which prints: Yo yo yo\n");
	SchedAddTask((sched_t*)sched, PrintMsg4, 3, NULL);

	return 0;
}

/*******************/

int TestStop(void* sched)
{
	SchedStop(sched);
	printf("stopped run\n");
	
	return 0;
}


void PrintUID(ilrd_uid_t uid)
{
	printf("time:\t\t%ld\n", uid.curr_time);
	printf("s/n:\t\t%ld\n", uid.counter);
	printf("is error:\t%d\n", uid.is_error);
	printf("pid:\t\t%d\n\n", uid.pid);
}


/*****************************************************************/
/*
struct action_func_data
{
	char *msg;
	ilrd_uid_t uid;
};

int PrintNonsense(void *str);
int PrintSize(void *sch);

int main()
{
	struct action_func_data ad[3];
	sched_t *sch = SchedCreate();
	ilrd_uid_t task_id;
	
	
	ad[1].uid = SchedAddTask(sch, PrintNonsense, 2, "Hey");
	ad[2].uid = SchedAddTask(sch, PrintNonsense, 3, "Jo");
	
	SchedStop(sch);
	SchedRun(sch);
		
	return 0;
}

int PrintNonsense(void *str)
{
	printf("%s\n", (char*)str);
	
	return 0;
}

int PrintSize(void *sch)
{
	printf("Elements including this task: %ld\n", PrintQueueSize((sched_t*)sch));
	
	return 0;
}*/


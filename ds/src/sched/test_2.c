/* 
 * Please save some time and copy this line: 
* gd sched_b.c sched.h sched_test.c task_manager.c uid.c uid.h tester.h ../dll/dll.c ../sl/sl.c ../pq/pq.c -I ../dll/ -I ../sl/ -I ../pq/
*/
#include <stdio.h> 	/* printf */
#include <stddef.h> 	/* size_t */

#include "sched.h" 	/* scheduler functions */
#include "tester.h" 		/* debug funcs */
#include "uid.h"		 	/* uid */

struct action_func_data
{
	char *msg;
	ilrd_uid_t uid;
};

void TestScheduler();

int Task1(void *str);
int Task2(void *str);
int Task3(void *str);
int Task4(void *scheduler);
int PrintElementsAmount(void *sch);

int main()
{
	TestScheduler();
	return 0;
}

void TestScheduler()
{
	sched_t *sch = SchedCreate();
	ilrd_uid_t task_uid;
	int i = 0;
	
	PrintElementsAmount(sch);
	
	task_uid = SchedAddTask(sch, Task3, 2, "Go home");
	task_uid = SchedAddTask(sch, Task2, 5, "Jo");
	task_uid = SchedAddTask(sch, Task4, 13, sch);
	task_uid = SchedAddTask(sch, Task1, 3, "Hey");
	
	PrintElementsAmount(sch);
	
	SchedRun(sch);
	SchedDestroy(sch);
}

int Task1(void *str)
{
	printf("%s\n", (char*)str);
	
	return 0;
}

int Task2(void *nothing)
{
	(void) nothing;
	printf("Lalalalaaaaaaaaaaa\n");
	
	return 0;
}

int Task3(void *str)
{
	printf("I'm back, %s\n", (char*)str);
	
	return 0;
}

int Task4(void *scheduler)
{
	printf("I am stopping now. . .\n");
	SchedStop(scheduler);
	
	return 0;
}

int PrintElementsAmount(void *sch)
{
	printf("Elements including this task: %ld\n", PrintQueueSize((sched_t*)sch));
	
	return 0;
}

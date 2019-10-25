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
int PrintElementsAmount(void *sch);

int main()
{
	TestScheduler();
	return 0;
}

void TestScheduler()
{
	struct action_func_data ad[3];
	sched_t *sch = SchedCreate();
	ilrd_uid_t task_id;
	
	PrintElementsAmount(sch);
	task_id = SchedAddTask(sch, Task1, 2, "Hey");
	SchedAddTask(sch, Task2, 3, "Jo");
	SchedAddTask(sch, Task3, 4, "Go home");
	SchedRemoveTask(sch, &task_id);
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
	printf("Lalalalaaaaaaaaaaa\n");
	
	return 0;
}

int Task3(void *str)
{
	printf("I'm back, %s\n", (char*)str);
	
	return 0;
}

int PrintElementsAmount(void *sch)
{
	printf("Elements including this task: %ld\n", PrintQueueSize((sched_t*)sch));
	
	return 0;
}

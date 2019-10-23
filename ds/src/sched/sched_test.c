/* 
 * Please save some time and copy this line: 
* gd sched_b.c sched.h sched_test.c task_manager.c uid.c uid.h tester.h ../dll/dll.c ../sl/sl.c ../pq/pq.c -I ../dll/ -I ../sl/ -I ../pq/
*/
#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "sched.h" /* scheduler functions */
#include "tester.h" /* debug funcs */

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
	
	/*ad[0].msg = "hello";
	ad[0].uid = SchedAddTask(sch, PrintNonsense, 2, ad[0].msg);
	
	ad[1].msg = "world";
	ad[1].uid = SchedAddTask(sch, PrintNonsense, 3, ad[0].msg);*/
	
	/*printf("Elements number in queue: %ld\n", PrintQueueSize(sch));*/
	
	/*printf("Elements number in queue: %ld\n", PrintQueueSize(sch));*/
	ad[1].uid = SchedAddTask(sch, PrintNonsense, 2, "Hey");
	ad[2].uid = SchedAddTask(sch, PrintSize, 3, "");
	/*SchedStop(sch);*/
	/*ad[1].uid = SchedAddTask(sch, (operation_func_t)SchedRemoveTask, 3, &ad[1].uid);
	ad[0].uid = SchedAddTask(sch, (operation_func_t)SchedRemoveTask, 4, &ad[0].uid);**/
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
}

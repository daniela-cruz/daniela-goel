/* 
 * Please save some time and copy this line: 
* gd sched_b.c sched.h sched_test.c uid.c uid.h tester.h ../dll/dll.c ../sl/sl.c ../pq/pq.c -I ../dll/ -I ../sl/ -I ../pq/
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

int main()
{
	struct action_func_data ad[3];
	sched_t *sch = SchedCreate();
	
	ad[0].msg = "hello";
	ad[0].uid = SchedAddTask(sch, PrintNonsense, 2, ad[0].msg);
	
	ad[1].msg = "world";
	ad[1].uid = SchedAddTask(sch, PrintNonsense, 3, ad[0].msg);
	
	printf("Elements number in queue: %ld\n", PrintQueueSize(sch));
	
	SchedRemoveTask(sch, &ad[0].uid);
	SchedRemoveTask(sch, &ad[1].uid);
	
	printf("Elements number in queue: %ld\n", PrintQueueSize(sch));
	
	SchedDestroy(sch);
	
	return 0;
}

int PrintNonsense(void *str)
{
	printf("%s\n", (char*)str);
	
	return 0;
}



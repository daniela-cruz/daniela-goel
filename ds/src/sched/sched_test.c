#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "sched.h" /* scheduler functions */
#include "uid.h" /* ilrd_uid_t */

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
	
	return 0;
}

int PrintNonsense(void *str)
{
	printf("%s\n", (char*)str);
	
	return 0;
}



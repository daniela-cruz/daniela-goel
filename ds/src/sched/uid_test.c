#include <stdio.h> /* printf */

#include "uid.h"

int main()
{
	ilrd_uid_t uid = UIDCreate();
	ilrd_uid_t uid2 = UIDCreate();
	
	printf("%ld\n", uid.curr_time);
	printf("%d\n", uid.pid);
	printf("%ld\n", uid.counter);
	printf("%d\n", uid.is_error);	
	
	printf("%ld\n", uid2.curr_time);
	printf("%d\n", uid2.pid);
	printf("%ld\n", uid2.counter);
	printf("%d\n", uid2.is_error);
	
	printf("Are the two processes equal? %d\n", UIDIsEqual(uid, uid2));
	
	return 0;
}

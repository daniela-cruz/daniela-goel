#include <stddef.h> /* size_t */
#include <sys/types.h> /* pid_t */
#include <unistd.h>
#include <time.h> /* time_t */

ilrd_uid_t UIDCreate()
{
	ilrd_uid_t uid;
	static size_t counter = 0;
	
	uid.curr_time = time(NULL);
	uid.process_is = getpid();
	uid.counter = counter++;
	uid.is_error = 	UIDIsError(uid);
	
	return uid;
}

int UIDIsEqual(ilrd_uid_t task1, ilrd_uid_t task2)
{
	if ((uid1.curr_time == uid2.curr_time) || 
		(uid1.process_is == uid2.process_is) || 
		(uid1.counter == uid2.counter))
	{
		return 1;
	}
	
	return 0;
}

int UIDIsError(ilrd_uid_t task)
{
	if ((NULL == uid.curr_time) || 
		(NULL == uid.process_is) || 
		(NULL == uid.counter))
	{
		return 1;
	}
	
	return 0;
}

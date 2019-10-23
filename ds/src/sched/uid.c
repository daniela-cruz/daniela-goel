#include <stddef.h> /* size_t */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* handle sleep() */
#include <time.h> /* time_t */

#include "uid.h"

ilrd_uid_t UIDCreate()
{
	ilrd_uid_t uid;
	static size_t counter = 0;
	
	uid.curr_time = time(NULL);
	uid.pid = getpid();
	uid.counter = counter++;
	uid.is_error = 	UIDIsError(uid);
	
	return uid;
}

int UIDIsEqual(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	if ((uid1.curr_time == uid2.curr_time) && 
		(uid1.pid == uid2.pid) && 
		(uid1.counter == uid2.counter))
	{
		return 1;
	}
	
	return 0;
}

int UIDIsError(ilrd_uid_t uid)
{
	if ((0 == uid.curr_time) || 
		(0 == uid.pid))
	{
		return 1;
	}
	
	return 0;
}

ilrd_uid_t UIDError(ilrd_uid_t uid)
{
	uid.is_error = 1;
	
	return uid;
}

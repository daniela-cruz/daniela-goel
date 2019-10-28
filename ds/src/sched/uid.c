#include <unistd.h> /* handle sleep() */

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
	return ((uid1.curr_time == uid2.curr_time) && 
		(uid1.pid == uid2.pid) && 
		(uid1.counter == uid2.counter));
}

int UIDIsError(ilrd_uid_t uid)
{
	return ((0 == uid.curr_time) || (0 == uid.pid));
}

ilrd_uid_t UIDError()
{
	ilrd_uid_t uid = UIDCreate();
	
	uid.is_error = 1;
	
	return uid;
}

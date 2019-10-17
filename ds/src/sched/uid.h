#ifndef __UID_H__
#define __UID_H__

#include <stddef.h> /* size_t */
#include <sys/types.h> /* pid_t */
/*#include <unistd.h>*/
#include <time.h> /* time_t */

typedef struct unique_id
{
	time_t curr_time;
	pid_t pid;
	size_t counter;
	int is_error;
} ilrd_uid_t;

ilrd_uid_t UIDCreate();

int UIDIsEqual(ilrd_uid_t uid1, ilrd_uid_t uid2);

int UIDIsError(ilrd_uid_t uid);

#endif /*__UID_H__*/

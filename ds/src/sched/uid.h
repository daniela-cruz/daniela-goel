#ifndef __UID_H__
#define __UID_H__

#include <stddef.h> /* size_t */

typedef struct user_id
{
	time_t curr_time;
	size_t counter;
	int is_error;
	pid_t process_id;
} uid_t;

#endif /*__UID_H__*/

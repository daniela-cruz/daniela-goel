#ifndef __UID_H__
#define __UID_H__

#include <stddef.h> /* size_t */
#include <sys/types.h> /* pid_t */
#include <time.h> /* time_t */

/* 	For internal use */
typedef struct unique_id ilrd_uid_t;

/* create a new process id 				*/
ilrd_uid_t UIDCreate();

/*	returns 1 if equal and zero if not 	*/
int UIDIsEqual(ilrd_uid_t uid1, ilrd_uid_t uid2);

/*	returns 1 if there was an error in 
 * 	the process of issuing the uid 		*/
int UIDIsError(ilrd_uid_t uid);

/*	a generic uid that returns an 
 * 	errouneous uid 								*/
ilrd_uid_t UIDError();

/**************************************
 * 		INTERNAL USE ONLY		  *
**************************************/
struct unique_id
{
	time_t curr_time;
	pid_t pid;
	size_t counter;
	int is_error;
};

#endif /*__UID_H__*/

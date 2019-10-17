#ifndef __UID_H__
#define __UID_H__

#include <stddef.h> /* size_t */

typedef struct user_id my_uid_t;

my_uid_t UIDCreate();

int UIDIsEqual(my_uid_t task1, my_uid_t task2);

int UIDIsError(my_uid_t task);

#endif /*__UID_H__*/

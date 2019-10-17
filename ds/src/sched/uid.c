#include <stddef.h> /* size_t */
#include <sys/types.h> /* pid_t */
#include <unistd.h>
#include <time.h> /* time_t */

struct user_id
{
	time_t curr_time;
	size_t counter;
	int is_error;
	pid_t process_id;
};

my_uid_t UIDCreate()
{
	pid_t process_id;

	process_id = getpid();
}

int UIDIsEqual(my_uid_t task1, my_uid_t task2);

int UIDIsError(my_uid_t task);

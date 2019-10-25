#include <time.h> 

time_t TimeDiff(time_t next_time, time_t curr_time)
{
	return next_time - curr_time;
}

time_t CurrTime()
{
	return time(NULL);
}


#include <stddef.h> /* size_t */

#include "queue.h" /* include FIFO queue and Priority queue implementations */

struct queue
{
	void (*destroy_func)(q_t*);
	int (*enqueue_func)(q_t*, void*);
	void* (*dequeue_func)(q_t*);
	int (is_empty_func)(q_t*);
	void* (*peek_func)(q_t*);
	size_t (*count_func)(q_t*);
	q_t* (*append_func)(q_t*, q_t*);
};

q_t *QCreate(void *data, void *param)
{
	if (NULL == data)
	{
		
	}
}

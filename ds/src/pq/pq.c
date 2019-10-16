#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "pq.h" /* pq_t and all functions below */

struct priority_queue
{
	sl_t *list;
};

pq_t *PQCreate(pq_is_before_t func, void *param)
{
	pq_t *queue = NULL;
	
	queue = malloc(sizeof(*queue));
	if (NULL == queue)
	{
		return NULL;
	}
	
	queue->list = SLCreate((sl_is_before_t)func, param);
	if (NULL == queue->list)
	{
		return NULL;
	}
	
	return queue;
}

void PQDestroy(pq_t *queue)
{
	SLDestroy(queue->list);
	free(queue);
}

int PQEnqueue(pq_t *queue, void *task)
{
	SLInsert(SLEnd(queue->list), task);
	
	return 0 == DLLIsEmpty(queue->list);
}

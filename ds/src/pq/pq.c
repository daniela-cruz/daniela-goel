#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "pq.h"
#include "sl.h" /* sorted list implementation */

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
		free(queue);
		return NULL;
	}
	
	return queue;
}

void PQDestroy(pq_t *queue)
{
	assert(NULL != queue);
	
	SLDestroy(queue->list);
	free(queue);
}

int PQEnqueue(pq_t *queue, void *task)
{
	assert(NULL != queue);
	
	SLInsert(queue->list, task);
	
	return 0 == SLIsEmpty(queue->list);
}

void *PQDequeue(pq_t *queue)
{
	assert(NULL != queue);
	
	return SLPopFront(queue->list);
}

int PQIsEmpty(const pq_t *queue)
{
	assert(NULL != queue);
	
	return SLIsEmpty(queue->list);
}

void *PQPeek(const pq_t *queue)
{
	assert(NULL != queue);
	
	return SLGetData(SLBegin(queue->list));
}

size_t PQCount(const pq_t *queue)
{
	assert(NULL != queue);
	
	return SLSize(queue->list);
}

void *PQErase(pq_t *queue, pq_is_match_t func, void *param)
{
	void *popped_data = NULL;
	
	assert(NULL != queue);
	popped_data = SLGetData(SLFindIf(SLBegin(queue->list), SLEnd(queue->list), func, param));
	SLRemove(SLFindIf(SLBegin(queue->list), SLEnd(queue->list), func, param));
	
	return popped_data;
}

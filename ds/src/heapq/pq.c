#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "pq.h"
#include "heap.h" 	/* heap_t and all funcs below */

struct priority_queue
{
	heap_t *heap;
};

pq_t *PQCreate(pq_is_before_t func, void *func_param)
{
	pq_t *heap_q = malloc(sizeof(*heap_q));
	if(NULL == heap_q)
	{
		return NULL;
	}

	heap_q->heap = HEAPCreate((is_before_t)func, func_param);
	if(NULL == heap_q->heap)
	{
		free(heap_q); heap_q = NULL;
		return NULL;
	}

	return heap_q;
}

void PQDestroy(pq_t *queue)
{
	HEAPDestroy(queue->heap);

	free(queue);
}

int PQEnqueue(pq_t *queue, void *data)
{
	return HEAPPush(queue->heap, data);
}

void *PQDequeue(pq_t *queue)
{
	void *data = HEAPPeek(queue->heap);

	HEAPPop(queue->heap);

	return data;
}

void *PQErase(pq_t *queue, pq_is_match_t func, void *param)
{
	void *removable = NULL;
	void *popped_data = NULL;
	int i = 0;
	size_t size = 0;

	size = PQCount(queue);
	for (i = size - 1; 0 < i; --i)
	{
		removable = HEAPPeek(queue->heap);
		if (func(&removable, param))
		{
			popped_data = removable;
			HEAPErase(queue->heap, (heap_is_match_t)func, removable);
			break;
		}
	}
	
	return popped_data;
}

int PQIsEmpty(const pq_t *queue)
{
	return HEAPIsEmpty(queue->heap);
}

void *PQPeek(const pq_t *queue)
{
	return HEAPPeek(queue->heap);
}

size_t PQCount(const pq_t *queue)
{
	return HEAPSize(queue->heap);
}


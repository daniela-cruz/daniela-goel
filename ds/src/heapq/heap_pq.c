#include <stdlib.h> /* malloc */

#include "heap_pq.h"
#include "heap.h"
#include "pq.h"

struct heap_q
{
	heap_t *heap;
};

heap_q_t *HeapQCreate(heapq_is_before_t func, void *func_param)
{
	heap_q_t *heap_q = malloc(sizeof(*heap_q));
	if(NULL == heap_q)
	{
		return NULL;
	}

	heap_q->heap = HEAPCreate(func, func_param);
	if(NULL == heap_q->heap)
	{
		free(heap_q); heap_q = NULL;
		return NULL;
	}

	return heap_q;
}

void HeapQDestroy(heap_q_t *queue)
{
	HEAPDestroy(queue->heap);

	free(queue);
}

int HeapQEnqueue(heap_q_t *queue, void *data)
{
	return HEAPPush(queue->heap, data);
}

void *HeapQDequeue(heap_q_t *queue)
{
	void *data = HEAPPeek(queue->heap);

	HEAPPop(queue->heap);

	return data;
}

void *HeapQRemove(heap_q_t *queue, heapq_is_match_t func, void *param)
{
	void *removable = NULL;
	int i = 0;
	size_t size = 0;

	size = HeapQCount(queue);

	for ( i = 0; i < size; i++)
	{
		removable = HeapQPeek(queue);
		if (func(removable, param))
		{
			break;
		}
		
	}
	
	
	return NULL;
}

int HeapQIsEmpty(const heap_q_t *queue)
{
	return HEAPIsEmpty(queue->heap);
}

void *HeapQPeek(const heap_q_t *queue)
{
	return HEAPPeek(queue->heap);
}

size_t HeapQCount(const heap_q_t *queue)
{
	return HEAPSize(queue->heap);
}


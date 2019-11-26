#include <stdlib.h> /* malloc */

#include "heap_pq.h"
#include "heap.h"
#include "pq.h"

struct pq
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
		free(heap_q);

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

void *HeapQRemove(heap_q_t *queue, heapq_is_match_t func, void *func_param)
{

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


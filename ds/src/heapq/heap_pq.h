#ifndef __HEAHeapQ_H__
#define __HEAHeapQ_H__

#include <stddef.h>     /* size_t */

typedef struct heap_q heap_q_t;

typedef int(*heapq_is_before_t)(const void *data1, const void *data2, void *param);
typedef int (*heapq_is_match_t)(const void *data, const void *param);

pq_t *HeapQCreate(heapq_is_before_t func, void *func_param);

void HeapQDestroy(pq_t *queue);

int HeapQEnqueue(pq_t *queue, void *data);

void *HeapQDequeue(pq_t *queue);

void *HeapQRemove(pq_t *queue, heapq_is_match_t func, void *func_param);

int HeapQIsEmpty(const pq_t *queue);

void *HeapQPeek(const pq_t *queue);

size_t HeapQCount(const pq_t *queue);

#endif /* __HEAHeapQ_H__ */

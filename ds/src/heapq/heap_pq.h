#ifndef __HEAHeapQ_H__
#define __HEAHeapQ_H__

#include <stddef.h>     /* size_t */

typedef struct heap_q heap_q_t;

typedef int(*heapq_is_before_t)(const void *data1, const void *data2, void *param);
typedef int (*heapq_is_match_t)(const void *data, const void *param);

heap_q_t *HeapQCreate(heapq_is_before_t func, void *func_param);

void HeapQDestroy(heap_q_t *queue);

int HeapQEnqueue(heap_q_t *queue, void *data);

void *HeapQDequeue(heap_q_t *queue);

void *HeapQRemove(heap_q_t *queue, heapq_is_match_t func, void *param);

int HeapQIsEmpty(const heap_q_t *queue);

void *HeapQPeek(const heap_q_t *queue);

size_t HeapQCount(const heap_q_t *queue);

#endif /* __HEAHeapQ_H__ */

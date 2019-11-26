#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>		/*size_t*/

typedef struct heap heap_t;

typedef int (*is_before_t)(const void *data1, const void *data2, void *param);

/********************************************************/
heap_t *HEAPCreate(is_before_t func, void *param);

void HEAPDestroy(heap_t *heap);

int HEAPPush(heap_t *heap, const void *data);

void HEAPPop(heap_t *heap);

void HEAPSort(heap_t *heap, size_t size);

void *HEAPPeek(heap_t *heap);

size_t HEAPSize(const heap_t *heap);

int HEAPIsEmpty(const heap_t *heap);

void PrintHeap(heap_t *heap);

/********************************************************/
#endif /*__HEAP_H__*/
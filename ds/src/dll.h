#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h>

typedef struct dll dll_t;
typedef struct dll_node dll_node_t;

typedef struct dll_iterator
{
	dll_node_t *cur;
} dll_iter_t;

typedef int (*dll_cmp_func_t)(const void *data, void *param);
typedef int (*dll_act_func_t)(void *data, void *param);

dll_t *DLLCreate();

void DLLDestroy(dll_t *dll);

dll_iter_t DLLInsert(dll_t *dll, dll_iter_t iterator, void *data);

dll_iter_t DLLRemove(dll_t *dll, dll_iter_t iterator);

int DLLIsEmpty(const dll_t *dll);

dll_t *DLLPushBack(dll_t *dll, void *data); /* int ?*/

dll_t *DLLPopBack(dll_t *dll);

dll_t *DLLPushFront(dll_t *dll, void *data); /* int ?*/

dll_t *DLLPopFront(dll_t *dll);

size_t DLLSize(const dll_t *dll);

/********************************************/
dll_iter_t DLLBegin(const dll_t *dll);

dll_iter_t DLLEnd(const dll_t *dll);

dll_iter_t DLLIterNext(dll_iter_t it);

int DLLIterIsEqual(dll_iter_t it1, dll_iter_t it2);

void *DLLGetData(dll_iter_t it);

/*******************************************/
dll_iter_t DLLFind(dll_iter_t it_start, dll_iter_t it_end, dll_act_func_t for_each_func, const void *param);

int DLLForEach(dll_iter_t it_start, dll_iter_t it_end, dll_cmp_func_t for_each_func, void *param);

#endif /*__DLL_H__*/

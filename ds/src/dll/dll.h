#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h>

typedef struct dll dll_t;
typedef struct dll_node dll_node_t;

typedef struct dll_iterator
{
	dll_node_t *curr_node; 
	dll_node_t *prev;
	dll_t *list;
} dll_iter_t;

typedef int (*dll_cmp_func_t)(const void *data, void *param);
typedef int (*dll_act_func_t)(void *data, void *param);

dll_t *DLLCreate();

void DLLDestroy(dll_t *dll);

dll_iter_t DLLInsert(dll_iter_t iterator, const void *data);/* done */

dll_iter_t DLLRemove(dll_iter_t iterator);/* done */

int DLLIsEmpty(const dll_t *dll);/* done */

dll_iter_t DLLPushBack(dll_t *dll, const void *data); /* done */

void *DLLPopBack(dll_t *dll);

dll_iter_t DLLPushFront(dll_t *dll, const void *data);  /* done */

void *DLLPopFront(dll_t *dll);

size_t DLLSize(const dll_t *dll);/* done */

/********************************************/

/* the user should send an actual address of a particular node casted as an iterator */
dll_iter_t DLLIterNext(dll_iter_t iterator);

dll_iter_t DLLIterPrev(dll_iter_t iterator);/* done */

dll_iter_t DLLBegin(const dll_t *dll);/* done */

dll_iter_t DLLEnd(const dll_t *dll);/* done */

int DLLIterIsEqual(dll_iter_t it1, dll_iter_t it2);/* done */

void *DLLGetData(dll_iter_t it);

/*******************************************/
dll_iter_t DLLFind(dll_iter_t it_start, dll_iter_t it_end, dll_cmp_func_t find_func, void *param);

int DLLForEach(dll_iter_t it_start, dll_iter_t it_end, dll_act_func_t for_each_func, void *param);

dll_iter_t DLLSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to);

#endif /*__DLL_H__*/

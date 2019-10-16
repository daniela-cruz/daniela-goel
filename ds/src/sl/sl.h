#ifndef __SL_H__
#define __SL_H__

#include <stddef.h> /* size_t */

#include "dll.h" /* dll_iter_t */

/*	Sorting function provided by user 					*/
typedef int (*sl_is_before_t)(void *data1, void *data2, void *param);

/*	Inclusive function provided by user				*/
typedef int (*sl_act_func_t)(void *data, void *param);

/*	Comparison function provided by user			*/
typedef int (*sl_cmp_func_t)(void *data, void *param);

/*	The user will receive a pointer to the list			*/
typedef struct sorted_list sl_t;

/*	The user will navigate between nodes in 
 * 	the list using the iterator. First call should 
 * 	be initialized using the SLBegin function			*/
typedef struct sl_iterator sl_iter_t;

/*************************************************
 *		 		General functions				*
 ************************************************/
/*	Get link to a new sorted list.
 * 	The user must provide link to a sorting 
 * 	function to determine sorting criteria.
 * 	The sorting function must return an int
 * 	and receive 2 void* parameters 					*/
sl_t *SLCreate(sl_is_before_t is_before_func, void *param);

/*	The user must call this function to free
 * 	allocated memory after using the list 				*/
void SLDestroy(sl_t *sorted_list);

/*	Insert a new node in place							*/
sl_iter_t SLInsert(sl_iter_t iterator, void *data);

/*	Remove a new node in place						*/
sl_iter_t SLRemove(sl_iter_t iterator);

void *SLPopBack(sl_t *list);

void *SLPopFront(sl_t *list);

int SLIsEmpty(sl_t *list);

size_t SLSize(sl_t *list);

/*************************************************
 *		 		Iterator functions					*
 ************************************************/

/*	iterated to node after last					*/
sl_iter_t SLBegin(sl_t *sorted_list);

/*	iterate to node after last.
 * 	Used for comparison or errors			*/
sl_iter_t SLEnd(sl_t *sorted_list);

sl_iter_t SLIterPrev(sl_iter_t iterator);

sl_iter_t SLIterNext(sl_iter_t iterator);

int SLIsEqual(sl_iter_t it1, sl_iter_t it2);

void *SLGetData(sl_iter_t iterator);

/*************************************************
 *		 		Extra functions					*
 ************************************************/
int SLForEach(sl_iter_t from, sl_iter_t to, sl_act_func_t func, void *param);

sl_iter_t  SLFind(sl_iter_t from, sl_iter_t to, sl_is_before_t func, void *param);

sl_iter_t  SLFindIf(sl_cmp_func_t func, void *data, void *param);

sl_iter_t SLMerge(sl_iter_t to, sl_iter_t from);

/* 	FOR INTERNAL USE ONLY 				*/
struct sl_iterator 
{
	dll_iter_t iterator;
	sl_t *sl;
};

#endif /*__SL_H__*/

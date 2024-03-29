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
sl_iter_t SLInsert(sl_t *list, void *data);

/*	Remove a new node in place						*/
sl_iter_t SLRemove(sl_iter_t iterator);

/*	Remove last node in list and provide its 
 * 	content														*/
void *SLPopBack(sl_t *list);

/*	Remove first element in list and provide its 
 * 	content														*/
void *SLPopFront(sl_t *list);

/*	returns one if empty and zero if not empty		*/
int SLIsEmpty(sl_t *list);

/*	Returns the number of elements in list 			*/
size_t SLSize(sl_t *list);

/*************************************************
 *		 		Iterator functions					*
 ************************************************/

/*	iterated to node after last					*/
sl_iter_t SLBegin(sl_t *sorted_list);

/*	iterate to the element after last.
 * 	Used for comparison or errors			*/
sl_iter_t SLEnd(sl_t *sorted_list);

/*	iterate to node after first.
 * 	If the list is empty it will return 
 * 	same output as SLEnd						*/
sl_iter_t SLIterPrev(sl_iter_t iterator);

/*	iterator to next element. 
 * 	If the iterator points to last element
 * 	it will return same as SLEnd 				*/
sl_iter_t SLIterNext(sl_iter_t iterator);

/*	returns 1 if both iterators point to 
 * 	same element, zero otherwise 			*/
int SLIsEqual(sl_iter_t it1, sl_iter_t it2);

/*	returns data of particular element 
 * in the list											*/
void *SLGetData(sl_iter_t iterator);

/*************************************************
 *		 		Extra functions					*
 ************************************************/
/*	the user should provide an action 
 * 	function as well as a look up range 	*/
int SLForEach(sl_iter_t from, sl_iter_t to, sl_act_func_t func, void *param);

/*	returns iterator to the element which
 * 	contains data 									*/
sl_iter_t  SLFind(sl_iter_t from, sl_iter_t to, void *data);

/*	same as SLFind using another 
 * 	function provided by the user 			*/
sl_iter_t  SLFindIf(sl_iter_t from, sl_iter_t to, sl_cmp_func_t func, void *param);

/*	Merge between two lists using 
 * 	is_before function as a sorting method*/
sl_iter_t SLMerge(sl_t *to, sl_t *from);

/* 	FOR INTERNAL USE ONLY 				*/
struct sl_iterator 
{
	dll_iter_t iterator;
	sl_t *sl;
};

#endif /*__SL_H__*/

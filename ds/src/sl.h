#ifndef __SL_H__
#define __SL_H__

#include <stddef.h> /* size_t */

#include "dll.h" /* dll_iter_t */

/*	Sorting function provided by user 				*/
typedef int (*sl_is_before_t)(void *, void *, void *param);

/*	Inclusive function provided by user			*/
typedef int (*sl_act_func_t)(void *, void *param);

/*	Comparison function provided by user		*/
typedef int (*sl_cmp_func_t)(void *, void *param);

/*	The user will receive a pointer to the list		*/
typedef struct sorted_list sl_t;

/*	The user will navigate between nodes in 
 * 	the list using the iterator							*/
typedef struct sl_iterator 
{
	dll_iter_t iterator;
} sl_iter_t;


/*************************************************
 *		 		General functions				*
 ************************************************/
/*	Get link to a new sorted list.
 * 	The user must provide link to a sorting 
 * 	function to determine sorting criteria.
 * 	The sorting function must return an int
 * 	and receive 2 void* parameters 				*/
sl_t *SLCreate(sl_is_before_t is_before_func);

/*	The user must call this function to free
 * 	allocated memory after using the list 			*/
void SLDestroy(sl_t *sorted_list);

/*	*/
sl_iter_t SLInsert(sl_t *sorted_list, sl_iter_t iterator, void *data);

sl_iter_t SLRemove(sl_t *sorted_list, sl_iter_t iterator);

/*************************************************
 *		 		Iterator functions					*
 ************************************************/
sl_iter_t SLBegin(sl_t *sorted_list);

sl_iter_t SLEnd(sl_t *sorted_list);

sl_iter_t SLPrev(sl_iter_t iterator);

sl_iter_t SLNext(sl_iter_t iterator);

/*************************************************
 *		 		Extra functions					*
 ************************************************/
int SLForEach(sl_iter_t from, sl_iter_t to, sl_act_func_t func, void *param);

sl_iter_t  SLFind(sl_iter_t from, sl_iter_t to, sl_cmp_func_t func, void *param);

#endif /*__SL_H__*/

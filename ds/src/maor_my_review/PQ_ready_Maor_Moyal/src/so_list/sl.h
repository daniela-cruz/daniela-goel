/*******************************************************************************
* Sorted list API                                                              *
* @author: Maor Moyal                                                          *
*                                                                              *
* ---------------------------------sl.h--------------------------------------- *
*                                                                              *
*******************************************************************************/

#ifndef __SL_H__
#define __SL_H__

#include <stddef.h>     /* size_t */

#include "dll.h"

/*******************************************************************************
*                                                                              *
* Define a structure for sorted linked list                                    *
*                                                                              *
*******************************************************************************/
typedef struct sl sl_t;

/*******************************************************************************
*                                                                              *
* Define is_before function povided by user.                                   *
* Return 1 if data1 is before data2.                                           *
*                                                                              *
*******************************************************************************/
typedef int (*sl_is_before_t)(void *data1, void *data2, void *param);

/*******************************************************************************
*                                                                              *
* Define for Action fucntion provided by user.                                 *
* Return 0 on success.                                                         *
*                                                                              *
*******************************************************************************/
typedef int (*sl_act_func_t)(void *data, void *param);

/*******************************************************************************
*                                                                              *
* Define for Compare function provided by user.                                *
* Return 0 on success.                                                         *
*                                                                              *
*******************************************************************************/
typedef int (*sl_cmp_func_t)(const void *data, void *param);

/*******************************************************************************
*                                                                              *
* Define a sorted list iterator                                                *
*                                                                              *
*******************************************************************************/
typedef struct sl_iter sl_iter_t;

/*******************************************************************************
*                                                                              *
* ------------------------- PUBLIC INTERFACE --------------------------------- *
*                                                                              *
*******************************************************************************/

/* Creates a new sorted list using an is_before func and param                */
sl_t *SLCreate(sl_is_before_t is_before_func, void *param);

/* Destroy existing sorted list                                               */
void SLDestroy(sl_t *sl);

/* Insert a new node with a new pointer to data, node will be insert according
 * to is_before function                                                      */
sl_iter_t SLInsert(sl_t *list, const void *data);

/* Remove existing node pointed by iterator iter                              */
sl_iter_t SLRemove(sl_iter_t iter);

/* Remove first node in the list and return pointer to data                   */
void *SLPopFront(sl_t *list);

/* Remove last node in the list and return pointer to data                    */
void *SLPopBack(sl_t *list);

/* Return the number of nodes in the list                                     */
size_t SLSize(const sl_t *list);

/* Check if the list is empty return 1 is list is emtpy                       */
int SLIsEmpty(const sl_t *list);

int SLForEach(sl_iter_t start, sl_iter_t end, sl_act_func_t func, void *param);

/* Find using is_before function */
sl_iter_t SLFind(sl_iter_t start, sl_iter_t end, void *data);

/* Find using cmp function */
sl_iter_t SLFindIf(sl_iter_t start, sl_iter_t end, sl_cmp_func_t func, void *param);

/* Move nodes in the range [from,to] before where node */
sl_iter_t SLMoveNodes(sl_iter_t where, sl_iter_t from, sl_iter_t to);

/* Merge two sorted list , return iterator to the head of dest list */ 
sl_iter_t SLMerge(sl_t *dest, sl_t *src);

/*******************************************************************************
*                                                                              *
* ------------------------- Sorted linked list iterator----------------------- *
*                                                                              *
*******************************************************************************/

/* Return an iterator to the first node in the list                           */  
sl_iter_t SLBegin(const sl_t *list);

/* Return an iterator to the past the end node in the list                    */
sl_iter_t SLEnd(const sl_t *list);

/* Return the previous iterator of iter                                       */
sl_iter_t SLIterPrev(sl_iter_t iter);

/* Return the Next iterator of iter                                           */
sl_iter_t SLIterNext(sl_iter_t iter);

/* Return pointer to data in iterator                                         */
void *SLIterGetData(sl_iter_t iter);

/* Check if two iterators pointing to the same node                           */
int SLIterIsEqual(sl_iter_t iter1, sl_iter_t iter2);

/*******************************************************************************
* FOR INTERNAL USAGE ONLY                                                      *
* Define a sorted list iterator.                                               *
*                                                                              *
*******************************************************************************/
struct sl_iter
{
    dll_iter_t diter;
    sl_t *list;
};

#endif /* __SL_H__ */

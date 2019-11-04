/*******************************************************************************
* Double linked list                                                           *
* @author: Maor Moyal                                                          *
*                                                                              *
* -------------------------------- dll.h ------------------------------------- *
*                                                                              *
*******************************************************************************/
#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h> /* size_t */

/*******************************************************************************
*                                                                              *
* Define a structure for node                                                  *
*                                                                              *
*******************************************************************************/
typedef struct dll_node dll_node_t;

/*******************************************************************************
*                                                                              *
* Define a structure for double linked list                                    *
*                                                                              *
*******************************************************************************/
typedef struct dll_list dll_t;

/*******************************************************************************
*                                                                              *
* Define a structure for double linked list Iterator                           *
*                                                                              *
*******************************************************************************/
typedef struct dll_iter
{
    dll_node_t* current;
    dll_t *list;
}dll_iter_t;

/*******************************************************************************
*                                                                              *
* Define an action function pointer                                            *
*                                                                              *
*******************************************************************************/
typedef int (*dll_act_func_t)(void *data, void *param);

/*******************************************************************************
*                                                                              *
* Define a compare function pointer                                            *
*                                                                              *
*******************************************************************************/
typedef int (*dll_cmp_func_t)(const void *data, void *param);


/*******************************************************************************
*                                                                              *
* ------------------------- PUBLIC INTERFACE --------------------------------- *
*                                                                              *
*******************************************************************************/

/* Create a double linked list, return list pointer                           */
dll_t* DLLCreate();

/* Destroy a double linked list                                               */
void DLLDestroy(dll_t *list);

/* Insert new node pointing to data before a node pointed by iter
 * return node pointed by iter                                                */
dll_iter_t DLLInsert(dll_iter_t iter, const void *data);

/* Remove a node pointed by iter
 * return node after the node pointed by iter or null if node is last node    */
dll_iter_t DLLRemove(dll_iter_t iter);

/* Push new node in front of a list 
 * return iterator for node after the new node                                */
dll_iter_t DLLPushFront(dll_t *list, const void *data);

/* Pop a node from the front of a list 
 * return data pointer                                                        */
void *DLLPopFront(dll_t *list);

/* Push new node in the back of a list
 * return iterator for node->next                                             */
dll_iter_t DLLPushBack(dll_t *list, const void *data);

/* Pop a node from the back 
 * return data pointer                                                        */
void *DLLPopBack(dll_t *list);

/* return the size of the list                                                */
size_t DLLSize(const dll_t *list);

/* return list state boolean                                                  */
int DLLIsEmpty(const dll_t *list);

/* Find search for first node that meet the requirements of the cmp function
 * cmp function is a compare functions provided by the user
 * find search in the range of node porvided by start and end iterators
 * param define the desirable value to found by the cmp function
 * return match iterator if the param was found or null */
dll_iter_t DLLFind(dll_iter_t start, dll_iter_t end, dll_cmp_func_t cmp_func, void * param);

/* ForEach function traversing the list from start iterator to end iterator
 * act func is a user provided function applied on each node in the above range 
 * return 0 on success, -1 on failure                                         */
int DLLForEach(dll_iter_t start, dll_iter_t end, dll_act_func_t act_func, void * param);

/* Splice function move nodes in the range [from,to) and connect them before where node
 * this function don't copy nodes from list to list, the nodes transfered to where list
 * return where iterator.                                                     */
dll_iter_t DLLSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to);


/*******************************************************************************
*                                                                              *
* ------------------------- Double linked list iterator----------------------- *
*                                                                              *
*******************************************************************************/

/* return iterator to the first element in the list                           */
dll_iter_t DLLBegin(const dll_t *list);

/* return iterator to past-the-end element in the list 
 * list boundary defined by [start,end)                                       */
dll_iter_t DLLEnd(const dll_t *list);

/* return iterator to the last element in the list                            */
dll_iter_t DLLRBegin(const dll_t *list);

/* return iterator to past-the-start element in the list
 * list boundary defined by (start,end]                                       */
dll_iter_t DLLREnd(const dll_t *list);

/* return iterator for next node of node pointed by iter                      */
dll_iter_t DLLIterNext(dll_iter_t iter);

/* return iterator for previous node of node pointed by iter                  */
dll_iter_t DLLIterPrev(dll_iter_t iter);

/* return boolean equality between two pointers                               */
int DLLIterIsEqual(dll_iter_t iter1, dll_iter_t iter2);

/* return data pointed by node pointed by iterator iter                       */
void *DLLIterGetData(dll_iter_t iter);

#endif /* __DLL_H__ */

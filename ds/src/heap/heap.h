#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>		/*size_t*/

/*  The user will receive a pointer to a
    heap (once HEAPCreate is called)            */
typedef struct heap heap_t;

/*  This function will be provided by the user  
    and must return a boolean value             */
typedef int (*is_before_t)(const void *data1, const void *data2, void *param);

/*************************************************
 *      FUNCTIONS                                *
*************************************************/
/*  The user must call this function before 
    pushing data to heap. The user must 
    provide an is_before_t function             */
heap_t *HEAPCreate(is_before_t func, void *param);

/*  The user must call this function before
    exiting the program in order to avoid 
    memory leaks.                               */
void HEAPDestroy(heap_t *heap);

/*  Addind items to heap is powered by LIFO     */
int HEAPPush(heap_t *heap, const void *data);

/*  Same as push. O(1)                          */
void HEAPPop(heap_t *heap);

/*  Selected data will be removed with a 
    complexity of O(n)                          */
void HEAPRemove(heap_t *heap, void *data);

void HEAPSort(heap_t *heap, size_t size);

/*  Highest complexity O(n)                     */
void *HEAPPeek(heap_t *heap);

/*  Complexity: O(n)                            */
size_t HEAPSize(const heap_t *heap);

/*  Complexity: O(1)                            */
int HEAPIsEmpty(const heap_t *heap);

void PrintHeap(heap_t *heap);

#endif /*__HEAP_H__*/

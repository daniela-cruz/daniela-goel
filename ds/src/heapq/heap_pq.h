#ifndef __HEAHeapQ_H__
#define __HEAHeapQ_H__

#include <stddef.h>     /* size_t */

typedef struct heap_q heap_q_t;

/*  This function will be provided by the user  
    and must return a boolean value             */
typedef int(*heapq_is_before_t)(const void *data1, const void *data2, void *param);

/*  This function will be provided by the user  
    and must return a boolean value             */
typedef int (*heapq_is_match_t)(const void *data, const void *param);

/**************************
 *      FUNCTIONS         *
**************************/
/*  The user must call this function before 
    pushing data to heap. The user must 
    provide an is_before_t function             */
heap_q_t *HeapQCreate(heapq_is_before_t func, void *func_param);

/*  The user must call this function before
    exiting the program in order to avoid 
    memory leaks.                               */
void HeapQDestroy(heap_q_t *queue);

/*  Enqueuing of a new task will be sorted
    using the user's is_before_t function
    which will determine the task's priority    */
int HeapQEnqueue(heap_q_t *queue, void *data);

/*  Dequeuing will be performed according to
    the previously set priority                 */
void *HeapQDequeue(heap_q_t *queue);

/*  Unlike HeapQDequeue, removal will disregard
    the priority of the requested task and also 
    will return the data held within the task 
    item before removal                         */
void *HeapQRemove(heap_q_t *queue, heapq_is_match_t func, void *param);

/*  Complexity: O(1)                            */
int HeapQIsEmpty(const heap_q_t *queue);

/*  The function will return the data saved in 
    the least prioritized item in queue         */
void *HeapQPeek(const heap_q_t *queue);

/*  Complexity: O(n)                            */
size_t HeapQCount(const heap_q_t *queue);

#endif /* __HEAHeapQ_H__ */

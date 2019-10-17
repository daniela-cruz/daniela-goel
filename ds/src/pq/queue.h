#ifndef __Q_H__
#define __Q_H__

#include <stddef.h> /* size_t */

#include "pq.h" /* priority queue functions*/
#include "fq.h" /* FIFO based queue */
#include "sl.h" /* sl_t and other sorted list functions */
#include "dll.h" /* the sorted list operats using doubly linked list */

enum status {SUCCESS, FAILURE};

typedef struct queue q_t;

/*		User's sorting function 										*/
typedef int (*q_cmp_func_t)(void *data, void *param);

/* 		the user will receive a pointer to the new 
 * 		memory location. If allocation fails the function
 * 		returns NULL							 						*/
q_t *QCreate(void *data, void *param);

/* 		free allocated memory
 * 		the user has to call this function in order to 
 * 		free up all allocated memory after calling create 	*/
void QDestroy(q_t *queue);

/*		insert new task to queue. Complexity: O(1) 		*/
int QEnqueue(q_t *q_element, void *data);

/*		remove task from queue. Complexity: O(1) 			*/
void *QDequeue(q_t *q_element);

/*		*/
int QIsEmpty(const q_t *queue);

/*		peek last element 											*/
void *QPeek(const q_t *queue);

size_t QCount(const q_t *queue);

q_t *QAppend(q_t *dest, q_t *src);

#endif /*__Q_H__*/

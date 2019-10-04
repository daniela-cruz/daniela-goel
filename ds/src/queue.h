#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <stddef.h> /* size_t */

enum status {SUCCESS, FAILURE};

typedef struct queue queue_t;

/* 		the user will receive a pointer to the new 
 * 		memory location. If allocation fails the function
 * 		returns NULL							 						*/
queue_t *QueueCreate();

/* 		free allocated memory
 * 		the user has to call this function in order to 
 * 		free up all allocated memory after calling create 	*/
void QueueDestroy(queue_t *q_element);

/*		insert new task to queue. COmplexity: O(1) 		*/
int QueueEnqueue(queue_t *q_element, void *data);

/*		remove task from queue. COmplexity: O(1) 		*/
queue_t *QueueDequeue(queue_t *q_element);

/*		*/
int QueueIsEmpty(const queue_t *q_element);

/*		peek last element 											*/
void *QueuePeek(const queue_t *q_element);

size_t QueueCount(const queue_t *first);

queue_t *QueueAppend(queue_t *dest, queue_t *src);

#endif /* __QUEUE_H__ */

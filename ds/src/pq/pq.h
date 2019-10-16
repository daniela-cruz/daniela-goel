#ifndef __PQ_H__
#define __PQ_H__

#include <stddef.h>

enum status {SUCCESS, FAILURE};

typedef struct priority_queue pq_t;

/*	Priority sorting function provided by user 				*/
typedef int (*pq_is_before_t)(void *data1, void *data2, void *param);

/* 		the user will receive a pointer to the new 
 * 		memory location. If allocation fails the function
 * 		returns NULL							 						*/
pq_t *PQCreate(pq_is_before_t func, void *param);

/* 		Free allocated memory
 * 		The user has to call this function in order to 
 * 		Free up all allocated memory after calling create */
void PQDestroy(pq_t *queue, void *data);

/*		Insert new task to queue									*/
int PQEnqueue(pq_t *queue, pq_t *task, void *data);

/*		Remove task from queue. 							 	*/
void *PQDequeue(pq_t *queue, pq_t *task);

/*		Check if there are any tasks left to execute 
 * 		in queue 														*/
int PQIsEmpty(const pq_t *queue);

/*		Peek at last element 										*/
void *PQPeek(const pq_t *queue);

/* 		Count number of tasks left in queue					*/
size_t PQCount(const pq_t *queue);

/*		Append queue "src" to "dest". Sort by priority		*/
pq_t *PQAppend(pq_t *dest, pq_t *src);

#endif /*__PQ_H__*/

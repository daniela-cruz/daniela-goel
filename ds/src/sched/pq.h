#ifndef __PQ_H__
#define __PQ_H__

#include <stddef.h> /* size_t */

#include "sl.h" /* sl_t and other sorted list functions */
#include "dll.h" /* the sorted list operats using doubly linked list */

enum status {SUCCESS, FAILURE};

typedef struct priority_queue pq_t;

typedef struct task
{
	void *task;
} task_t;

/*		Priority sorting function provided by user 			*/
typedef int (*pq_is_before_t)(void *data1, void *data2, void *param);

/*		Matching function by user									*/
typedef int (*pq_is_match_t)(void *data, void *param);

/* 		the user will receive a pointer to the new 
 * 		memory location. If allocation fails the function
 * 		returns NULL							 						*/
pq_t *PQCreate(pq_is_before_t func, void *param);

/* 		Free allocated memory. The user has to call 
 * 		this function in order to free up all allocated 
 * 		memory after calling create 								*/
void PQDestroy(pq_t *queue);

/*		Insert new task to queue									*/
int PQEnqueue(pq_t *queue, void *task);

/*		Remove task from queue. 							 	*/
void *PQDequeue(pq_t *queue);

/*		Check if there are any tasks left to execute 
 * 		in queue 														*/
int PQIsEmpty(const pq_t *queue);

/*		Peek at last element 										*/
void *PQPeek(const pq_t *queue);

/* 		Count number of tasks left in queue					*/
size_t PQCount(const pq_t *queue);

/*		Erase particular node in list by matching data		*/
void PQErase(pq_t *queue, pq_is_match_t func, void *param);

#endif /*__PQ_H__*/

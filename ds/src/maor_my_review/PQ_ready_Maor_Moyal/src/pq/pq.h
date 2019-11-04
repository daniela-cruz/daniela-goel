/*******************************************************************************
* Priority Queue API                                                           *
* @author: Maor Moyal                                                          *
*                                                                              *
* -------------------------------- pq.h -------------------------------------- *
*                                                                              *
*******************************************************************************/

#ifndef __PQ_H__
#define __PQ_H__

#include <stddef.h> /* size_t */

/*******************************************************************************
*                                                                              *
* Define a Priority Queue structure                                            *
*                                                                              *
*******************************************************************************/
typedef struct pq pq_t;

/*******************************************************************************
*                                                                              *
* Define an is_before compare function pointer.                                *
* Return 1 if data1 is before data2                                            *
*                                                                              *
*******************************************************************************/
typedef int(*pq_is_before_t)(void *data1, void *data2, void *param);

/*******************************************************************************
*                                                                              *
* Define for Compare function provided by user.                                *
* Return 0 on success.                                                         *
*                                                                              *
*******************************************************************************/
typedef int (*pq_is_match_t)(const void *data, void *param);

/*******************************************************************************
*                                                                              *
* ----------------------------- Public Interface ----------------------------  *
*                                                                              *
*******************************************************************************/

/* Create priority queue and return a pointer to pq                           */
pq_t *PQCreate(pq_is_before_t is_before, void *param);

/* Insert a new data specified by data pointer into queue.                      
 * Data will be inserted according to is_before function.
 * It is the reaponsibility of the caller to manage the storage associated 
 * with the data.                                                   
 * 
 * Complexity O(n)                                                            */
int PQEnqueue(pq_t *q, const void *data);

void *PQDequeue(pq_t *q);

void *PQPeek(const pq_t *q);

void *PQErase(pq_t *q, pq_is_match_t is_match, void *param);

int PQIsEmpty(const pq_t *q);

size_t PQCount(const pq_t *q);


/* Destroy pq                                                                 */
void PQDestroy(pq_t *q);


#endif /* __PQ_H__ */

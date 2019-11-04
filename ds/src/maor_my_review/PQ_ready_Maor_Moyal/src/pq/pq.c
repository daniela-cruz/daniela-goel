/*******************************************************************************
* Priority Queue                                                               *
* Implemented On a sorted double linked list                                   *
* Queue structre implemented with dummies nodes.                               *
*                                                                              *
* -------------------------------- fq.c -------------------------------------- *
*                                                                              *
*******************************************************************************/

#include <stdlib.h> /* malloc */

#include "pq.h"     /* Priority Queue API */
#include "sl.h"     /* Sorted list API    */

/*******************************************************************************
*                                                                              *
* Define a structure for priority queue.                                       *
*                                                                              *
*******************************************************************************/
struct pq
{
    sl_t *list;
    pq_is_before_t is_before;
    void *param;
};

/*******************************************************************************
*                                                                              *
* Static Functions                                                             *
*                                                                              *
*******************************************************************************/

/* Create Priority Queue */
pq_t *PQCreate(pq_is_before_t is_before, void *param)
{
    pq_t *pq = NULL;

    /* Create memory allocation for pq_t */
    pq = (pq_t *)malloc(sizeof(*pq));
    if (NULL == pq)
    {
        return NULL;
    }

    /* Create Sorted list */
    pq->list = SLCreate(is_before,param);
    if (NULL == pq->list)
    {
        /* Cleanup */
        free(pq);
        return NULL;
    }

    /* Set pq members */
    pq->is_before = is_before;
    pq->param = param;
    
    return pq;
}

int PQEnqueue(pq_t *q, const void *data)
{
    if (SLIterGetData(SLInsert(q->list, data)))
    {
        return -1;
    }
    
    return 0;
}

void *PQDequeue(pq_t *q)
{
    return SLPopFront(q->list);
}

void *PQPeek(const pq_t *q)
{
    return SLIterGetData(SLBegin(q->list));
}

void *PQErase(pq_t *q, pq_is_match_t is_match, void *param )
{
    sl_iter_t iter  = {NULL};
    void *data = NULL;
    
    /* search for param according to is_match function */
    iter = SLFindIf(SLBegin(q->list), SLEnd(q->list), is_match, param);
     
    if (SLIterIsEqual(iter,SLEnd(iter.list)))
    {
        return NULL;
    }

    /* hold data in iter */
    data = SLIterGetData(iter);
    
    /* remove selected element in case of not NULL */
    SLRemove(iter);

    return data;
}

int PQIsEmpty(const pq_t *q)
{
    return SLIsEmpty(q->list);
}

size_t PQCount(const pq_t *q)
{
    return SLSize(q->list);
}

void PQDestroy(pq_t *q)
{
    /* Destroy list */
    SLDestroy(q->list);

    /* Point to null */
    q->is_before = NULL;
    q->param     = NULL;

    /* Destroy queue */
    free(q);
}


/*******************************************************************************
* Double linked list                                                           *
* Implemented with dummies nodes                                               *
*                                                                              *
* ----------------------------- sl.c ----------------------------------------- *
*                                                                              *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "dll.h"

/*******************************************************************************
*                                                                              *
* Define a structure for node                                                  *
*                                                                              *
*******************************************************************************/
struct dll_node
{
    void* data;
    struct dll_node* next; 
    struct dll_node* prev;
};

/*******************************************************************************
*                                                                              *
* Define a structure for double linked list                                    *
*                                                                              *
*******************************************************************************/
struct dll_list
{
    dll_node_t* front;
    dll_node_t* back;
};

/*******************************************************************************
*                                                                              *
* Static Functions                                                             *
*                                                                              *
*******************************************************************************/

/* Create node */
static dll_node_t *DLLCreateNode(const void *data);

/* Free node */
static void DLLFreeNode(dll_node_t *node);

/*******************************************************************************
*                                                                              *
* Implementation                                                               *
*                                                                              *
*******************************************************************************/

/* Disconnect nodes from existing list */
void DLLDisconnectNodes(dll_iter_t from, dll_iter_t to);


/* Creates a new list and returns a pointer to it */
dll_t *DLLCreate()
{
    dll_t *new_list = NULL;

    new_list = (dll_t *) malloc(sizeof(*new_list));
    if(NULL == new_list)
    {
        return NULL;
    }
   
    /* Create dummy node for front */
    new_list->front = DLLCreateNode(NULL);
    if (NULL == new_list->front)
    {
        free(new_list);
        return NULL;
    }
    
    /* Create dummy node for back */
    new_list->back = DLLCreateNode(NULL);
    if (NULL == new_list->back)
    {
        free(new_list->front);
        free(new_list);
        return NULL;
    }
    
    /* Set dummy front and back to point each other */
    new_list->front->prev = NULL;
    new_list->front->next = new_list->back;

    new_list->back->next = NULL;
    new_list->back->prev = new_list->front;

    return new_list;
}

/* Creates a new Node and returns pointer to it */
static dll_node_t *DLLCreateNode(const void *data)
{
    dll_node_t *new_node = NULL;
    
    new_node = (dll_node_t *) malloc(sizeof(*new_node));
    if (NULL == new_node)
    {
        return NULL;
    }
     
    new_node->data = (void *)data;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

static void DLLFreeNode(dll_node_t *node)
{
    node->data = NULL;
    node->prev = node->next = NULL;
    free(node);
}

/* push node before head node and returns an iterator to the next node */
dll_iter_t DLLPushFront(dll_t *list, const void *data)
{
    assert(list);

    return DLLInsert(DLLBegin(list),data);
}
/* push node after last node and return an iterator to the next node */
dll_iter_t DLLPushBack(dll_t *list, const void *data)
{
    assert(list);

    return DLLInsert(DLLEnd(list),data);
}

void *DLLPopFront(dll_t *list)
{
    void *tmp_data = NULL;
    
    assert(list && !DLLIsEmpty(list));

    tmp_data = DLLIterGetData(DLLBegin(list));

    DLLRemove(DLLBegin(list));

    return tmp_data;
}

void *DLLPopBack(dll_t *list)
{
    void *tmp_data = NULL;
    
    assert(list && !DLLIsEmpty(list));

    tmp_data = DLLIterGetData(DLLIterPrev(DLLEnd(list)));

    DLLRemove(DLLIterPrev(DLLEnd(list)));

    return tmp_data;
}

/* DLLInsert: Insert node at current iter position
 * Return iterator that point to new node                                     */
dll_iter_t DLLInsert(dll_iter_t iter, const void *data)
{
    dll_node_t *new_node = NULL;
    
    assert(iter.current);

    /* Creates a new node */
    new_node = DLLCreateNode(data);

    /* check creation of new node */
    if (NULL == new_node)
    {
        return DLLEnd(iter.list);
    }

    new_node->prev = iter.current->prev;
    iter.current->prev = new_node;
    new_node->next = iter.current;
    new_node->prev->next = new_node;
   
    iter = DLLIterPrev(iter);
    /*iter.current = iter.current->prev;*/

    return iter;
}

dll_iter_t DLLRemove(dll_iter_t iter)
{
    dll_iter_t tmp = {NULL,NULL};
     
    /* check iter.current is NULL or list is empty */
    assert((iter.current) && (iter.list));
    
    /* hold iter next node members */
    tmp.current = iter.current->next;
    tmp.list = iter.list;
    
    /* Change pointers of next and prev nodes of current */
    iter.current->next->prev = iter.current->prev;
    iter.current->prev->next = iter.current->next;
    
    /* Free node */
    DLLFreeNode(iter.current);
    
    return tmp;
}

int DLLForEach(dll_iter_t start, dll_iter_t end, dll_act_func_t act_func, void *param)
{
    dll_iter_t iter = {NULL, NULL};
    
    for (iter = start; !DLLIterIsEqual(iter,end); iter = DLLIterNext(iter))
    {
        act_func(DLLIterGetData(iter),param);
    }

    return 0;
}

dll_iter_t DLLFind(dll_iter_t start, dll_iter_t end, dll_cmp_func_t cmp_func, void *param)
{
    dll_iter_t iter = {NULL, NULL};
    
    for (iter = start; !DLLIterIsEqual(iter, end); iter = DLLIterNext(iter))
    {
        if (0 == cmp_func(DLLIterGetData(iter),param))
        {
            return iter;
        }
    }
    
    return iter;
}

/* move elements [from,to] to where */
dll_iter_t DLLSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to)
{
    /* Disconnect nodes from source list */
    DLLDisconnectNodes(from,to);
    
    /* Connect front part of the list */
    where.current->prev->next = from.current;
    from.current->prev = where.current->prev;

    /* Connect back part of the list */
    to.current->next = where.current;
    where.current->prev = to.current;
    
    return from;
}

void DLLDisconnectNodes(dll_iter_t from, dll_iter_t to)
{
    /* Change next of previous node of from */
    from.current->prev->next = to.current->next;

    /* Change prev of next node of to */
    to.current->next->prev = from.current->prev;

    /* Set from prev to null */
    from.current->prev = NULL;

    /* Set to next to null */
    to.current->next = NULL;

}

int DLLIsEmpty(const dll_t *list)
{
    assert(list);

    return DLLIterIsEqual(DLLBegin(list),DLLEnd(list));
}

size_t DLLSize(const dll_t *list)
{
    dll_iter_t iter = {NULL,NULL};
    size_t count = 0;

    assert (list);
    for (iter = DLLBegin(list); 
            !DLLIterIsEqual(iter,DLLEnd(list)); 
            iter = DLLIterNext(iter))
    {
        count++;
    }

    return count;
}

void DLLDestroy(dll_t *list)
{
    assert (list);

    while (!DLLIsEmpty(list))
    {
        DLLPopBack(list);
    }

    free(list->front);
    list->front = NULL;

    free(list->back);
    list->back  = NULL;

    free(list);
}

/*******************************************************************************
*                                                                              *
* Double linked list Iterator functions                                        *
*                                                                              *
*******************************************************************************/

dll_iter_t DLLBegin(const dll_t *list)
{
    dll_iter_t iter = {NULL, NULL};

    iter.current = list->front->next;
    iter.list = (dll_t *) list;

    return iter;
}

dll_iter_t DLLEnd(const dll_t *list)
{
    dll_iter_t iter = {NULL, NULL};

    iter.current = list->back;
    iter.list = (dll_t *)list;

    return iter;
}

dll_iter_t DLLRBegin(const dll_t *list)
{
    dll_iter_t iter = {NULL, NULL};
    
    iter.current = list->back->prev;
    iter.list = (dll_t *)list;

    return iter;
}

dll_iter_t DLLREnd(const dll_t *list)
{
    dll_iter_t iter = {NULL, NULL};

    iter.current = list->front;
    iter.list = (dll_t *)list;

    return iter;
}

dll_iter_t DLLIterNext(dll_iter_t iter)
{
    iter.current = iter.current->next;

    return iter;
}

dll_iter_t DLLIterPrev(dll_iter_t iter)
{
    iter.current = iter.current->prev;

    return iter;
}

int DLLIterIsEqual(dll_iter_t iter1, dll_iter_t iter2)
{
    return (iter1.current == iter2.current);
}

void *DLLIterGetData(dll_iter_t iter)
{
    return iter.current->data;
}

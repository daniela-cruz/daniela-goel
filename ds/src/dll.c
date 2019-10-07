#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "dll.h"
/*
struct dll_node* XOR (dll_node *a, dll_node *b) 
{ 
    return (dll_node* ) ((uintptr_t) (a) ^ (uintptr_t) (b)); 
};
*/
struct dll_node
{
	void *data;
	struct dll_node *n_prev;
	struct dll_node *n_next;
	/*dll_node* npx;*/
};

struct dll
{
	dll_node_t *first;
	dll_node_t *last;
	size_t size;
};

/******************************************
 * dll functions: 
******************************************/
dll_t *DLLCreate()
{
	dll_t *new_dll = malloc(sizeof(*new_dll));
	dll_node_t *temp = NULL;
	
	if (NULL == new_dll)
	{
		return NULL;
	}

	temp = malloc(sizeof(*temp));
	if (NULL == temp)
	{
		free(new_dll);
		return NULL;
	}
	
	new_dll->first = temp; 
	new_dll->first->data = NULL;
	free(temp);
	
	temp = malloc(sizeof(*temp));
	if (NULL == temp)
	{
		free(new_dll);
		return NULL;
	}
	
	new_dll->last = temp;
	new_dll->last->n_next = NULL;
	new_dll->last->n_prev = new_dll->first;
	new_dll->last->data = NULL;
	new_dll->first->n_next = new_dll->last;
	new_dll->size = 0;
	
	return new_dll;
}

void DLLDestroy(dll_t *dll)
{
	free(dll);
}

dll_iter_t DLLInsert(dll_t *dll, dll_iter_t iterator, void *data)
{
	dll_node_t *new_node = NULL;
	dll_node_t *temp = NULL;
	
	new_node = malloc(sizeof(*new_node));
	if (NULL == new_node)
	{
		return NULL;
	}
	
/**/	
	return iterator = dll->back->prev;
}

dll_iter_t DLLRemove(dll_t *dll, dll_iter_t iterator);

int DLLIsEmpty(const dll_t *dll)
{
	return dll->size == 0;
}

dll_t *DLLPushBack(dll_t *dll, void *data); 

dll_t *DLLPopBack(dll_t *dll);

dll_t *DLLPushFront(dll_t *dll, void *data); 

dll_t *DLLPopFront(dll_t *dll);

size_t DLLSize(const dll_t *dll)
{
	return dll->size;
}


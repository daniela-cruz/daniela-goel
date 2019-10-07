#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "dll.h"

struct dll_node
{
	void *data;
	void *n_prev;
	void *n_next;
	dll_node* npx;
}


struct dll_node* XOR (dll_node *a, dll_node *b) 
{ 
    return (dll_node* ) ((uintptr_t) (a) ^ (uintptr_t) (b)); 
} 

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
	
	if (NULL != new_dll)
	{
		return NULL;
	}

	temp = malloc(sizeof(*temp));
	if (NULL != temp)
	{
		free(new_dll);
		return NULL;
	}
	
	new_dll->first = temp; 
	new_dll->first->data = NULL;
	free(temp);
	
	temp = malloc(sizeof(*temp));
	if (NULL != temp)
	{
		free(new_dll);
		return NULL;
	}
	
	new_dll->last = temp;
	new_dll->last->next = NULL;
	new_dll->last->prev = new_dll->first;
	new_dll->last->data = NULL;
	new_dll->first->next = new_dll->last;
	new_dll->size = 0;
	
	return new_dll;
}

void DLLDestroy(dll_t *dll)
{
	free(dll);
}

dll_iter_t DLLInsert(dll_iter_t iterator, void *data)
{
	dll_node_t *temp = NULL;
	
	temp = malloc(sizeof(*temp));
	if (NULL != new_dll)
	{
		return NULL;
	}
	
	temp->data = data;
	return iterator = temp;
}

dll_iter_t DLLRemove(dll_iter_t iterator)
{
	
}

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


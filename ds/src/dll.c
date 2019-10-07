#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "dll.h"

struct dll_node
{
	void *data;
	void *xored; /* ? */
	void *n_prev;
	void *n_next;
}

struct dll
{
	dll_node_t *first;
	dll_node_t *last;
	size_t size;
};

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
	
	new_dll->first = temp; free(temp);
	
	temp = malloc(sizeof(*temp));
	if (NULL != temp)
	{
		free(new_dll);
		return NULL;
	}
	
	new_dll->last = temp;
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
}

dll_iter_t DLLRemove(dll_iter_t iterator);

int DLLIsEmpty(const dll_t *dll);

dll_t *DLLPushBack(dll_t *dll, void *data); 

dll_t *DLLPopBack(dll_t *dll);

dll_t *DLLPushFront(dll_t *dll, void *data); 

dll_t *DLLPopFront(dll_t *dll);

size_t DLLSize(const dll_t *dll);


#include <stdio.h>  /* perror */
#include <stdint.h> /* uintptr_t for portability*/
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "dll.h"

struct dll_node
{
	void *data;
	dll_node_t *prev;
	uintptr_t npx;
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
	dll_t *dll = NULL;
	dll_node_t *new_node = NULL;
	
	dll = malloc(sizeof(*dll));
	if (NULL == dll)
	{
		return NULL;
	}
	
	dll->first = malloc(sizeof(* new_node));
	if (NULL == dll->first)
	{
		free(dll);
		return NULL;
	}
	dll->last = malloc(sizeof(* new_node)); 
	if (NULL == dll->first)
	{
		free(dll); free(dll->first);
		return NULL;
	}
	
	dll->last->prev = NULL;
	dll->first->npx = (uintptr_t)NULL ^ (uintptr_t)dll->last;
	
	dll->last->prev = dll->first;
	dll->last->npx = dll->last->prev ^ NULL;
	
	dll->size = 0;
	
	return dll;
}

void DLLDestroy(dll_t *dll)
{

}

dll_iter_t DLLInsert(dll_iter_t iterator, void *data)
{
	dll_node_t *new_node = NULL;
	dll_node_t *prev_addr = (dll_node_t *)iterator;
	dll_node_t *next_addr = (dll_node_t *)DLLIterNext(prev_addr);
	
	new_node = malloc(*new_node);
	if (NULL == new_node)
	{
		perror("Could not insert new node. ");
		return (dll_iter_t)NULL;
	}
	
	new_node->prev = prev_addr;
	new_node->npx = prev_addr ^ next_addr;
	
	next_addr->npx = new_node ^ DLLIterNext(next_addr);
	next_addr->prev = new_node;
	
	prev_addr->npx = prev_addr->prev ^ new_node;
	
	dll->size++;
	
	return (dll_iter_t)new_node;
}

void DLLRemove(dll_t *dll, dll_iter_t iterator)
{
	if ((0 != DLLIterIsEqual(dll->first->npx, iterator)) && (0 != DLLIterIsEqual(dll->last->npx, iterator)))
	{
		dll_node_t *current_node = (dll_node_t *)iterator;
		dll_node_t *prev_address = current_node->prev;
		dll_node_t *next_addr = (dll_node_t *)DLLIterNext(iterator);
		
		if (1 == dll->size)
		{
			dll->first->npx = NULL ^ dll->last;
			dll->last->prev = dll->first;
			dll->last->npx = dll->first ^ NULL;
		}
		else
		{
			prev_address->npx = prev_address->prev ^ next_addr;
			next_addr->npx = prev_address ^ (next_addr->npx ^ next_addr->prev);
		}
		
		free(current_node); 
		dll->size--;
	} 
}

int DLLIsEmpty(const dll_t *dll)
{
	return dll->size == 0;
}

dll_t *DLLPushBack(dll_t *dll, void *data)
{
	dll_node_t *new_node = DLLInsert(dll->last, data);
	
	if (NULL != new_node)
	{
		dll_node_t *prev_node = dll->back->prev;
		
		new_node->data = data;
		new_node->prev = prev_node;
		new_node->npx = prev_node ^ dll->last;
		
		dll->last->prev = new_node;
		dll->last->npx = prev_node ^ NULL;
		
		prev_node->npx = prev_node->prev ^ new_node;
		dll->size++;
	}
	
	return dll;
}

dll_t *DLLPopBack(dll_t *dll);

dll_t *DLLPushFront(dll_t *dll, void *data)
{
	dll_node_t *new_node = DLLInsert(DLLIterNext(dll->first), data);

	return dll;
}

dll_t *DLLPopFront(dll_t *dll);

size_t DLLSize(const dll_t *dll)
{
	return dll->size;
}

/***************************************
 * ITERATOR functions: 				*
***************************************/

/* the user should send an actual address of a particular node casted as an iterator */
dll_iter_t DLLIterNext(dll_iter_t iterator)
{
	dll_iter_t *it_cpy = iterator;
	
	return (dll_iter_t)(it_cpy->npx ^ it_cpy->prev);
}

dll_iter_t DLLIterPrev(dll_iter_t iterator)
{
	
	return (dll_iter_t)((dll_node_t *))iterator->prev);
}

int DLLIterIsEqual(dll_iter_t it1, dll_iter_t it2)
{
	return (it1 == it2);
}

dll_iter_t DLLBegin(const dll_t *dll)
{
	return dll->first;
}

dll_iter_t DLLEnd(const dll_t *dll)
{
	return dll->last;
}

void *DLLGetData(dll_iter_t it)
{
	dll_t *dll_node_cpy = NULL;
	
	dll_node_cpy = DLLIterPrev(it);
	dll_node_cpy = DLLIterNext(dll_node_cpy);
	
	return dll_node_cpy->data;
}

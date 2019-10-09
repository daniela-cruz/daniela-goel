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

static dll_iter_t *local_it = (dll_iter_t *)NULL;

static uintptr_t NodeAddressXOR(dll_node_t *a, dll_node_t *b)
{
	return (uintptr_t)a ^ (uintptr_t)b;
}

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
	dll->first->npx = NodeAddressXOR(NULL, dll->last);
	
	dll->last->prev = dll->first;
	dll->last->npx = NodeAddressXOR(dll->last->prev, NULL);
	
	dll->size = 0;
	
	return dll;
}

void DLLDestroy(dll_t *dll)
{
	/*
	for (; 0 < dll->size; DLLRemove(dll, ))
	{
	
	}
	*/
	free(dll);
}

dll_iter_t DLLInsert(dll_iter_t iterator, void *data)
{
	dll_node_t *new_node = NULL;
	dll_node_t *prev_addr = NULL;
	dll_node_t *next_addr = NULL;
	
	prev_addr = DLLIterPrev(iterator).curr_node_addr;
	next_addr = iterator.curr_node_addr;
	
	new_node = malloc(sizeof(*new_node));
	if (NULL == new_node)
	{
		perror("Could not insert new node. ");
		return iterator;
	}
	
	new_node->data = data;
	new_node->prev = prev_addr;
	new_node->npx = NodeAddressXOR(prev_addr, next_addr);
	
	iterator.curr_node_addr = next_addr;
	next_addr->npx = NodeAddressXOR(new_node, DLLIterNext(iterator).curr_node_addr);
	next_addr->prev = new_node;
	
	prev_addr->npx = NodeAddressXOR(prev_addr->prev, new_node);
	
	iterator.curr_node_addr = new_node;
	
	return iterator;
}

void DLLRemove(dll_t *dll, dll_iter_t iterator)
{
	dll_iter_t first_iter, last_iter;
	
	first_iter.curr_node_addr = dll->first;
	last_iter.curr_node_addr = dll->last;
	
	if ((0 != DLLIterIsEqual(first_iter, iterator)) && (0 != DLLIterIsEqual(last_iter, iterator)))
	{
		dll_node_t *current_node = iterator.curr_node_addr;
		dll_node_t *prev_address = current_node->prev;
		dll_node_t *next_addr = DLLIterNext(iterator).curr_node_addr;
		
		if (1 == dll->size)
		{
			dll->first->npx = NodeAddressXOR(NULL, dll->last);
			dll->last->prev = dll->first;
			dll->last->npx = NodeAddressXOR(dll->first, NULL);
		}
		else
		{
			prev_address->npx = NodeAddressXOR(prev_address->prev, next_addr);
			next_addr->npx = NodeAddressXOR(prev_address, (dll_node_t *)NodeAddressXOR(next_addr, next_addr->prev));
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
	dll_iter_t *iterator = NULL;
	dll_node_t *new_node = NULL;
	
	iterator = malloc(sizeof(*iterator));
	if (NULL == iterator)
	{
		return NULL;
	}
	
	iterator->curr_node_addr = dll->last;
	
	new_node = DLLInsert(*iterator, data).curr_node_addr;
	if (NULL != new_node)
	{
		dll_node_t *prev_node = dll->last->prev;
		
		new_node->data = data;
		new_node->prev = prev_node;
		new_node->npx = NodeAddressXOR(prev_node, dll->last);
		
		dll->last->prev = new_node;
		dll->last->npx = NodeAddressXOR(prev_node, NULL);
		
		prev_node->npx = NodeAddressXOR(prev_node->prev, new_node);
		dll->size++;
	}
	
	free(iterator);
	
	return dll;
}

dll_t *DLLPopBack(dll_t *dll)
{
	dll_node_t *current = dll->last->prev;
	
	dll->last->prev->prev->npx = NodeAddressXOR(dll->last->prev->prev->prev, dll->last);
	dll->last->prev = dll->last->prev->prev;
	dll->last->npx = NodeAddressXOR(dll->last->prev, NULL);
	free(current);
	
	dll->size--;
	
	return dll;
}

dll_t *DLLPushFront(dll_t *dll, void *data)
{
	dll_iter_t *iterator = NULL;
	dll_node_t *new_node = NULL;
	
	iterator = malloc(sizeof(*iterator));
	if (NULL == iterator)
	{
		perror("Iterator was not allocated ");
		return dll;
	}
	
	iterator->curr_node_addr = dll->first;
	new_node = DLLInsert(DLLIterNext(*iterator), data).curr_node_addr;
	if (NULL == new_node)
	{
		perror("new node was not pushed ");
		return dll;
	}
	
	dll->size++;
	
	return dll;
}

dll_t *DLLPopFront(dll_t *dll)
{
	dll_node_t *current = NULL;
	dll_node_t *next = NULL;
	
	current = (dll_node_t *)NodeAddressXOR(dll->first, NULL);
	next = (dll_node_t *)NodeAddressXOR(current, current->prev);
	
	dll->first->npx = NodeAddressXOR(NULL, next);
	next->prev = dll->first;
	next->npx = NodeAddressXOR(next->prev, (dll_node_t *)NodeAddressXOR(current, current->prev));
	
	free(current);
	
	dll->size--;
	
	return dll;
}

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
	iterator.curr_node_addr = 
		(dll_node_t *)NodeAddressXOR((dll_node_t *)iterator.curr_node_addr->npx, iterator.curr_node_addr->prev);
		
	return iterator;
}

dll_iter_t DLLIterPrev(dll_iter_t iterator)
{
	iterator.curr_node_addr = iterator.curr_node_addr->prev;
	
	return iterator;
}

int DLLIterIsEqual(dll_iter_t it1, dll_iter_t it2)
{
	return (it1.curr_node_addr == it2.curr_node_addr);
}

dll_iter_t DLLBegin(const dll_t *dll)
{
	dll_iter_t it;
	
	it.curr_node_addr = dll->first;
	
	return it;
}

dll_iter_t DLLEnd(const dll_t *dll)
{
	dll_iter_t it;
	
	it.curr_node_addr = dll->last;
	
	return it;
}

void *DLLGetData(dll_iter_t it)
{
	dll_node_t *dll_node_cpy = NULL;
	/*
	dll_node_cpy = it.curr_node_addr;
	dll_node_cpy = DLLIterNext(it).curr_node_addr;
	*/
	return it.curr_node_addr->data;
}

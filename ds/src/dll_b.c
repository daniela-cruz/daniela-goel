#include <stdio.h>  /* perror */
#include <stdint.h> /* uintptr_t for portability*/
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "dll_b.h"

struct dll_node
{
	void *data;
	uintptr_t npx;
};

struct dll
{
	dll_node_t *first;
	dll_node_t *last;
};

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
	
	dll->first->npx = NodeAddressXOR(NULL, dll->last);
	dll->last->npx = NodeAddressXOR(dll->first, NULL);
	
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

dll_iter_t DLLInsert(dll_iter_t iterator, const void *data)
{
	dll_node_t *new_node = NULL;
	dll_node_t *prev_addr = NULL;
	dll_node_t *next_addr = NULL;
	
	prev_addr = iterator.prev;
	next_addr = iterator.curr_node_addr;
	
	new_node = malloc(sizeof(*new_node));
	if (NULL == new_node)
	{
		perror("Could not insert new node. ");
		return iterator;
	}
	
	new_node->data = (void *)data;
	new_node->npx = NodeAddressXOR(prev_addr, next_addr);
	
	iterator.curr_node_addr = next_addr;
	next_addr->npx = NodeAddressXOR(new_node, DLLIterNext(iterator).curr_node_addr);
	prev_addr->npx = NodeAddressXOR((dll_node_t *)NodeAddressXOR((dll_node_t *)prev_addr->npx, new_node), new_node);
	
	iterator.curr_node_addr = new_node;

	return iterator;
}

dll_iter_t DLLRemove(dll_iter_t iterator)
{
	dll_node_t *curr_addr = iterator.curr_node_addr;
	dll_node_t *prev_addr = iterator.prev;
	dll_node_t *next_addr = DLLIterNext(iterator).curr_node_addr;
	
	/* if we are at the first or last nodes do nothing */
	if (((NodeAddressXOR(NULL, next_addr) == curr_addr->npx)) &&
		(NodeAddressXOR(NULL, prev_addr)== curr_addr->npx))
	{
		iterator.curr_node_addr = NULL;
		
		return iterator;
	}
	
	/* if we are at the last node but there is at least one real node */
	if ((NULL == next_addr) && (NULL != curr_addr))
	{
		next_addr->npx = (uintptr_t)prev_addr;
		prev_addr->npx = NodeAddressXOR((dll_node_t *)NodeAddressXOR((dll_node_t *)prev_addr->npx, curr_addr), next_addr);
	}
	/* if we are in the middle of the list */
	else
	{
		prev_addr->npx = NodeAddressXOR((dll_node_t *)NodeAddressXOR((dll_node_t *)prev_addr->npx, curr_addr), next_addr);
		next_addr->npx = NodeAddressXOR(prev_addr, (dll_node_t *)NodeAddressXOR(curr_addr, (dll_node_t *)next_addr->npx));
	}
	
	free(curr_addr);
	iterator.curr_node_addr = next_addr;
	iterator.prev = prev_addr;
	
	return iterator;
}

dll_iter_t DLLSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to)
{
	return where;
}

int DLLIsEmpty(const dll_t *dll)
{
	return DLLSize(dll) == 0;
}

dll_iter_t DLLPushBack(dll_t *dll, const void *data)
{
	dll_iter_t iterator = *(dll_iter_t *)0;
	dll_node_t *new_node = NULL;
	
	iterator.curr_node_addr = dll->last;
	iterator.prev = DLLIterPrev(iterator).curr_node_addr;
	
	new_node = DLLInsert(iterator, data).curr_node_addr;
	if (NULL != new_node)
	{
		new_node->data = (void *)data;
		new_node->npx = NodeAddressXOR(iterator.prev, dll->last);
		
		iterator.prev->npx = NodeAddressXOR((dll_node_t *)iterator.prev->npx, new_node);
		dll->last->npx = NodeAddressXOR(new_node, NULL);
	}
	
	return iterator;
}

void *DLLPopBack(dll_t *dll)
{
	dll_iter_t iterator = *(dll_iter_t *)0;
	dll_node_t *current = NULL;
	void *popped_data = NULL;
	
	if (dll->last->npx != NodeAddressXOR(NULL, dll->last))
	{
		iterator.curr_node_addr = dll->last;
		current = DLLIterPrev(iterator).curr_node_addr;
		popped_data = current->data;
		
		iterator.prev->npx = NodeAddressXOR(iterator.prev, current);
		
		free(current);
	}
	
	return popped_data;
}

dll_iter_t DLLPushFront(dll_t *dll, const void *data)
{
	dll_iter_t iterator = *(dll_iter_t *)0;
	dll_node_t *new_node = NULL;
	
	iterator.curr_node_addr = dll->first;
	new_node = DLLInsert(DLLIterNext(iterator), data).curr_node_addr;
	if (NULL == new_node)
	{
		iterator.curr_node_addr = NULL;
	}
	
	return iterator;
}

void *DLLPopFront(dll_t *dll)
{
	dll_node_t *current = NULL;
	dll_node_t *next = NULL;
	void *popped_data = NULL;
	
	
	/*
	current = (dll_node_t *)NodeAddressXOR(dll->first, NULL);
	next = (dll_node_t *)NodeAddressXOR(current, current->prev);
	
	dll->first->npx = NodeAddressXOR(NULL, next);
	next->prev = dll->first;
	next->npx = NodeAddressXOR(next->prev, (dll_node_t *)NodeAddressXOR(current, current->prev));
	*/
	free(current);
	
	return dll;
}

size_t DLLSize(const dll_t *dll)
{
	size_t size = 0;
	dll_node_t *from = (dll_node_t *)dll->first;
	dll_node_t *to = (dll_node_t *)dll->last;
	
	for (; from != to; to = (dll_node_t *)NodeAddressXOR(to, (dll_node_t *)to->npx), size++)
	{
	}
	
	return size;
}

/***************************************
 * ITERATOR functions: 			*
***************************************/

/* the user should send an actual address of a particular node casted as an iterator */
dll_iter_t DLLIterNext(dll_iter_t iterator)
{
	iterator.curr_node_addr = 
		(dll_node_t *)NodeAddressXOR((dll_node_t *)iterator.curr_node_addr->npx, iterator.prev);
		
	return iterator;
}

dll_iter_t DLLIterPrev(dll_iter_t iterator)
{
	iterator.prev = (dll_node_t *)NodeAddressXOR((dll_node_t *)iterator.curr_node_addr->npx, iterator.curr_node_addr);
	
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
	it.prev = DLLIterPrev(it).prev;
	
	return it;
}

void *DLLGetData(dll_iter_t it)
{
	return it.curr_node_addr->data;
}

/***************************************
 * EXTRA functions:		 				*
***************************************/
dll_iter_t DLLFind(dll_iter_t it_start, dll_iter_t it_end, dll_cmp_func_t find_func, void *param)
{
	dll_node_t *start = it_start.curr_node_addr;
	dll_node_t *end = it_end.curr_node_addr;
	void *param_cpy = (void *)param;
	
	if (start > end)
	{
		end = it_start.curr_node_addr;
		start = it_end.curr_node_addr;
	}
	
	for (; start != end; start = DLLIterNext(it_start).curr_node_addr)
	{
		if (1 == find_func(param_cpy, start->data))
		{
			it_start.curr_node_addr = start;
			break;
		}
	}
	
	if ((start != end) && (1 != find_func(param_cpy, start->data)))
	{
		printf("Parameter was not found.\n");
	}

	return it_start;
}

#include <stdio.h>  /* perror */
#include <stdint.h> /* uintptr_t for portability*/
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "dll.h"

struct dll_node
{
	void *data;
	dll_node_t *npx;
};

struct dll
{
	dll_node_t *first;
	dll_node_t *last;
};

static dll_node_t *DLLCreateNode(const void *data);
static dll_node_t *NodeXOR(dll_node_t *a, dll_node_t *b);

/******************************************
 * dll functions: 									*
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
	
	dll->first = DLLCreateNode(NULL);
	if (NULL == dll->first)
	{
		free(dll);
		return NULL;
	}
	dll->last = DLLCreateNode(NULL);
	if (NULL == dll->last)
	{
		free(dll); free(dll->first);
		return NULL;
	}
	
	dll->first->npx = dll->last;
	dll->last->npx = dll->first;
	
	return dll;
}

void DLLDestroy(dll_t *dll)
{
	for (; dll->front->npx != dll->back; DLLPopFront(dll));
	
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
	new_node->npx = NodeXOR(prev_addr, next_addr);
	
	iterator.curr_node_addr = next_addr;
	next_addr->npx = NodeXOR(new_node, DLLIterNext(iterator).curr_node_addr);
	prev_addr->npx = NodeXOR((dll_node_t *)NodeXOR((dll_node_t *)prev_addr->npx, new_node), new_node);
	
	iterator.curr_node_addr = new_node;

	return iterator;
}

dll_iter_t DLLRemove(dll_iter_t iterator)
{
	dll_node_t *curr_addr = iterator.curr_node_addr;
	dll_node_t *prev_addr = iterator.prev;
	dll_node_t *next_addr = DLLIterNext(iterator).curr_node_addr;
	
	/* if we are at the first or last nodes do nothing */
	if (((NodeXOR(NULL, next_addr) == curr_addr->npx)) &&
		(NodeXOR(NULL, prev_addr)== curr_addr->npx))
	{
		iterator.curr_node_addr = NULL;
		
		return iterator;
	}
	
	/* if we are at the last node but there is at least one real node */
	if ((NULL == next_addr) && (NULL != curr_addr))
	{
		next_addr->npx = prev_addr;
		prev_addr->npx = NodeXOR(NodeXOR(prev_addr->npx, curr_addr), next_addr);
	}
	/* if we are in the middle of the list */
	else
	{
		prev_addr->npx = NodeXOR((dll_node_t *)NodeXOR((dll_node_t *)prev_addr->npx, curr_addr), next_addr);
		next_addr->npx = NodeXOR(prev_addr, (dll_node_t *)NodeXOR(curr_addr, (dll_node_t *)next_addr->npx));
	}
	
	free(curr_addr);
	iterator.curr_node_addr = next_addr;
	iterator.prev = prev_addr;
	
	return iterator;
}

dll_iter_t DLLSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to)
{
	dll_node_t *from_next = NodeXOR(from.prev, from.curr_node_addr->npx);
	dll_node_t *to_next = NodeXOR(to.prev, to.curr_node_addr->npx);
	dll_node_t *where_next = NodeXOR(where.prev, where.curr_node_addr->npx);

	from.prev->npx = NodeXOR(NodeXOR(from.prev->npx, from.curr_node_addr), to_next);
	to_next->npx = NodeXOR(from.prev, NodeXOR(to.curr_node_addr, to_next->npx));
	
	from.curr_node_addr->npx = NodeXOR(where.prev, from_next);
	where.prev->npx = (NodeXOR(where.prev->npx, where.curr_node_addr), from.curr_node_addr);
	to.curr_node_addr->npx = NodeXOR(to.prev, where.curr_node_addr);
	where.curr_node_addr->npx = NodeXOR(to.curr_node_addr, where_next);
	
	where.curr_node_addr = where.prev;
	where.prev = NodeXOR(where.prev->npx, from.curr_node_addr);

	return where;
}


int DLLIsEmpty(const dll_t *dll)
{
	return dll->last == dll->first->npx;
}

dll_iter_t DLLPushBack(dll_t *dll, const void *data)
{
	dll_iter_t iterator = {NULL, NULL, NULL};
	dll_node_t *new_node = NULL;
	
	iterator.curr_node_addr = dll->last;
	iterator.prev = dll->last->npx;
	iterator.list = dll;
	
	new_node = DLLCreateNode(data);
	if (NULL == new_node)
	{
		iterator = DLLEnd(dll);
		
		return iterator;
	}
	
	new_node->npx = NodeXOR(iterator.prev, dll->last);
	dll->last->npx = new_node;
	iterator.prev->npx = NodeXOR(NodeXOR(iterator.prev->npx, dll->last), new_node);
	iterator.curr_node_addr = new_node;
	
	return iterator;
}

void *DLLPopBack(dll_t *dll)
{
	dll_iter_t iterator = {NULL, NULL, NULL};
	dll_node_t *to_pop = NULL;
	void *popped_data = NULL;
	
	if (dll->last->npx != dll->first)
	{
		iterator.curr_node_addr = dll->last;
		iterator.prev = dll->last->npx;
		iterator.list = dll;
		to_pop = dll->last->npx;
		popped_data = to_pop->data;
		
		
		iterator = DLLIterPrev(iterator);
		iterator.prev->npx = NodeXOR(NodeXOR(iterator.prev->npx, to_pop), dll->last);
		dll->last->npx = iterator.prev;
		
		free(to_pop);
	}
	
	return popped_data;
}

dll_iter_t DLLPushFront(dll_t *dll, const void *data)
{
	dll_iter_t iterator = {NULL, NULL, NULL};
	dll_node_t *new_node = NULL;
	
	iterator.curr_node_addr = dll->first;
	iterator.prev = NULL;
	iterator.list = dll;
	
	new_node = DLLCreateNode(data);
	if (NULL == new_node)
	{
		iterator = DLLEnd(dll);
		
		return iterator;
	}
	
	new_node->npx = NodeXOR(dll->first->npx, dll->first);
	dll->first->npx->npx = NodeXOR(NodeXOR(dll->first->npx->npx, dll->first), new_node);
	dll->first->npx = new_node;
	
	iterator.curr_node_addr = new_node;
	iterator.prev = dll->first;
	
	return iterator;
}

void *DLLPopFront(dll_t *dll)
{
	dll_node_t *to_pop = NULL;
	dll_node_t *next = NULL;
	void *popped_data = NULL;
	dll_iter_t iterator = {NULL, NULL, NULL};
	
	to_pop = dll->first->npx;
	popped_data = dll->first->npx->data;
	
	iterator.list = dll;
	iterator.curr_node_addr = dll->first->npx;
	iterator.prev = dll->first;
	
	iterator = DLLIterNext(iterator);
	dll->first->npx = iterator.curr_node_addr;
	iterator.curr_node_addr->npx = NodeXOR(NodeXOR(iterator.curr_node_addr->npx, dll->first), dll->first);
	
	free(to_pop);
	/*
	current = dll->first->npx;
	popped_data = current->data;
	next = NodeXOR(current->npx, dll->first);
	
	dll->first->npx = next;
	next->npx = NodeXOR(dll->first, NodeXOR(dll->first, next->npx));

	free(current);
	*/
	return popped_data;
}

size_t DLLSize(const dll_t *dll)
{
	size_t size = 0;
	
	dll_iter_t start = {NULL, NULL, NULL};
	dll_iter_t end = {NULL, NULL, NULL};
	
	if (1 == DLLIsEmpty(dll))
	{
		return 0;
	}
	
	for (start = DLLIterNext(DLLBegin(dll)), end = DLLIterPrev(DLLEnd(dll)); 
			!DLLIterIsEqual(start, end); size++, start = DLLIterNext(start))
	{
	}

	return size;
}

/***************************************
 * ITERATOR functions: 			*
***************************************/
dll_iter_t DLLIterNext(dll_iter_t iterator)
{
	dll_node_t *prev_n = iterator.curr_node_addr;
	
	if (iterator.curr_node_addr == iterator.list->last)
	{
		iterator = DLLEnd(iterator.list);
		
		return iterator;
	}
	/*TODO*/
	iterator.curr_node_addr = NodeXOR(iterator.prev, iterator.curr_node_addr->npx);
	iterator.prev = prev_n;
	
	return iterator;

}

dll_iter_t DLLIterPrev(dll_iter_t iterator)
{
	dll_node_t *next_node = NULL;
	
	if (iterator.list->first == iterator.prev)
	{
		iterator = DLLEnd(iterator.list);
	}
	next_node = iterator.curr_node_addr;
	
	iterator.curr_node_addr = iterator.prev;
	iterator.prev = NodeXOR(iterator.curr_node_addr->npx, next_node);
	
	return iterator;
}

int DLLIterIsEqual(dll_iter_t it1, dll_iter_t it2)
{
	return it1.curr_node_addr == it2.curr_node_addr;
}

dll_iter_t DLLBegin(const dll_t *dll)
{
	dll_iter_t iterator = {NULL, NULL, NULL};
	
	iterator.list = (dll_t *)dll;
	iterator.curr_node_addr = dll->first;
	iterator.prev = NULL;
	
	return iterator;
}

dll_iter_t DLLEnd(const dll_t *dll)
{
	dll_iter_t iterator = {NULL, NULL, NULL};
	
	iterator.curr_node_addr = NULL; 
	iterator.prev = dll->last;
	iterator.list = (dll_t *)dll;
	
	return iterator;
}

void *DLLGetData(dll_iter_t it)
{
	return it.curr_node_addr->data;
}

/***************************************
 * EXTRA functions:		 			*
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

int DLLForEach(dll_iter_t from, dll_iter_t to, dll_act_func_t func, void *param) 
{ 	
	for (; !DLLIterIsEqual(from, to); from = DLLIterNext(from)) 	
	{ 		
		if (func((from.curr)->data, param)) 		
		{ 			
			return 1; 		
		} 	
	} 		
	
	return 0; 
}

/***************************************
 * Internal functions:			 			*
***************************************/
static dll_node_t *DLLCreateNode(const void *data)
{
	dll_node_t *node = NULL;
	
	node = malloc(sizeof(*node));
	if (NULL != node)
	{
		node->data = (void *)data;
		node->npx = NULL;
	}
	
	return node;
}

static dll_node_t *NodeXOR(dll_node_t *a, dll_node_t *b)
{
	return (dll_node_t *)((uintptr_t)a ^ (uintptr_t)b);
}

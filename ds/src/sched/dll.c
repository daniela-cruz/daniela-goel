#include <stdint.h> /* uintptr_t for portability*/
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* asert */

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
	for (; dll->first->npx != dll->last; DLLPopFront(dll));
	
	free(dll->last);
	free(dll->first);
	free(dll);
}

dll_iter_t DLLInsert(dll_iter_t iterator, const void *data)
{
	dll_node_t *new_node = NULL;
	
	new_node = DLLCreateNode(data);
	if (NULL == new_node)
	{
		return DLLEnd(iterator.list);
	}
	
	if (iterator.curr_node == iterator.list->first)
	{
		iterator = DLLIterNext(iterator);
	}
	
	new_node->npx = NodeXOR(iterator.prev, iterator.curr_node);
	iterator.prev->npx = NodeXOR(NodeXOR(iterator.prev->npx, iterator.curr_node), new_node);
	iterator.curr_node->npx = NodeXOR(NodeXOR(iterator.curr_node->npx, iterator.prev), new_node);
	
	iterator.curr_node = new_node;
	
	return iterator;
}

dll_iter_t DLLRemove(dll_iter_t iterator)
{
	dll_node_t *curr_addr = iterator.curr_node;
	dll_node_t *prev_addr = iterator.prev;
	dll_node_t *next_addr = DLLIterNext(iterator).curr_node;
	
	/* if we are at the first or last nodes do nothing */
	if (((NodeXOR(NULL, next_addr) == curr_addr->npx)) &&
		(NodeXOR(NULL, prev_addr)== curr_addr->npx))
	{
		iterator.curr_node = NULL;
		
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
		prev_addr->npx = 
			NodeXOR((dll_node_t *)NodeXOR((dll_node_t *)prev_addr->npx, curr_addr), next_addr);
		next_addr->npx = 
			NodeXOR(prev_addr, (dll_node_t *)NodeXOR(curr_addr, (dll_node_t *)next_addr->npx));
	}
	
	free(curr_addr);
	iterator.curr_node = next_addr;
	iterator.prev = prev_addr;
	
	return iterator;
}

int DLLIsEmpty(const dll_t *dll)
{
	return dll->last == dll->first->npx;
}

dll_iter_t DLLPushBack(dll_t *dll, const void *data)
{
	dll_iter_t iterator = {NULL, NULL, NULL};
	dll_iter_t it_prev = {NULL, NULL, NULL};
	dll_node_t *new_node = NULL;
	
	iterator.curr_node = dll->last;
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
	
	it_prev.curr_node = iterator.prev;
	it_prev.curr_node->npx = NodeXOR(NodeXOR(iterator.prev->npx, iterator.curr_node), new_node);
	/*
	iterator.prev->npx = NodeXOR(NodeXOR(iterator.prev->npx, dll->last), new_node);
	*/
	iterator.curr_node = new_node;
	
	return iterator;
}

void *DLLPopBack(dll_t *dll)
{
	dll_node_t *to_pop = NULL;
	void *popped_data = NULL;
	dll_iter_t iterator = DLLIterPrev(DLLEnd(dll));
	
	if (dll->last->npx != dll->first)
	{
		to_pop = iterator.curr_node;
		popped_data =to_pop->data;
		
		iterator.list = dll;
		
		iterator = DLLIterPrev(iterator);
		iterator.curr_node->npx = NodeXOR(NodeXOR(iterator.curr_node->npx, to_pop), dll->last);
		
		dll->last->npx = iterator.curr_node;
		
		free(to_pop);
	}
	
	return popped_data;
}

dll_iter_t DLLPushFront(dll_t *dll, const void *data)
{
	dll_iter_t iterator = {NULL, NULL, NULL};
	dll_node_t *new_node = NULL;
	
	iterator.curr_node = dll->first;
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
	
	iterator.curr_node = new_node;
	iterator.prev = dll->first;
	
	return iterator;
}

void *DLLPopFront(dll_t *dll)
{
	dll_node_t *to_pop = NULL;
	void *popped_data = NULL;
	dll_iter_t iterator = {NULL, NULL, NULL};
	
	if (dll->first->npx != dll->last)
	{
		to_pop = dll->first->npx;
		popped_data = dll->first->npx->data;
		
		iterator.list = dll;
		iterator.curr_node = dll->first->npx;
		iterator.prev = dll->first;
		
		iterator = DLLIterNext(iterator);
		iterator.curr_node->npx = NodeXOR(NodeXOR(iterator.curr_node->npx, to_pop), dll->first);
		
		dll->first->npx = iterator.curr_node;
		
		free(to_pop);
	}
	
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
	
	for (start = DLLBegin(dll), end = DLLEnd(dll); 
			!DLLIterIsEqual(DLLIterNext(start), end); size++, start = DLLIterNext(start))
	{
	}

	return size;
}

/***************************************
 * ITERATOR functions: 			*
***************************************/
dll_iter_t DLLIterNext(dll_iter_t iterator)
{
	dll_node_t *prev_n = iterator.curr_node;
	
	if (iterator.curr_node == iterator.list->last)
	{
		iterator = DLLEnd(iterator.list);
		
		return iterator;
	}
	
	iterator.curr_node = NodeXOR(iterator.prev, iterator.curr_node->npx);
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
	next_node = iterator.curr_node;
	
	iterator.curr_node = iterator.prev;
	iterator.prev = NodeXOR(iterator.curr_node->npx, next_node);
	
	return iterator;
}

int DLLIterIsEqual(dll_iter_t it1, dll_iter_t it2)
{
	return it1.curr_node == it2.curr_node;
}

dll_iter_t DLLBegin(const dll_t *dll)
{
	dll_iter_t iterator = {NULL, NULL, NULL};
	
	iterator.list = (dll_t *)dll;
	iterator.curr_node = dll->first->npx;
	iterator.prev = dll->first;
	
	return iterator;
}

dll_iter_t DLLEnd(const dll_t *dll)
{
	dll_iter_t iterator = {NULL, NULL, NULL};
	
	iterator.curr_node = dll->last; 
	iterator.prev = dll->last->npx;
	iterator.list = (dll_t *)dll;
	
	return iterator;
}

void *DLLGetData(dll_iter_t it)
{
	return it.curr_node->data;
}

/***************************************
 * 		EXTRA functions:		 	*
***************************************/
dll_iter_t DLLFind(dll_iter_t it_start, dll_iter_t it_end, dll_cmp_func_t find_func, void *param)
{
	void *param_cpy = (void *)param;
	
	for (; !DLLIterIsEqual(it_start, it_end); it_start = DLLIterNext(it_start))
	{
		if (1 == find_func(param_cpy, it_start.curr_node->data))
		{
			return it_start;
		}
	}

	return DLLEnd(it_start.list); 
}

int DLLForEach(dll_iter_t from, dll_iter_t to, dll_act_func_t func, void *param)
{
	for (; 0 != DLLIterIsEqual(from, to); from = DLLIterNext(from))
	{
		if (1 == func((from.curr_node)->data, param))
		{
			return 1;
		}
	}
	
	return 0;
}

dll_iter_t DLLSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to)
{
	where.prev->npx = NodeXOR(DLLIterPrev(where).prev, from.curr_node);
	from.curr_node->npx = NodeXOR(NodeXOR(from.curr_node->npx, from.prev), where.prev);
	where.curr_node->npx = NodeXOR(NodeXOR(where.curr_node->npx, where.prev), to.curr_node);
	to.curr_node->npx = NodeXOR(to.prev, where.curr_node);

	return from;
}
/*******Internal functions:*********/
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

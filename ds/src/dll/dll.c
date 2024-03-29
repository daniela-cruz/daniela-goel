#include <stdint.h> /* uintptr_t for portability*/
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* asert */

#include "dll.h" /* all functions below */

struct dll_node
{
	void *data;
	dll_node_t *npx;
};

struct dll
{
	dll_node_t first;
	dll_node_t last;
};

static dll_node_t *DLLCreateNode(const void *data);
static dll_node_t *NodeXOR(dll_node_t *a, dll_node_t *b);

/******dll functions:********/
dll_t *DLLCreate()
{
	dll_t *dll = NULL;
	
	dll = malloc(sizeof(*dll));
	if (NULL == dll)
	{
		return NULL;
	}
	
	dll->first.npx = &dll->last;
	dll->last.npx = &dll->first;
	
	return dll;
}

void DLLDestroy(dll_t *dll)
{
	for (; dll->first.npx != &dll->last; DLLPopFront(dll));
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
	
	new_node->npx = NodeXOR(iterator.prev, iterator.curr_node);
	iterator.prev->npx = NodeXOR(NodeXOR(iterator.prev->npx, iterator.curr_node), new_node);
	iterator.curr_node->npx = NodeXOR(NodeXOR(iterator.curr_node->npx, iterator.prev), new_node);
	iterator.curr_node = new_node;
	
	return iterator;
}

dll_iter_t DLLRemove(dll_iter_t iterator)
{
	dll_node_t *next_addr = DLLIterNext(iterator).curr_node;
	
	if (1 == DLLIterIsEqual(iterator, DLLEnd(iterator.list)) || (1 == DLLIsEmpty(iterator.list)))
	{
		return DLLEnd(iterator.list);
	}
	
	iterator.prev->npx = NodeXOR(next_addr, NodeXOR(iterator.prev->npx, iterator.curr_node));
	next_addr->npx = NodeXOR(iterator.prev, NodeXOR(next_addr->npx, iterator.curr_node));
	
	free(iterator.curr_node);
	iterator.curr_node = next_addr;
	
	return iterator;
}

int DLLIsEmpty(const dll_t *dll)
{
	return dll->first.npx == &dll->last;
}

dll_iter_t DLLPushBack(dll_t *dll, const void *data)
{
	assert(NULL != dll);
	
	return DLLInsert(DLLEnd(dll),data);
}

void *DLLPopBack(dll_t *dll)
{
	void *popped_data = NULL;
	
	assert(NULL != dll);
	popped_data = DLLGetData(DLLIterPrev(DLLEnd(dll)));
	DLLRemove(DLLIterPrev(DLLEnd(dll)));
	
	return popped_data;
}

dll_iter_t DLLPushFront(dll_t *dll, const void *data)
{
	assert(NULL != dll);
	
	return DLLInsert(DLLBegin(dll),data);
}

void *DLLPopFront(dll_t *dll)
{
	void *popped_data = NULL;
	
	assert(NULL != dll);
	popped_data = DLLGetData(DLLBegin(dll));
	DLLRemove(DLLBegin(dll));
	
	return popped_data;
}

size_t DLLSize(const dll_t *dll)
{
	size_t size = 0;
	dll_iter_t start = {NULL, NULL, NULL};
	dll_iter_t end = {NULL, NULL, NULL};
	
	assert(NULL != dll);
	if (1 == DLLIsEmpty(dll))
	{
		return 0;
	}
	
	for (start = DLLBegin(dll), end = DLLEnd(dll), size = 1; 
			!DLLIterIsEqual(DLLIterNext(start), end); size++, start = DLLIterNext(start));

	return size;
}

/******ITERATOR functions:******/
/*dll_iter_t DLLIterNext(dll_iter_t iterator)
{
	dll_node_t *prev_n = iterator.curr_node;
	
	if (iterator.curr_node == &iterator.list->last)
	{
		return DLLEnd(iterator.list);
	}
	
	iterator.curr_node = NodeXOR(iterator.prev, iterator.curr_node->npx);
	iterator.prev = prev_n;
	
	return iterator;
}*/

dll_iter_t DLLIterNext(dll_iter_t iter)
{
	dll_node_t *temp = iter.prev;
	
	if (!DLLIterIsEqual(iter,DLLEnd(iter.list)))
	{
		iter.prev = iter.curr_node;
		iter.curr_node = NodeXOR(temp, (iter.curr_node)->npx);
	}
	
	return iter;
}


dll_iter_t DLLIterPrev(dll_iter_t iterator)
{
	dll_node_t *next_node = NULL;
	
	if (&iterator.list->first == iterator.prev)
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
	iterator.curr_node = dll->first.npx;
	iterator.prev = (dll_node_t *)&dll->first;
	
	return iterator;
}

dll_iter_t DLLEnd(const dll_t *dll)
{
	dll_iter_t iterator = {NULL, NULL, NULL};
	
	iterator.curr_node = (dll_node_t *)&dll->last; 
	iterator.prev = dll->last.npx;
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
	dll_node_t *from_next = DLLIterNext(from).curr_node;
	dll_node_t *to_next = DLLIterNext(to).curr_node;
	dll_node_t *where_next = DLLIterNext(where).curr_node;
	
	from.prev->npx = NodeXOR(NodeXOR((from.prev)->npx, from.curr_node) , to_next);
	to_next->npx = NodeXOR(from.prev, NodeXOR(to_next->npx, to.curr_node));  
	
	if (DLLIterIsEqual(to, DLLEnd(to.list)) && (!DLLIterIsEqual(to, from)))
	{
		to = DLLIterPrev(to);
	}
	
	if (DLLIterIsEqual(to, from))
	{
		from_next = to_next;
		to_next = where.curr_node;
		from.prev = to.prev = where.prev;
	}
	
	from.prev = where.prev;
	
	to.curr_node->npx = NodeXOR(to.prev, where.curr_node);
	from.curr_node->npx = NodeXOR(from.prev, from_next);
	from.prev->npx = NodeXOR(NodeXOR((where.prev)->npx, where.curr_node), from.curr_node);

	where.curr_node->npx = NodeXOR(to.curr_node, where_next);
	where.prev = to.curr_node;
	
	return DLLIterPrev(from);
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


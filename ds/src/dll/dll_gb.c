#include <stdlib.h> /*   malloc  */
#include <stdint.h> /* uintptr_t */
#include <assert.h> /*   assert  */

#include "dll.h"
/* -------------------- Prototypes ---------------------*/

/* Helper function that returns the xor of <x> with <y> */
static dll_node_t* XOR(dll_node_t *x, dll_node_t *y);

/* Helper to create a new dll_node_t 					*/
static dll_node_t *CreateDLLNode(const void *data);

/* -------------------- Structures ---------------------*/

struct dll
{
	dll_node_t *front;
	dll_node_t *back;
};

struct dll_node
{
	void *data;
	dll_node_t *npx;
};

/* ---------------------- DLL API ----------------------*/

dll_t *DLLCreate()
{
	dll_t *dll = malloc(sizeof(*dll));
	if(NULL == dll)
	{
		return NULL;
	}
	
	dll->front = malloc(sizeof(*dll->front));
	if(NULL == dll)
	{
		free(dll);
		return NULL;
	}
	
	dll->back = malloc(sizeof(*dll->back));
	if(NULL == dll)
	{
		free(dll->front);
		free(dll);
		return NULL;
	}
	
	dll->front->npx = dll->back;
	dll->front->data = NULL;
	dll->back->npx = dll->front;
	dll->back->data = NULL;
	
	return dll;
}

dll_iter_t DLLInsert(dll_iter_t iter, const void *data)
{
	dll_iter_t new_iter = DLLEnd(iter.list);
	dll_node_t *new_node = NULL;

	dll_node_t *prev = iter.prev;
	dll_node_t *curr = iter.curr;
	dll_node_t *next = XOR(iter.prev, curr->npx);
	
	new_node = CreateDLLNode(data);
	if(NULL == new_node)
	{
		return new_iter;
	}

	new_iter.curr = new_node;
	new_iter.prev = iter.prev;
	new_iter.list = iter.list;
	
	new_node->npx = XOR(prev, curr);
	curr->npx = XOR(new_node, next);
	prev->npx = XOR(XOR(prev->npx, curr), new_node);
	
	return new_iter;
}

dll_iter_t DLLRemove(dll_iter_t iter)
{
	dll_iter_t new_iter;
	dll_node_t *removed_node = iter.curr;
	dll_node_t *next = XOR(iter.prev, (iter.curr)->npx);
	dll_node_t *prev = iter.prev;

	if(DLLIterIsEqual(DLLEnd(iter.list), iter))
	{
		return DLLEnd(iter.list);
	}

	new_iter.curr = next;
	new_iter.prev = prev;
	new_iter.list = iter.list;

	prev->npx = XOR(XOR(prev->npx, removed_node), next);
	next->npx = XOR(prev, XOR(removed_node, next->npx));
	
	free(removed_node);
	
	return new_iter;
}

dll_iter_t DLLPushFront(dll_t *dll, const void *data)
{
	assert(NULL != dll);

	return DLLInsert(DLLBegin(dll), data);
}

dll_iter_t DLLPushBack(dll_t *dll, const void *data)
{
	assert(NULL != dll);
	
	return DLLInsert(DLLEnd(dll), data);
}

void *DLLPopFront(dll_t *dll)
{
	void *data = DLLIterGetData(DLLBegin(dll));

	assert(NULL != dll);
	
	DLLRemove(DLLBegin(dll));
	
	return data;
}

void *DLLPopBack(dll_t *dll)
{
	void *data = DLLIterGetData(DLLIterPrev(DLLEnd(dll)));

	assert(NULL != dll);
	
	DLLRemove(DLLIterPrev(DLLEnd(dll)));
	
	return data;
}

size_t DLLSize(const dll_t *dll)
{
	dll_iter_t start;
	size_t size = 0;
	
	assert(NULL != dll);

	for (start = DLLBegin(dll); !DLLIterIsEqual(start, DLLEnd(dll)); start = DLLIterNext(start))
	{
		size++;
	}
	
	return size;
}

int DLLIsEmpty(const dll_t *dll)
{
	assert(NULL != dll);
	
	return dll->front->npx == dll->back;
}

dll_iter_t DLLFind(dll_iter_t from, dll_iter_t to, dll_cmp_func_t func, void *param)
{
	assert(NULL != from.curr);
	
	for (; !DLLIterIsEqual(from, to); from = DLLIterNext(from))
	{
		if (func((from.curr)->data, param))
		{
			return from;
		}
	}
	
	return DLLEnd(from.list);
}

int DLLForEach(dll_iter_t from, dll_iter_t to, dll_act_func_t func, void *param)
{
	assert(NULL != from.curr);
	
	for (; !DLLIterIsEqual(from, to); from = DLLIterNext(from))
	{
		if (func((from.curr)->data, param))
		{
			return 1;
		}
	}
	
	return 0;
}

dll_iter_t DLLBegin(const dll_t *dll)
{
	dll_iter_t iter;

	assert(NULL != dll);
	
	iter.curr = dll->front->npx;
	iter.prev = dll->front;
	iter.list = (dll_t *)dll;
	
	return iter;
}

dll_iter_t DLLEnd(const dll_t *dll)
{
	dll_iter_t iter;
	
	assert(NULL != dll);
	
	iter.curr = dll->back;
	iter.prev = dll->back->npx;
	iter.list = (dll_t *)dll;
	
	return iter;
}

dll_iter_t DLLSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to)
{
	dll_node_t *where_next = XOR(where.prev, where.curr->npx);

	from.prev->npx = XOR(XOR(from.prev->npx, from.curr), to.curr);
	to.curr->npx = XOR(from.prev, XOR(to.prev, to.curr->npx));
	
	where.prev->npx = XOR(XOR(where.prev->npx, where.curr), from.curr);
	where.curr->npx = XOR(to.prev, where_next);
	from.curr->npx = XOR(where.prev, XOR(from.prev, from.curr->npx));
	to.prev->npx = XOR(XOR(to.prev->npx, to.curr), where.curr);
	
	where.curr = from.curr;

	return where;
}

void DLLDestroy(dll_t *dll)
{
	assert(NULL != dll);
	
	for (; !DLLIsEmpty(dll); DLLPopFront(dll));
	
	free(dll->front);
	free(dll->back);
	free(dll);
}

/* ----------------- DLL Iterator API ------------------*/

dll_iter_t DLLIterNext(dll_iter_t iter)
{
	dll_node_t *temp = iter.curr;
	
	assert(NULL != iter.curr);
	
	iter.curr = XOR(iter.prev, (iter.curr)->npx);
	iter.prev = temp;
	
	return iter;
}

dll_iter_t DLLIterPrev(dll_iter_t iter)
{
	dll_node_t *temp = iter.prev;
	
	assert(NULL != iter.curr);
	
	iter.prev = XOR((iter.prev)->npx, iter.curr);
	iter.curr = temp;
	
	return iter;
}

int DLLIterIsEqual(dll_iter_t iter1, dll_iter_t iter2)
{
	return iter1.curr == iter2.curr;
}

void *DLLIterGetData(dll_iter_t iter)
{
	assert(NULL != iter.curr);
	
	return iter.curr->data;
}

/* ---------------------- Helpers ----------------------*/

static dll_node_t *XOR(dll_node_t *x, dll_node_t *y)
{
	return (dll_node_t *)((uintptr_t)(x) ^ (uintptr_t)(y));
}

static dll_node_t *CreateDLLNode(const void *data)
{
	dll_node_t *node = malloc(sizeof(*node));
	if (NULL == node)
	{
		return NULL;
	}
	
	node->data = (void *)data;
	node->npx = NULL;
	
	return node;
}

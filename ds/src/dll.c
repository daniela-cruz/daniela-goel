#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "dll.h"

struct dll_node
{
	void *data;
	dll_node *npx;
};

struct dll
{
	dll_node_t *first;
	dll_node_t *last;
	size_t size;
};

static dll_iter_t GetNextAddressIterator(dll_t *prev_address, dll_t *cur_address);
static dll_node_t *AddressXOR (dll_node_t *prev_addr, dll_node_t *next_addr);
static dll_node_t *CreateNewNode(void *data); /*?*/

/******************************************
 * dll functions: 
******************************************/
dll_t *DLLCreate()
{
	dll_t *dll = NULL;
	dll_node_t *new_node = NULL, *new_node_2 = NULL;
	
	dll = malloc(sizeof(*dll));
	if (NULL == dll)
	{
		return NULL;
	}
	
	/* create node for first and last */
	new_node = malloc(sizeof(*new_node));
	if (NULL == new_node)
	{
		free(dll);
		return NULL;
	}
	dll->last = new_node;
	dll->last->npx = NULL ^ new_node; 
	dll->last->data = NULL;
	
	new_node_2 = malloc(sizeof(*new_node_2));
	if (NULL == new_node_2)
	{
		free(new_node);
		free(dll);
		return NULL;
	}
	dll->first = new_node_2;
	dll->first->npx = NULL ^ dll->last;
	dll->first->data = NULL;
	
	dll->size = 0;
	
	return dll;
}

void DLLDestroy(dll_t *dll)
{
	free(dll);
}

dll_iter_t DLLInsert(dll_t *dll, dll_iter_t iterator, void *data)
{
	dll_node_t *new_node = NULL;
	
	new_node = malloc(sizeof(*new_node));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = NULL;
	new_node->npx = AddressXOR(&dll->first, NULL);	
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

/***************************************
 * Internal functions: 						*
***************************************/
static dll_iter_t GetNextAddressIterator(dll_t *prev_address, dll_t *cur_address)
{
	dll_iter_t it = 0;
	
	return it;
}

static dll_node_t *AddressXOR (dll_node_t *prev_addr, dll_node_t *next_addr) 
{ 
    return (dll_node_t *) ((uintptr_t) (prev_addr) ^ (uintptr_t) (next_addr)); 
} 

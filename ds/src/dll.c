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
	dll_iter_t *iterator;
	size_t size;
};

dll_t *DLLCreate()
{
	dll_t *new_dll = malloc(*new_dll);
}


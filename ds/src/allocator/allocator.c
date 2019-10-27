#include <stddef.h> /* size_t */

#include "allocator.h"

struct allocator
{
	size_t block_size;
	size_t block_num;
};

alloc_t *ALInit(void *buffer, size_t block_size, size_t block_num)
{
	size_t struct_size = sizeof(*allocator);
	return allocator;
}

void ALDestroy(alloc_t *allocated_space);

void *ALallocator(alloc_t *allocated_space, void *element);

void ALFree(alloc_t *, void *);

size_t ALCountFreeBlocks(alloc_t *allocated_space);

size_t ALSuggest(size_t block_num, size_t block_size);

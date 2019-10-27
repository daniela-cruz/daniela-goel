#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include <stddef.h> /* size_t */

typedef struct allocator alloc_t;

alloc_t *ALInit(void *buffer, size_t block_size, size_t block_num);

void ALDestroy(alloc_t *allocated_space);

void *ALallocator(alloc_t *allocated_space, void *element);

void ALFree(alloc_t *, void *);

size_t ALCountFreeBlocks(alloc_t *allocated_space);

size_t ALSuggest(size_t block_num, size_t block_size);

#endif /* __ALLOCATOR_H__ */

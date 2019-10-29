#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "allocator.h"

struct fsa
{
	size_t next_free;
};

static size_t InitBlocks(fsa_t *allocator);

const size_t block_header_size = sizeof(size_t);

/********************************
 * 	IMPLEMENTATION: 	*
********************************/
fsa_t *FSAInit(void *buffer, size_t buff_size, size_t block_size)
{
	fsa_t *allocator = NULL;
	size_t i = 0;
	
	assert(NULL != buffer);
	allocator = (fsa_t *)buffer;
	allocator->next_free = offsetof(fsa_t, next_free);
	
	for (i = 0; i < (buff_size - offsetof(fsa_t, next_free) / block_size) - 1; i++)
	{
		allocator->next_free + (i * block_size) = ((i + 1) * block_size);
	}
	
	allocator->next_free + ((i + 1) * block_size) = 0;
		
	return allocator;
}

void FSADestroy(fsa_t *fsa)
{
	assert(NULL != fsa);
}

void *FSAalloc(fsa_t *fsa)
{
	char *new_element = 0;
	size_t new_offset = 0;
	
	assert(NULL != fsa);
	new_element = (char *)fsa + fsa->next_free + block_header_size;
	fsa->next_free = *(size_t *)(new_element - block_header_size);
	
	return (void *)new_element;
}

void FSAFree(void *block)
{
	fsa_t *fsa_next_free = NULL;
	char *block_cpy = NULL;
	
	assert(NULL != block);
	block_cpy = (char *)block;
	fsa_next_free = block_cpy - (*(size_t *)(block_cpy - block_header_size));
	*(size_t *)(block_cpy - block_header_size) = fsa_next_free;
	fsa_next_free = block_cpy;
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t free_blocks_ctr = 0;
	size_t i = 0;
	fsa_t *fsa_cpy = (fsa_t *)fsa;
	char *block = NULL;
	
	assert(NULL != fsa);
	for (i = 0, block = (char *)fsa_cpy + offsetof(fsa_t, next_free); i < fsa_cpy->block_num; i++)
	{
		(0 != (*(fsa->buff_start + (i * fsa->block_size) - block_header_size))) ? 
			free_blocks_ctr++ : free_blocks_ctr;
	}
	
	return free_blocks_ctr;
}

size_t FSASuggest(size_t block_num, size_t block_size)
{
	return sizeof(fsa_t *) + (block_num * (block_size + sizeof(block_header_size)));
}

/********************************
 * INTERNFSA FUNCS: 	*
********************************/
/*static size_t InitBlocks(fsa_t *allocator)
{
	size_t i = 0;
	char *block = NULL;
	
	assert(NULL != allocator);
	block = (char *)allocator + offsetof(fsa_t, buff_start) - block_header_size;
	
	for (i = 0; i < allocator->block_num - 1; i++)
	{
		*(size_t *)(block + (i * allocator->block_size)) = (i * allocator->block_size) + block_header_size;
	}
	
	*(block + ((i + 1) * allocator->block_size)) = block_header_size;
	
	return offsetof(fsa_t, buff_start) + block_header_size;
}*/

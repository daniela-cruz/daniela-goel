#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "allocator.h"

struct fsa
{
	size_t block_size;
	size_t block_num;
	char *next_free;
	char *buff_start;
};

static size_t InitBlocks(fsa_t *allocator);

const size_t block_header_size = sizeof(size_t);

/********************************
 * 	IMPLEMENTATION: 	*
********************************/
fsa_t *FSAInit(void *buffer, size_t buff_size, size_t block_size)
{
	fsa_t *allocator = NULL;
	
	assert(NULL != buffer);
	allocator = (fsa_t *)buffer;
	
	allocator->block_size = block_size + block_header_size;
	allocator->block_num = (buff_size - sizeof(*allocator)) / block_size;
	allocator->buff_start = (char *)buffer + offsetof(fsa_t, next_free) + block_header_size;
	InitBlocks(allocator);
	allocator->next_free = (char *)buffer + offsetof(fsa_t, next_free) + block_header_size; 
	
	return allocator;
}

void FSADestroy(fsa_t *fsa)
{
	assert(NULL != fsa);
}

void *FSAalloc(fsa_t *fsa)
{
	void *element = NULL;
	
	assert(NULL != fsa);
	element = fsa->next_free;
	*(size_t*)((char *)element - block_header_size) = -1;
			
	return element;
}

void FSAFree(void *block)
{
	*(size_t*)((char *)block - block_header_size) = 0;
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t free_blocks_ctr = 0;
	size_t i = 0;
	fsa_t *fsa_cpy = (fsa_t *)fsa;
	
	assert(NULL != fsa);
	for (i = 0; i < fsa_cpy->block_num; i++)
	{
		(0 == (*(fsa->buff_start + (i * fsa->block_size) - block_header_size))) ? 
			free_blocks_ctr++ : free_blocks_ctr;
	}
	
	return free_blocks_ctr;
}

size_t FSASuggest(size_t block_num, size_t block_size)
{
	size_t suggested_size = 0;
	
	suggested_size = sizeof(fsa_t *) + (block_num * (block_size + sizeof(size_t)));
	
	return suggested_size;
}

/********************************
 * INTERNFSA FUNCS: 	*
********************************/
static size_t InitBlocks(fsa_t *allocator)
{
	size_t i = 0;
	
	for (i = 0; i < allocator->block_num; i ++)
	{
		*(allocator->buff_start + (i * allocator->block_size) - block_header_size) = 0;
	}
	
	return offsetof(fsa_t, buff_start) + block_header_size;
}
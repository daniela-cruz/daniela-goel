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
	allocator->block_num = ((buff_size - offsetof(fsa_t, next_free)) / (allocator->block_size)) + 1;
	allocator->buff_start = (char *)buffer + offsetof(fsa_t, buff_start) + block_header_size;
	InitBlocks(allocator);
	allocator->next_free = (char *)buffer + offsetof(fsa_t, buff_start) + block_header_size; 
	
	return allocator;
}

void FSADestroy(fsa_t *fsa)
{
	assert(NULL != fsa);
}

void *FSAalloc(fsa_t *fsa)
{
	char *new_element = NULL;
	size_t next_free_offset = 0;
	size_t element_header = 0;
	
	assert(NULL != fsa);
	new_element = fsa->next_free;
	next_free_offset = *(size_t *)(new_element - block_header_size);
	fsa->next_free	 = fsa->buff_start + next_free_offset;
	
	return (void *)new_element;
}

void FSAFree(void *block)
{
	size_t current_block_header_offset = 0;
	size_t next_linked_block_offset = 0;
	char *admin_next_ptr = NULL;
	
	assert(NULL != block);
	current_block_header_offset = *(size_t*)((char *)block - block_header_size);
	admin_next_ptr = (char *)block - current_block_header_offset;
	
	next_linked_block_offset = *(size_t*)((char *)admin_next_ptr - block_header_size);
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t free_blocks_ctr = 0;
	size_t i = 0;
	fsa_t *fsa_cpy = (fsa_t *)fsa;
	
	assert(NULL != fsa);
	for (i = 0; i < fsa_cpy->block_num; i++)
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
static size_t InitBlocks(fsa_t *allocator)
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
}

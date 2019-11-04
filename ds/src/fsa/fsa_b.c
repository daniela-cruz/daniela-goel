#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "allocator.h"

#define WORD_SIZE sizeof(size_t)

struct fsa
{
	size_t next_free;
};

static size_t CalcAlignedBlockSize(size_t block_size);

const size_t block_header_size = sizeof(size_t);

/********************************
 * 	IMPLEMENTATION: 	*
********************************/
fsa_t *FSAInit(void *buffer, size_t buff_size, size_t block_size)
{
	fsa_t *allocator = NULL;
	size_t i = 0;
	size_t block_num = 0;
	char *curr_block = NULL;
	
	assert(NULL != buffer);
	allocator = (fsa_t *)buffer;
	block_size += CalcAlignedBlockSize(block_size);
	block_num = ((buff_size - sizeof(size_t)) / block_size);
	
	for (i = 0, curr_block = (char *)allocator + offsetof(fsa_t, next_free); 
		i < block_num; i++, curr_block += block_size)
	{
		*(size_t *)curr_block = sizeof(fsa_t) + ((i + 1) * block_size);
	}
	
	*(size_t *)(curr_block + block_size) = 0;
	allocator->next_free = sizeof(size_t);
		
	return allocator;
}

void FSADestroy(fsa_t *fsa)
{
	assert(NULL != fsa);
}

void *FSAAlloc(fsa_t *fsa)
{
	char *new_element = 0;
	
	assert(NULL != fsa);
	if (-1 != fsa->next_free)
	{
		new_element = (char *)fsa + fsa->next_free + block_header_size;
		fsa->next_free = *(size_t *)(new_element - block_header_size);
	}
	
	if (0 == *(size_t *)(new_element - block_header_size))
	{
		*(size_t *)new_element = -1;
	}	
	
	return (void *)new_element;
}

void FSAFree(void *block)
{
	char *fsa_next_free = NULL;
	char *block_cpy = NULL;
	size_t block_header = 0;
	
	assert(NULL != block);
	block_cpy = (char *)block;
	block_header = *(size_t *)block_cpy - block_header_size;
	fsa_next_free = block_cpy -  block_header_size + block_header;
	
	*((size_t *)block_cpy - block_header_size) = *(size_t *)fsa_next_free;
	*(size_t *)fsa_next_free = block_cpy - fsa_next_free;
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t free_blocks_ctr = 0;
	char *fsa_cpy = (char *)fsa;
	char *curr_block = NULL;
	char *next_block = NULL;
	
	assert(NULL != fsa);
	for (curr_block = fsa_cpy + ((fsa_t *)fsa_cpy)->next_free , next_block = fsa_cpy + *(size_t *)curr_block;
		(curr_block - fsa_cpy != ((fsa_t *)fsa_cpy)->next_free);
		free_blocks_ctr++)
	{
		curr_block = fsa_cpy + ((fsa_t *)fsa_cpy)->next_free;
	}
	
	return free_blocks_ctr;
}

size_t FSASuggest(size_t block_num, size_t block_size)
{
	return sizeof(fsa_t)+ (block_num * (block_header_size + block_size + CalcAlignedBlockSize(block_size)));
}

/********************************
 * INTERNFSA FUNCS: 	*
********************************/
static size_t CalcAlignedBlockSize(size_t block_size)
{
	for (; (block_size > WORD_SIZE); block_size -= WORD_SIZE);
	
	return sizeof(size_t) % block_size;
}

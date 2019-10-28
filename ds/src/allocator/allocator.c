#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "allocator.h"

struct allocator
{
	size_t block_size;
	size_t block_num;
	char *next_free;
	char *buff_start;
};

static char *InitBlocks(fsa_t *allocator);
static size_t GetFirstFreeBlockNum(fsa_t *allocated_space);

const size_t block_header_size = sizeof(size_t);

/********************************
 * 	IMPLEMENTATION: 	*
********************************/
fsa_t *FSAInit(void *buffer, size_t buff_size, size_t block_size)
{
	fsa_t *allocator = NULL;
	
	assert(NULL != buffer);
	allocator = (fsa_t *)buffer;
	
	allocator->block_size = block_size;
	allocator->block_num = block_num;
	allocator->buff_start = (char *)buffer + offsetof(allocator, next_free);
	allocator->next_free = allocator->buff_start;
	InitBlocks(allocator);
	
	return allocator;
}

void FSADestroy(fsa_t *fsa)
{
	/*assert(NULL != allocated_space);
	free(allocated_space->block_arr);
	free(allocated_space->buff_start);
	free(allocated_space); allocated_space = NULL;*/
}

void *FSAalloc(fsa_t *fsa)
{
	size_t free_block_idx = 0;
	
	assert(NULL != allocated_space);
	free_block_idx = GetFirstFreeBlockNum(allocated_space);
	allocated_space->buff_start + free_block_idx = element;
	allocated_space->block_arr[free_block_idx] = 1;
	
	return element;
}

void FSAFree(void *block)
{
	free(element); element = NULL;
	allocator->block_arr[(char *)element - allocator->buff_start] = 0;
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t free_blocks_ctr = 0;
	int i = 0;
	
	for (i = 0; i < allocated_space->block_num; i++)
	{
		(0 == allocated_space->block_arr[i]) ? free_blocks_ctr++ : free_blocks_ctr;
	}
	
	return free_blocks_ctr;
}

size_t FSASuggest(size_t block_num, size_t block_size)
{
	size_t suggested_size = 0;
	
	suggested_size = sizeof(fsa_t *) + (block_num * block_size);
	(0 != (suggested_size % block_size)) ? return suggested_size + 1 : return suggested_size;
}

/********************************
 * INTERNFSA FUNCS: 	*
********************************/
static char *InitBlocks(fsa_t *allocator)
{
	int i = 0;
	
	for (i = 0; i < allocator->block_num; i++)
	{
		(allocator->buff_start[i * allocator->block_size] = 0;
	}
	
	allocator->next_free = offsetof(fsa_t, buff_start) + block_header_size;
}

static size_t GetFirstFreeBlockNum(fsa_t *allocated_space)
{
	size_t i = 0;
	
	for (i = 0; (i < (allocated_space->block_num)) && (0 < allocated_space->block_arr[i]); i++);
	
	return i;
}

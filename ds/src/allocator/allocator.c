#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "allocator.h"

struct allocator
{
	char *block_arr;
	size_t block_size;
	size_t block_num;
	char *buff_start;
};

static void *InitBlockArr(size_t block_num, char *block_arr);
static size_t GetFirstFreeBlockNum(fsa_t *allocated_space);

/********************************
 * 	IMPLEMENTATION: 	*
********************************/
fsa_t *FSAInit(void *buffer, size_t buff_size, size_t blick_size)
{
	fsa_t *allocator = NULL;
	
	assert(NULL != buffer);
	do
	{
		allocator = malloc(sizeof(*allocator));
		if (NULL == allocator)
		{
			break;
		}
		buffer = allocator;
		
		allocator->block_arr = malloc(sizeof(*allocator->block_arr) * block_num);
		if (NULL == allocator->block_arr)
		{
			break;
		}
		
		allocator->block_arr = InitBlockArr(block_num, allocator->block_arr);
		allocator->block_size = block_size;
		allocator->block_num = block_num;
		allocator->buff_start = buffer + offsetof(allocator, block_num);
	
	} while (0);
	
	/* cleanup */
	(NULL == allocator) ? allocator = NULL: allocator;
	(NULL == allocator->block_arr) ? free(allocator) : allocator->block_arr;
	
	return allocator;
}

void FSADestroy(fsa_t *fsa)
{
	assert(NULL != allocated_space);
	free(allocated_space->block_arr);
	free(allocated_space->buff_start);
	free(allocated_space); allocated_space = NULL;
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
 * INTERNFSA FUNCS: 		*
********************************/
static void *InitBlockArr(size_t block_num, char *block_arr)
{
	int i = 0;
	
	assert(NULL != block_arr);	
	for (i = 0; 0 < block_num; i++)
	{
		block_arr[i] = 0;
	}
	
	return block_arr;
}

static size_t GetFirstFreeBlockNum(fsa_t *allocated_space)
{
	size_t i = 0;
	
	for (i = 0; (i < (allocated_space->block_num)) && (0 != allocated_space->block_arr[i]); i++);
	
	return i;
}
/*static GetBitArrNum(size_t block_num)
{
	size_t bit_arr_num = block_num / word_size;
	
	if (0 < block_num % word_size)
	{
	
	}
	
	return bit_arr_num;
}*/

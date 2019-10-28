#include <stddef.h> /* size_t */

#include "allocator.h"
#include "bitarray.h" /* bitarray */

struct allocator
{
	char *block_arr;
	size_t block_size;
	size_t block_num;
	char *buff_start;
	/*size_t arr_num;
	size_t bit_arr;*/
};

static void *InitBlockArr(size_t block_num, char *block_arr);
static size_t GetFirstFreeBlockNum(alloc_t *allocated_space);

/********************************
 * 	IMPLEMENTATION: 	*
********************************/
alloc_t *ALInit(void *buffer, size_t block_size, size_t block_num)
{
	alloc_t *allocator = NULL;
	
	assert(NULL != buffer);
	do
	{
		allocator = malloc(sizeof(*allocator));
		if (NULL == allocator)
		{
			break;
		}
		
		allocator->block_arr = malloc(sizeof(*allocator->block_arr) * block_num);
		if (NULL == allocator->block_arr)
		{
			break;
		}
		
		allocator->block_arr = InitBlockArr(block_num, allocator->block_arr);
		allocator->block_size = block_size;
		allocator->block_num = block_num;
		allocator->buff_start = buffer;
	
	} while (0);
	
	/* cleanup */
	(NULL == allocator) ? allocator = NULL: allocator;
	(NULL == allocator->block_arr) ? free(allocator) : allocator->block_arr;
	
	return allocator;
}

void ALDestroy(alloc_t *allocated_space)
{
	assert(NULL != allocated_space);
	free(allocated_space->block_arr);
	free(allocated_space->buff_start);
	free(allocated_space); allocated_space = NULL;
}

void *ALallocator(alloc_t *allocated_space, void *element)
{
	assert(NULL != allocated_space);
	
	element = allocated_space->buff_start + GetFirstFreeBlockNum(allocated_space);
	
	return element;
}

void ALFree(alloc_t *allocator, void *element)
{
	free(element); element = NULL;
	allocator->block_arr[(char *)element - allocator->buff_start] = 0;
}

size_t ALCountFreeBlocks(alloc_t *allocated_space);

size_t ALSuggest(size_t block_num, size_t block_size);

/********************************
 * INTERNAL FUNCS: 		*
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

static size_t GetFirstFreeBlockNum(alloc_t *allocated_space)
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

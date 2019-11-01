#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "vsa.h"

struct vsa
{
	char buffer[1];
};

typedef struct
{
	size_t size;
} vsa_header_t;

/*************************/

static size_t AlignVarSize(size_t var_size);
static size_t AlignToBlockSize(size_t buff_size);

static int IsFree(vsa_header_t *header);

static vsa_header_t *FindRightSizeBlock(const vsa_t *vsa, size_t var_size);

/*************************/

const size_t word_size = sizeof(size_t);
const size_t header_size = sizeof(vsa_header_t);
const size_t buff_end = 7;

/**********IMPLEMENTATION:***************/
vsa_t *VSAInit(void *buffer, size_t buff_size)
{
	vsa_t *vsa = NULL;
	vsa_header_t *first_header = NULL;
	
	assert(NULL != buffer);
	buff_size = AlignToBlockSize(buff_size);
	vsa = buffer;
	first_header = (vsa_header_t *)vsa;
	first_header->size = buff_size - sizeof(first_header);

	*(size_t *)((char *)vsa + buff_size - word_size) = buff_end; 
	
	return vsa;
}

void *VSAAlloc(vsa_t *vsa, size_t var_size)
{
	vsa_header_t *element = NULL;
	vsa_header_t *next_header = NULL;
	
	assert(NULL != vsa);
	var_size += AlignVarSize(var_size);
	element = (vsa_header_t *)vsa; 
	
	if (var_size <= VSAMaxFreeBlock(vsa))
	{
		element = FindRightSizeBlock(vsa, var_size);
		next_header = (vsa_header_t *)((char *)element + var_size + header_size);
		if (buff_end != next_header->size)
		{
			next_header->size = element->size - var_size - header_size;
			element->size = var_size + header_size + 1;
			element = (vsa_header_t *)((char *)element + header_size);
		}
		
	}
	
	return (void *)element;
}

void VSAFree(void *block)
{
	vsa_header_t *header = NULL;
	
	assert(NULL != block);
	header = (vsa_header_t *)((char *)block - header_size);
	header->size--;
}

size_t VSAMaxFreeBlock(const vsa_t *vsa)
{
	size_t max_size = header_size;
	size_t curr_max = 0;
	vsa_header_t *header = NULL;
	vsa_header_t *curr_header = NULL;
	
	assert(NULL != vsa);
	
	for (header = curr_header = (vsa_header_t *)vsa, max_size = 0; 
		buff_end != header->size; )
	{
		if (IsFree(header))
		{
			for (curr_max = 0; (IsFree(header)) && buff_end != header->size; 
				header = (vsa_header_t *)((char *)header + header->size))
			{
				curr_max += header->size;
				max_size = (max_size < curr_max) ? curr_max : max_size;
			}
			
			curr_header->size = curr_max;
		}
		
		else
		{
			header = curr_header = (vsa_header_t *)(((char *)header)+ header->size - 1);
		}
	}
	
	return max_size;
}

/****************************
 * 		INTERNAL: 		*
****************************/
static size_t AlignVarSize(size_t var_size)
{
	for (; var_size > word_size; var_size -= word_size);
	
	return word_size % var_size;
}

static vsa_header_t *FindRightSizeBlock(const vsa_t *vsa, size_t var_size)
{
	size_t curr_max = 0;
	vsa_header_t *header = NULL;
	vsa_header_t *curr_header = NULL;
	
	assert(NULL != vsa);
	for (header = curr_header = (vsa_header_t *)vsa; 
		buff_end != header->size; )
	{
		if (IsFree(header))
		{
			for (curr_max = 0; (IsFree(header)) && buff_end != header->size; 
				header = (vsa_header_t *)((char *)header + header->size))
			{
				curr_max += header->size;
				if (var_size <= curr_max - header_size)
				{
					return curr_header;
				}
			}
			
			curr_header->size = curr_max;
		}
		
		else
		{
			header = curr_header = (vsa_header_t *)(((char *)header)+ header->size - 1);
		}
	}
	
	return NULL;
}

static size_t AlignToBlockSize(size_t buff_size)
{
	return (0 != buff_size % word_size) ? 
			(((buff_size + word_size - 1) & ~(word_size - 1)) - word_size) : buff_size;
}

static int IsFree(vsa_header_t *header)
{
	assert(NULL != header);
	
	return ((word_size <= header->size) && (0 == header->size % 2));
}

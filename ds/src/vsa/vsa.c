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
static size_t FindRightSize(const vsa_t *vsa, size_t size);
static void UpdateHeadersSizes(vsa_header_t *header, size_t var_size);
static vsa_t *DefragFreeBlocks(const vsa_t *vsa);

/*************************/

const size_t word_size = sizeof(size_t);
const size_t header_size = sizeof(vsa_header_t);
const size_t buff_end = -1;

/**********IMPLEMENTATION:***************/
vsa_t *VSAInit(void *buffer, size_t buff_size)
{
	vsa_t *vsa = NULL;
	vsa_header_t *first_header = NULL;
	
	assert(NULL != buffer);
	buff_size = AlignToBlockSize(buff_size);
	vsa = buffer;
	first_header = (vsa_header_t *)vsa;
	first_header->size = buff_size - sizeof(first_header->size);

	*(size_t *)((char *)vsa + buff_size - word_size) = buff_end; 
	
	return vsa;
}

void *VSAAlloc(vsa_t *vsa, size_t var_size)
{
	char *element = NULL;
	vsa_header_t *header = NULL;
	
	assert(NULL != vsa);
	var_size += AlignVarSize(var_size);
	
	for (header = (vsa_header_t *)vsa; 
		1 != header->size; 
		header = (vsa_header_t *)((char *)header + header->size))
	{
		if (var_size <= FindRightSize(header, var_size))
		{
			element = (char *)header + sizeof(vsa_header_t);
			UpdateHeadersSizes(header, var_size);
			break;
		}
	}
	
	return (void *)element;
}

void VSAFree(void *block)
{
	
}

size_t VSAMaxFreeBlock(const vsa_t *vsa)
{
	size_t max_size = 0;
	size_t curr_max = 0;
	vsa_header_t *header = NULL;
	
	assert(NULL != vsa);
	/*DefragFreeBlocks(vsa);*/
	
	for (header = (vsa_header_t *)vsa; 
		buff_end != header->size; 
		header = (vsa_header_t *)((char *)header + header->size + header_size))
	{
		if (IsFree(header))
		{
			curr_max += header->size;
			max_size = (max_size < curr_max) ? curr_max : max_size;
		}
		else
		{
			curr_max = 0;
			header = (vsa_header_t *)((char *)header - 1);
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

static size_t FindRightSize(const vsa_t *vsa, size_t size)
{
	size_t new_size = 0;
	vsa_header_t *header = NULL;
	
	assert(NULL != vsa);
	new_size = DefragFreeBlocks(vsa);
	
	/*or (; (1 == IsFree(header)) && (new_size <= size); 
		new_size += header->size, header = (vsa_header_t *)((char *)header + header->size));*/
	for (header = (vsa_header_t *)vsa; 
		buff_end != header->next;
		header = (vsa_header_t *)((char *)header + header->size + header_size))
	{
		
	}
	
	return new_size;
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

static void UpdateHeadersSizes(vsa_header_t *header, size_t var_size)
{
	vsa_header_t *next_header = NULL;
	
	assert(NULL != header);
	next_header = (vsa_header_t *)((char *)header + header->size + header_size);
	
	if ((header->size > var_size) && (buff_end != next_header->size))
	{
		next_header->size = header->size - var_size - header_size;
	}
	
	header->size = var_size + 1;
}

static vsa_t *DefragFreeBlocks(const vsa_t *vsa)
{
	vsa_t *vsa_cpy = NULL;
	vsa_header_t *header = NULL;
	vsa_header_t *curr_header = NULL;
	size_t block_size = 0;
	
	assert(NULL != vsa);
	vsa_cpy = (vsa_t *)vsa;
	
	
	for (curr_header = header = (vsa_header_t *)vsa, block_size = header->size; 
		buff_end != header->size; 
		curr_header = header = (vsa_header_t *)((char *)header + header->size + header_size))
	{
		for (; (1 == IsFree(header)); 
			header = (vsa_header_t *)((char *)header + header->size + header_size))
		{
			curr_header->size += header->size;
		}
	}
	
	return vsa_cpy;
}

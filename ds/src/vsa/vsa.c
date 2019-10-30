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
static int IsFree(vsa_header_t *header);
static size_t FindRightSize(vsa_header_t *header, size_t size);
/*************************/

const size_t word_size = sizeof(size_t);

vsa_t *VSAInit(void *buffer, size_t buff_size)
{
	vsa_t *vsa = NULL;
	vsa_header_t *first_header = NULL;
	
	assert(NULL != buffer);
	vsa = buffer;
	first_header = (vsa_header_t *)vsa;
	first_header->size = buff_size - sizeof(first_header->size);
	/* mark end of buffer with a 1 */
	*(size_t *)((char *)vsa + buff_size - word_size) = 1; 
	
	return vsa;
}

void *VSAAlloc(vsa_t *vsa, size_t var_size)
{
	char *element = NULL;
	vsa_header_t *header = NULL;
	vsa_header_t *first_header = NULL;
	size_t new_size = 0;
	
	assert(NULL != vsa);
	for (header = (vsa_header_t *)vsa; 
		1 != header->size; 
		header = (vsa_header_t *)((char *)header + header->size))
	{
		if ((var_size <= FindRightSize(header, var_size)) &&(IsFree(header)))
		{
			element = (char *)header + header->size + sizeof(vsa_header_t);
			break;
		}
	}
	
	return (void *)element;
}

void VSAFree(void *block);

size_t VSAMaxFreeSize(vsa_t *vsa)
{
	size_t max_size = 0;
	vsa_header_t *header = NULL;
	
	assert(NULL != vsa);
	for (header = (vsa_header_t *)vsa; 1 != header->size; 
		header = (vsa_header_t *)((char *)header + header->size))
	{
		if ((0 == header->size % 2) && (max_size < header->size))
		{
			max_size = header->size;
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

static size_t FindRightSize(vsa_header_t *header, size_t size)
{
	size_t new_size = 0;
	
	assert(NULL != header);
	for (; (1 == IsFree(header)) && (new_size <= size); 
		new_size += header->size, header = (vsa_header_t *)((char *)header + header->size));
	
	return new_size;
}

static int IsFree(vsa_header_t *header)
{
	assert(NULL != header);
	
	return ((word_size <= header->size) && (0 == header->size % 2));
}

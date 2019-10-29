#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "vsa.h"

#define VSA_MAGIC_NUM -1

struct vsa
{
	size_t max_size;
};

typedef struct
{
	size_t size;
} vsa_header_t;

vsa_t *VSAInit(void *buffer, size_t buff_size)
{
	vsa_t *vsa = NULL;
	vsa_header_t *first_header = NULL;
	char *first_empty = NULL;
	
	assert(NULL != buffer);
	vsa = buffer;
	vsa->max_size = buff_size;
	
	first_header->size = buff_size - sizeof(first_header->size) - sizeof(vsa_t);
	first_empty = (char *)buffer + first_header->size;
	*first_empty = ~0;
	
	return vsa;
}

void *VSAAlloc(vsa_t *vsa)
{
	char *allocated = NULL;
	
	assert(NULL != vsa);
	
	return allocated;
}

void VSAFree(void *block);

size_t VSAMaxFreeSize(vsa_t *vsa);

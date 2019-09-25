#include <stdio.h> /* printf */
#include <stdlib.h> /* calloc, realloc, free */
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <string.h> /* memset */

#include "vector.h" /* vector_t */

struct vector
{
	size_t ele_size;
	void *buffer;
	size_t capacity;
	size_t size; /* amount of current number of elements in the array */
};

vector_t *VectorCreate(size_t element_size, size_t size)
{
	vector_t *vector_arr = NULL;
	
	vector_arr = malloc(sizeof(vector_t));
	vector_arr->capacity = size;
    vector_arr->size = 0;
    vector_arr->buffer = calloc(element_size, vector_arr->size * vector_arr->capacity);
    
    return vector_arr;
}

void VectorDestroy(vector_t *vector_ptr);

void *VectorGetItemAddress(vector_t *vector_ptr, size_t index);

int VectorPushBack(vector_t *vector_ptr, const void *data);

int VectorPopBack(vector_t * vector_ptr);

size_t VectorSize(const vector_t *vector_ptr);

size_t VectorCapacity(const vector_t *vector_ptr);

int VectorReserve(const vector_t *vector_ptr, size_t new_capacity);

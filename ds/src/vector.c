#include <stdio.h> /* printf */
#include <stdlib.h> /* calloc, realloc, free */
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <string.h> /* memset */

#include "vector.h" /* vector_t */

struct vector
{
	size_t ele_size;
	void *data;
	size_t capacity;
	size_t size; /* amount of current number of elements in the array */
};

enum status_t {SUCCESS, FAILURE};

const size_t capacity_factor = 2;

vector_t *VectorCreate(size_t element_size, size_t size)
{
	vector_t *vector_arr = NULL;
	
	vector_arr = calloc(sizeof(vector_t),1);
	vector_arr->ele_size = element_size;
    vector_arr->size = size;
    vector_arr->data = calloc(vector_arr->ele_size, vector_arr->size);
	vector_arr->capacity = size;
    
    return vector_arr;
}

void VectorDestroy(vector_t *vector_ptr)
{
	free(vector_ptr->data); vector_ptr->data = NULL;
	free(vector_ptr); vector_ptr = NULL;
}

void *VectorGetItemAddress(vector_t *vector_ptr, size_t index)
{
        return (char *)vector_ptr->data + (index * vector_ptr->ele_size);
}

int VectorPushBack(vector_t *vector_ptr, const void *new_data)
{
	/* if no more room left for new data*/
	if (vector_ptr->capacity == vector_ptr->size) 
	{
		vector_ptr->data = realloc(vector_ptr->data, 
						(vector_ptr->ele_size) * (vector_ptr->capacity * capacity_factor));
		vector_ptr->capacity *= capacity_factor;
		
		if (!vector_ptr->data)
		{	
			perror("Push failed.");
			return FAILURE;
		}
	}

	vector_ptr->size++;
	memcpy((char *)vector_ptr->data + (vector_ptr->ele_size * vector_ptr->size), 
				 new_data, vector_ptr->ele_size);
	
	return SUCCESS;
}

int VectorPopBack(vector_t * vector_ptr)
{
	enum status_t status = SUCCESS;
	*(((char *)vector_ptr->data) + (vector_ptr->size * vector_ptr->ele_size)) = 0;
	
    vector_ptr->size--;

    if (((0 < vector_ptr->size) && vector_ptr->capacity) == (vector_ptr->capacity / capacity_factor))
    {
        status = VectorReserve(vector_ptr, vector_ptr->capacity / capacity_factor);
	}
	
	return status;
}

size_t VectorSize(const vector_t *vector_ptr)
{
	return vector_ptr->size;
}

size_t VectorCapacity(const vector_t *vector_ptr)
{
	return vector_ptr->capacity;
}

int VectorReserve(vector_t *vector_ptr, size_t new_capacity)
{
	if (new_capacity > vector_ptr->capacity)
	{
		vector_ptr->capacity = new_capacity;
		vector_ptr->data = realloc(vector_ptr->data, 
				(vector_ptr->ele_size) * (vector_ptr->capacity * capacity_factor));
	}
	
	if (!vector_ptr)
	{
		perror("Could nor reserve space");
		return FAILURE;
	}
	
	return SUCCESS;
}

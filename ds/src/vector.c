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

enum g_status {SUCCESS, FAILURE};

const size_t capacity_factor = 2;

vector_t *VectorCreate(size_t element_size, size_t size)
{
	vector_t *vector_arr = NULL;
	
	vector_arr = calloc(1, sizeof(vector_t));
	
	if (!vector_arr)
	{
		perror("VectorCreate: calloc for vector_arr failed.");
	}
	
	vector_arr->ele_size = element_size;
    vector_arr->size = size;
    vector_arr->data = calloc(vector_arr->size, vector_arr->ele_size);
    
    if (!vector_arr->data)
	{
		perror("VectorCreate: calloc for data failed.");
	}
    
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
		
		if (vector_ptr->data)
		{
			vector_ptr->capacity *= capacity_factor;
		}
		else
		{
			perror("PushBack:  vector_ptr->data was not allocated.");
			
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
	int status = SUCCESS;
	
	*(((char *)vector_ptr->data) + (vector_ptr->size * vector_ptr->ele_size)) = 0;
	
    vector_ptr->size--;

    if (((0 < vector_ptr->size) && vector_ptr->capacity) == (vector_ptr->capacity / capacity_factor))
    {
		void *temp_buffer = NULL;
		
		temp_buffer = realloc(vector_ptr->data, 
				(vector_ptr->ele_size) * (vector_ptr->capacity / capacity_factor));
		
		if (!temp_buffer)
		{
			prerror("PopBack: ");
			
			return FAILURE;
		}
		
		vector_ptr->data = temp_buffer;
	}
	
	return SUCCESS;
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

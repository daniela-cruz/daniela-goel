#include <string.h> /*		   memcpy		 */
#include <stdio.h>  /*	   perror, size_t	 */
#include <stdlib.h> /* malloc, realloc, free */

#include "vector.h"

static float growth_factor = 2;
static float shrink_factor = 0.75;

struct vector
{
	size_t item_size;
	size_t size;
	size_t capacity;
	void *items;
};
 
vector_t *VectorCreate(size_t num_of_items, size_t item_size)
{
	vector_t *vector = (vector_t *)malloc(sizeof(*vector));
	if(NULL == vector)
	{
		perror("malloc");
		return NULL;
	}
	
	vector->items = malloc(item_size * num_of_items);
	if(NULL == vector->items)
	{
		free(vector);
		perror("malloc");
		return NULL;
	}
	
	vector->item_size = item_size;
	vector->size = 0;
	vector->capacity = num_of_items;
	
	return vector; 
}

void *VectorGetItemAdd(vector_t *vector, size_t index)
{
	return (char *)vector->items + (vector->item_size * index); 
}

int VectorPushBack(vector_t *vector, const void *data)
{
	if(vector->size == vector->capacity)
	{
		void *temp = realloc(vector->items, vector->capacity * growth_factor * vector->item_size);
		if(NULL == temp)
		{
			return 1;
		}
		
		vector->capacity *= growth_factor;
		vector->items = temp;
	}
	memcpy((char *)vector->items + (vector->size * vector->item_size), data, vector->item_size);
	vector->size += 1;
	
	return 0;
}

int VectorPopBack(vector_t *vector)
{
	if(vector->size == vector->capacity / growth_factor)
	{
		void *temp = realloc(vector->items, shrink_factor * vector->capacity * vector->item_size);
		if(NULL == temp)
		{
			return 1;
		}
		
		vector->capacity *= shrink_factor;
		vector->items = temp; 
	}
	
	vector->size -= 1;
	
	return 0;
}

size_t VectorSize(const vector_t *vector)
{
	return vector->size;
}

size_t VectorCapacity(const vector_t *vector)
{
	return vector->capacity;
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	if(new_capacity > vector->capacity)
	{
		void *temp = realloc(vector->items, new_capacity * vector->item_size);
		if(NULL == temp)
		{
			return 1;
		}
	
		vector->capacity = new_capacity;
		vector->items = temp;
	}
	
	return 0;
}

void VectorDestroy(vector_t *vector)
{
	free(vector->items);
	vector->items = NULL;
	
	free(vector);
}


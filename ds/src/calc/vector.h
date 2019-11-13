#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* size_t */

typedef struct vector vector_t;

/*	*Create dynamic array of size element_s * element_num
	*return pointer to the created array				*/
vector_t *VectorCreate(size_t element_size, size_t num_of_elements);

/* 	*Frees allocated memory to our array and set 
		dynamic array pointer to zero				*/
void VectorDestroy(vector_t *element);

/*	*returns address of requested element in dynamic
		array in position represented by index value
	*If index is not in range of array - undefined	 		*/
void *VectorGetItemAddress(vector_t *element, size_t index);

/* 	*Add element to the end of the dynamic array
	*If we reached array capacity, then 
		allocate capacity * 2 to expand the array							 
	*return 1 for failure
		   0 for success	
	*Amortized complexity O(1)					*/
int VectorPushBack(vector_t *element,const void *data);

/* 	*Remove element from the end of the dynamic array
	*Amortized complexity O(1)					*/
int VectorPopBack(vector_t *element);

/*   	*return how much elements currently are in
		dynamic array						*/
size_t VectorSize(const vector_t *element);

/* 	*return capacity of our dynamic array, stored
		members + empty space left				*/
size_t VectorCapacity(const vector_t *element);

/* 	*In case size reached capacity, allocate 
		capacity * 2 to dynamic array for new elements
		to come (dynamic vector)				*/
int VectorReserve(vector_t *element, size_t new_capacity);

#endif /* __VECTOR_H__ */


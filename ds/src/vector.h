#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* ptrdiff_t */

typedef struct vector vector_t;

/* 		element_size: the size of a single element in the array
* 		size: the desired amount of elements the function will 
* 		allocate a memore and return pointer to the new array		*/
vector_t *VectorCreate(size_t element_size, size_t size);

/* 		The user must provide the pointer to the array 				*/
void VectorDestroy(vector_t *vector_ptr);

/* 		Provides pointer to desired address or NULL is fails 		*/
void *VectorGetItemAddress(vector_t *vector_ptr, size_t index);

/* 		returns 0 if push realloc succeeds or 1 if failed. 
 * 		Complexity: O(1) 														*/
int VectorPushBack(vector_t *vector_ptr, const void *data);

/* 		returns 0 if push realloc succeeds or 1 if failed 
 * 		Complexity: O(1) 														*/
int VectorPopBack(vector_t * vector_ptr);

/* 		Complecity: O(1) 														*/
size_t VectorSize(const vector_t *vector_ptr);

/* 		Complecity: O(1) 														*/
size_t VectorCapacity(const vector_t *vector_ptr);

/* 		returns 0 if push realloc succeeds or 1 if failed */
int VectorReserve(vector_t *vector_ptr, size_t new_capacity);

#endif /* __VECTOR_H__ */

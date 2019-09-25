#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* ptrdiff_t */

typedef struct vector vector_t;

/* growth factor + shrink factor */

/* element_size: the size of a single element in the array
* size: the desired amount of elements
* the function will allocate a memore and return pointer to the new array
* After finishing the use of the vectory the user must call VectorDestroy to free the allocated space */
vector_t *VectorCreate(size_t element_size, size_t size);

/* The user must provide the pointer to the array */
void VectorDestroy(vector_t *vector_ptr);

/**/
void *VectorGetItemAddress(vector_t *vector_ptr, size_t index);

/* returns 0 if push realloc succeeds or 1 if failed */
int VectorPushBack(vector_t *vector_ptr, const void *data);

/* returns 0 if push realloc succeeds or 1 if failed */
int VectorPopBack(vector_t * vector_ptr);

/**/
size_t VectorSize(const vector_t *vector_ptr);

/**/
size_t VectorCapacity(const vector_t *vector_ptr);

/* returns 0 if push realloc succeeds or 1 if failed */
int VectorReserve(const vector_t *vector_ptr, size_t new_capacity);

#endif /* __VECTOR_H__ */

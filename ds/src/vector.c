#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <string.h> /* strlen */

#include "vector.h" /* vector_t */

vector_t *VectorCreate(size_t element_size, size_t size);

void VectorDestroy(vector_t *vector_ptr);

void *VectorGetItemAddress(vector_t *vector_ptr, size_t index);

int VectorPushBack(vector_t *vector_ptr, const void *data);

int VectorPopBack(vector_t * vector_ptr);

size_t VectorSize(const vector_t *vector_ptr);

size_t VectorCapacity(const vector_t *vector_ptr);

int VectorReserve(const vector_t *vector_ptr, size_t new_capacity);

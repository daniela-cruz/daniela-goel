#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* size_t */

typedef struct vector vector_t;

/* Create vector array  */
vector_t *VectorCreate(size_t size, size_t element_size);

/* Free vector array */
void VectorDestroy(vector_t *v);

/* Get address of ele number index*/
void *VectorGetItemAddress(vector_t *v, size_t index);

/* push & pop */
int VectorPushBack(vector_t *v, const void *element);

int VectorPopBack(vector_t *v);

size_t VectorCapacity(const vector_t *v);

size_t VectorSize(const vector_t *v);

int VectorReserve(vector_t *vector, size_t num_ele);


#endif /* __VECTOR_H__*/

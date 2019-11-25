/********************
*dev shachar.herbet
*rev  
*date 24.9.2019		
*status 
*********************/


#ifndef VECTOR_HEDDER_GURD
#define VECTOR_HEDDER_GURD

	#include <stddef.h> /* size_t */

	typedef struct vector vector_t;

	vector_t	*VectorCreate		(size_t size, size_t el_size);
	void     	VectorDestroy		(vector_t *vector);
	int     	VectorPushBack		(vector_t *vector, const void *el); 
	int 	 	VectorPopBack		(vector_t *vector); 
	void 	 	*VectorGetItemAdd	(vector_t *vector, size_t idx);
	size_t   	VectorSize			(const vector_t *vector); 
	size_t 	 	VectorCapacity		(const vector_t *vector);
	int			VectorReserve		(vector_t *vector , size_t capacity);

#endif



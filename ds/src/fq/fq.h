#ifndef __FQ_H__
#define __FQ_H__
#include <stddef.h> /* size_t */

enum status {SUCCESS, FAILURE};

typedef struct fifo_queue fq_t;

/* 		the user will receive a pointer to the new 
 * 		memory location. If allocation fails the function
 * 		returns NULL							 						*/
fq_t *FQCreate();

/* 		free allocated memory
 * 		the user has to call this function in order to 
 * 		free up all allocated memory after calling create 	*/
void FQDestroy(fq_t *q_element);

/*		insert new task to queue. Complexity: O(1) 		*/
int FQEnqueue(fq_t *q_element, void *data);

/*		remove task from queue. Complexity: O(1) 		*/
void *FQDequeue(fq_t *q_element);

/*		*/
int FQIsEmpty(const fq_t *q_element);

/*		peek last element 											*/
void *FQPeek(const fq_t *q_element);

size_t FQCount(const fq_t *first);

fq_t *FQAppend(fq_t *dest, fq_t *src);

#endif /* __FQ_H__ */


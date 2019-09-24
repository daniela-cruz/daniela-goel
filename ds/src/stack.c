#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "stack.h" /* stack_t */

stack_t
{
	void *data;
	size_t index;
}

/*
* create a stack using the sizeof element 
* and the size for the cells number
*/
stack_t *StkCreate(size_t size);

/*
* remove element from stack
*/
void *StkPop(stack_t *element_ptr);

/*
* add element to stack
*/
void StkPush(stack_t *element_ptr);

/*
* get value of element from stack
*/
void *StkPeek(const stack_t *element_ptr);

/*
* get elements amount in stack
*/
size_t StkCount(const stack_t *element_ptr);

/*
* returns 0 if stack is empty or 1 if full
*/
int StkIsEmpty(const stack_t *element_ptr);

/*
* destroy stack
*/
void StkDestroy(stack_t *element_ptr);

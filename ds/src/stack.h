#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h> /* size_t */

typedef struct stack stack_t;

/*
* create a stack using the sizeof element and the size for the cells number
* The user will have to call StkDestroy in order to free the allocation created on create
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

#endif /* __STACK_H__ */

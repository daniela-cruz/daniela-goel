#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "stack.h" /* stack_t */

struct stack
{
	size_t ele_size;
	int top; /* stack pointer, points to top of stack */
	void *elements;
};

stack_t *StkCreate(size_t stack_size, size_t element_capacity)
{
	stack_t *stack_ptr = malloc(sizeof(stack_t));
	stack_ptr->ele_size = element_capacity;
    stack_ptr->top = 0;
    stack_ptr->elements = calloc(element_capacity, stack_size);
 
    return stack_ptr;
}

void StkPop(stack_t *stk)
{
	stk->top--;
}

void StkPush(stack_t *stk, void *data)
{
	memcpy((char *)stk->elements + (stk->top * stk->ele_size), data, stk->ele_size);
	stk->top++;
}

void *StkPeek(const stack_t *stk)
{
	return (char *)stk->elements + ((stk->top-1) * stk->ele_size);
}

size_t StkCount(const stack_t *stk)
{
	return stk->top;
}

int StkIsEmpty(const stack_t *stk)
{
	 return stk->top == 0;
}

void StkDestroy(stack_t *stk)
{	
	free(stk); stk = NULL;
}

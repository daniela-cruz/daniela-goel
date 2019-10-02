#include <stdlib.h> /* malloc, calloc, free */
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
	
	if (!stack_ptr)
	{
		perror("StkCreate: Could not allocate stack_ptr.");
	}
	
	stack_ptr->ele_size = element_capacity;
    stack_ptr->top = 0;
    stack_ptr->elements = calloc(stack_size, element_capacity);
    
    if (!stack_ptr->elements)
	{
		perror("StkCreate: Could not allocate elements.");
	}
 
    return stack_ptr;
}

void StkPop(stack_t *stk)
{
	assert(stk);
	
	stk->top--;
}

void StkPush(stack_t *stk, void *data)
{
	assert(stk);
	assert(data);
	
	memcpy((char *)stk->elements + (stk->top * stk->ele_size), data, stk->ele_size);
	stk->top++;
}

void *StkPeek(const stack_t *stk)
{
	assert(stk);
	
	return (char *)stk->elements + ((stk->top-1) * stk->ele_size);
}

size_t StkCount(const stack_t *stk)
{
	assert(stk);
	
	return stk->top;
}

int StkIsEmpty(const stack_t *stk)
{
	 return stk->top == 0;
}

void StkDestroy(stack_t *stk)
{	
	assert(stk);
	
	free(stk->elements); stk->elements = NULL;
	free(stk); stk = NULL;
}

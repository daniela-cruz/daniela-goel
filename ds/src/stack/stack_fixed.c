#include <stdlib.h> /* malloc, calloc, free */
#include <string.h> /*		  memcpy		*/

#include "stack.h"

struct stack
{
	int ele_size;
	int top;
	void *elements;
};

stack_t *StkCreate(size_t stack_size, size_t ele_size)
{
	stack_t *stack = (stack_t *)malloc(sizeof(*stack));
	if(NULL == stack)
	{
		return NULL;
	}
	
	stack->elements = malloc(stack_size * ele_size);
	if(NULL == stack->elements)
	{
		free(stack);
		return NULL;
	}
	
	stack->ele_size = ele_size;
	stack->top = 0;
	
	return stack;
}

void StkPop(stack_t *stk)
{
	stk->top--;
}

void StkPush(stack_t *stk, const void *val)
{
	memcpy((char *)stk->elements + (stk->top * stk->ele_size), val, stk->ele_size);
	stk->top++;
}

void *StkPeek(const stack_t *stk)
{
	return (char *)stk->elements + ((stk->top - 1) * stk->ele_size);
}

size_t StkCount(const stack_t *stk)
{
	return stk->top;
}

int StkIsEmpty(const stack_t *stk)
{
	return stk->top == 0;
}

void StkSort(stack_t *stk)
{
	int holder = 0;
	
	if(1 == StkCount(stk))
	{
		StkPush(stk, &holder);
		return;
	}

	StkSort(stk);

	holder = *(int *)StkPeek(stk);
	StkPop(stk);

	if(holder < *(int *)StkPeek(stk))
	{
		int temp = *(int *)StkPeek(stk);
		StkPop(stk);
		StkPush(stk, &holder);
		holder = temp;
		StkSort(stk);
	}
	
	StkPush(stk, &holder);
}

void StkDestroy(stack_t *stk)
{
	free(stk->elements);
	stk->elements = NULL;
	
	free(stk);
}

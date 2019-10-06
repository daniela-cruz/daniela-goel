#include <stddef.h> /*	   size_t	*/
#include <string.h> /* 	   memcpy	*/
#include <stdio.h>  /*	   perror	*/
#include <stdlib.h> /* 	malloc, free	*/

#include "stack.h"

struct stack
{
	int top;
	int max_size;
	void *base_of_data;
	size_t item_size;
};

stack_t *StkCreate(size_t size_of_stack, size_t element_size)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	if(NULL == stack)
	{
		perror("malloc failed in stack creation");

		return NULL;
	}

	stack->top = 0;
	stack->max_size = size_of_stack;
	stack->base_of_data = calloc(size_of_stack, element_size); /* n, sizeof */
	stack->item_size = element_size;
	if(NULL == stack->base_of_data)
	{
		perror("calloc failed in stack creation");

		return NULL;
	}

	return stack;
}

void StkPush(stack_t *p_stack, void *new_element)
{
	if(p_stack->top == p_stack->max_size)
	{
		return;
	}

	memcpy((char *)p_stack->base_of_data + (p_stack->top * p_stack->item_size),
		 new_element, p_stack->item_size);
	 
	p_stack->top++;
}

void StkPop(stack_t *p_stack)
{
	if(0 == p_stack->top)
	{
		
		return;
	}

	p_stack->top--;
}

void *StkPeek(const stack_t *p_stack)
{
	return (char *)p_stack->base_of_data + 
				((p_stack->top - 1) * p_stack->item_size);
}

size_t StkCount(const stack_t *p_stack)
{
	return p_stack->top;
}

int StkIsEmpty(const stack_t *p_stack)
{
	return (0 == p_stack->top);
}

void StkDestroy(stack_t *p_stack)
{
	
	free(p_stack->base_of_data);
	p_stack->base_of_data = NULL;
	
	free(p_stack);
	p_stack = NULL;
}

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "stack.h" /* stack_t */

struct stack
{
	size_t ele_size;
	size_t max_top; /* element size multiplied by amount */
	int top; /* stack pointer, points to top of stack */
	void *elements;
};

stack_t *StkCreate(size_t stack_size, size_t element_capacity)
{
	stack_t *pt = (stack_t*)malloc(sizeof(element_capacity * stack_size));
 
    pt->max_top = stack_size;
    pt->top = 0;
    pt->elements = (void *)malloc(sizeof(element_capacity));
 
    return pt;
}

void StkPop(stack_t *element_ptr)
{
	char *element_ptr_cpy = NULL;
	
	if (StkIsEmpty(element_ptr))
	{
		printf("Stack is empty\n"); 
	}
	
	element_ptr->top--;
	*element_ptr_cpy = *(char *)element_ptr->elements * element_ptr->top--;
}

void StkPush(stack_t *element_ptr, void *data)
{
	 char *element_ptr_cpy = NULL;
	 
	 assert(data);
	 
	 if (StkIsEmpty(element_ptr))
    {
        printf("Stack is empty\n"); 
    }
    else
    {
		element_ptr_cpy = (char *)element_ptr->elements + (element_ptr->top * element_ptr->ele_size);
		element_ptr->elements = (void *)element_ptr_cpy;
		element_ptr->elements = memcpy(element_ptr->elements, data, element_ptr->ele_size);
		element_ptr->top++;
	}
}

void *StkPeek(const stack_t *element_ptr)
{
	char *element_ptr_cpy = NULL;
	
	if (!StkIsEmpty(element_ptr))
	{
		element_ptr_cpy = (char *)element_ptr->elements + element_ptr->top;
		
		return (void *)element_ptr_cpy;
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}

size_t StkCount(const stack_t *element_ptr)
{
	return element_ptr->top;
}

int StkIsEmpty(const stack_t *element_ptr)
{
	 return (element_ptr->top == 0) ? 1: 0;
}

void StkDestroy(stack_t *element_ptr)
{	
	free(element_ptr); element_ptr = NULL;
}

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "stack.h" /* stack_t */

stack_t
{
	void *data;
	size_t index;
}

stack_t *StkCreate(size_t element_capacity, size_t size)
{
    struct stack *pt = (struct stack*)malloc(sizeof(struct stack));
 
    pt->maxsize = capacity;
    pt->top = -1;
    pt->items = (int*)malloc(sizeof(int) * capacity);
 
    return pt;
}
void *StkPop(stack_t *element_ptr);

void StkPush(stack_t *element_ptr);

void *StkPeek(const stack_t *element_ptr);

size_t StkCount(const stack_t *element_ptr);

int StkIsEmpty(const stack_t *element_ptr);

void StkDestroy(stack_t *element_ptr);

#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h> /* size_t */

typedef struct stack stack_t;

/* 		creates a stack of <size> members
	   recieves number of members that the stack can fill
	   and the size of the argument the stack is expected
	   to save. 																		   		*/
stack_t *StkCreate(size_t stack_size, size_t element_capacity);

/* 		Pops the last inserted member in the stack
   		pop when stack is empty behavior is undefined. 
   		Complexity: O(1) 																*/
void StkPop(stack_t *element_ptr);

/* 		Push the requested value into the stack.
   		push when stack is full is undefined. Complexity: O(1)	 		   */
void  StkPush(stack_t *element_ptr, const void *data);

/* 		Peeks at the last inserted member in the stack
   		returns it to the user. If stack is empty behavior is undefined		*/
void *StkPeek(const stack_t *element_ptr);

/* 		Counts the inserted member in the stack
   		returns it to the user.							   								*/
size_t StkCount(const stack_t *element_ptr);

/* 		Returns 1 if stack is empty, 0 if not.									   */
int StkIsEmpty(const stack_t *element_ptr);

/* 		destroys the stack 															   */
void StkDestroy(stack_t *element_ptr);

#endif /* __STACK_H__ */

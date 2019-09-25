#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "stack.h" /* all below */

static void StkCreateTest();

int main()
{
	struct students
	{
		char* name;
		int class;
	};
	
	struct students student1 = {"hadas", 77};
	struct students student2 = {"yosi", 90};
	
	int empty = 0;
	
	struct students *a = NULL;
	stack_t *my_stack = NULL;
	
	my_stack = StkCreate(3, sizeof(struct students));
	
	empty = StkIsEmpty(my_stack);
	printf("is the stack empty? %d\n" ,empty);
	
	StkPush(my_stack, &student1);
	StkPush(my_stack, &student2);
	
	printf("number of members after pushing: %ld\n" ,StkCount(my_stack));
	
	a = StkPeek(my_stack);
	printf("name of the top student %s\n" ,a->name);
	printf("class of the top student %d\n" ,a->class);
	
	StkPop(my_stack);
	
	printf("number of members: %ld\n" ,StkCount(my_stack));
	
	a = StkPeek(my_stack);
	printf("name of the top student %s\n" ,a->name);
	printf("class of the top student %d\n" ,a->class);
	
	StkDestroy(my_stack);

	return 0;
}

static void StkCreateTest()
{
	size_t element_size = 0, element_amount = 0;
	stack_t *stk_ptr = NULL;
	int check_val = 0, src_val = 12;
	void *data = NULL;
	
	element_amount = 3;
	element_size = sizeof(int);
	stk_ptr = StkCreate(element_amount, element_size);	
	
	printf("\nCreating stack. . .\n");
	
	if (NULL != stk_ptr)
	{
		printf("Success! Stack has been creted!\n");	
	}
	else
	{
		printf("Failed to create a stack pointer\n");
	}
	
	printf("\nPushind data to stack. . .\n");
	data = (void *)src_val;
	StkPush(stk_ptr, data);
	
	printf("\nPeeking test. . .\n");
	check_val = (int)StkPeek(stk_ptr);
	printf("\nsaved data is: %d\n", check_val);
	
}


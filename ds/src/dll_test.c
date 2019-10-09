#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "dll.h" /* all below*/

static void UserDLL();
static void IsEmptyTest();

dll_t *new_dll = NULL;
dll_iter_t *iterator = NULL;

int main()
{
	iterator = malloc(sizeof(*iterator));
	
	UserDLL();
	IsEmptyTest();
		
	return 0;
}

static void UserDLL()
{
	printf("\nCreate test. . .\t");
	new_dll = DLLCreate();
	(NULL != new_dll) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
	printf("Size check. . .\t\t");
	(0 == DLLSize(new_dll)) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}

static void IsEmptyTest()
{
	printf("IsEmpty check. . .\t");
	(1 == DLLIsEmpty(new_dll)) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}
/*
static void InsertTest()
{
	int num = 123;
	printf("\nInsert test. . .\t\t");
	iterator->curr_node_addr = new_dll->first;
	DLLInsert(*iterator, (void *)&num);
	(num == *(int *)new_dll->last->prev->data) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}*/

static void PushBackTest()
{
	int num = 123;
	new_dll = DLLPushBack(new_dll, (void *)&num);
}

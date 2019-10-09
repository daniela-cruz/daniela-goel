#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "dll.h" /* all below*/

static void UserDLL();
static void PushBackTest(int num);
static void PushFrontTest(int num);
static void IsEmptyTest(int expected);
static void SizeTest(size_t expected);
static void GetDataTest(int num);

static dll_t *new_dll = NULL;
static dll_iter_t *iterator = NULL;

int main()
{
	int num = 123, num2 = 456;
	iterator = malloc(sizeof(*iterator));
	
	UserDLL();
	*iterator = DLLEnd(new_dll);
	PushBackTest(num);
	SizeTest(1);
	*iterator = DLLIterPrev(*iterator);
	GetDataTest(num);
	*iterator = DLLBegin(new_dll);
	PushFrontTest(num2);
	SizeTest(2);
	GetDataTest(num2);
		
	return 0;
}

static void UserDLL()
{
	printf("\nCreate test. . .\t");
	new_dll = DLLCreate();
	(NULL != new_dll) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
	SizeTest(0);
	IsEmptyTest(1);
	
}

static void PushBackTest(int num)
{
	printf("\nPush back test. . .\n");
	new_dll = DLLPushBack(new_dll, (void *)&num);
	
	IsEmptyTest(0);
}

static void PushFrontTest(int num)
{
	printf("\nPush front test. . .\n");
	new_dll = DLLPushFront(new_dll, (void *)&num);
	IsEmptyTest(0);
	*iterator = DLLBegin(new_dll);
	*iterator = DLLIterNext(*iterator);
}

static void GetDataTest(int num)
{
	printf("\nGet data test. . .\t");
	(num == *(int *)DLLGetData(*iterator)) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}

static void IsEmptyTest(int expected)
{
	printf("IsEmpty check. . .\t");
	(expected == DLLIsEmpty(new_dll)) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}

static void SizeTest(size_t expected)
{
	printf("Size check. . .\t\t");
	(expected== DLLSize(new_dll)) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}

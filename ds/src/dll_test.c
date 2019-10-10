#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "dll_b.h" /* all below*/

static void FindTest();
static int FindFunc(const void *data, void *param);

static void UserDLL();
static void PushBackTest(int num);
static void PushFrontTest(int num);
static void IsEmptyTest(int expected);
static void SizeTest(size_t expected);
static void GetDataTest(int num);

static void PushTests();
static void PopTests();

static dll_t *new_dll = NULL;
static dll_iter_t iterator = {NULL, NULL};
static int num = 123, num2 = 456, num3 = 789;

int main()
{
	UserDLL();
	PushTests();
	/*PopTests();*/
	/*FindTest();*/
		
	return 0;
}

static void FindTest()
{
	dll_iter_t start = {NULL, NULL};
	dll_iter_t end = {NULL, NULL};
	
	printf("\nFind test. . .\t");

	start = DLLBegin(new_dll);
	start = DLLIterNext(start);
	end = DLLBegin(new_dll);
	
	iterator = DLLIterNext(start);
	start = DLLFind(start, end, FindFunc, (void *)&num2);
	(iterator.curr_node_addr == start.curr_node_addr) ?
		printf("SUCCESS!\n"): printf("FAILURE! Found iterator shows: %d\n", *(int*)DLLGetData(start));
	
}

static int FindFunc(const void *data, void *param)
{
	return param == (void *)data;
}

static void PushTests()
{
	printf("\n\n\nPush tests: \n\n");
	
	iterator = DLLEnd(new_dll);
	PushBackTest(num);
	SizeTest(1);
	iterator = DLLIterPrev(iterator);
	GetDataTest(num);
	iterator = DLLBegin(new_dll);
	PushFrontTest(num2);
	SizeTest(2);
	GetDataTest(num2);
	PushFrontTest(num3);
	SizeTest(3);
	GetDataTest(num3);
}

static void PopTests()
{
	printf("\n\n\nPop tests: \n\n");
	
	DLLPopBack(new_dll);
	SizeTest(2);
	DLLPopFront(new_dll);
	SizeTest(1);
	DLLPopBack(new_dll);
	SizeTest(0);
	IsEmptyTest(1);
	PushBackTest(num);
	SizeTest(1);
	PushFrontTest(num2);
	SizeTest(2);
	PushFrontTest(num3);
	SizeTest(3);
	IsEmptyTest(0);
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
	iterator = DLLPushBack(new_dll, (void *)&num);
	
	IsEmptyTest(0);
}

static void PushFrontTest(int num)
{
	printf("\nPush front test. . .\n");
	iterator = DLLPushFront(new_dll, (void *)&num);
	IsEmptyTest(0);
	iterator = DLLBegin(new_dll);
	iterator = DLLIterNext(iterator);
}

static void GetDataTest(int num)
{
	printf("\nGet data test. . .\t");
	(num == *(int *)DLLGetData(iterator)) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
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

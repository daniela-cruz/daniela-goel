#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "dll.h" /* all below*/

static void SpliceTest();

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

static dll_t *dll2 = NULL;
static dll_t *new_dll = NULL;
static dll_iter_t iterator = {NULL, NULL, NULL};
static int num1 = 123, num2 = 456, num3 = 789;
static int num4 = 1, num5 = 2, num6 = 3;

int main()
{
	UserDLL();
	printf("\nSize is: %d\n", DLLSize(new_dll));
	PushTests();
	/*PopTests();*/
	/*FindTest();*/
	/*SpliceTest();*/
		
	return 0;
}

static void SpliceTest()
{
	dll_iter_t start = {NULL, NULL, NULL};
	dll_iter_t end = {NULL, NULL, NULL};
	
	printf("\nSPLICE test. . .\n");
	dll2 = DLLCreate();
	DLLPushFront(dll2, &num6);
	DLLPushFront(dll2, &num5);
	DLLPushFront(dll2, &num4);
	
	iterator = DLLIterNext(DLLIterNext(DLLBegin(new_dll)));
	start = DLLIterNext(DLLBegin(dll2));
	
	iterator = DLLSplice(iterator, start, DLLIterNext(start));
	
	printf("Output check: \t\t");
	(!DLLIterIsEqual(DLLEnd(new_dll), iterator)) ?
		printf("SUCCESS!\n"): printf("FAILURE!\n"); 
	
	GetDataTest(num4);
}

static void FindTest()
{
	dll_iter_t start = {NULL, NULL, NULL};
	dll_iter_t end = {NULL, NULL, NULL};
	
	printf("\nFind test. . .\t");

	start = DLLIterNext(DLLBegin(new_dll));
	end = DLLIterPrev(DLLEnd(new_dll));
	iterator = DLLIterNext(start);
	
	start = DLLFind(start, end, FindFunc, (void *)&num3);
	(DLLIterIsEqual(start, iterator)) ?
		printf("SUCCESS!\n"): printf("FAILURE!\n");
	
}

static int FindFunc(const void *data, void *param)
{
	return param == (void *)data;
}

static void PushTests()
{
	printf("\n\n\nPush tests: \n\n");
	
	iterator = DLLEnd(new_dll);
	PushBackTest(num1);
	SizeTest(1);
	PushFrontTest(num2);
	SizeTest(2);
	PushFrontTest(num3);
	SizeTest(3);
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
	PushBackTest(num1);
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
	GetDataTest(num);
	IsEmptyTest(0);
}

static void PushFrontTest(int num)
{
	printf("\nPush front test. . .\n");
	iterator = DLLPushFront(new_dll, (void *)&num);
	GetDataTest(num);
	IsEmptyTest(0);
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

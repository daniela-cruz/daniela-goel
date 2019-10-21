#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "dll.h" /* all below*/

static void SpliceTest();

static void FindTest(dll_iter_t iterator);
static int FindFunc(const void *data, void *param);

static void UserDLL();
static void PushBackTest(dll_iter_t iterator, int num);
static void PushFrontTest(dll_iter_t iterator, int num);
static void IsEmptyTest(int expected);
static void SizeTest(size_t expected);
static void GetDataTest(dll_iter_t iterator, int num);

static void PushTests();
static void PopTests();

static const int num1 = 123, num2 = 456, num3 = 789;
static const int num4 = 1, num5 = 2, num6 = 3;

int main()
{
	SpliceTest();
		
	return 0;
}

static void SpliceTest()
{
	static dll_t *dll2 = NULL;
	static dll_t *new_dll = NULL;
	dll_iter_t iterator1, iterator2;
	int n1 = 123, n2 = 456, n3 = 789;
	int n4 = 1, n5 = 2, n6 = 3;
	
	printf("Splice:\n");
	
	new_dll = DLLCreate();
	iterator1 = DLLPushBack(new_dll, &n1);
	iterator1 = DLLPushBack(new_dll, &n2);
	iterator1 = DLLPushBack(new_dll, &n3);
	
	printf("\nPrint before pop 1:\n");
	for (iterator1 = DLLBegin(new_dll); !DLLIterIsEqual(iterator1, DLLEnd(new_dll)); iterator1 = DLLIterNext(iterator1))
	{
		printf("%d\n", *(int*)DLLGetData(iterator1));
	}
	
	dll2 = DLLCreate();
	iterator2 = DLLPushFront(dll2, &n4);
	iterator2 = DLLPushFront(dll2, &n5);
	iterator2 = DLLPushFront(dll2, &n6);
	
	printf("\nPrint before pop 2:\n");
	for (iterator2 = DLLBegin(dll2); !DLLIterIsEqual(iterator2, DLLEnd(dll2)); iterator2 = DLLIterNext(iterator2))
	{
		printf("%d\n", *(int*)DLLGetData(iterator2));
	}
	
	DLLSplice(DLLIterPrev(DLLEnd(new_dll)), DLLBegin(dll2), DLLEnd(dll2));
	
	printf("\nPrint after splice:\n");
	for (iterator1 = DLLBegin(new_dll); !DLLIterIsEqual(iterator1, DLLEnd(new_dll)); iterator1 = DLLIterNext(iterator1))
	{
		printf("%d\n", *(int*)DLLGetData(iterator1));
	}
	
	iterator1 = DLLRemove(DLLIterPrev(DLLEnd(new_dll)));
	iterator1 = DLLRemove(DLLIterPrev(iterator1));
	iterator1 = DLLRemove(DLLIterPrev(iterator1));
	iterator1 = DLLRemove(DLLIterPrev(DLLEnd(new_dll)));
	iterator1 = DLLPushFront(new_dll, &n4);
	iterator1 = DLLPushFront(new_dll, &n5);
	
	printf("\nPrint after pop:\n");
	for (iterator1 = DLLBegin(new_dll); !DLLIterIsEqual(iterator1, DLLEnd(new_dll)); iterator1 = DLLIterNext(iterator1))
	{
		printf("%d\n", *(int*)DLLGetData(iterator1));
	}
}
/*
static void FindTest(dll_iter_t iterator)
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
*/
static void PushTests()
{
	dll_iter_t iterator = {NULL, NULL, NULL};
	printf("\n\n\nPush tests: \n\n");
	/*
	iterator = DLLEnd(new_dll);
	PushBackTest(iterator, num1);
	SizeTest(1);
	iterator = DLLBegin(new_dll);
	iterator = DLLIterNext(iterator);
	GetDataTest(iterator, num1);*/
	
	/*iterator = DLLEnd(new_dll);*/
	/*iterator = DLLIterPrev(DLLIterPrev(iterator));
	GetDataTest(iterator, num1);
	
	PushFrontTest(iterator, num2);
	iterator = DLLBegin(new_dll);
	iterator = DLLIterNext(iterator);
	GetDataTest(iterator, num2);
	SizeTest(2);
	PushFrontTest(iterator, num3);
	SizeTest(3);
	GetDataTest(iterator, num3);*/
}

static void PopTests()
{
	printf("\n\n\nPop tests: \n\n");
	
	/*DLLPopBack(new_dll);
	SizeTest(2);
	DLLPopFront(new_dll);
	SizeTest(1);
	DLLPopBack(new_dll);
	SizeTest(0);
	IsEmptyTest(1);
	/*PushBackTest(iterator, num1);
	SizeTest(1);
	PushFrontTest(iterator, num2);
	SizeTest(2);
	PushFrontTest(iterator, num3);
	SizeTest(3);
	IsEmptyTest(0);*/
}

static void UserDLL()
{
	/*printf("\nCreate test. . .\t");
	new_dll = DLLCreate();
	(NULL != new_dll) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
	SizeTest(0);
	IsEmptyTest(1);
*/	
}

static void PushBackTest(dll_iter_t iterator, int num)
{
	/*printf("\nPush back test. . .\n");
	DLLPushBack(new_dll, &num);
	IsEmptyTest(0);*/
}
/*
static void PushFrontTest(dll_iter_t iterator, int num)
{
	printf("\nPush front test. . .\n");
	DLLPushFront(new_dll, &num);
	IsEmptyTest(0);
}

static void GetDataTest(dll_iter_t iterator, int num)
{
	printf("\nGet data test. . .\t");
	(num == *(int *)DLLGetData(iterator)) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
	printf("Data is: %d\n", *(int *)DLLGetData(iterator));
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
}*/

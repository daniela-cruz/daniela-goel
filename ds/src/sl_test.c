#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "sl.h" /* for all tests below */

static void CreateAndDestroy();
static void InsertAndGetData();

static void CreateTest();
static void InsertTest(int num);
static void IsEmptyTest(int result);
static void SizeTest(size_t expected_size);
static void GetDataTest(int expected_value);

int IsBefore(void *node1, void *node2, void *param);

static sl_t *new_sl = NULL;
sl_iter_t iterator = {NULL};
int num = 123;

int main()
{
	/*CreateAndDestroy();*/
	InsertAndGetData();
	
	return 0;
}

/**********************************
 * 			System Tests:				*
**********************************/
static void CreateAndDestroy()
{
	printf("\n\nSystem test: CREATE AND DESTROY\n");
	CreateTest();
	iterator = SLBegin(new_sl);
	IsEmptyTest(1);
	SizeTest(0);
	InsertTest(num);
	IsEmptyTest(0);
	SizeTest(1);
	SLDestroy(new_sl);
	printf("To complete memory leak test - CHECK USING VALGRIND\n");
}

static void InsertAndGetData()
{
	printf("\n\nSystem test: INSERT AND GET DATA\n");
	CreateTest();
	iterator = SLBegin(new_sl);
	InsertTest(num);
	iterator = SLBegin(new_sl);
	iterator = SLNext(iterator);
	GetDataTest(num);
	SLDestroy(new_sl);
}

/*************************************
 * 			Functions Tests:				*
*************************************/
static void CreateTest()
{
	printf("\nCreate test. . .\t");
	new_sl = SLCreate((sl_is_before_t)IsBefore);
	(NULL != new_sl) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}

static void InsertTest(int num)
{
	printf("\nInserting new node in place. . .\n");
	iterator = SLInsert(iterator, (void *)&num);
}

static void IsEmptyTest(int result)
{
	printf("Is the list empty?\t");
	(result == SLIsEmpty(new_sl)) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}

static void SizeTest(size_t expected_size)
{
	printf("Size test. . .\t\t");
	(expected_size == SLSize(new_sl)) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}

static void GetDataTest(int expected_value)
{
	printf("Get data test. . .\t\t");
	(expected_value == *(int*)SLGetData(iterator)) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}

/**************************************************
 * internal functions
 *************************************************/

int IsBefore(void *node1, void *node2, void *param)
{
	return node1 > node2;
}


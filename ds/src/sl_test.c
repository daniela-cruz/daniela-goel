#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "sl.h" /* for all tests below */

static void CreateAndDestroy();
static void InsertAndGetData();

static void CreateTest();
static void InsertTest(sl_iter_t iter, int num);
static void IsEmptyTest(int result);
static void SizeTest(size_t expected_size);
static void GetDataTest(sl_iter_t iter, int expected_value);

int IsBefore(void *node1, void *node2, void *param);

static sl_t *new_sl = NULL;
sl_iter_t iterator = {NULL};
const int num1 = 123;

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
	InsertTest(iterator, num1);
	IsEmptyTest(0);
	SizeTest(1);
	SLDestroy(new_sl);
	printf("To complete memory leak test - CHECK USING VALGRIND\n");
}

static void InsertAndGetData()
{
	sl_iter_t it = {NULL};
	
	printf("\n\nSystem test: INSERT AND GET DATA\n");
	CreateTest();
	it = SLBegin(new_sl);
	it = SLNext(it);
	InsertTest(it, num1);
	it = SLBegin(new_sl);
	it = SLNext(it);
	GetDataTest(it, num1);
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

static void InsertTest(sl_iter_t iter, int num)
{
	printf("\nInserting new node in place. . .\n");
	iterator = SLInsert(iter, (void *)&num);
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

static void GetDataTest(sl_iter_t iter, int expected_value)
{
	printf("Get data test. . .\t\t");
	(expected_value == *(int*)SLGetData(iter)) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}

/**************************************************
 * internal functions
 *************************************************/

int IsBefore(void *node1, void *node2, void *param)
{
	return node1 > node2;
}


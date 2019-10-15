#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "sl.h" /* for all tests below */

static void CreateAndDestroy();
static void InsertAndGetData();

static sl_t *CreateTest(sl_t new_sl);
static void InsertTest(sl_iter_t iter, int num);
static void IsEmptyTest(sl_t *sl_ptr, int result);
static void SizeTest(sl_t sl_ptr, size_t expected_size);
static void GetDataTest(sl_iter_t iter, int expected_value);

int IsBefore(void *node1, void *node2, void *param);

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
	sl_t *sl = NULL;
	printf("\n\nSystem test: CREATE AND DESTROY\n");
	sl = CreateTest(sl);
	iterator = SLBegin(sl);
	IsEmptyTest(sl, 1);
	SizeTest(sl, 0);
	InsertTest(iterator, num1);
	IsEmptyTest(sl, 0);
	SizeTest(sl, 1);
	SLDestroy(sl);
	printf("To complete memory leak test - CHECK USING VALGRIND\n");
}

static void InsertAndGetData()
{
	sl_iter_t it = {NULL};
	sl_t *sl = NULL;
	
	printf("\n\nSystem test: INSERT AND GET DATA\n");
	sl = DLLCreate((sl_is_before_t)IsBefore);
	it = SLBegin(*sl);
	it = SLNext(it);
	InsertTest(it, num1);
	it = SLBegin(*sl);
	it = SLNext(it);
	GetDataTest(it, num1);
	SLDestroy(*sl);
}

/*************************************
 * 			Functions Tests:				*
*************************************/
static sl_t  *CreateTest(sl_t new_sl)
{
	printf("\nCreate test. . .\t");
	new_sl = SLCreate((sl_is_before_t)IsBefore);
	(NULL != new_sl) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
	
	return &sl;
}

static void InsertTest(sl_iter_t iter, int num)
{
	printf("\nInserting new node in place. . .\n");
	iterator = SLInsert(iter, (void *)&num);
}

static void IsEmptyTest(sl_t *sl_ptr, int result)
{
	printf("Is the list empty?\t");
	(result == SLIsEmpty(sl_ptr)) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}

static void SizeTest(sl_t sl_ptr, size_t expected_size)
{
	printf("Size test. . .\t\t");
	(expected_size == SLSize(sl_ptr)) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
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


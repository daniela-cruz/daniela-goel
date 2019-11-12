#include <stdio.h>
#include <assert.h>

#include "bst.h"

#define UNUSED(x) (void)(x) 

int CreateInsertForEachTest();
int FindTest();
int IsIntBefore(const void* key1, const void* key2, void *param);
int PrintInts(void* data, void* param);
int CompareInts(void* data, void* param);

int main()
{
	/*CreateInsertForEachTest();*/
/*
	FindTest();
*/
	return 0;
}

int CreateInsertForEachTest()
{
	bst_t *bst = NULL;
	size_t i = 0;
	size_t size = 10;

	int arr[10] = {23, 17, 12, 90, 4, 100, 1, 50, 13, 66};
	int expected[10] = {1, 4, 12, 13, 17, 23, 50, 66, 90, 100};

	puts("***************************************************\n");
	puts("Create+ Insert + For Each Test:\n");

	bst = BSTCreate(IsIntBefore, NULL);

	for (i = 0; i < size; ++i)
	{
		BSTInsert(bst, &arr[i]);
	}

	BSTforEach(BSTBegin(bst), BSTEnd(bst), CompareInts, &expected);
	
	return 0;
}

int FindTest()
{
	bst_t *bst = NULL;
	size_t i = 0;
	size_t size = 10;
	bst_iter_t expected[5] = {0};
	int data[5] = {50, 4, 67, 100, 11};

	int arr[10] = {23, 17, 12, 90, 4, 100, 1, 50, 13, 66};

	puts("***************************************************\n");
	puts("Find Test:\n");

	bst = BSTCreate(IsIntBefore, NULL);

	for (i = 0; i < size; ++i)
	{
		BSTInsert(bst, &arr[i]);
	}

	for (i = 0; i < 5; ++i)
	{
		expected[i] = BSTFind(bst, &data[i]);
	}

	BSTIterIsSame(expected[0], BSTEnd(bst)) ? puts("1: Error\n") : puts ("1: Success\n");
	BSTIterIsSame(expected[0], BSTEnd(bst)) ? puts("2: Error\n") : puts ("2: Success\n");
	BSTIterIsSame(expected[0], BSTEnd(bst)) == 0 ? puts("3: Error\n") : puts ("3: Success\n");
	BSTIterIsSame(expected[0], BSTEnd(bst)) ? puts("4: Error\n") : puts ("4: Success\n");
	BSTIterIsSame(expected[0], BSTEnd(bst)) == 0 ? puts("5: Error\n") : puts ("5: Success\n");

	return 0;
}


int IsIntBefore(const void* key1, const void* key2, void *param)
{
	UNUSED(param);

	assert(key1 != NULL);
	assert(key2 != NULL);	

	return (*(int *)key1 < *(int *)key2);
}

int PrintInts(void* data, void* param)
{
	UNUSED(param);

	assert(data != NULL);

	printf("%d\t", *(int *)data);
	
	return 0;
}

int CompareInts(void* data, void* param)
{
	static int i = 0;

	if (*(int *)data != *((int *)param + i))
	{
		puts ("Error in ForEach");
	}

	++i;

	return 0;
}

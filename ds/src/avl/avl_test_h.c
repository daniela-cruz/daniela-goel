#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

#define UNUSED(x) (void)(x)

int InsertForEachTest();
int RemoveTest();
int HeightTest();
int LeftRotationTest();
int RightRotationTest();
int RemoveRotationTest();

static int IsIntBefore(const void *data1, const void *data2, void *param);
static int PrintInt(void *data, void *param);

int main()
{
	InsertForEachTest();

	RemoveTest();

	HeightTest();

	LeftRotationTest();

	RightRotationTest();

	RemoveRotationTest();

	return 0;
}

/************************************************************/

int InsertForEachTest()
{
	int arr[20] = {23, 4, 67, 32, 21, 100, 42, 27, 88, 16, 18, 3, 55, 22, 77, 99, 33, 44, 30, 60};
	
	/* int arr[4] = {300, 200, 400, 100}; */
	int z = 65;
	int *find = NULL;
	int result = 0;
	size_t i = 0;

	avl_t *avl = AVLCreate(IsIntBefore, NULL);
	if(NULL == avl)
	{
		return 1;
	}

	puts("********************************************");
	puts("*********Functions Test*********************");

	AVLIsEmpty(avl) == 1 ? puts("IsEmpty works") : puts("Error in IsEmpty");
	AVLSize(avl) == 0 ?  puts("Size Works") : puts("Error in Size");

	for (i = 0; i < 20; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	AVLIsEmpty(avl) == 0 ? puts("IsEmpty works") : puts("Error in IsEmpty");

	result = AVLForEach(avl, PrintInt, NULL);

	result == 0 ? puts("\nForEach works") : puts("\nError in ForEach");

	AVLSize(avl) == 20 ?  puts("Size Works") : puts("Error in Size");

	find = AVLFind(avl, &arr[5]);
	*(int *)find == 100 ? puts("Find Works") : puts("Error in Find");

	find = AVLFind(avl, &arr[0]);
	*(int *)find == 23 ? puts("Find Works") : puts("Error in Find");

	find = AVLFind(avl, &z);
	find == NULL ? puts("Find Works") : puts("Error in Find");

	AVLDestroy(avl);

	return 0;
}

/************************************************************/

int RemoveTest()
{
	int arr[24] = {23, 4, 67, 32, 21, 100, 42, -27, 88, 16, 18, 3, -55, 22, -77, 99, 33, 44, 30, 60, 31, 87, 50, 97};
	size_t i = 0;

	avl_t *avl = AVLCreate(IsIntBefore, NULL);
	if(NULL == avl)
	{
		return 1;
	}

	puts("********************************************");
	puts("***********Destroy Test*********************");

	for (i = 0; i < 24; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	AVLForEach(avl, PrintInt, NULL);
	puts("\n");

	for (i = 0; i < 24; ++i)
	{
		AVLRemove(avl, &arr[i]);
		AVLForEach(avl, PrintInt, NULL);
		puts("\n");
	}

	AVLDestroy(avl);

	return 0;
}

/************************************************************/

int HeightTest()
{
	int arr[8] = {5, 2, 8, 10, 1, 7, 6, 12};
	int result[8] = {0, 1, 2, 2, 3, 3, 3, 4}; 
	size_t i = 0;

	avl_t *avl = AVLCreate(IsIntBefore, NULL);
	if(NULL == avl)
	{
		return 1;
	}

	puts("********************************************");
	puts("************Height Test*********************");

	for (i = 0; i < 8; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	AVLHeight(avl) == 4 ? puts("Height works") : puts("Error in Height");
	
	for (i = 7; i >= 1; --i)
	{
		AVLRemove(avl, &arr[i]);
		AVLHeight(avl) != result[i] ? puts("Error in height") : puts("Height Works");
	}

	AVLDestroy(avl);

	return 0;
}

/************************************************************/

static void LeftTest1();
static void LeftTest2();
static void LeftTest3();
static void LeftTest4();
static void LeftTest5();
static void LeftTest6();


int LeftRotationTest()
{
	puts("********************************************");
	puts("********Left Rotation Test******************");

	LeftTest1();
	LeftTest2();
	LeftTest3();
	LeftTest4();
	LeftTest5();
	LeftTest6();

	return 0;
}

static void LeftTest1()
{
	int arr[3] = {10, 8, 6};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 3; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 2 ? puts("Left Rotation Succes\n") : puts("Left Rotation Failure\n");
	AVLDestroy(avl);
}

static void LeftTest2()
{
	int arr[6] = {10, 12, 7, 8, 6, 4};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 6; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 3 ? puts("Left Rotation Succes\n") : puts("Left Rotation Failure\n");
	AVLDestroy(avl);
}

static void LeftTest3()
{
	int arr[6] = {10, 12, 8, 13, 6, 5};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 6; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 3 ? puts("Left Rotation Succes\n") : puts("Left Rotation Failure\n");
	AVLDestroy(avl);
}

static void LeftTest4()
{
	int arr[8] = {10, 12, 8, 9, 6, 5, 7, 4};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 8; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 4 ? puts("Left Rotation Succes\n") : puts("Left Rotation Failure\n");
	AVLDestroy(avl);
}

static void LeftTest5()
{
	int arr[6] = {10, 12, 6, 5, 8, 9};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 6; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 3 ? puts("Left Rotation Succes\n") : puts("Left Rotation Failure\n");
	AVLDestroy(avl);
}

static void LeftTest6()
{
	int arr[9] = {20, 22, 10, 23, 12, 6, 5, 8, 9};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 9; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 4 ? puts("Left Rotation Succes\n") : puts("Left Rotation Failure\n");
	AVLDestroy(avl);
}

/************************************************************/

static void RightTest1();
static void RightTest2();
static void RightTest3();

int RightRotationTest()
{
	puts("********************************************");
	puts("********Right Rotation Test******************");

	RightTest1();
	RightTest2();
	RightTest3();

	return 0;
}

static void RightTest1()
{
	int arr[3] = {10, 12, 15};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 3; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 2 ? puts("Right Rotation Succes\n") : puts("Right Rotation Failure\n");
	AVLDestroy(avl);
}

static void RightTest2()
{
	int arr[200] = {0};
	size_t i = 0;
	avl_t *avl = NULL;

	for(i = 0; i < 200; ++i)
	{
		arr[i] = i;
	}

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 200; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	AVLHeight(avl) == 8 ? puts("Right Rotation Succes\n") : puts("Right Rotation Failure\n");
	AVLDestroy(avl);
}

static void RightTest3()
{
	int arr[6] = {10, 8, 15, 2, 20, 1};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 6; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	AVLHeight(avl) == 3 ? puts("Right Rotation Succes\n") : puts("Right Rotation Failure\n");
	AVLDestroy(avl);
}

/**********************************************************************/

int RemoveRotationTest()
{
	int arr[7] = {10, 5, 15, 8, 20, 2, 1};
	size_t i = 0;
	avl_t *avl = NULL;

	puts("********************************************");
	puts("********Remove Rotation Test****************");

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 7; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	AVLHeight(avl) == 4 ? puts("Remove Rotation Succes\n") : puts("Remove Rotation Failure\n");
	AVLRemove(avl, &arr[1]);
	AVLHeight(avl) == 3 ? puts("Remove Rotation Succes\n") : puts("Remove Rotation Failure\n");
	AVLDestroy(avl);

	return 0;
}

/**********************************************************************/

static int IsIntBefore(const void *data1, const void *data2, void *param)
{
	UNUSED(param);

	return (*(int *)data1 < *(int *)data2);
}

static int PrintInt(void *data, void *param)
{
	UNUSED(param);

	printf("%d\t", *(int *)data);

	return 0;
}





#include <stdio.h> /* printf */

#include "search.h"

static void BinaryRecTest();
static void BinaryTest();
static void JumpTest();

int CmpFunc(const void *data1, const void *data2);
static void *GetAddress(int *array, int idx);

static int arr[10] = {-12, -3, 0, 7, 15, 31, 47, 52, 111, 1200};
static int size = 10;
static int ele_size = sizeof(int);


int main()
{
    /* BinaryRecTest(); */
    BinaryTest();
    /* JumpTest(); */
    return 0;
}

static void BinaryRecTest()
{
    int* element = NULL;
    void* key = NULL;

    printf("\nRecursive binary search test\n");

    key = GetAddress(arr, 0);
    element = BinSearchRec(arr, size, sizeof(int), key, CmpFunc);
    (-12 == *(int *)element) ? printf ("SUCCESS\n") : printf("FAILURE\n");

    key = GetAddress(arr, size -1);
    element = BinSearchRec(arr, size, sizeof(int), key, CmpFunc);
    (1200 == *(int *)element) ? printf ("SUCCESS\n") : printf("FAILURE\n");

    key = GetAddress(arr, 5);
     element = BinSearchRec(arr, size, sizeof(int), key, CmpFunc);
    (31 == *(int *)element) ? printf ("SUCCESS\n") : printf("FAILURE\n");

    key = GetAddress(arr, 8);
     element = BinSearchRec(arr, size, sizeof(int), key, CmpFunc);
    (111 == *(int *)element) ? printf ("SUCCESS\n") : printf("FAILURE\n");
}

static void BinaryTest()
{
    int* element = NULL;
    void* key = NULL;

    printf("\nBinary search test\n");

    key = GetAddress(arr, 0);
    element = BinarySearch(arr, size, sizeof(int), key, CmpFunc);
    (-12 == *(int *)element) ? printf ("SUCCESS\n") : printf("FAILURE\n");

    key = GetAddress(arr, size -1);
    element = BinarySearch(arr, size, sizeof(int), key, CmpFunc);
    (1200 == *(int *)element) ? printf ("SUCCESS\n") : printf("FAILURE\n");

    key = GetAddress(arr, 5);
     element = BinarySearch(arr, size, sizeof(int), key, CmpFunc);
    (31 == *(int *)element) ? printf ("SUCCESS\n") : printf("FAILURE\n");

    key = GetAddress(arr, 8);
     element = BinarySearch(arr, size, sizeof(int), key, CmpFunc);
    (111 == *(int *)element) ? printf ("SUCCESS\n") : printf("FAILURE\n");
}

static void JumpTest()
{
    int* element = NULL;
    void* key = NULL;

    printf("\nJump search test\n");

    key = GetAddress(arr, 0);
    element = JumpSearch(arr, size, sizeof(int), key, CmpFunc);
    (-12 == *(int *)element) ? printf ("SUCCESS\n") : printf("FAILURE\n");

    key = GetAddress(arr, size -1);
    element = JumpSearch(arr, size, sizeof(int), key, CmpFunc);
    (1200 == *(int *)element) ? printf ("SUCCESS\n") : printf("FAILURE\n");

    key = GetAddress(arr, 5);
    element = JumpSearch(arr, size, sizeof(int), key, CmpFunc);
    (31 == *(int *)element) ? printf ("SUCCESS\n") : printf("FAILURE\n");

    key = GetAddress(arr, 8);
    element = JumpSearch(arr, size, sizeof(int), key, CmpFunc);
    (111 == *(int *)element) ? printf ("SUCCESS\n") : printf("FAILURE\n");
}



int CmpFunc(const void *data1, const void *data2)
{
    return *(int *)data1 - *(int *)data2;
}

static void *GetAddress(int *array, int idx)
{
    return ((char *)array + (idx * ele_size));
}

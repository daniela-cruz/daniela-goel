#include <stdio.h>          /* printf */
#include <stdlib.h>         /* rand */
#include <time.h>           /* clock */

#include "sort.h"

static int *RandArr(int *arr, size_t size);
static void PrintArr(int *arr, size_t size);

static void TimeTest();

static void BubbleTest(int *arr, size_t size);
static void OptimizedBubbleTest(int *arr, size_t size);
static void InsertionSortTest(int *arr, size_t size);
static void SelectionSortTest(int *arr, size_t size);
static void CountSortTest();


/*static int arr[100];*/
static int arr[8] = {2, 73, -6, 15, 6, 8, 120, -64};

int main()
{
    int size = 8;
    
    /*BubbleTest(arr, 5);*/
    /*OptimizedBubbleTest(arr, size);*/
    /*InsertionSortTest(arr, 5);*/
    /*SelectionSortTest(arr, size);*/
    CountSortTest();

    /*TimeTest();*/


    return 0;
}

static void TimeTest()
{
    clock_t start, end;
    double exe_time = 0;
    size_t size = 8;

    RandArr(arr, size);
    PrintArr(arr, size);
    
    start = clock();
    BubbleSort(arr, size);    
    end = clock();
    exe_time = (end - start) / (double)(CLOCKS_PER_SEC);
    printf("\nBubble execution time:\t\t%f\n", exe_time);

    start = clock();
    OptimizedBubbleSort(arr, size);    
    end = clock();
    exe_time = (end - start) / (double)(CLOCKS_PER_SEC);
    printf("\nOptiBubble execution time:\t%f\n", exe_time);

    start = clock();
    SelectionSort(arr, size);    
    end = clock();
    exe_time = (end - start) / (double)(CLOCKS_PER_SEC);
    printf("\nSelection sort execution time:\t%f\n", exe_time);

    start = clock();
    InsertionSort(arr, size);    
    end = clock();
    exe_time = (end - start) / (double)(CLOCKS_PER_SEC);
    printf("\nInsertion sort execution time:\t%f\n", exe_time);
}

static void BubbleTest(int *arr, size_t size)
{
    printf("\nBubble sort test\n\n");
    arr = RandArr(arr, 5);
    printf("\nBefore:\n");
    
    PrintArr(arr, size);
    BubbleSort(arr, size);    
    
    printf("\nAfter:\n");

    PrintArr(arr, size);
}

static void OptimizedBubbleTest(int *arr, size_t size)
{
    
    printf("\nOptimized Bubble sort test\n\n");
    arr = RandArr(arr, 5);
    
    printf("\nBefore:\n");
    PrintArr(arr, size);
    
    OptimizedBubbleSort(arr, size);    
    printf("\nAfter:\n");
    PrintArr(arr, size);
}

static void InsertionSortTest(int *arr, size_t size)
{
    printf("\nInsertion sort test\n\n");
    arr = RandArr(arr, 5);
    printf("\nBefore:\n");
    
    PrintArr(arr, size);
    InsertionSort(arr, size);    
  
    printf("\nAfter:\n");
    PrintArr(arr, size);
}

static void SelectionSortTest(int *arr, size_t size)
{
    printf("\nSelection sort test\n\n");
    arr = RandArr(arr, 5);
    printf("\nBefore:\n");
    
    PrintArr(arr, size);
    SelectionSort(arr, size);  
    printf("\nAfter:\n");

    PrintArr(arr, size);
}

static void CountSortTest()
{
    /*int non_sorted_arr[8] = {10, 8, 11, 14, 7, 8, 11, 11};*/
    int non_sorted_arr[8] = {4, -3, 1, 0, -2, 2, 2, -1};
    size_t size = 8;
    int *result = NULL;

    printf("\nCount sort test:\n");
    result = malloc(sizeof(*result) * size);

    CountSort(non_sorted_arr, size, -3, 4, result);

    PrintArr(result, size);
}

/********************
 * INTERNAL FUNCS:  *
********************/
static void PrintArr(int *arr, size_t size)
{
    int i = 0;

    for (i = 0; i < size; i++)
    {
        printf("%d \n", arr[i]);
    }
}

static int *RandArr(int *arr, size_t size)
{
    int i = 0;

    for (i = 0; i < size; i++)
    {
        arr[i] = rand() % 3000 - 6000;
    }

    return arr;
}
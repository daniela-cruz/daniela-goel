/****************************************************
*													*
*	SORT TESTS               						*
*													*
*	Developer: Yara									*
*	Reviewer:   									*	
*	date: 05.11.19									*
*	status: in progress								*
*													*
****************************************************/
#include <stdio.h>      /*printf*/
#include <stdlib.h>     /*rand, srand, qsort*/
#include <string.h>     /*memcpy*/
#include <time.h>       /*clock*/

#include "sort.h"   /*API*/

/*printf color macros*/
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"

/*test funcs*/
static void TestBubbleSort();
static void TestInsertionSort();
static void TestSelectionSort();
static void TestCountSort();
/*callback funcs*/
static void Integration(void);
static void SimpAlgoTimeAndCorrectness(int *rand_arr, 
                                       int *cmp,
                                       void (*sort_func)(int *arr, size_t nmem), 
                                       size_t nmem);
static void ArrCpy(int *dest, int *src, size_t nmem);
static void CreatRandArr(int *arr, size_t nmem);
/********************************************************/		
/********************************************************/
int main()
{
    puts("\n***************************************************");
	printf("\n%s 	**TESTS FOR VAR SIZED ALLOCATOR**%s\n", KGRN, KNRM);
	puts("\n***************************************************");

    /*base tests*/
    TestBubbleSort();
    TestInsertionSort();
    TestSelectionSort();
    TestCountSort();

    /*integration tests*/
    Integration();

	printf("\n\n%s***************************************************%s\n\n", KRED, KNRM);
    return 0;
}
/********************************************************/		
/********************************************************/
/************************************************
*		          BASE TESTS     				*
************************************************/
static void TestBubbleSort()
{
    int to_sort[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int sorted[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t nmem = 10;

    printf("%s***************************************************\n", KRED);
	printf("%sTEST BUBBLE SORT", KNRM);
	printf("%s\n***************************************************%s\n", KRED, KNRM);

    BubbleSort(to_sort, nmem);
    if (memcmp(to_sort, sorted, (nmem * sizeof(int))) != 0)
    {
        printf("\n%s    sorting failed%s", KRED, KNRM);
    }
}

/********************************************************/
static void TestInsertionSort()
{
    int to_sort[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int sorted[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t nmem = 10;

    printf("%s***************************************************\n", KRED);
	printf("%sTEST INSERTION SORT", KNRM);
	printf("%s\n***************************************************%s\n", KRED, KNRM);

    InsertionSort(to_sort, nmem);
    if (memcmp(to_sort, sorted, (nmem * sizeof(int))) != 0)
    {
        printf("\n%s    sorting failed%s", KRED, KNRM);
    }
}

/********************************************************/
static void TestSelectionSort()
{
    int to_sort[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int sorted[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t nmem = 10;

    printf("%s***************************************************\n", KRED);
	printf("%sTEST SELECTION SORT", KNRM);
	printf("%s\n***************************************************%s\n", KRED, KNRM);

    SelectionSort(to_sort, nmem);
    if (memcmp(to_sort, sorted, (nmem * sizeof(int))) != 0)
    {
        printf("\n%s    sorting failed%s", KRED, KNRM);
    }
}

/********************************************************/
static void TestCountSort()
{
    const int to_sort[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int sorted[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int return_arr[10] = {0};

    printf("%s***************************************************\n", KRED);
	printf("%sTEST COUNTING SORT", KNRM);
	printf("%s\n***************************************************%s\n", KRED, KNRM);

    if (0 != CountSort(to_sort, 10, 1, 10, return_arr))
    {
        printf("\n%s    bad return value%s", KRED, KNRM);
    }
    if (memcmp(return_arr, sorted, (10 * sizeof(int))) != 0)
    {
        printf("\n%s    sorting failed%s", KRED, KNRM);
    }
}

/************************************************
*		       INTERGRATION TEST    			*
************************************************/
static void Integration(void)
{
    int *rand_arr = NULL;
    int *sorted_arr = NULL;
    size_t nmem = 20000;

    rand_arr = (int *)malloc(nmem * sizeof(int));
    if (NULL == rand_arr)
    {
        exit(1);
    }
    
    sorted_arr = (int *)malloc(nmem * sizeof(int));
    if (NULL == sorted_arr)
    {
        exit(1);
    }

    /*create random and sorted arr*/
    CreatRandArr(rand_arr, nmem);
    ArrCpy(sorted_arr, rand_arr, nmem);
    BubbleSort(sorted_arr, nmem);

    /*send to time and correctnes with copy*/
    puts("Bubble sort integ test");
    SimpAlgoTimeAndCorrectness(rand_arr, sorted_arr, 
                               BubbleSort, nmem);

    puts("Insertion sort integ test");
    SimpAlgoTimeAndCorrectness(rand_arr, sorted_arr,
                               InsertionSort, nmem);

    puts("Selection sort integ test");
    SimpAlgoTimeAndCorrectness(rand_arr, sorted_arr, 
                               SelectionSort, nmem);

    /*free*/
    free(rand_arr);
    free(sorted_arr);
}

/************************************************
*		         CALLBACK FUNCS    				*
************************************************/
static void SimpAlgoTimeAndCorrectness(int *rand_arr, int *cmp,
                                       void (*sort_func)(int *arr, size_t nmem), 
                                       size_t nmem)
{
    int *cpy = NULL;
    __clock_t t = 0;

    /*make copy*/
    cpy = (int *)malloc(nmem * sizeof(int));
    if (NULL == cpy)
    {
        exit(1);
    }
    ArrCpy(cpy, rand_arr, nmem);
    
    /*take time*/
    t = clock();
    sort_func(cpy, nmem);
    t = clock() - t;
    
    /*check correctness*/
    if (memcmp(cpy, cmp, (nmem * sizeof(int))) != 0)
    {
        printf("\n%s    sorting failed%s\n", KRED, KNRM);
    }
    else
    {
        printf("\n%s    run time for %lu sized arr is: %f%s\n", KGRN, nmem, ((double)t/CLOCKS_PER_SEC), KNRM);
    }

    /*free copy*/
    free(cpy);
}

/********************************************************/
static void CreatRandArr(int *arr, size_t nmem)
{
    size_t i = 0;

    /*create a truly random rand*/
    srand(time(NULL));
    
    /*set arr with signed rand numbers up to 3 digits*/
    for (i = 0; i < nmem; i++)
    {
        arr[i] = rand()%100 - 50;    
    }
}

/********************************************************/
static int Compar(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

/********************************************************/
static void ArrCpy(int *dest, int *src, size_t nmem)
{
    size_t i;

    for (i = 0; i < nmem; i++)
    {
        dest[i] = src[i];
    }
    
}

/********************************************************/
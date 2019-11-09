/****************************************************
*													*
*	SORT ALGORITHMS         						*
*													*
*	Developer: Yara									*
*	Reviewer:   									*	
*	date: 05.11.19									*
*	status: in progress								*
*													*
****************************************************/
#include <stdio.h>      /*sprintf*/
#include <assert.h>     /*assert*/
#include <stdlib.h>     /*malloc*/
#include <string.h>     /*memset*/

#include "sort.h"   /*API*/

static void Swap(int *a, int *b);
/************************************************
*		    SIMPLE SORT ALGORITHMS				*
************************************************/
void BubbleSort(int *arr, size_t size)
{
    size_t i = 0;
    size_t swap_counter = 0;

    assert(NULL != arr);

    for (swap_counter = 0; size > 1; size--) 
    {
        for (i = 0; i < (size - 1); i++)
        {
            if (arr[i] > arr[i + 1])
            {
                Swap(&arr[i], &arr[i + 1]);
                ++swap_counter;
            }
            
        }
        /*if no swap were mades in the end of round, arr is sorted*/
        if (swap_counter == 0)  
        {
            break;
        }
    }
}

/********************************************************/
void InsertionSort(int *arr, size_t size)
{
    size_t i = 0;
    size_t j = 0;
    int tmp = 0;

    assert(NULL != arr);

    for (i = 1; i < size; i++)
    {
        tmp = arr[i];
        for (j = (i - 1); ((int)j >= 0) && (arr[j] > tmp); j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = tmp;
    }
    
}

/********************************************************/
void SelectionSort(int *arr, size_t size)
{
    size_t i = 0;
    size_t j = 0;
    size_t min = 0;

    assert(NULL != arr);

    for (i = 0; i < (size - 1); i++)
    {
        min = i;
        for (j = (i + 1); j < size; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }

        Swap(&arr[i], &arr[min]);

    }
    
}

/************************************************
*		 NON COMPARISON SORT ALGORITHMS			*
************************************************/
int CountSort(const int *to_sort, size_t size, 
              int lowest, int highest, int *return_arr)
{
    int *lut = NULL;
    size_t histogram = highest-lowest + 1;  
    size_t i = 0;

    assert(NULL != to_sort);
    assert(NULL != return_arr);
    
    /*establish histogram size LUT of zeros*/
    lut = (int *)malloc(histogram * sizeof(int));
    if(NULL == lut)
    {
        return 1;
    }
    memset(lut, 0, histogram * sizeof(int));

    /*record num of appearances of values in arr into lut*/
    for (i = 0; i < size; i++)
    {
        ++lut[to_sort[i] - lowest]; /*lut holds relative values*/
    }

    /*transform lut values from appearances num into consecutive indexes*/
    --lut[0];   /*set offsets from 0*/
    for (i = 1; i < histogram; i++)
    {
        lut[i] += lut[i - 1];
    }

    /*sort arr backwords(to keep stability) using lut indexes*/
    for (i = (size - 1); (int)i >= 0; i--)
    {
        return_arr[lut[to_sort[i] - lowest]] = to_sort[i];
        --lut[to_sort[i] - lowest]; /*for next index of the same value*/
    }

    free(lut);

    return 0;
    
}

/************************************************
*		         CALLBACK FUNCS    				*
************************************************/
static void Swap(int *a, int *b)
{
    int tmp = 0;

    tmp = *a;
    *a = *b;
    *b = tmp;
}
/********************************************************/
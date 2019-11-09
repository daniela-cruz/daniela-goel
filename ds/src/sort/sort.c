#include <stdlib.h> /* calloc */
#include <stddef.h> /* size_t */
#include <string.h> /* memset */
#include <assert.h> /* assert */

/*************INTERNAL:**************/
static void Swap(int *data1, int *data2);

static void RadixCountingSort(unsigned int *arr, size_t size, int *histogram, size_t n_bits, 
	size_t iteration, unsigned int *dest);
/*static void InsertResults(int *arr, size_t size, int lower_limit, 
    int upper_limit, int denominator, int *result, int *count_arr);*/

/************CONSTANTS:*************/
static const size_t bits_num = sizeof(size_t) * __CHAR_BIT__;

/********IMPLEMENTATION:*********/
void OptimizedBubbleSort(int *arr, size_t size)
{
    int i = 0, j = 0;
    int flag = 0;

    assert(NULL != arr);
    for (i = 0; (i < size - 1), (0 == flag); i++)
    {
        flag = 1;

        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                Swap(&arr[j], &arr[j + 1]);
                flag = 0;
            }
        }
    }
}

void BubbleSort(int *arr, size_t size)
{
    int i = 0, j = 0;

    assert(NULL != arr);
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                Swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void InsertionSort(int *arr, size_t size)
{
    int i = 0, j = 0;
    int key = 0;

    assert(NULL != arr);
    /*for (i = 1; i < size; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (arr[i] < arr[j])
            {
                Swap(&arr[j], &arr[i]);
            }
        }
    }*/
    for ( i = 1; i < size; i++)
    {
        key = arr[i];

       /* if (j = i - 1; (j > 0) && (arr[i] < arr[j]); j--)
        {
            

        }*/
    }
}

void SelectionSort(int *arr, size_t size)
{
    int i = 0, j = 0;
    int min = 0;

    assert(NULL != arr);
    for (i = 0; i < size; i++)
    {
        min = i;

        for (j = i + 1; j < size; j++)
        {
            min = (arr[j] < arr[min]) ? j : min;
        }
        
        Swap(&arr[i], &arr[min]);
    }
}

int CountSort(const int *arr, size_t size, int lower_limit, int upper_limit, 
    int *result)
{
    int i = 0;
    int j = 0;
    int *count_arr = NULL;
    size_t range = upper_limit - lower_limit + 1;

    assert(NULL != arr);
    assert(NULL != result);
    
    count_arr = calloc(sizeof(*count_arr), range);
    if (NULL == count_arr)
    {
        return 1;
    }
    
    for (i = 0; i < size; i++)
    {
        count_arr[arr[i] - lower_limit]++;
    }

    for (i = 0; i < size; i++)
    {
        for (j = i; (j < size) && (0 < count_arr[i]); j++)
        {
            result[j] = i + lower_limit;
        }
    }

    return 0;
}

int OptimizedCountSort(const int *arr, size_t size, int lower_limit, 
    int upper_limit, int *result)
{
    int i = 0;
    int *count_arr = NULL;
    size_t range = upper_limit - lower_limit + 1;

    assert(NULL != arr);
    assert(NULL != result);
    
    count_arr = calloc(sizeof(*count_arr), range);
    if (NULL == count_arr)
    {
        return 1;
    }
    
    for (i = 0; i < size; i++)
    {
       count_arr[arr[i] - lower_limit]++; 
    }

    for (i = 1; i < range; i++)
    {
        count_arr[i] += count_arr[i - 1];
    }
    

    for (i = size - 1; 0 <= i; i--)
    {
        result[count_arr[arr[i] - lower_limit] - 1] = arr[i];
        count_arr[arr[i] - lower_limit]--;
    }
    
    return 0;
}

int RadixSort(unsigned int *arr, size_t size, size_t n_bits)
{
    int *histogram = NULL;
    unsigned int *result = NULL;
    unsigned int i = 0;
    size_t range = 1 << n_bits;

    result = malloc(sizeof(arr[0]) * size);
    if (NULL == result)
    {
        return 1;
    }

    histogram = malloc(sizeof(*histogram) * range);
    if (NULL == histogram)
    {
        free(result);
        return 1;
    }

    for (i = 0; i < sizeof(int) * __CHAR_BIT__ / n_bits; i++)
    {
        memset(histogram, 0, range * sizeof(arr[0]));
        RadixCountingSort(arr, size, histogram, n_bits, i, result);
    }

    free(result);
    free(histogram);

    return 0;
}

/****************************
 * INTERNAL FUNCS:  *
****************************/
static void Swap(int *data1, int *data2)
{
    int temp;
    
    assert(NULL != data1);
    assert(NULL != data2);

    temp = *data1;
    *data1 = *data2;
    *data2 = temp;
}

static void RadixCountingSort(unsigned int *arr, size_t size, int *histogram, size_t n_bits, 
	size_t iteration, unsigned int *dest)
{
    ptrdiff_t i = 0;
    size_t range = 1 << n_bits; 
    size_t mask = (1 << n_bits) - 1;

    for(i = 0; i < size; i++)
    {
        histogram[(arr[i] >> (iteration * n_bits)) & mask]++;
    }

    for(i = 1; i < range; i++)
    {
        histogram[i] = histogram[i] + histogram[i - 1];
    }

    for(i = (ptrdiff_t)size - 1; 0 <= i; i--)
    {
        size_t curr_idx = 0;

        histogram[(arr[i] >> (iteration * n_bits)) & mask]--;
        curr_idx =  histogram[(arr[i] >> (iteration * n_bits)) & mask];
        dest[curr_idx] = arr[i];
    }

    memcpy(arr, dest, size * sizeof(int));
}

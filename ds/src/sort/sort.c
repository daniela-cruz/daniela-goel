#include <stdlib.h> /* calloc */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

static const size_t bits_num = sizeof(size_t) * __CHAR_BIT__;
/*static const size_t base = 10;*/

static void Swap(int *data1, int *data2);

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
    /*for ( i = 1; i < size; i++)
    {
        key = arr[i];

        if (j = i - 1; (j > 0) && (arr[i] < arr[j]); j--)
        {
            

        }
       
    }*/
    
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
/*
void RadixSort(int *arr, size_t size, int lower_limit, int upper_limit, 
    int* result)
{
    int denominator = 1;

    assert(NULL != arr);
    assert(NULL != result);

    for (; upper_limit; )
    {
        RadixCountSort(arr, size, lower_limit, upper_limit, denominator, result);
        denominator *= base;
        upper_limit /= base;
    }
}*/

int RadixSort(size_t *arr, size_t size, size_t n_bits)
{
    size_t *histogram = NULL;
    int i = 0, j = 0;

    assert(NULL != arr);
    histogram = calloc(sizeof(*histogram), n_bits * size_t);
    if (NULL == histogram)
    {
        return 1;
    }
    
    for ( i = bits_num / n_bits; 0 < i; i >>= n_bits)
    {
        for (j = 0; j < size; j++)
        {
            if (i == (arr[j] & i))
            {
                histogram[i]++;
            }
        }
    }
    

    return 0;
}

/********************
 * INTERNAL FUNCS:  *
********************/
static void Swap(int *data1, int *data2)
{
    int temp;
    
    assert(NULL != data1);
    assert(NULL != data2);

    temp = *data1;
    *data1 = *data2;
    *data2 = temp;
}

static void RadixCountSort(int *arr, size_t size, int lower_limit, 
    int upper_limit, int denominator, int *result)
{
    int i = 0;

    /*int i, freq[range]={0};
    int output[n];

    for(i=0;i<n;i++)
            freq[(arr[i]/place)%range]++;
    for(i=1;i<range;i++)
            freq[i]+=freq[i-1];
    for(i=n-1;i>=0;i--)
    {
            output[freq[(arr[i]/place)%range]-1]=arr[i];
            freq[(arr[i]/place)%range]--;
    }
    for(i=0;i<n;i++)
        arr[i]=output[i];*/
}
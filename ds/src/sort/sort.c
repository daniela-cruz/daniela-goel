#include <stdlib.h> /* calloc */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

static void Swap(int *data1, int *data2);

void OptimizedBubbleSort(int *arr, size_t size)
{
    int i = 0, j = 0;
    int temp = 0;
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
    int temp = 0;

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
    int temp = 0; 

    for (i = 1; i < size; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (arr[i] < arr[j])
            {
                Swap(&arr[j], &arr[i]);
            }
        }
    }
}

void SelectionSort(int *arr, size_t size)
{
    int i = 0, j = 0;
    int temp = 0;
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
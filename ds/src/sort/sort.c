#include <stdlib.h> /* calloc */
#include <stddef.h> /* size_t */
#include <string.h> /* memset */
#include <assert.h> /* assert */

#include "sort.h" /* cmp_func_t */

/*************INTERNAL:**************/
static void Swap(int *data1, int *data2);

static void RadixCountingSort(unsigned int *arr, size_t size, int *histogram, size_t n_bits, 
	size_t iteration, unsigned int *dest);

void MergeDown(void *arr, size_t element_size, size_t arr_size, 
    cmp_func_t func, void *param);

static void *GetAddr(void *arr, size_t idx, size_t element_size);

/*static void InsertResults(int *arr, size_t size, int lower_limit, 
    int upper_limit, int denominator, int *result, int *count_arr);*/

/************CONSTANTS:*************/
static const size_t bits_num = sizeof(size_t) * __CHAR_BIT__;

/********IMPLEMENTATION:*********/
void MergeSort(void *arr, size_t element_size, size_t arr_size, 
    cmp_func_t func, void *param)
{
    int left = 0, mid = 0, right = 0;
    void *arr_start = NULL, *arr_end = NULL;

    mid = arr_size / 2;
    right = arr_size;

    arr_start = arr;
    arr_end = (char *)arr + ((arr_size - 1) * element_size);
    

    if (arr_start == arr_end)
    {
        return;
    }

        MergeSort(arr, element_size, mid, func, param);
        MergeSort((char *)arr + (mid * element_size), element_size, 
            right - mid, func, param);
        MergeDown(arr, element_size, arr_size, func, param);
        /* MergeDown((char *)arr + (mid * element_size), element_size, right - mid, func, param); */
}

void MergeDown(void *arr, size_t element_size, size_t arr_size, 
    cmp_func_t func, void *param)
{
    void *arr_l = NULL, *arr_r = NULL;
    int left = 0, mid = 0, right = arr_size;
    int i = 0, j = 0, k = 0;
    void *arr_end = NULL;

    arr_end = (char *)arr + ((arr_size - 1) * element_size);

    mid = arr_size / 2;
    
    arr_l = malloc(element_size * mid);
    if (NULL == arr_l)
    {
<<<<<<< HEAD
        return;
    }
    
    /* memcpy(arr_l, arr, element_size * mid); */
    memcpy(arr_l, GetAddr(arr, 0, element_size), mid * element_size);
=======
        return NULL;
    }
    
    /* memcpy(arr_l, arr, element_size * mid); */
    memcpy(arr_l, GetAddr(arr, mid, element_size), mid * element_size);
>>>>>>> 8775a961cebe605abd532bcc97a11cf3ba574632
    
    arr_r = malloc(element_size * (arr_size - mid));
    if (NULL == arr_r)
    {
        free(arr_l);
<<<<<<< HEAD
        return;
    }
    /* memcpy(arr_r, ((char *)arr + mid), element_size * (arr_size - mid)); */
    memcpy(arr_r, GetAddr(arr, right - mid, element_size), 
        (right - mid) * element_size);
=======
        return NULL;
    }
    /* memcpy(arr_r, ((char *)arr + mid), element_size * (arr_size - mid)); */
    memcpy(arr_r, GetAddr(arr, right - mid, element_size), (right - mid) * element_size);
>>>>>>> 8775a961cebe605abd532bcc97a11cf3ba574632

    for (i = 0, j = 0, k = 0; (i < mid) && (j < right - mid); k++)
    {
        if (0 < func(((char *)arr_l + (i * element_size)), ((char *)arr_r + 
            (j * element_size)), param))
        {
            /* memcpy(((char *)arr + (k * element_size)), ((char *)arr_l + (i * element_size)), 
                element_size); */
<<<<<<< HEAD
            memcpy(GetAddr(arr, k, element_size), GetAddr(arr_l, i, element_size), 
                element_size);
=======
            memcpy(GetAddr(arr, k, element_size), GetAddr(arr_l, i, element_size), element_size);
>>>>>>> 8775a961cebe605abd532bcc97a11cf3ba574632
            i++;
        }
        else
        {
            /* memcpy((char *)arr + (k * element_size), 
                ((char *)arr_r + ((mid + j) * element_size)), element_size); */
            memcpy(GetAddr(arr, k, element_size), GetAddr(arr_r, j, element_size), element_size);
            j++;
        }
    }

    if(i < mid)
    {
        memcpy(GetAddr(arr, k, element_size), GetAddr(arr_l, i, element_size), 
            (mid - i) * element_size);
    }
    else
    {
        memcpy(GetAddr(arr, k, element_size), GetAddr(arr_r, j, element_size), 
            (arr_size - mid - j) * element_size);
    }


    free(arr_l); free(arr_r); 

    return;
}

static void *GetAddr(void *arr, size_t idx, size_t element_size)
{
    return ((char *)arr + idx * element_size);
}

<<<<<<< HEAD
=======
static void *GetAddr(void *arr, size_t idx, size_t element_size)
{
    return ((char *)arr + idx * element_size);
}

>>>>>>> 8775a961cebe605abd532bcc97a11cf3ba574632

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
    for ( i = 1; i < size; i++)
    {
		key = arr[i];
		
		for (j = i - 1; (0 < j) && (key < arr[j]); j--)
		{
			arr[j + 1] = arr[j]; 
		}
		
		arr[j + 1] = key;
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

    free(result); result = NULL;
    free(histogram); histogram = NULL;

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
    int i = 0;
    size_t range = 1 << n_bits; 
    size_t mask = (1 << n_bits) - 1;

    for (i = 0; i < size; i++)
    {
        histogram[(arr[i] >> (iteration * n_bits)) & mask]++;
    }

    for (i = 1; i < range; i++)
    {
        histogram[i] = histogram[i] + histogram[i - 1];
    }

    for (i = size - 1; 0 <= i; i--)
    {
        size_t curr_idx = 0;

        histogram[(arr[i] >> (iteration * n_bits)) & mask]--;
        curr_idx =  histogram[(arr[i] >> (iteration * n_bits)) & mask];
        dest[curr_idx] = arr[i];
    }

    memcpy(arr, dest, size * sizeof(int));
}

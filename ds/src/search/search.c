#include <math.h> /* sqrt */

#include "search.h"

static void *GetAddr(void *arr, size_t ele_size, int index);

void *BinSearchRec(void *arr, int last_idx, size_t ele_size,
                   void *key, srch_cmp_func_t cmp_func)
{
    int result = -1;
    void *element = NULL;

    element = (char *)arr + ((last_idx / 2) * (ele_size));

    if (NULL == element)
    {
        return NULL;
    }

    result = cmp_func(element, key);
    if (0 == result)
    {
        return element;
    }
    else if (0 < result)
    {
        BinSearchRec(arr, last_idx / 2, ele_size, key, cmp_func);
    }
    else
    {
        BinSearchRec(element, last_idx - (last_idx / 2), ele_size, key, cmp_func);
    }
}

void *BinarySearch(void *arr, int last_idx, size_t ele_size,
                   void *key, srch_cmp_func_t cmp_func)
{
    int result = -1;
    int mid = 0;
    void *first_ptr = NULL;
    void *last_ptr = NULL;

    mid = (last_idx / 2) - 1;
    first_ptr = GetAddr(arr, ele_size, mid);
    last_ptr = GetAddr(arr, ele_size, last_idx - 1);

    while (first_ptr <= last_ptr)
    {
        result = cmp_func(first_ptr, key);
        if (0 == result)
        {
            return first_ptr;
        }

        mid = (((char *)last_ptr - (char *)first_ptr) / ele_size) / 2;
        if (0 < result)
        {
            last_ptr = first_ptr;
            first_ptr = GetAddr(arr, ele_size, mid / 2);
        }
        else
        {
            first_ptr = GetAddr(arr, ele_size, 
                (((char *)last_ptr - (char *)arr) / ele_size) - mid);
        }
    }

    return NULL;
}

void *JumpSearch(void *arr, int last_idx, size_t ele_size,
                 void *key, srch_cmp_func_t cmp_func)
{
    int i = 0;
    void *element = NULL;
    double jump = 0;

    jump = sqrt(last_idx);
    for (i = 0; i < last_idx; i += jump)
    {
        element = GetAddr(arr, ele_size, i);

        if (0 <= cmp_func(element, key))
        {
            break;
        }
    }

    for (; 0 <= i; i--)
    {
        element = GetAddr(arr, ele_size, i);
        if (0 == cmp_func(element, key))
        {
            return element;
        }
    }

    return NULL;
}

/****************************
 *       INTERNAL           *
****************************/

static void *GetAddr(void *arr, size_t ele_size, int idx)
{
    return ((char *)arr + (idx * ele_size));
}

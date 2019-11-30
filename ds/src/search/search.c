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

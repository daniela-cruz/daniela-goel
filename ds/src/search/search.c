#include "search.h"


void *BinSearchRec(void *arr, int last_idx, size_t ele_size, 
    void* key, srch_cmp_func_t cmp_func)
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
        BinSearchRec(element, last_idx, ele_size, key, cmp_func);
    }
    else
    {
        BinSearchRec(arr, last_idx / 2, ele_size, key, cmp_func);
    }
}
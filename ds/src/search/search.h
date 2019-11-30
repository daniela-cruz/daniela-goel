#ifndef __SEARCH_H__
#define __SEARCH_H__
#include <stddef.h>

typedef int(*srch_cmp_func_t)(const void *data1, const void *data2);

void *BinarySearch(void *arr, int last_idx, size_t ele_size,
    void *key, srch_cmp_func_t cmp_func);
    
void *BinSearchRec(void *arr, int last_idx, size_t ele_size, 
    void* key, srch_cmp_func_t cmp_func);

void *JumpSearch(void *arr, int last_idx, size_t ele_size,
    void *key, srch_cmp_func_t cmp_func);

#endif /* __SEARCH_H__ */
#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h> /* size_t */

typedef int (*cmp_func_t)(void *ele1, void *ele2, void *param);

void BubbleSort(int *arr, size_t size);

void OptimizedBubbleSort(int *arr, size_t size);

void InsertionSort(int *arr, size_t size);

void SelectionSort(int *arr, size_t size);

int CountSort(const int *arr, size_t size, int lower_limit, int upper_limit, 
    int *result);

/*      Same as countSort with an O(n)      * 
 *      time complecity                     */
int OptimizedCountSort(const int *arr, size_t size, int lower_limit, 
    int upper_limit, int *result);

int RadixSort(unsigned int *arr, size_t size, size_t n_bits);

void *MergeSort(void *arr, size_t element_size, size_t arr_size, 
    cmp_func_t func, void *param);

#endif /* __SORT_H__ */

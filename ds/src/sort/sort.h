#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h> /* size_t */

void BubbleSort(int *arr, size_t size);

void OptimizedBubbleSort(int *arr, size_t size);

void InsertionSort(int *arr, size_t size);

void SelectionSort(int *arr, size_t size);

/*  */
int CountSort(const int *arr, size_t size, int lower_limit, int upper_limit, 
    int *result);

/*      Same as countSort with an O(n) 
 *      time complecity                     */
int OptimizedCountSort(const int *arr, size_t size, int lower_limit, 
    int upper_limit, int *result);

#endif /* __SORT_H__ */
/****************************************************
*													*
*	SORT API                 						*
*													*
*	Developer: Yara									*
*	Reviewer:   									*	
*	date: 05.11.19									*
*	status: in progress								*
*													*
****************************************************/
#ifndef __OL7677_SORT_ALGORITHMS
	#define __OL7677_SORT_ALGORITHMS

#include <stddef.h>  /*size_t*/

/********************************************************/
/*simple sorting*/
/*worst time complexity: O(n^2)*/
void BubbleSort(int *arr, size_t size);
void InsertionSort(int *arr, size_t size);
void SelectionSort(int *arr, size_t size);
/********************************************************/
/*non comparison sorting*/
int CountSort(const int *shuffled_arr, size_t size, 
              int lowest, int highest, int *sorted_arr);
/********************************************************/

#endif /*__OL7677_SORT_ALGORITHMS*/
#include <stdio.h> /* printf */

#include "sort.h"

static int arr[5] = {64, 12, 56, 11, 5};

int main()
{
    int i = 0;
    int *arr_ptr = arr;

    arr_ptr = BubbleSort(arr_ptr, 5);
    /*arr_ptr = SelectionSort(arr_ptr, 5);*/

    for (i = 0; i < 5; i++)
    {
        printf("%d \n", arr[i]);
    }
    return 0;
}
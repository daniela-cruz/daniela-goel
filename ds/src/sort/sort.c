
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

int *BubbleSort(int *arr, size_t size)
{
    int i = 0, j = 0, end = 0;
    int temp = 0;

    assert(NULL != arr);
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }

    return arr;
}

int *SelectionSort(int *arr, size_t size)
{
    int i = 0, j = 0;
    int temp = 0;
    int min = 0;

    assert(NULL != arr);
    for (i = 0; i < size - 1; i++)
    {
        for (j = i + 1; j < size; j++)
        {
            min = (arr[j] < arr[i]) ? j : min;
        }

        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }

    return arr;
}
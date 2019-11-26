#include <stdio.h> /*printf*/

#include "heap.h"

int IsBefore(const void *data1, const void *data2, void *param);

int main()
{
    int arr[] = {12, 13, 80, 20, 90, 70, 0, 21, -31, 22, -19};
    size_t i = 0;
    heap_t *heap1 = NULL;

    heap1 = HEAPCreate(IsBefore, NULL);
    for (i = 0; i < 11 ;++i)
    {
        HEAPPush(heap1, &arr[i]);
    }
    PrintHeap(heap1);
    printf("\n%lu - size \n", HEAPSize(heap1));

    HEAPPop(heap1);
    HEAPPop(heap1);
    HEAPPop(heap1);

    PrintHeap(heap1);
    printf("\n%lu - size \n", HEAPSize(heap1));

    HEAPDestroy(heap1);

    return 0;
}

int IsBefore(const void *data1, const void *data2, void *param)
{
    (void)param;
    return !!(*(int *)data1 < *(int *)data2);
}

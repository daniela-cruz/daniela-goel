#include <stdio.h> /* printf */

#include "heap.h"

static void HeapTest();
int IsBefore(const void *data1, const void *data2, void *param);

static size_t arr[10] = {20, -10, 30, 50, 100, 40, 60, 80, 90, 70};

int main()
{
    HeapTest();

    return 0;
}

static void HeapTest()
{
    int i = 0;
    heap_t *heap = NULL;
    size_t size = 10;

    printf("Heap test\n");
    heap = HEAPCreate(IsBefore, NULL);

    printf("Heap is empty? 1 for yes: %d\n", HEAPIsEmpty(heap));

    for ( i = 0; i < size; i++)
    {
        HEAPPush(heap, (void *)&arr[i]);
    }
    
    printf("Printing heap:\n");
    PrintHeap(heap);

    printf("Heap size is: %ld\n", HEAPSize(heap));
    printf("Heap is empty? 0 for no: %d\n", HEAPIsEmpty(heap));
    printf("\n");

    for ( i = size - 1; 0 <= i; --i)
    {
        printf("Peek %d is: %ld\n", i + 1, *(size_t *)HEAPPeek(heap));
        HEAPPop(heap);
    }
    
    HEAPDestroy(heap);
}

int IsBefore(const void *data1, const void *data2, void *param)
{
    (void)param;

    return **(int **)data1 < **(int**)data2;
}
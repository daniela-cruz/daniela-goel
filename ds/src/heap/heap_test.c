#include <stdio.h> /* printf */

#include "heap.h"

static void HeapTest();
int IsBefore(const void *data1, const void *data2, void *param);

static size_t arr[5] = {10,15,79,2,8};

int main()
{
    HeapTest();

    return 0;
}

static void HeapTest()
{
    int i = 0;
    heap_t *heap = NULL;

    printf("Heap test\n");
    heap = HEAPCreate(IsBefore, NULL);

    for ( i = 0; i < 5; i++)
    {
        HEAPPush(heap, (void *)&arr[i]);
        printf("Peek %d is: %ld\n", i, *(size_t *)HEAPPeek(heap));
    }
    

    HEAPDestroy(heap);
}

int IsBefore(const void *data1, const void *data2, void *param)
{
    (void)param;

    return *(int *)data1 < *(int*)data2;
}
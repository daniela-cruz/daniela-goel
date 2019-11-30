#include <stdio.h> /*puts*/
#include "heap.h"

void TestCreate();
int IsBeforeInt(const void *data1, const void *data2, void *param);
void TestPush();
int IsMatchInt(const void *data1, const void *data2);

int main()
{
    TestCreate();
    TestPush();

    return 0;
}

void TestCreate()
{
    heap_t *heap = NULL;

    heap = HEAPCreate(IsBeforeInt, NULL);
    heap != NULL ? puts("SUCC") : puts("ERROR");

    HEAPIsEmpty(heap) ? puts("SUCC") : puts("ERROR");
}

void TestPush()
{
    heap_t *heap = NULL;
    int data[] = {3, 4, 5, 2, 10, 2, 2, -1, 5};
    int push_status = 0;

    heap = HEAPCreate(IsBeforeInt, NULL);
    push_status = HEAPPush(heap, &data[0]);
    push_status != 0 ? puts("ERROR") : puts("SUCC");

    printf("push 3\n");
    PrintHeapVec(heap);

    HEAPPush(heap, &data[1]);
    HEAPPush(heap, &data[2]);
    HEAPPush(heap, &data[3]);

    printf("push 4 5 2\n");
    PrintHeapVec(heap);

    HEAPPop(heap);
    printf("after pop\n");
    PrintHeapVec(heap);

    HEAPPush(heap, &data[4]);
    HEAPPush(heap, &data[5]);
    HEAPPush(heap, &data[6]);
    HEAPPush(heap, &data[7]);
    HEAPPush(heap, &data[8]);

    printf("exp:\n5 4 2 3 2 2 1\nres:\n");
    PrintHeapVec(heap);

    printf("after removal of 5:\n");
    HEAPErase(heap, IsMatchInt, &data[2]);
    PrintHeapVec(heap);

}

int IsBeforeInt(const void *data1, const void *data2, void *param)
{
    (void)param;

    return *(int *)data1 < *(int *)data2;
}

int IsMatchInt(const void *data1, const void *data2)
{
    return *(int *)data1 == *(int *)data2;
}


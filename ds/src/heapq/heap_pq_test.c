#include <stdio.h> /* printf */

#include "pq.h"

void HeapQTest();
int IsBefore(void *data1, void *data2, void *param);

int arr[10] = {20, -10, 30, 50, 100, 40, 60, 80, 90, 70};

int main()
{
    HeapQTest();
    
    return 0;
}

void HeapQTest()
{
    pq_t *pq = NULL;
    size_t size = 10;
    int i = 0;

    pq = PQCreate(IsBefore, NULL);

    (NULL == pq) ? printf("ERROR\n") : printf("Allocated new queue\n");
    printf("Is queue empty? expecting 1 for yes: %d\n", PQIsEmpty(pq));

    for (i = 0; i < size; i++)
    {
        PQEnqueue(pq, &arr[i]);
        printf("%d\n", *(int*)PQPeek(pq));
    }
    
    printf("\nDequeuing tasks:\n");
    for ( i = 0; i < size; i++)
    {
       printf("%d\n", *(int*)PQPeek(pq));
       PQDequeue(pq) ;
    }
    
}

int IsBefore(void *data1, void *data2, void *param)
{
    (void)param;
    
    return *(int*)data1 > *(int*)data2;
}
#include <stdio.h>

#include "hash.h"

size_t HashFunc(const void* key);
int CmpData(const void* data1, const void* data2);
int ActionFunc(void *data, void *param);

static void HashTest();


static int arr[100] = {0};

int main()
{
    HashTest();

    return 0;
}

static void HashTest()
{
    hash_t *hash = NULL;
    size_t size = 10;
    int i = 0;

    for ( i = 0; i < 100; i++)
    {
        arr[i] = i + 100;
    }
    

    printf("Hash test\n");
    hash = HASHCreate(HashFunc, CmpData, size);
    (NULL == hash) ? printf("Could not allocate hash\n") : printf("");

    for ( i = 0; i < 100; i++)
    {
        HASHInsert(hash, &arr[i]);
    }
    
    printf("Size counted is: %ld, size expected is 100\n", HASHSize(hash));
    (0 == HASHIsEmpty(hash)) ? printf("") : printf("Returned empty but hahs is full\n");

    for ( i = 0; i < 100; i++)
    {
        printf("%d\n", *(int*)HASHFind(hash, &arr[i]));
    }

    printf("Removing some items\n");
    for ( i = 0; i < 50; i++)
    {
        HASHRemove(hash, &arr[i + 20]);
    }
    
    printf("Size counted is: %ld, size expected is 50\n", HASHSize(hash));

    

    HASHDestroy(hash);

}

size_t HashFunc(const void* key)
{
    if(0 > *(int *)key)
    {
        return -(*(int *)key % 10);
    }

    return *(int *)key % 10;
}

int CmpData(const void* data1, const void* data2)
{
    return *(int*)data1 - *(int*)data2;
}

int ActionFunc(void *data, void *param)
{
    (void)param;

    printf("%d\n", *(int *)data);
}
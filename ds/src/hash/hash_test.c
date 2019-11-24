#include <printf.h>

#include "hash.h"

size_t HashFunc(const void* key);
int CmpData(const void* data1, const void* data2);

size_t HashFunc(const void* key);


static int arr[100];

int main()
{
    HashTest();

    return 0;
}

static void HashTest()
{
    hash_t *hash = NULL;
    size_t size = 10;

    printf("Hash test\n");
    hash = HASHCreate(HashFunc, CmpData, size);
    (NULL == hash) ? printf("Error %d\n", __LINE__) : printf("");

    

}

size_t HashFunc(const void* key)
{
    if(0 > *(int *)key)
    {
        return -(*(int *)key % 7);
    }

    return *(int *)key % 10;
}

int CmpData(const void* data1, const void* data2)
{
    return *(int*)data1 - *(int*)data2;
}
#include <stdio.h>
#include "bst.h"

int IsBefore(void* key1, void* key2, void *param);
static int Print (void* data, void* param);


int main()
{
    bst_t *new_bst = NULL;
    size_t i = 0;
    int arr1[23] = {30, 10, 40, 15, 50, 2, 17, -16, 97, 9, 45 , 48, 46, 12, 37, 38, 35, 100, 200 , 175 ,-13, -20 , 120 };
    /*int arr1[14] = {15, 18, 6, 7, 13, 9, 8, 3, 4, 2, 16 , 20, 17, -3};*/

    new_bst = BSTCreate(IsBefore, NULL);
    for(i = 0 ; i < 23 ; ++i)
    {
        BSTInsert(new_bst, &arr1[i]);
    }
    
    
    printf("all array :\n");
    BSTForEach(BSTBegin(new_bst), BSTEnd(new_bst), Print, NULL );printf("\n");
    printf("last 2 elements\n");
    BSTForEach(BSTIterPrev(BSTIterPrev(BSTEnd(new_bst))), BSTEnd(new_bst), Print, NULL );
    printf("\nfrom %d to %d\n",arr1[2], arr1[11]);
    BSTForEach(BSTFind(new_bst,&arr1[2]), BSTFind(new_bst,&arr1[11]), Print, NULL );
    printf("\nremove %d and %d and %d\n", arr1[2], arr1[1], arr1[6]);
    BSTRemove(BSTFind(new_bst,&arr1[1]));
    BSTRemove(BSTFind(new_bst,&arr1[2]));
    BSTRemove(BSTFind(new_bst,&arr1[6]));
    printf("all array :\n");
    BSTForEach(BSTBegin(new_bst), BSTEnd(new_bst), Print, NULL );
    printf("\n");
    printf("\n");
    BSTInsert(new_bst, &arr1[1]);
    BSTInsert(new_bst, &arr1[2]);
    BSTInsert(new_bst, &arr1[6]);
    for(i = 0 ; i < 23 ; ++i)
    {
        BSTRemove(BSTFind(new_bst,&arr1[i]));
        BSTForEach(BSTBegin(new_bst), BSTEnd(new_bst), Print, NULL );
        printf("- array with no %d\n", arr1[i]);
        BSTInsert(new_bst, &arr1[i]);
    }
    BSTDestroy(new_bst);
   
    return 0; 
}
int IsBefore(void* key1, void* key2, void *param)
{
    return *(int *)key1 < *(int *)key2;
}

static int Print (void* data, void* param)
{
    (void)param;
    printf("%d ", *(int*)data);
    fflush(stdout);
    return 0;
}
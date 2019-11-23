#include <stdlib.h>
#include <assert.h>
#include <stdio.h> 
#include<time.h> 

#include "avl.h"

int Lenght = 6;
int user_is_before(const void *data1, const void *data2, void *param);
int user_action_print(void *data1, void *param);
int InsertSecondTree(void *data1, void *param);
static void RandomArr(int *arr, size_t size);

int main()
{
    avl_t *avl;
    avl_t *avl2;
    /*int arr[23] = {4, 2, 3, 15, 50, 2, 17, -16, 97, 9, 45 , 48, 46, 12, 37, 38, 35, 100, 200 , 175 ,-13, -20 , 120 };*/
    int arr[6] = {1,2,3,4,5,6};
    int arr2[6] = {7,8,9,10,11,12};
    size_t i = 0;
    
    /* RandomArr(arr , Lenght); */

    avl = AVLCreate(user_is_before , NULL);
    avl2 = AVLCreate(user_is_before , NULL);

    printf("Inserting to avl\n");
    for(i = 0 ; i < Lenght ; ++i)
    {
        AVLInsert(avl, &arr[i]);
    }
    
    /* printf("For each\n");
    AVLForEach(avl , InsertSecondTree, avl2); */

    printf("Remove & insert:\n");
    for(i = 0 ; i < Lenght ; ++i)
    {
        printf("Removing %d\n", i);
        AVLRemove(avl, &arr[i]);
        printf("Adding back %d\n", i);
        AVLInsert(avl, &arr[i]);
    }
    
    /*AVLForEach(avl2 , user_action_print, NULL);*/
    printf("\nfirst tree height - %lu  size -%lu\n",AVLHeight(avl), AVLSize(avl));
    printf("\nsecond tree height - %lu\n",AVLHeight(avl2) );
    AVLDestroy(avl);
    AVLDestroy(avl2);
    
    return 0;
}

int user_is_before(const void *data1, const void *data2, void *param)
{
    (void)param;

    return *(int*)data1 < *(int*)data2;
}

int user_action_print(void *data1, void *param)
{
    printf("%d, ", *(int*)data1);
    fflush(stdout);
    return 0;
}
int InsertSecondTree(void *data1, void *param)
{
    AVLInsert(param, data1);
    return 0 ;
}
static void RandomArr(int *arr, size_t size)
{
    size_t i = 0;

    srand(time(0));

    for(i = 0; i < size; ++i)
    {
        arr[i] =  rand();
    }
}


#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

#define ADD_RED printf("\033[1;31m")
#define END_RED printf("\033[0m")

static void CreateTest();
static void MultipleInsertTest();
static void IterTest(bst_t *tree);

int IsBefore(void *data1, void *data2, void *param);

int Add10(void *data, void *param);

static int arr[10];
const size_t arr_size = 10;

int main()
{
    /*CreateTest();*/
    /*InsertTest();*/
    MultipleInsertTest();

    return 0;
}

static void CreateTest()
{
    bst_t *tree = NULL;
    bst_iter_t it;

    printf("\nBST Create test:\n");
    tree = BSTCreate(IsBefore, NULL);
    
    if (NULL != tree)
    {
        printf("Allocated a new tree. . .\n");
    }
    else
    {
        ADD_RED; printf("Could not allocate the tree.\n"); END_RED;
    }
}

static void MultipleInsertTest()
{
    bst_t *tree = NULL;
    int i = 0, j = 0, num1 = 1, num2 = 2, num3 = 3;
    bst_iter_t it;

    printf("\nMultiple insert test\n");

    tree = BSTCreate(IsBefore, NULL);
    for ( i = 0; i < arr_size; i++)
    {
        arr[i] = i;
    }
    
    for ( i = arr_size / 2; i < arr_size; i++)
    {
        it = BSTInsert(tree, &arr[i]);
    }

    for ( i = 0; i < arr_size / 2; i++)
    {
        it = BSTInsert(tree, &arr[i]);
    }
    
    

    printf("\nNext Iteration test\n");
    for ( it = BSTBegin(tree); 
        !BSTIterIsSame(it, BSTEnd(tree)); 
        it = BSTIterNext(it))
    {
        printf("Element is: %d\n", *(int*)BSTGetData(it));
    }
    
    printf("\nFind test\n");
    it = BSTFind(tree, &arr[4]);
    printf("Element is: %d\n", *(int*)BSTGetData(it));

    BSTforEach(BSTBegin(tree), BSTEnd(tree), Add10, NULL);
    
    printf("\nForEach test\n");
    for ( it = BSTIterPrev(BSTEnd(tree)); 
        !BSTIterIsSame(it, BSTEnd(tree));
        it = BSTIterPrev(it))
    {
        printf("Element is: %d\n", *(int*)BSTGetData(it));
    }


    printf("\nRemoval test\n");
    it = BSTIterNext(BSTIterNext(BSTBegin(tree)));
    printf("Element to be removed is: %d\n", *(int*)BSTGetData(it));
    it = BSTRemove(it);
    printf("Element after previous was removed is: %d\n", *(int*)BSTGetData(it));
}

/**********************
 *  FUNCTIONS         *
**********************/
int IsBefore(void *data1, void *data2, void *param)
{
    (void) param;

    return *(int *)data1 < *(int *)data2;
}

int Add10(void *data, void *param)
{
    *(int *)data += 10;

    return 0;
}
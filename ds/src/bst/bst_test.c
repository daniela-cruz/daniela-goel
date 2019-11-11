#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

#define ADD_RED printf("\033[1;31m")
#define END_RED printf("\033[0m")

static void CreateTest();
static void InsertTest();
static void MultipleInsertTest();
static void IterTest(bst_t *tree);

int IsBefore(void *data1, void *data2, void *param);

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
    int i = 0, num1 = 1, num2 = 2, num3 = 3;
    bst_iter_t it;

    printf("\nMultiple insert test\n");

    tree = BSTCreate(IsBefore, NULL);
    for ( i = 0; i < arr_size; i++)
    {
        arr[i] = i;
    }
    
    for ( i = 0; i < arr_size; i++)
    {
        it = BSTInsert(tree, &arr[i]);
    }
    
    it = BSTBegin(tree);

    printf("\nNext Iteration test\n");
    for ( i = arr_size / 2; i < arr_size; i++)
    {
        printf("Element is: %d\n", *(int*)BSTGetData(it));
        it = BSTIterNext(it);
    }

    for ( i = arr_size - 1; (arr_size / 2) - 1 < i ; i--)
    {
        printf("Element is: %d\n", *(int*)BSTGetData(it));
        it = BSTIterNext(it);
    }

    it = BSTEnd(tree);
    it = BSTIterPrev(it);
    printf("\nPrev Iteration test\n");
    printf("Element is: %d\n", *(int*)BSTGetData(it));
    /*for ( i = 0; i < arr_size; i++)
    {
        printf("Element is: %d\n", *(int*)BSTGetData(it));
        it = BSTIterPrev(it);
    }*/

    /*printf("\nRemove test\n");
    it = BSTIterNext(BSTBegin(tree));
    printf("Removing element: %d\n", *(int*)BSTGetData(it));
    it = BSTRemove(it);*/

    /*printf("Iterator now points to: %d\n", *(int*)BSTGetData(it));*/
    /*it = BSTBegin(tree);
    for ( i = 0; i < arr_size - 1; i++)
    {
        printf("Element is: %d\n", *(int*)BSTGetData(it));
        it = BSTIterNext(it);
    }*/
    

    /*printf("\nPrev Iteration test\n");
    for ( i = arr_size - 1; 0 <= i; i--)
    {
        printf("Element is: %d\n", *(int*)BSTGetData(it));
        it = BSTIterPrev(it);
    }*/
}
static void InsertTest()
{
    bst_t *tree = NULL;
    int num1 = 1, num2 = 2, num3 = 3;
    bst_iter_t it; 

    printf("\nBST Insert test:\n");
    tree = BSTCreate(IsBefore, NULL);

    it = BSTInsert(tree, (void *)&num2);
    
    printf("\nInserting to root. . .\n");
    if (num2 == *(int *)BSTGetData(it)) 
    {
        printf("Data in root stored correctly\n");
        it = BSTBegin(tree);
        if (num2 == *(int *)BSTGetData(it)) 
        {
            printf("Data from iterator in root stored correctly\n"); 
        }
        else
        {
            ADD_RED; printf("ERROR: data is: %d\n", *(int *)BSTGetData(it)); END_RED;
        }
    }
    else
    {
        ADD_RED; printf("ERROR: data is: %d\n", *(int *)BSTGetData(it)); END_RED;
    }

    printf("\nInserting to left node. . .\n");
    it = BSTInsert(tree, (void *)&num1);
    if (num1 == *(int *)BSTGetData(it)) 
    {
        printf("Data in new node stored correctly\n");
    }
    else
    {
        ADD_RED; printf("ERROR: data is: %d\n", *(int *)BSTGetData(it)); END_RED;
    }

    printf("\nInserting to right node. . .\n");
    it = BSTInsert(tree, (void *)&num3);
    if (num3 == *(int *)BSTGetData(it)) 
    {
        printf("Data in 3rd new node stored correctly\n");
    }
    else
    {
        ADD_RED; printf("ERROR: data is: %d\n", *(int *)BSTGetData(it)); END_RED;
    }

    IterTest(tree);
}

static void IterTest(bst_t *tree)
{
    bst_iter_t it = BSTBegin(tree);

    printf("\nBST Iterators test:\n");
    printf("Begin iterator's data is: %d\n", *(int *)BSTGetData(it));
}

/**********************
 *  FUNCTIONS         *
**********************/
int IsBefore(void *data1, void *data2, void *param)
{
    (void) param;

    return *(int *)data1 < *(int *)data2;
}
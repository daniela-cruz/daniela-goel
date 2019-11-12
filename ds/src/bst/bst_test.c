#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

#define ADD_RED printf("\033[1;31m")
#define END_RED printf("\033[0m")

static void CreateTest();
static void InsertTest();
static void IterTest(bst_t *tree);

int IsBefore(void *data1, void *data2, void *param);

int main()
{
    /*CreateTest();*/
    InsertTest();

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
        it = BSTBegin(tree);
        if (!(num2 == *(int *)BSTGetData(it)) )
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
    if (!(num1 == *(int *)BSTGetData(it)) )
    {
        ADD_RED; printf("ERROR: data is: %d\n", *(int *)BSTGetData(it)); END_RED;
    }

    printf("\nInserting to right node. . .\n");
    it = BSTInsert(tree, (void *)&num3);
    if (!(num3 == *(int *)BSTGetData(it))) 
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
    printf("Prev iterator's data is: %d\n", *(int *)BSTGetData(BSTIterPrev(it)));
}

/**********************
 *  FUNCTIONS         *
**********************/
int IsBefore(void *data1, void *data2, void *param)
{
    (void) param;

    return *(int *)data1 < *(int *)data2;
}


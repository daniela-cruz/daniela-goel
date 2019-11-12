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
<<<<<<< HEAD
        it = BSTBegin(tree);
        if (!(num2 == *(int *)BSTGetData(it)) )
=======
        printf("Data in root stored correctly\n");
        it = BSTBegin(tree);
        if (num2 == *(int *)BSTGetData(it)) 
        {
            printf("Data from iterator in root stored correctly\n"); 
        }
        else
>>>>>>> 434b963ced2597cdbdf56dc6f36e5ebff39bc8ff
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
<<<<<<< HEAD
    if (!(num1 == *(int *)BSTGetData(it)) )
=======
    if (num1 == *(int *)BSTGetData(it)) 
    {
        printf("Data in new node stored correctly\n");
    }
    else
>>>>>>> 434b963ced2597cdbdf56dc6f36e5ebff39bc8ff
    {
        ADD_RED; printf("ERROR: data is: %d\n", *(int *)BSTGetData(it)); END_RED;
    }

    printf("\nInserting to right node. . .\n");
    it = BSTInsert(tree, (void *)&num3);
<<<<<<< HEAD
    if (!(num3 == *(int *)BSTGetData(it))) 
=======
    if (num3 == *(int *)BSTGetData(it)) 
    {
        printf("Data in 3rd new node stored correctly\n");
    }
    else
>>>>>>> 434b963ced2597cdbdf56dc6f36e5ebff39bc8ff
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
<<<<<<< HEAD
    printf("Prev iterator's data is: %d\n", *(int *)BSTGetData(BSTIterPrev(it)));
=======
>>>>>>> 434b963ced2597cdbdf56dc6f36e5ebff39bc8ff
}

/**********************
 *  FUNCTIONS         *
**********************/
int IsBefore(void *data1, void *data2, void *param)
{
    (void) param;

    return *(int *)data1 < *(int *)data2;
<<<<<<< HEAD
}

=======
}
>>>>>>> 434b963ced2597cdbdf56dc6f36e5ebff39bc8ff

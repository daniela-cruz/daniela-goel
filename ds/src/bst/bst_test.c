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
<<<<<<< HEAD
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
=======
        arr[i] = i;
>>>>>>> 6201ea11bf171342ce7e68dbc4eb67c8ad04d318
    }
    
    for ( i = arr_size / 2; i < arr_size; i++)
    {
        it = BSTInsert(tree, &arr[i]);
    }

<<<<<<< HEAD
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
=======
    for ( i = 0; i < arr_size / 2; i++)
>>>>>>> 6201ea11bf171342ce7e68dbc4eb67c8ad04d318
    {
        it = BSTInsert(tree, &arr[i]);
    }
    
    

<<<<<<< HEAD
    printf("\nInserting to right node. . .\n");
    it = BSTInsert(tree, (void *)&num3);
<<<<<<< HEAD
    if (!(num3 == *(int *)BSTGetData(it))) 
=======
    if (num3 == *(int *)BSTGetData(it)) 
=======
    printf("\nNext Iteration test\n");
    for ( it = BSTBegin(tree); 
        !BSTIterIsSame(it, BSTEnd(tree)); 
        it = BSTIterNext(it))
>>>>>>> 6201ea11bf171342ce7e68dbc4eb67c8ad04d318
    {
        printf("Element is: %d\n", *(int*)BSTGetData(it));
    }
<<<<<<< HEAD
    else
>>>>>>> 434b963ced2597cdbdf56dc6f36e5ebff39bc8ff
=======

    printf("\nFind test\n");
    it = BSTFind(tree, &arr[4]);
    printf("Element is: %d\n", *(int*)BSTGetData(it));

    BSTForEach(BSTBegin(tree), BSTEnd(tree), Add10, NULL);
    
    printf("\nForEach test\n");
    for ( it = BSTBegin(tree); 
        !BSTIterIsSame(it, BSTEnd(tree));
        it = BSTIterNext(it))
>>>>>>> 6201ea11bf171342ce7e68dbc4eb67c8ad04d318
    {
        printf("Element is: %d\n", *(int*)BSTGetData(it));
    }


<<<<<<< HEAD
    printf("\nBST Iterators test:\n");
    printf("Begin iterator's data is: %d\n", *(int *)BSTGetData(it));
<<<<<<< HEAD
    printf("Prev iterator's data is: %d\n", *(int *)BSTGetData(BSTIterPrev(it)));
=======
>>>>>>> 434b963ced2597cdbdf56dc6f36e5ebff39bc8ff
=======
    printf("\nRemoval test\n");
    it = BSTIterNext(BSTIterNext(BSTBegin(tree)));
    printf("Element to be removed is: %d\n", *(int*)BSTGetData(it));
    it = BSTRemove(it);
    printf("Element after previous was removed is: %d\n", *(int*)BSTGetData(it));
>>>>>>> 6201ea11bf171342ce7e68dbc4eb67c8ad04d318
}

/**********************
 *  FUNCTIONS         *
**********************/
int IsBefore(void *data1, void *data2, void *param)
{
    (void) param;

    return *(int *)data1 < *(int *)data2;
<<<<<<< HEAD
<<<<<<< HEAD
}

=======
}
>>>>>>> 434b963ced2597cdbdf56dc6f36e5ebff39bc8ff
=======
}

int Add10(void *data, void *param)
{
    *(int *)data += 10;

    return 0;
}
>>>>>>> 6201ea11bf171342ce7e68dbc4eb67c8ad04d318

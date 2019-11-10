#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

#define ADD_RED printf("\033[1;31m")
#define END_RED printf("\033[0m")

static void CreateTest();

int IsBefore(void *data1, void *data2, void *param);

int main()
{
    CreateTest();

    return 0;
}

static void CreateTest()
{
    bst_t *tree = NULL;
    int num1 = 1, num2 = 2, num3 = 3;
    bst_iter_t it;

    printf("\nBST Create test:\n");
    tree = BSTCreate(IsBefore, NULL);
    
    if (NULL != tree)
    {
        printf("Allocated a new tree. . .\n");
        printf("Begin iterator. . .\n");
        it = BSTBegin(tree);
        
        printf("\nInsert to root\n");
        it = BSTInsert(it, (void *)&num2);
        if (num2 == *(int *)BSTGetData(it))
        {
            printf("Data stored correctly\n");
        }
        else
        {
            ADD_RED; printf("ERROR: data is: %d\n", *(int *)BSTGetData(it)); END_RED;
        }
    }
    else
    {
        ADD_RED; printf("Could not allocate the tree.\n"); END_RED;
    }
    
    
}

/**********************
 *  FUNCTIONS         *
**********************/
int IsBefore(void *data1, void *data2, void *param)
{
    (void) param;

    return *(int *)data1 < *(int *)data2;
}
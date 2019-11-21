#include <stdio.h> /* printf */

#include "avl.h" /* avl_t */

#define PRINT_ERR printf("\nERROR: line %d\n", __LINE__)

int IsBefore(void *data1, void* data2, void *param);

static void Create();

int main()
{
    Create();
    return 0;
}

static void Create()
{
    avl_t *tree = NULL;
    int arr[10] = {4, 2, 7, -1, 27, 53, -11, 15, 100, 70};
    int size = 10, i = 0;

    printf("AVL test:\n");
    tree = AVLCreate((avl_is_before_t)IsBefore, NULL);
    (NULL == tree) ? printf("\nERROR: %d could not allocate tree\n", __LINE__) : 
        printf("\nCreated tree\n");

    (AVLIsEmpty(tree)) ? printf("") : PRINT_ERR;
    
    for ( i = 0; i < size; i++)
    {
        (AVLInsert(tree, &arr[i])) ? 
            printf("Problem with insertion %d\n", __LINE__) : 
            printf("Inserted data\n");
    }

    (AVLIsEmpty(tree)) ? printf("\nERROR: line %d\n", __LINE__) : printf("OK");

    PrintTree(tree);
}

int IsBefore(void *data1, void* data2, void *param)
{
    (void)param;
    return (int)data1 < (int)data2;
}
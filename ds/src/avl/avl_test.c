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
    int arr[5] = {4,2,7,-1, 27};

    printf("AVL test:\n");
    tree = AVLCreate((avl_is_before_t)IsBefore, NULL);
    (NULL == tree) ? printf("\nERROR: %d could not allocate tree\n", __LINE__) : 
        printf("\nCreated tree\n");

    (AVLIsEmpty(tree)) ? printf("") : PRINT_ERR;
    (0 == AVLSize(tree)) ? printf("") : printf("Error: size counted is %ld\n", AVLSize(tree));

    (AVLInsert(tree, &arr[0])) ? printf("Problem with insertion %d\n", __LINE__) : printf("Inserted data\n");

    (AVLIsEmpty(tree)) ? printf("\nERROR: line %d\n", __LINE__) : printf("");

    (1 == AVLSize(tree)) ? printf("") : printf("Error: size counted is %ld\n", AVLSize(tree));

    (AVLInsert(tree, &arr[1])) ? printf("Problem with insertion %d\n", __LINE__) : printf("Inserted data\n");
    (AVLInsert(tree, &arr[2])) ? printf("Problem with insertion %d\n", __LINE__) : printf("Inserted data\n");
    (AVLInsert(tree, &arr[3])) ? printf("Problem with insertion %d\n", __LINE__) : printf("Inserted data\n");
    (AVLInsert(tree, &arr[4])) ? printf("Problem with insertion %d\n", __LINE__) : printf("Inserted data\n");
}

int IsBefore(void *data1, void* data2, void *param)
{
    (void)param;
    return (int)data1 < (int)data2;
}
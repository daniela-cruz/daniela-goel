#include <stdlib.h> /* malloc, free */

#include "avl.h" /* avl_node_t, avl_t */

typedef enum child_t {BEFORE, AFTER};

typedef struct avl_node
{
    size_t height;
    void *data;
    struct avl_node *child[2];
} avl_node_t;

struct avl 
{
    avl_node_t *root;
    avl_is_before_t is_before;
    void *param;
};

/*---------------------------Forward declarations-----------------------------*/

/*****UTILITIES******/
static avl_node_t *NodeCreate(void *data);
int InsertRec(avl_node_t *head, avl_is_before_t func, void *data);
size_t Counter(avl_node_t *head, size_t counter);
int ForEachRecursive(avl_node_t *head, avl_action_func_t func, void *param);
avl_node_t *FindData(avl_node_t *head, avl_is_before_t func, const void *data);

void *GetMaxNode(avl_node_t *head);
void *GetMinNode(avl_node_t *head);
void *GetLOCALMaxNode(avl_node_t *head);
void *GetLOCALMinNode(avl_node_t *head);

/*****ROTATORS******/
avl_node_t *RotateLeftLeft(avl_node_t *head);
avl_node_t *RotateLeftRight(avl_node_t *head);
avl_node_t *RotateRightLeft(avl_node_t *head);
avl_node_t *RotateRightRight(avl_node_t *head);

/**********************
 *  FUNCTIONS         *
**********************/
avl_t *AVLCreate(avl_is_before_t func, void *param)
{
    avl_t *tree = NULL;
    avl_node_t *root = NULL;

    tree = malloc(sizeof(*tree));
    if (NULL == tree)
    {
        return NULL;
    }

    root = NodeCreate(NULL);
    if (NULL == root)
    {
        free(tree);
        return NULL;
    }
    
    tree->root = root;
    tree->is_before = func;
    tree->param = param;

    return tree; 
}
 
void AVLDestroy(avl_t *tree)
{
    /* recursive remove if not empty */
    free(tree); tree = NULL;
}

int AVLInsert(avl_t *tree, void *data)
{
    int status = 0;

    if (AVLIsEmpty(tree))
    {
        tree->root = NodeCreate(data);
        return (NULL == tree->root);
    }
    
    status = InsertRec(tree->root, tree->is_before, data);
    /* update height */
    
    return status;
}

void AVLRemove(avl_t *tree, const void *data);

int AVLIsEmpty(const avl_t *tree)
{
    return (NULL == tree->root->data);
}

size_t AVLHeight(const avl_t *tree)
{
    return tree->root->height;
}

size_t AVLSize(const avl_t *tree)
{
    return Counter(tree->root, 0);
}

int AVLForEach(avl_t *tree, avl_action_func_t func, void *param)
{
    return ForEachRecursive(tree->root, func, param);
}

void *AVLFind(const avl_t *tree, const void *data)
{
   return FindData(tree->root, tree->is_before, data)->data;
}

/**********************
 *  ROTATORS          *
**********************/
avl_node_t *RotateLeftLeft(avl_node_t *head);
avl_node_t *RotateLeftRight(avl_node_t *head);
avl_node_t *RotateRightLeft(avl_node_t *head);
avl_node_t *RotateRightRight(avl_node_t *head);

/**********************
 *  Utilities         *
**********************/
void *GetMaxNode(avl_node_t *head);
void *GetMinNode(avl_node_t *head);
void *GetLOCALMaxNode(avl_node_t *head);
void *GetLOCALMinNode(avl_node_t *head);

int InsertRec(avl_node_t *head, avl_is_before_t func, void *data)
{
    if (NULL == head)
    {
        head = NodeCreate(data);

        return 0;
    }
    
    if (func(head->data, data, NULL))
    {
        InsertRec(head->child[AFTER], func, data);
    }
    else
    {
        InsertRec(head->child[BEFORE], func, data);
    }
    
    return 1;
}

size_t Counter(avl_node_t *head, size_t counter)
{
    if (NULL == head)
    {
        return 0;
    }

    if (NULL != head->data)
    {
        Counter(head->child[BEFORE], counter);
        Counter(head->child[AFTER], counter);

        return 1;
    }
    
}

ForEachRecursive(avl_node_t *head, avl_action_func_t func, void *param)
{
    int status = 0;

    if (NULL == head)
    {
        return 0;
    }
    
    status = func(head, param);
    status += ForEachRecursive(head->child[BEFORE], func, param);
    status += ForEachRecursive(head->child[AFTER], func, param);

    return status;
}

avl_node_t *FindData(avl_node_t *head, avl_is_before_t func, const void *data)
{
    if (NULL == head)
    {
        return NULL;
    }
    
    if (1 == func(head->data, data, NULL))
    {
        return head;
    }
    
    FindData(head->child[BEFORE], func, data);
    FindData(head->child[AFTER], func, data);
}

static avl_node_t *NodeCreate(void *data)
{
    avl_node_t *node = NULL;

    node = malloc(sizeof(*node));
    if (NULL == node)
    {
        return NULL;
    }
    
    node->child[0] = NULL;
    node->child[1] = NULL;
    node->data = data;
    node->height = 1;

    return node; 
}
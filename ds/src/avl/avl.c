#include "avl.h" /* avl_node_t, avl_t */

typedef struct  
{
    void *data;
    avl_node_t *before, *after;
    int balance;
}avl_node_t;

struct avl 
{
    void *tree;
    avl_cmp_func_t is_before;
    void *param;
};

/*---Forward declarations---*/
static avl_node_t *NodeCreate(void *data);

/**********************
 *  FUNCTIONS         *
**********************/
avl_t *AVLCreate(avl_cmp_func_t func, void *param)
{
   avl_t *tree = NULL;

   return tree; 
}
 
void AVLDestroy(avl_t *tree);

int AVLInsert(avl_t *tree, void *data);

void AVLRemove(avl_t *tree, const void *data);

/*  returns a boolean value, 1 if empty
 *  0 if not                                     */
int AVLIsEmpty(const avl_t *tree);

size_t AVLHeight(const avl_t *tree);

size_t AVLSize(const avl_t *tree);

/*  return value is boolean and thus the user
 *  should provide a suitable function          */
int AVLForEach(avl_t *tree, avl_action_func_t func, void *param);

void *AVLFind(const avl_t *tree, const void *data);

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

static avl_node_t *NodeCreate(void *data)
{
    avl_node_t *node = NULL;

    node = malloc(sizeof(* node));
    if (NULL == node)
    {
        return NULL;
    }

    node->data = data;
    node->before = NULL;
    node->after = NULL;

    return node; 
}
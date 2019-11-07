#include <stdlib.h> /* malloc, free */

#include "bst.h"

struct bst_node
{
    bst_node_t *parent;
    bst_node_t *child_before, *child_after;
    void *data;
};

struct bst
{
    bst_node_t *root;
    bst_is_before_func_t func;
    void *param;
};

/**********************
 *  FUNCTIONS         *
**********************/
bst_t *BSTCreate(bst_is_before_func_t func, void *param)
{
    bst_t *tree = NULL;



    return tree;
}
 
void BSTDestroy(bst_t *tree);

bst_iter_t BSTInsert(bst_iter_t iterator, void *data);

/*      returns iterator to next node       */
bst_iter_t BSTRemove(bst_t *tree, void *data);

bst_iter_t BSTFind(const bst_t *tree, void *key);

int BSTForEach(bst_t *tree, bst_action_func_t func, void *param);

void *BSTGetData(bst_iter_t iterator);

int BSTIsEmpty(bst_t *tree);

/**********************
 *  ITERATOR FUNCS    *
**********************/
bst_iter_t BSTBegin(const bst_t *tree);

bst_iter_t BSTEnd(const bst_t *tree);

bst_iter_t BSTIterNext(bst_iter_t iterator);

bst_iter_t BSTIterPrev(bst_iter_t iterator);

bst_iter_t BSTIterIsSame(bst_iter_t iterator1, bst_iter_t iterator2);

/**********************
 *  INTERNAL FUNCS    *
**********************/
static bst_node_t *NodeCreate(void *data)
{
    bst_node_t *node = NULL;

    node = malloc(sizeof(* node));
    if (NULL == node)
    {
        return NULL;
    }

    node->data = data;
    node->child_before = NULL;
    node->child_after = NULL;
    node->parent = NULL;

    return node; 
}
#include <stdlib.h>     /* malloc, free */
#include <assert.h>     /* assert */

#include "bst.h"        /* bst_node_t, bst_t, bst_iter_t, bst_is_before_func_t */

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

static bst_node_t *NodeCreate(void *data);

/**********************
 *  FUNCTIONS         *
**********************/
bst_t *BSTCreate(bst_is_before_func_t func, void *param)
{
    bst_t *tree = NULL;
    
    tree = malloc(sizeof(*tree));
    if (NULL == tree)
    {
        return NULL;
    }
    tree->func = func;
    tree->param = param;

    tree->root = NodeCreate(NULL);
    if (NULL == tree->root)
    {
        free(tree); tree = NULL;
        return NULL;
    }

    return tree;
}
 
void BSTDestroy(bst_t *tree)
{
    bst_iter_t iterator = {NULL, NULL};

    assert(NULL != tree);
    iterator.tree = tree; 

    for (iterator = BSTBegin(tree); 
        (NULL != iterator.curr) && (BSTIterIsSame(iterator, BSTEnd(tree))); 
        iterator = BSTIterNext(iterator))
    {
        BSTRemove(iterator);
    }
    
    free(tree); tree = NULL;
}

bst_iter_t BSTInsert(bst_iter_t iterator, void *data)
{
    assert(NULL != data);
    

    return iterator;
}

bst_iter_t BSTRemove(bst_iter_t iterator);

bst_iter_t BSTFind(const bst_t *tree, void *key)
{
    bst_iter_t iterator = {NULL, NULL};

    assert(NULL != tree);
    for (iterator = BSTBegin(tree); !BSTIterIsSame(iterator, BSTEnd(tree)); iterator = BSTIterNext(iterator))
    {
        if (iterator.curr->data == key)
        {
            return iterator;
        }
    }

    return BSTEnd(tree);
}

int BSTForEach(bst_t *tree, bst_action_func_t func, void *param);

void *BSTGetData(bst_iter_t iterator)
{
    return iterator.curr->data;
}

int BSTIsEmpty(bst_t *tree)
{
    return !(NULL == tree->root->data);
}

/**********************
 *  ITERATOR FUNCS    *
**********************/
bst_iter_t BSTBegin(const bst_t *tree)
{
    bst_iter_t begin_iter = {NULL, NULL};

    assert(NULL != tree);
    begin_iter.tree = tree;
    
    for (begin_iter.curr = tree->root->child_before; 
        NULL != begin_iter.curr->child_before; 
        begin_iter.curr = begin_iter.curr->child_before);

    return begin_iter; 
}

bst_iter_t BSTEnd(const bst_t *tree)
{
    bst_iter_t end_iter = {NULL, NULL};

    assert(NULL != tree);
    end_iter.tree = tree;
    
    for (end_iter.curr = tree->root->child_after; 
        NULL != end_iter.curr->child_after; 
        end_iter.curr = end_iter.curr->child_after);

    return end_iter; 
}

bst_iter_t BSTIterNext(bst_iter_t iterator)
{
    bst_iter_t iter_parent = iterator;

    if ((NULL != iterator.curr->child_after) && (NULL != iterator.curr))
    {
        iterator.curr = iterator.curr->child_after;
        return iterator;
    }

    iter_parent.curr = iterator.curr->parent;
    if (NULL != iter_parent.curr) /* if we're not in the root node */
    {
        if (iterator.tree->func(iter_parent.curr->data, iterator.curr->data, iterator.tree->param))
        {
            return iter_parent;
        }
        else
        {
            return BSTIterNext(iter_parent);
        }
    }

    return BSTEnd(iterator.tree);
}

bst_iter_t BSTIterPrev(bst_iter_t iterator);

int BSTIterIsSame(bst_iter_t iterator1, bst_iter_t iterator2)
{
    return iterator1.curr == iterator2.curr;
}

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
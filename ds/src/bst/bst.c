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

static bst_iter_t GetMinimalChildInBranch(bst_iter_t it);

static bst_iter_t GetMaximalChildInBranch(bst_iter_t it);

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
    tree->param = malloc(sizeof(param));
    if (NULL == tree->param)
    {
        free(tree); tree = NULL;
        return NULL;
    }
    
    tree->root = NodeCreate(NULL);
    if (NULL == tree->root)
    {
        free(tree->param); tree->param = NULL;
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

bst_iter_t BSTInsert(bst_t *tree, void *data)
{
    bst_iter_t iterator = {NULL, NULL};
    bst_iter_t parent_iter = {NULL, NULL};
    bst_node_t *new_node = NULL;
    int is_smaller = 0;

    assert(NULL != tree);
    assert(NULL != data);
    
    iterator.tree = tree;
    iterator.curr = tree->root;
    parent_iter.tree = tree;
    parent_iter.curr = tree->root->parent;

    new_node = NodeCreate(data);
    if (NULL == new_node)
    {
        return BSTEnd(iterator.tree);
    }
    
    for (iterator.curr = tree->root; NULL != iterator.curr;)
    {
        /* if the tree is empty */
        if (NULL == BSTGetData(iterator))
        {
            break;
        }

        /* if data value is before curr, move to child_before */
        for (parent_iter.curr = iterator.curr; NULL != iterator.curr;)
        {
            if (iterator.tree->func(data, BSTGetData(iterator), iterator.tree->param))
            {
                iterator.curr = iterator.curr->child_before;
                is_smaller = 1;
            }
        }
        
        /* if data value is after curr, move to child_after */
        for (parent_iter.curr = iterator.curr; NULL != iterator.curr;)
        {
            if (iterator.tree->func(BSTGetData(iterator), data, iterator.tree->param))
            {
                parent_iter.curr = iterator.curr;
                iterator.curr = iterator.curr->child_after;
                is_smaller = 0;
            }
        }
    }

    if (is_smaller)
    {
        new_node->parent = parent_iter.curr;
        iterator.curr = new_node;
    }
    else if (!is_smaller && (iterator.curr != iterator.tree->root))
    {
       parent_iter.curr->child_after = new_node; 
    }
    else /* the tree is empty, insert to root */
    {
        free(new_node); new_node = NULL;
        iterator.tree->root->data = data;
        iterator.curr = iterator.tree->root;
    }

    return iterator;
}

bst_iter_t BSTRemove(bst_iter_t iterator)
{
    iterator.curr = NULL;
    /* there's a lot more to this function*/

    return BSTIterNext(iterator);
}

bst_iter_t BSTFind(const bst_t *tree, void *key)
{
    bst_iter_t iterator = {NULL, NULL};

    assert(NULL != tree);
    for (iterator = BSTBegin(tree); 
        !BSTIterIsSame(iterator, BSTEnd(tree)); 
        iterator = BSTIterNext(iterator))
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
    begin_iter.tree = (bst_t *)tree;
    begin_iter.curr = tree->root;
    
    for (begin_iter.curr = tree->root; 
        NULL != begin_iter.curr->data; 
        begin_iter.curr = begin_iter.curr->child_before)
    {
        if (NULL == begin_iter.curr->child_before)
        {
            break;
        }
    }

    return begin_iter; 
}

bst_iter_t BSTEnd(const bst_t *tree)
{
    bst_iter_t end_iter = {NULL, NULL};

    assert(NULL != tree);
    end_iter.tree = (bst_t *)tree;
    end_iter.tree->root->parent;

    return end_iter; 
}

bst_iter_t BSTIterNext(bst_iter_t iterator)
{
    bst_iter_t iter_parent = iterator;

    iter_parent.curr = iterator.curr->parent;
    iter_parent.tree = iterator.tree;
    /*
    if (iterator.tree->func(iter_parent.curr->data, iter_parent.curr->data, iterator.tree->param))
    {
        if (NULL != iterator.curr->child_after)
        {
            iterator.curr = iterator.curr->child_after;
        }
        else
        {
            iterator.curr = iter_parent.curr;
        }
    }
    else
    {
        if (NULL != iterator.curr->child_after)
        {
            iterator.curr = iterator.curr->child_after;
        }
        else
        {
            iterator = BSTEnd(iterator.tree);
        }
    }*/

    if (NULL != iterator.curr->child_after)
    {
        return GetMinimalChildInBranch(iterator);
    }

    return iterator;
}

bst_iter_t BSTIterPrev(bst_iter_t iterator)
{
    bst_iter_t parent_iter = {NULL, NULL};

    if (NULL == iterator.curr)
    {
        return BSTEnd(iterator.tree);
    }

    parent_iter.tree = iterator.tree;

    /* if current value is smaller than parent's */
    if (iterator.tree->func(iterator.curr->data, iterator.curr->parent->data, 
        iterator.tree->param))
    {
        parent_iter.curr = iterator.curr;

        for (; NULL != iterator.curr->parent->child_before; )
        {
            iterator.curr = iterator.curr->parent;
        }
    }
    /* if current value is bigger than parent's */
    else if (iterator.tree->func(iterator.curr->parent->data, 
        iterator.curr->data, iterator.tree->param))
    {
        for (; ;)
        {
            /* code */
        }
        
        parent_iter.curr = iterator.curr->parent;
    }

    return iterator;
}

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

static bst_iter_t GetMinimalChildInBranch(bst_iter_t it)
{
    for (; NULL != it.curr; it.curr = it.curr->child_before);
    
    return it;
}

static bst_iter_t GetMaximalChildInBranch(bst_iter_t it)
{
    for (; NULL != it.curr; it.curr = it.curr->child_after);
    
    return it;
}


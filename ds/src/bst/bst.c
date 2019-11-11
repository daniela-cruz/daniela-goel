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
	bst_node_t *parent_node = NULL;
    bst_node_t *curr_node = NULL;
    bst_node_t *new_node = NULL;
    bst_iter_t iterator = {NULL, NULL};
    
    assert(NULL != tree);
    assert(NULL != data);
    iterator = BSTBegin(tree);
    
    for (curr_node = tree->root; NULL != curr_node; )
    {
        /* if the tree is empty */
        if (NULL == BSTGetData(iterator))
        {
            break;
        }

        parent_node = curr_node;
        if (tree->func(data, curr_node->data, tree->param))
        {
            curr_node = curr_node->child_before;
        }
        else
        {
            curr_node = curr_node->child_after;
        }
    }
    
    new_node = NodeCreate(data);
    if (NULL == new_node)
    {
        return BSTEnd(tree);
    }
    new_node->parent = parent_node;

    if (NULL == parent_node)
    {
        tree->root = new_node;
    }
    else if (tree->func(new_node->data, parent_node->data, tree->param))
    {
        parent_node->child_before = new_node;
    }
    else
    {
        parent_node->child_after = new_node;
    }
    
    iterator.curr = new_node;

    return iterator;
}

bst_iter_t BSTRemove(bst_iter_t iterator)
{
    bst_iter_t parent_iter = {NULL, NULL};
    bst_node_t *removable = NULL;

    if ((NULL == iterator.curr->child_after) && (NULL == iterator.curr->child_after))
    {
        free(iterator.curr->data); iterator.curr->data = NULL;
        free(iterator.curr); iterator.curr = NULL;
    }
    
    parent_iter.tree = iterator.tree;
    parent_iter.curr = iterator.curr->parent;
    removable = iterator.curr;

    if (removable == parent_iter.curr->child_after)
    {
        /* tie parent to one child to the right 
         * then go all the way to left 
         * tie removable's children to left most node */
        iterator.curr = iterator.curr->child_after;
        parent_iter.curr->child_after = iterator.curr;
        iterator = GetMinimalChildInBranch(iterator);
        
        if (NULL != removable->child_before)
        {
            iterator.curr->child_before = removable->child_before;
        }
        
        
    }

    else /* if removable is a child_before */
    {
        /* tie parent to one child to left
         * then go all the way to right most node 
         * tie removable's right child to right most node */
        iterator.curr = iterator.curr->child_before;
        parent_iter.curr->child_before = iterator.curr;
        iterator = GetMaximalChildInBranch(iterator);

        if (NULL != removable->child_after)
        {
            iterator.curr->child_after = removable->child_after;
            removable->child_after->parent = iterator.curr;
        }
    }
    
    
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
	bst_node_t *parent = NULL;
    bst_iter_t parent_iter = {NULL, NULL};

    if (NULL == iterator.curr)
    {
        return BSTEnd(iterator.tree);
    }
    
    if (NULL != iterator.curr->child_before)
    {
        return GetMaximalChildInBranch(iterator);
    }

    parent = iterator.curr->parent;
    
    for (; parent != NULL && iterator.curr == parent->child_before; 
    	iterator.curr = parent, parent = parent->parent);

    iterator.curr = parent;

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
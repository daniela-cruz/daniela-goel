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
    tree->param = param;
    
    tree->root = NodeCreate(NULL);
    if (NULL == tree->root)
    {
        free(tree->param); tree->param = NULL;
        free(tree); tree = NULL;
        return NULL;
    }

    tree->root->parent = NodeCreate(NULL);
    if (NULL == tree->root->parent)
    {
        free(tree->param); tree->param = NULL;
        free(tree->root); tree->root = NULL;
        free(tree); tree = NULL;

        return NULL;
    }

    tree->root->parent->child_before = tree->root;

    return tree;
}
 
void BSTDestroy(bst_t *tree)
{
    bst_iter_t iterator = {NULL, NULL};

    assert(NULL != tree->root);

    for (iterator = BSTBegin(tree); 
        (BSTIterIsSame(iterator, BSTEnd(tree))); 
        iterator = BSTIterNext(iterator))
    {
        BSTRemove(iterator);
    }
    
    free(tree->root->parent); tree->root->parent = NULL;
    free(tree->root); tree->root = NULL;
    free(tree); tree = NULL;
}

bst_iter_t BSTInsert(bst_t *tree, void *data)
{
	bst_node_t *parent_node = NULL;
    bst_node_t *curr_node = NULL;
    bst_node_t *new_node = NULL;
    bst_iter_t iterator = {NULL, NULL};
    
    assert(NULL != tree);
    iterator = BSTBegin(tree);
    
    /* if the tree is empty */
    if (NULL == BSTGetData(iterator))
    {
        tree->root->data = data;
        iterator.curr = tree->root;
        return iterator;
    }

    for (curr_node = tree->root; NULL != curr_node; )
    {
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
    if (tree->func(new_node->data, parent_node->data, tree->param))
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
    bst_node_t *child_after = NULL;

    if ((iterator.tree->root == iterator.curr))
    {
        iterator.curr->data = NULL;
        return iterator;
    }

    removable = iterator.curr;
    if (NULL == removable->child_before)
    {
        iterator.curr = removable->parent;
        if (NULL != removable->child_after)
        {
            if (removable->parent->child_after == removable)
            {
                iterator.curr->child_after = removable->child_after;
            }
            else
            {
                iterator.curr->child_before = removable->child_after;
            }
        }
        
        removable->child_after->parent = iterator.curr;
        free(removable); removable = NULL;

        return iterator;
    }
    else if (NULL == removable->child_after)
    {
        iterator.curr = removable->child_before;
        if (NULL == removable->child_after)
        {
            if (removable->parent->child_after == removable)
            {
                parent_iter.curr->child_after = iterator.curr;
            }
            else
            {
                parent_iter.curr->child_before = iterator.curr;
                iterator.curr = parent_iter.curr;
            }
            
            free(removable); removable = NULL;

            return iterator;
        }
    }
    else /* node has both children */
    {
        if (removable == removable->parent->child_after)
        {
            parent_iter.curr = removable->parent;
            if (NULL == parent_iter.curr->child_before)
            {
                parent_iter.curr->child_after = removable->child_before;
                child_after = removable->child_after;
                iterator.curr = removable->child_before;
                
                iterator = GetMaximalChildInBranch(iterator);
                iterator.curr->child_after = child_after;
                child_after->parent = iterator.curr;
            }
            else /* parent has a child_before */
            {
                iterator.curr = parent_iter.curr->child_before;
                iterator = GetMaximalChildInBranch(iterator);
                iterator.curr->child_after = removable->child_before;
                removable->child_before->parent = iterator.curr;
                
                /*parent_iter.curr = iterator.curr;*/
                iterator.curr = removable->child_before;
                iterator = GetMaximalChildInBranch(iterator);
                child_after = removable->child_after;
                
                iterator.curr->child_after = child_after;
                child_after->parent = iterator.curr;
                iterator.curr = child_after;
            }
            
            free(removable); removable = NULL;

            return iterator;
        }
        
    }
    
    return iterator;
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

int BSTForEach(bst_iter_t from, bst_iter_t to, bst_action_func_t func, void *param)
{
    bst_iter_t it = {NULL, NULL};

    for (it = from; !BSTIterIsSame(it, to); it = BSTIterNext(it))
    {
        if (func(it.curr->data, it.tree->param))
        {
            return 1;
        }
    }
    
    return 0;
}

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

    if (NULL != tree->root->child_before)
    {
        begin_iter = GetMinimalChildInBranch(begin_iter);
    }

    return begin_iter; 
}

bst_iter_t BSTEnd(const bst_t *tree)
{
    bst_iter_t end_iter = {NULL, NULL};

    assert(NULL != tree);
    end_iter.tree = (bst_t *)tree;
    end_iter.curr = tree->root->parent;

    return end_iter; 
}

bst_iter_t BSTIterNext(bst_iter_t iterator)
{   
    if (BSTIterIsSame(iterator, BSTEnd(iterator.tree)))
    {
        return BSTEnd(iterator.tree);
    } 


    
    if (NULL != iterator.curr->child_after)
    {
        iterator.curr = iterator.curr->child_after;
        iterator = GetMinimalChildInBranch(iterator);
    }
    else
    {
        for (; !BSTIterIsSame(iterator, BSTEnd(iterator.tree)); 
            iterator.curr = iterator.curr->parent)
        {
            if (iterator.curr == iterator.curr->parent->child_before)
            {
                iterator.curr = iterator.curr->parent;
                break;
            }
        }
    }

    return iterator;
}

bst_iter_t BSTIterPrev(bst_iter_t iterator)
{
    if (BSTIterIsSame(iterator, BSTEnd(iterator.tree)))
    {
        iterator.curr = iterator.tree->root;
        return GetMaximalChildInBranch(iterator);
    }
    else if (BSTIterIsSame(iterator, BSTBegin(iterator.tree)))
    {
        return BSTEnd(iterator.tree);
    }
    else
    {
        if (NULL != iterator.curr->child_before)
        {
            iterator.curr = iterator.curr->child_before;
        }
        else
        {
            if (iterator.curr == iterator.curr->parent->child_before)
            {
                for (; BSTIterIsSame(iterator, BSTEnd(iterator.tree)); 
                    iterator.curr = iterator.curr->parent)
                {
                    if (iterator.curr == iterator.curr->parent->child_after)
                    {
                        break;
                    }
                }
            }
            
            iterator.curr = iterator.curr->parent;
        }
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
    if (NULL != it.curr->child_before)
    {
        for (; NULL != it.curr->child_before; it.curr = it.curr->child_before);
    }
    
    return it;
}

static bst_iter_t GetMaximalChildInBranch(bst_iter_t it)
{
    if (NULL != it.curr->child_after)
    {
        for (; NULL != it.curr->child_after; it.curr = it.curr->child_after);
    }

    return it;
}


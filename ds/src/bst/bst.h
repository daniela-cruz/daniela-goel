#ifndef __BST_H__
#define __BST_H__

typedef int (*bst_is_before_func_t)(void *data1, void *data2);

typedef int (*bst_action_func_t)(void *data, void *param);

typedef struct bst_node bst_node_t;

typedef struct tree bst_t;

typedef struct bst_iter bst_iter_t;

/**********************
 *  FUNCTIONS         *
**********************/
bst_t *BSTCreate(bst_is_before_func_t func, void *param);
 
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
 *  INTERNAL USE      *
**********************/
struct 
{
   bst_node_t *curr; 
   bst_t *tree;
} bst_iter;

#endif /* __BST_H__ */


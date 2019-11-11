#ifndef __BST_H__
#define __BST_H__

typedef int (*bst_is_before_func_t)(void *data1, void *data2, void *param);

typedef int (*bst_action_func_t)(void *data, void *param);

typedef struct bst_node bst_node_t;

typedef struct bst bst_t;

typedef struct bst_iter bst_iter_t;

/**********************
 *  FUNCTIONS         *
**********************/
bst_t *BSTCreate(bst_is_before_func_t func, void *param);
 
void BSTDestroy(bst_t *tree);

bst_iter_t BSTInsert(bst_t *tree, void *data);

/*      returns iterator to next node       */
bst_iter_t BSTRemove(bst_iter_t iterator);

void *BSTGetData(bst_iter_t iterator);

int BSTIsEmpty(bst_t *tree);

/**********************
 *  EXTRA FUNCS       *
**********************/
int BSTforEach(bst_iter_t from, bst_iter_t to, bst_action_func_t func, void *param);

bst_iter_t BSTFind(const bst_t *tree, void *key);

/**********************
 *  ITERATOR FUNCS    *
**********************/
bst_iter_t BSTBegin(const bst_t *tree);

bst_iter_t BSTEnd(const bst_t *tree);

bst_iter_t BSTIterNext(bst_iter_t iterator);

bst_iter_t BSTIterPrev(bst_iter_t iterator);

int BSTIterIsSame(bst_iter_t iterator1, bst_iter_t iterator2);

/**********************
 *  INTERNAL USE      *
**********************/
struct bst_iter
{
   bst_node_t *curr; 
   bst_t *tree;
};

#endif /* __BST_H__ */


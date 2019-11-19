#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */

typedef int (*avl_is_before_func_t)(void *data1, void *data2, void *param);

typedef int (*avl_action_func_t)(void *data, void *param);

typedef struct avl avl_t;

/**********************
 *  FUNCTIONS         *
**********************/
avl_t *AVLCreate(avl_is_before_func_t func, void *param);
 
void AVLDestroy(avl_t *tree);

int AVLInsert(avl_t *tree, void *data);

void AVLRemove(avl_t *tree);

int AVLIsEmpty(avl_t *tree);

int AVLHeight(avl_t *tree);

size_t AVLSize(avl_t *tree);

int AVLForEach(avl_t *tree, avl_action_func_t func, void *param);

void *AVLFind(const avl_t *tree, void *key);

#endif /* __AVL_H__ */

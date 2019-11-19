#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */

/*  the user should provide a comparisson function
 *  which returns a zero if data is equal, 0< if 
 * data1 contains a higher value than data2 and 
 * 0> vice versa                                  */
typedef int (*avl_cmp_func_t)(const void *data1, const void *data2, void *param);

/*  returns a boolean value, 0 upon success and
 *  1 upon failure                                  */
typedef int (*avl_action_func_t)(void *data, void *param);

typedef struct avl avl_t;

/**********************
 *  FUNCTIONS         *
**********************/
avl_t *AVLCreate(avl_cmp_func_t func, void *param);
 
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

#endif /* __AVL_H__ */

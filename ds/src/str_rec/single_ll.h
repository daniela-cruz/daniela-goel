#ifndef __SINGLE_LL_H__
#define __SINGLE_LL_H__

#include <stddef.h> /* size_t */

/*	User functions on linked array members
	typedef for foreach				*/ 
typedef int(*sll_foreach_func_t)(void *data, void *param);

/*	User functions on linked array members
	typedef for find				*/
typedef int(*sll_find_func_t)(const void *data, void *param);

typedef struct sll_node sll_node_t;

struct sll_node
{
	void *data;
	sll_node_t *next;
};

/* 	*/
sll_node_t *SLLCreateNode(void *data, sll_node_t *next);

/*		*/
void SLLFreeAll(sll_node_t *root);

/*		*/
sll_node_t *SLLRemove(sll_node_t *target);

/*	*/
sll_node_t *SLLRemoveAfter(sll_node_t *target);

/*		*/
sll_node_t *SLLInsert(sll_node_t *target, sll_node_t *new_node);

/* 		*/
sll_node_t *SLLInsertAfter(sll_node_t *target, sll_node_t *new_node);

/* 	*/
size_t SLLCount(const sll_node_t *root);

/* 	*/
int SLLForEach(sll_node_t *root, sll_foreach_func_t func, const void *func_param);

/* 		*/
sll_node_t *SLLFind(const sll_node_t *root, sll_find_func_t func, const void *func_param);

/* 			*/
sll_node_t *SLLFlip(sll_node_t *root);

/* 	*/
int SLLHasLoop(const sll_node_t *node);

/* 			*/
sll_node_t *SLLFindIntersection(const sll_node_t *first_list, const sll_node_t *second_list);

#endif /* __SINGLE_LL_H__ */


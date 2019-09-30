#ifndef __SLL_H__
#define __SLL_H__

#include <stddef.h> /* size_t */

typedef struct node sll_node_t;

/* 		Function pointer to be passed as an argument to SLLForEach.
 * 		Must recieve and pass the same function signatures as specified.		*/
typedef int (*sll_foreach_action)(void *data, void *param);	

/* 		Function pointer to be passed as an argument to SLLFind.
 * 		Must recieve and pass the same function signatures as specified.		*/
typedef int (*sll_find)(const void *data, void *param);

struct node
{
	void *item ;
	sll_node_t *next_node;
};

/* 		returns the created root for the user. 												*/
sll_node_t *SLLCreateNode(void *data, sll_node_t *next);

/* 		Frees all pointers from the provided pointer onward.
 * 		If SLLFreeAll recieves a NULL: behaviour is undefined.				*/
void SLLFreeAll(sll_node_t *root);

/* 		Removes provided pointer from the linked list and returns new root.
 * 		If <target> has no previous node, next will become root. 
 * 		If <target> has a next, it will be assigned to previous node.			*/
sll_node_t *SLLRemove(sll_node_t *target);

/* 		Removes <target>'s next node.														*/

sll_node_t *SLLRemoveAfter(sll_node_t *target);

/* 		Inserts <new node> to the linked list before <target>.
 * 		If <target> has no previous node, <new node> will become root	*/
sll_node_t *SLLInsert(sll_node_t *root, sll_node_t *new_node);

/* 		Inserts <new node> to <target>'s next
 * 		If <target> has a next, it becomes <new node>'s next instead.		*/
sll_node_t *SLLInsertAfter(sll_node_t *target, sll_node_t *new_node);

/* 		Counts on the items in the linked list 												*/
size_t SLLCount(const sll_node_t *root);

/*		receives root, function pointer and parameter as arguments and 
 *		performs the desired action over the entire list 								*/
int SLLForeach(sll_node_t *root, sll_foreach_action func, const void *func_param);

sll_node_t *SLLFind(const sll_node_t *root, sll_find func, const void *func_param);

sll_node_t *SLLFlip(sll_node_t *root);

int SLLHasLoop(const sll_node_t *root);

sll_node_t *SLLFindIntersection(const sll_node_t *root1, const sll_node_t *root2);



#endif /*__SLL_H__*/

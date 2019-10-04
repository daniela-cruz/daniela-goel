#ifndef __SINGLE_LL_H__
#define __SINGLE_LL_H__

/*	User functions on linked array members
	typedef for foreach				*/ 
typedef int(*sll_foreach_func_t)(void *data, void *param);

/*	User functions on linked array members
	typedef for find				*/
typedef int(*sll_find_func_t)(const void *data, void *param);

typedef struct sll_node sll_node_t;

struct sll_node{
	void *data;
	sll_node_t *next;
};

/* 	*Creates root for new linked list
		of users data
	*Returns pointer to the root			*/
sll_node_t *SLLCreateNode(void *data, sll_node_t *next);

/*	*Remove all nodes from list including root
	*Complexcity O(n)				*/
void SLLFreeAll(sll_node_t *root);

/*	*Removes specified node from linked list
	*Returns pointer to next node.
	*Complexity O(1)	
	*Does not handle last node as an argument	*/
sll_node_t *SLLRemove(sll_node_t *target);

/*	*Removes node from linked list, 
			after specified node.
	*Returns pointer to next element 		
	*Complexity O(1)				*/
sll_node_t *SLLRemoveAfter(sll_node_t *target);

/*	*Insert a new item before <target>, 
		re-links adjacent items.
	*Returns pointer to the next node, in case 
		no previous node exists, become root.
	*Complexity O(1)				*/
sll_node_t *SLLInsert(sll_node_t *target, sll_node_t *new_node);

/* 	*Insert new node to <target> next node.
	*Return pointer to target node.
	*Complexity O(1)				*/
sll_node_t *SLLInsertAfter(sll_node_t *target, sll_node_t *new_node);

/* 	*Returns number of elements in linked list	*/
size_t SLLCount(const sll_node_t *root);

/* 	*User performs action (function) on everry 
		element of the linked list
	*Complexity O(n)				*/
int SLLForEach(sll_node_t *root, sll_foreach_func_t func, void *func_param);

/* 	*Search for spesific element in linked list.
	*Returns pointer to that element.		*/
sll_node_t *SLLFind(const sll_node_t *root, sll_find_func_t func, void *func_param);

/* 	*Flips linked list
	*Returns pointer to new linked list		*/
sll_node_t *SLLFlip(sll_node_t *root);

/* 	*Check if one of the elements points to one 
		of the previous element in linked list
		(making a closed loop). 
	*Solution by Floyd's Cycle detection.	
	*Return 1 if there is loop
		0 if not.				*/
int SLLHasLoop(const sll_node_t *node);

/* 	*Check if there is element which both linked 
		lists points to (intersection between
				lists).	
	*Solution by using 2 loops.
	*Complexity O(n * m )
	Other possible solution is to mark visited nodes
	   Complexity O (n + m) 			*/
sll_node_t *SLLFindIntersection(const sll_node_t *first_list, const sll_node_t *second_list);

#endif /* __SINGLE_LL_H__ */


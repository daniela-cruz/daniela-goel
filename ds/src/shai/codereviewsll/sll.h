#ifndef __SINGLE_LL_H__
#define __SINGLE_LL_H__

#include <stddef.h> /* size_t */

/*################################ typedef ###################################*/

/*  Struct of the node that constitute.  							   	      */
typedef struct sll_node
{
	void *data;
	struct sll_node *next;
} sll_node_t;


/*  Signature of the <foreach function>.  							   	      */
typedef int (*sll_foreach_func_t)(void *data, void *param);

/*  Signature of the <find function>.  							   		      */
typedef int (*sll_ismatch_func_t)(const void *data, void *param);


/*############################### functions ##################################*/

/*  Creates a new node.
	Receives 2 pointers - the 1st (<data>) points to data that the node will 
	hold. The 2nd pointer (<next>) points to the next node on the linked list.
	Return Value:
		the created node.
	NOTE - the 1st node that is created should have <next> pointing to NULL.  */

sll_node_t *SLLCreateNode(void *data, sll_node_t *next);



/*  Frees all nodes from <root> onwards.									  */
void SLLFreeAll(sll_node_t *root);



/*  Removes the inserted node from the linked list.
	Return Value:
		The next node. 												 
	NOTE - this function  changes the node themselves, so after using it, don't 
	try to track the nodes themselves, only the data stored inside.			  */
sll_node_t *SLLRemove(sll_node_t *node);



/*  Removes the <next> node of the inserted node from the linked list.
	Return Value:
		The inserted node. 								  					  */
sll_node_t *SLLRemoveAfter(sll_node_t *node);



/*  Inserts a new node to the linked list.
	Return Value:
		<reference_node>.
	NOTE - this function  changes the node themselves, so after using it, don't 
	try to track the nodes themselves, only the data stored inside.			  */
sll_node_t *SLLInsert(sll_node_t *reference_node, sll_node_t *new_node);



/*  Inserts a new node to the linked list.
	Return Value:
		<reference_node>.										  			  */
sll_node_t *SLLInsertAfter(sll_node_t *reference_node, sll_node_t *new_node);



/* Counts the number of items in the linked list. 							  */
size_t SLLCount(const sll_node_t *root);



/*  Preform the user- function <sll_foreach_func_t> on each of the nodes in the 
	list (from <root> onwards). The user-function can receive 1 argument 
	(<param>), and must return status (0 for sucsses, !0 for failure). In case 
	the user-function fails, no action will be preformed on the remaining nodes
	of the list.
	Return Value:
		0 for sucsses, !0 for failure.							 			  */
int SLLForEach(sll_node_t *root, sll_foreach_func_t foreach_func, void *param);



/*  Finds the location of a value in the list (from <root> onwards), using the 
	user-function <sll_ismatch_func_t>. The user-function can receive 1
	argument (<param>), and must return status (1 if  the value was found, 0 if
	it wasn't).
	Return Value:
		The first node where the value is stored. If the value isn't found, 
		returns NULL.										 				  */
sll_node_t *SLLFind(const sll_node_t *root, sll_ismatch_func_t find_func,
					void *param);



/*  Flips the order of the list. 
	Return Value:
		The new root (formerly the last node).
	Complexity:
		O(n)					  											  */
sll_node_t *SLLFlip(sll_node_t *root);



/*  Checks whether one of the nodes in the list is pointing to a previous node 
	(i.e. the list has a "loop").
	Return Value:
		1 if there is a loop, 0 if there isn't.	
	Complexity:
		O(n)					  											  */
int SLLHasLoop(const sll_node_t *root);



/*  Checks whether the two roots have an intesection (i.e., one node from each
	list point to the same node).	
	Return Value:
		The intesection node (the node pointed to). NULL if there is no 
		intersection.	
	Complexity:
		O(n^2)					  											  */
sll_node_t *SLLFindIntersection(const sll_node_t *root1, 
								const sll_node_t *root2);


#endif /* end of __SINGLE_LL_H__ */




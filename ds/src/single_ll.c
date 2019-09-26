#include <stdio.h> /* pfrintf */
#include <stdlib.h> /* malloc, calloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "single_ll.h" /* sll_node_t */


sll_node_t *SLLCreateNode(void *data, sll_node_t *next)
{
	sll_node_t * next_cpy;

	next_cpy = (sll_node_t *) malloc(sizeof(sll_node_t));
	next->item = data;
	next->next_node = NULL;

	return next_cpy;
}

/* 		Frees all pointers from the provided pointer onward.
 * 		If SLLFreeAll recieves a NULL: behaviour is undefined.					*/
void SLLFreeAll(sll_node_t *root)
{
	sll_node_t *runner = NULL;
	
	runner = root;
	
	/* find last node */
	for (; NULL != root->next_node;)
	{
		runner = root;
		
		for (; NULL != root->next_node->next_node;)
		{
			runner->next_node = runner->next_node->next_node;
			free(runner->next_node); runner->next_node = NULL;
		}
	}
	
	free(root); root = NULL;
}

/* 		Removes provided pointer from the linked list.
 * 		If <target> has no previous node, next will become root. 
 * 		If <target> has a next, it will be assigned to previous node.				*/
void SLLRemove(sll_node_t *target);

/* 		Removes <target>'s next node.														*/
void SLLRemoveAfter(sll_node_t *target);

void SLLInsert(sll_node_t *root, sll_node_t *new_node)
{
	sll_node_t *temp_node = NULL;
	
	temp_node->next_node = root->next_node;
	root->next_node = new_node;
	new_node->next_node = temp_node->next_node;
}

void SLLInsertAfter(sll_node_t *target, sll_node_t *new_node)
{
	sll_node_t *temp_node = NULL;
	
	temp_node->next_node = new_node->next_node; /* new node's target's next address */
	new_node->next_node = target->next_node;
	target->next_node = temp_node->next_node; /*  */
}

/* 		Counts on the items in the linked list 												*/
size_t SLLCount(const sll_node_t *root);

int SLLForeach(sll_node_t root, sll_foreach_action func, const void *func_param);

sll_node_t *SLLFind(const sll_node_t root, sll_find func, const void *func_param);

void SLLFlip(sll_node_t *root)
{
	sll_node_t *temp_node = NULL;
	
		
}

int SLLHasLoop(const sll_node_t *root)
{
	sll_node_t *slow_p = (sll_node_t *)root, *fast_p = (sll_node_t *)root; 

	while (slow_p && fast_p && fast_p->next_node) 
	{ 
		slow_p = slow_p->next_node; 
		fast_p = fast_p->next_node->next_node; 
		
		if (slow_p == fast_p) 
		{ 
		    printf("Found Loop"); 
		    return 1; 
		} 
	} 
	
	return 0;
}

sll_node_t *SLLFindIntersection(const sll_node_t *root1, const sll_node_t *root2)
{
	sll_node_t *root1_cpy = NULL, *root2_cpy = NULL;
	
	root1_cpy = (sll_node_t *)root1;
	root2_cpy = (sll_node_t *)root2;
	
	for (; NULL != root1_cpy->next_node;)
	{
		root1_cpy = root1_cpy->next_node;
		
		for (; NULL != root2_cpy->next_node;)
		{
			root2_cpy = root2_cpy->next_node;
			
			if (root1_cpy == root2_cpy)
			{
				return root1_cpy;
			}
		}
	}
	
	return NULL;
}

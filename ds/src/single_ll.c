#include <stdio.h> /* pfrintf */
#include <stdlib.h> /* malloc, calloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "single_ll.h" /* sll_node_t */

sll_node_t *SLLCreateNode(void *data, sll_node_t *next)
{
	sll_node_t *new_node = NULL;
	
	new_node = malloc(sizeof(next));
	
	if (NULL == new_node)
	{
		perror("Could not allocate memory for Create.");
	}

	new_node->item = data;
	next = new_node;
	next->next_node = NULL;

	return new_node;
}

void SLLFreeAll(sll_node_t *root)
{
	if (NULL != root->next_node)
	{
		SLLFreeAll(root->next_node);
	}
	
	root->next_node = NULL;
	free(root); root = NULL;
}

/* 		Removes provided pointer from the linked list.
 * 		If <target> has no previous node, next will become root. 
 * 		If <target> has a next, it will be assigned to previous node.				*/
void SLLRemove(sll_node_t *target);

/* 		Removes <target>'s next node.														*/
void SLLRemoveAfter(sll_node_t *target);

sll_node_t *SLLInsert(sll_node_t *root, sll_node_t *new_node)
{
		new_node->next_node = root;
	
	return new_node;
}

sll_node_t *SLLInsertAfter(sll_node_t *target, sll_node_t *new_node)
{
	sll_node_t *temp_node = NULL;
	
	temp_node = target->next_node;
	target->next_node = new_node;
	new_node->next_node = temp_node;

	return new_node;
}

/* 		Counts on the items in the linked list 												*/
size_t SLLCount(const sll_node_t *root);

int SLLForeach(sll_node_t *root, sll_foreach_action *func, const void *func_param);

sll_node_t *SLLFind(const sll_node_t *root, sll_find func, const void *func_param)
{
	sll_node_t * temp_node = NULL;
	void *item_cpy = NULL;
	void *param_cpy = NULL;
	
	temp_node = (sll_node_t *)root;
	item_cpy = temp_node->item;
	param_cpy = (void *)func_param;
	
	for (; NULL != temp_node; temp_node = temp_node->next_node)
	{
		if (func(item_cpy, param_cpy))
		{
			return (sll_node_t *)temp_node;
		}
	}
	
	return NULL;
}

sll_node_t *SLLFlip(sll_node_t *root)
{
	sll_node_t *temp_node = NULL, *current_node = NULL, *new_root = NULL;
	
	/* promote new_root to last node and temp to one before last */
	for (new_root = root; 
			NULL != new_root->next_node; 
			temp_node = new_root, new_root = new_root->next_node)
	{
	}
	
	/* start from last node and change new_root->next_node to previus node */
	for (current_node = new_root; 
			current_node != root; 
			current_node = temp_node, temp_node = temp_node->next_node)
	{
		for (temp_node = root; 
				temp_node->next_node != current_node; 
				temp_node = temp_node->next_node)
		{
		}
	}

	root->next_node = NULL;
	
	return new_root;
}

int SLLHasLoop(const sll_node_t *root)
{
	sll_node_t *slow_p = NULL, *fast_p = NULL; 
	
	slow_p = (sll_node_t *)root;
	fast_p = (sll_node_t *)root; 
	
	for (; slow_p && fast_p && fast_p->next_node; 
			slow_p = slow_p->next_node, fast_p = fast_p->next_node->next_node) 
	{ 
		if (slow_p == fast_p) 
		{ 
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

#include <stdlib.h> /* malloc, calloc, free */
#include <stddef.h> /* size_t */
 #include <stdio.h> /* perror */
 
#include "single_ll.h" /* sll_node_t */

sll_node_t *SLLCreateNode(void *data, sll_node_t *next)
{
	sll_node_t *new_node = NULL;
	
	new_node = malloc(sizeof(sll_node_t));
	
	if (NULL == new_node)
	{
		perror("Could not allocate memory for new node.");
	}

	new_node->item = data;
	new_node->next_node = next;

	return new_node;
}

void SLLFreeAll(sll_node_t *root)
{
	sll_node_t *temp_node = NULL;
	
	for (temp_node = root; NULL != root; temp_node = root)
	{
		root = temp_node->next_node;
		free(temp_node); temp_node = NULL;
	}
	
	free(temp_node); temp_node = NULL;
}

sll_node_t *SLLRemove(sll_node_t *target)
{
	sll_node_t *next_node = NULL;
	
	next_node = target->next_node;
	free(target);
	
	return next_node;
}


sll_node_t *SLLRemoveAfter(sll_node_t *target)
{
	sll_node_t *temp_node = NULL;
	
	temp_node = target->next_node;
	target->next_node = target->next_node->next_node;
	
	free(temp_node); temp_node = NULL;
	
	return target;
}

sll_node_t *SLLInsert(sll_node_t *root, sll_node_t *new_node)
{
	root->next_node = new_node->next_node;
	new_node->next_node = root;
	
	return new_node;
}

sll_node_t *SLLInsertAfter(sll_node_t *target, sll_node_t *new_node)
{
	sll_node_t *temp_node = NULL;
	
	temp_node = target->next_node;
	target->next_node = new_node;
	new_node->next_node = temp_node;

	return target;
}

size_t SLLCount(const sll_node_t *root)
{
	size_t counter = 1;
	sll_node_t *current = NULL;
	
	for (current = (sll_node_t *)root; 
			(NULL != current) && (NULL != current->next_node); 
			current = current->next_node, counter++)
	{
	}
	
	return counter;
}

int SLLForEach(sll_node_t *root, sll_foreach_action func, const void *func_param)
{
	sll_node_t *current = NULL;
	int status = 1;
	
	for (current = root; NULL != current; current = current->next_node)
	{
		if (0 == func(current->item, (void *)func_param))
		{
			status = 0;
			break;
		}
	}
	
	return status;
}

sll_node_t *SLLFind(const sll_node_t *root, sll_find func, const void *func_param)
{
	for(;NULL != root; root = root->next_node)
	{
		if (func(root->item, (void *)func_param))
		{
			return (sll_node_t *)root;
		}
	}
	
	return NULL;
}

sll_node_t *SLLFlip(sll_node_t *root)
{
	sll_node_t *flipped_list = NULL;

	if (NULL == root || NULL == root->next_node) 
	{
		return root; 
	}

	flipped_list = SLLFlip(root->next_node); 
	root->next_node->next_node = root; 
	root->next_node = NULL; 

	return flipped_list; 
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
	sll_node_t *root2_start = NULL;	

	for (; NULL != root1 ; root1 = root1->next_node)
	{
		for (root2_start = (sll_node_t *)root2; NULL != root2_start ; root2_start = root2_start->next_node)
		{
			if (root1 == root2_start)
			{
				return (sll_node_t *)root1;
			}
		}
	}
	
	return NULL;
}


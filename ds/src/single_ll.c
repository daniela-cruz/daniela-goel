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
	
	for (temp_node = root; NULL != root; temp_node = root, root = root->next_node)
	{
		free(temp_node); temp_node = NULL;
	}
}

sll_node_t *SLLRemove(sll_node_t *target)
{
	sll_node_t *temp_node = NULL;
	
	temp_node = target->next_node;
	free(target); target = NULL;
	
	return temp_node;
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

int SLLForeach(sll_node_t *root, sll_foreach_action func, const void *func_param)
{
	void *param_cpy = NULL;
	sll_node_t *current = NULL;
	int status = 0;
	
	param_cpy = ( void *)func_param;
	
	for (current = root; 
			NULL != current; 
			current = current->next_node)
	{
		if (1 == func(current->item, param_cpy))
		{
			perror("ForEach function failed.\n");
			status = 1;
			break;
		}
	}
	
	return status;
}

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
	sll_node_t *temp_node = NULL, *current = NULL, *new_root = NULL;
	
	/* promote new_root to last node and temp to one before last */
	for (new_root = root; 
			NULL != new_root->next_node; 
			temp_node = new_root, new_root = new_root->next_node)
	{
	}
	
	/* start from last node and change new_root->next_node to previus node */
	for (current = new_root; 
			current != root; 
			current = temp_node, temp_node = temp_node->next_node)
	{
		for (temp_node = root; 
				temp_node->next_node != current; 
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

	for (root1_cpy = (sll_node_t *)root1; NULL != root1_cpy->next_node; root1_cpy = root1_cpy->next_node)
	{
		for (root2_cpy = (sll_node_t *)root2; NULL != root2_cpy->next_node; root2_cpy = root2_cpy->next_node)
		{
			if (root1_cpy == root2_cpy)
			{
				return root1_cpy;
			}
		}
	}
	
	return NULL;
}

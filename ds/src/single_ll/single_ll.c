#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "single_ll.h" /* sll_node_t */

sll_node_t *SLLCreateNode(void *data, sll_node_t *next)
{
	sll_node_t *new_node = NULL;
	
	new_node = malloc(sizeof(*new_node));
	if (NULL == new_node)
	{
		return NULL;
	}

	new_node->data = data;
	new_data->next = next;

	return new_node;
}

void SLLFreeAll(sll_node_t *root)
{
	for (; NULL != root->next; root->next = root->next->next)
	{
		SLLRemove(root->next);
	}
	
	free(root); root = NULL;
}

sll_node_t *SLLRemove(sll_node_t *target)
{
	sll_node_t *temp_node = NULL;
	
	temp_node = target->next;
	free(target);
	
	return temp_node;
}

sll_node_t *SLLRemoveAfter(sll_node_t *target)
{
	sll_node_t *temp_node = NULL;
	
	temp_node = target->next->next;
	free(target->next->next);
	target->next= temp_node;
	
	return target;
}

sll_node_t *SLLInsert(sll_node_t *root, sll_node_t *new_node)
{
		new_node->next = root;
	
	return new_node;
}

sll_node_t *SLLInsertAfter(sll_node_t *target, sll_node_t *new_node)
{
	sll_node_t *temp_node = NULL;
	
	temp_node = target->next;
	target->next = new_node;
	new_node->next = temp_node;

	return new_node;
}

size_t SLLCount(const sll_node_t *root)
{
	size_t counter = 0;
	sll_node_t *current_node = NULL;
	
	for (current_node = (sll_node_t *)root; 
			NULL != current_node; 
			current_node = current_node->next, counter++)
	{
	}
	
	return counter;
}

int SLLForEach(sll_node_t *root, sll_foreach_func_t func, const void *func_param)
{
	void *param_cpy = NULL;
	sll_node_t *current_node = NULL;
	int status = 0;
	
	param_cpy = ( void *)func_param;
	
	for (current_node = root; 
			NULL != current_node; 
			current_node = current_node->next)
	{
		if (1 == func(current_node->data, param_cpy))
		{
			perror("ForEach function failed.\n");
			status = 1;
			break;
		}
	}
	
	return status;
}

sll_node_t *SLLFind(const sll_node_t *root, sll_find_func_t func, const void *func_param)
{
	sll_node_t * temp_node = NULL;
	void *item_cpy = NULL;
	void *param_cpy = NULL;
	
	temp_node = (sll_node_t *)root;
	item_cpy = temp_node->data;
	param_cpy = (void *)func_param;
	
	for (; NULL != temp_node; temp_node = temp_node->next)
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
			NULL != new_root->next; 
			temp_node = new_root, new_root = new_root->next)
	{
	}
	
	/* start from last node and change new_root->next to previus node */
	for (current_node = new_root; 
			current_node != root; 
			current_node = temp_node, temp_node = temp_node->next)
	{
		for (temp_node = root; 
				temp_node->next != current_node; 
				temp_node = temp_node->next)
		{
		}
	}

	root->next = NULL;
	
	return new_root;
}

int SLLHasLoop(const sll_node_t *root)
{
	sll_node_t *slow_p = NULL, *fast_p = NULL; 
	
	slow_p = (sll_node_t *)root;
	fast_p = (sll_node_t *)root; 
	
	for (; slow_p && fast_p && fast_p->next; 
			slow_p = slow_p->next, fast_p = fast_p->next->next) 
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
	
	for (; NULL != root1_cpy->next;)
	{
		root1_cpy = root1_cpy->next;
		
		for (; NULL != root2_cpy->next;)
		{
			root2_cpy = root2_cpy->next;
			
			if (root1_cpy == root2_cpy)
			{
				return root1_cpy;
			}
		}
	}
	
	return NULL;
}


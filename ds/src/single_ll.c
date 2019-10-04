#include <stdlib.h> /*	malloc	*/ 
#include <stdio.h>  /*  perror	*/

#include "single_ll.h"

sll_node_t *SLLCreateNode(void *data, sll_node_t *next)
{
	sll_node_t *node = NULL;
	node = (sll_node_t *)malloc(sizeof(node));
	if (NULL == node)
	{
		perror("Malloc failed in root creation");
		
		return NULL;
	}

	node->data = data;
	node-> next = next;

	return node; 
}

void SLLFreeAll(sll_node_t *root)
{
	sll_node_t *temp_node = root;
	
	for (; NULL != root; temp_node = root, root = root->next)
	{
		free(temp_node);
		temp_node = NULL;
	}
}

sll_node_t *SLLRemove(sll_node_t *target)
{
	sll_node_t *temp_node = target->next;
	
	target->data = target->next->data;
	target->next = target->next->next;

	free(temp_node);
	temp_node = NULL;

	return target;	
}

sll_node_t *SLLRemoveAfter(sll_node_t *target)
{
	sll_node_t *temp_node = target->next;
	
	target->next = target->next->next;

	free(temp_node);
	temp_node = NULL;

	return target;
}

sll_node_t *SLLInsert(sll_node_t *target, sll_node_t *new_node)
{
	void *new_node_data = new_node->data;
	
	new_node->next = target->next;
	new_node->data = target->data;
	target->next = new_node;
	target->data = new_node_data;

	return target;
}

sll_node_t *SLLInsertAfter(sll_node_t *target, sll_node_t *new_node)
{
	target->next = new_node;
	new_node->next = target->next;
	
	return target;	
}

size_t SLLCount(const sll_node_t *root)
{
	size_t node_counter = 0;

	for (node_counter = 0; NULL != root; node_counter++)
	{
		root = root->next;
	}
	
	return node_counter;
}

int SLLForEach(sll_node_t *root, sll_foreach_func_t func, void *func_param)
{
	for (; NULL != root; root = root->next)
	{
		if (0 != func(root->data, func_param))
		{
			return 1;	
		}		
	}
	
	return 0;
}

sll_node_t *SLLFind(const sll_node_t *root, sll_find_func_t func, void *func_param)
{
	for (; NULL != root; root = root->next)
	{
		if (0 == func(root->data, func_param))
		{
			return (sll_node_t *)root;
		}	
	}
	
	return NULL;
}

sll_node_t *SLLFlip(sll_node_t *root)
{
	int i = 0;
	int list_size = SLLCount(root);
	int counter = 0;  
	sll_node_t *curr_node = root;
	sll_node_t *last_node = root;
	void *temp_data = NULL;

	for (counter = list_size / 2; 0 != counter; curr_node = curr_node->next, counter--)
	{
		for (last_node = root, i = 0;
			i != list_size - 1;
			i++, last_node = last_node->next);

		temp_data = curr_node->data;
		curr_node->data = last_node->data; 
		last_node->data = temp_data;

		list_size--; 
	}

	return curr_node;
}

/* returns 1 if there is a loop, 0 if not */
int SLLHasLoop(const sll_node_t *node)
{
	sll_node_t *slow_p = (sll_node_t *)node;
	sll_node_t *fast_p = (sll_node_t *)node;

	/* Floyd's Cycle detection algorithm */ 
	for (; NULL != slow_p && NULL != fast_p && NULL != fast_p->next;
		slow_p = slow_p->next, fast_p = fast_p->next->next)
	{
		/* if slow_p and fast_p meet at some pooint
		   then there is a loop			    */
		if (slow_p == fast_p)
		{
			return 1;
		}	
	}
		
	return 0;
}

sll_node_t *SLLFindIntersection(const sll_node_t *first_list, const sll_node_t *second_list)
{
	sll_node_t *second_list_iterator = (sll_node_t *)second_list;
	
	for (; NULL != first_list; first_list = first_list->next)
	{
		for (second_list_iterator = (sll_node_t *)second_list;
			NULL != second_list_iterator;
			second_list_iterator = second_list_iterator->next)
		{
			if (first_list == second_list_iterator)
			{
				return (sll_node_t *)first_list;
			}
		}
	}

	return NULL;
}


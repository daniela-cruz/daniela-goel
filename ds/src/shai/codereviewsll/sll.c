#include <stddef.h> /* size_t       */
#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* perror       */
#include <assert.h> /* assert       */

#include "sll.h"

/* ############################### Functions ################################ */

sll_node_t *SLLCreateNode(void *data, sll_node_t *next)
{
	sll_node_t *new_node = NULL;

	new_node = (sll_node_t*)malloc(sizeof(*new_node));
	if (NULL == new_node)
	{
		perror("malloc");
		return NULL;
	}

	new_node->data = data;
	new_node->next = next;

	return new_node;
}



void SLLFreeAll(sll_node_t *root)
{
	sll_node_t *node_temp = root;

	assert(root != NULL);

	for (node_temp = root; NULL != root;)
	{
		node_temp = root;
		root = root->next;
	
		free(node_temp);
		node_temp = NULL;
	}
}



sll_node_t *SLLRemove(sll_node_t *node)
{
	sll_node_t *node_temp = node->next;

	assert(node != NULL);

	node->data = node->next->data;
	node->next = node->next->next;

	free(node_temp);
	node_temp = NULL;
	
	return node;
}



sll_node_t *SLLRemoveAfter(sll_node_t *node)
{
	sll_node_t *node_temp = node->next;

	assert(node != NULL);

	node->next = node->next->next;

	free(node_temp);
	node_temp = NULL;
	
	return node;
}



sll_node_t *SLLInsert(sll_node_t *reference_node, sll_node_t *new_node)
{
	void *data_temp = new_node->data;

	assert(reference_node != NULL);
	assert(new_node != NULL);

	new_node->next = reference_node->next;
	reference_node->next = new_node;

	new_node->data = reference_node->data;
	reference_node->data = data_temp;
	
	return reference_node;
}



sll_node_t *SLLInsertAfter(sll_node_t *reference_node, sll_node_t *new_node)
{
	assert(reference_node != NULL);
	assert(new_node != NULL);

	new_node->next = reference_node->next;
	reference_node->next = new_node;

	return reference_node;
}



size_t SLLCount(const sll_node_t *root)
{
	size_t node_counter = 0;

	assert(root != NULL);

	for (node_counter = 0; NULL != root;)
	{
		node_counter++;
		root = root->next;
	}

	return node_counter;
}



int SLLForEach(sll_node_t *root, sll_foreach_func_t foreach_func, void *param)
{
	int is_success = 0;

	assert(root != NULL);

	for (is_success = 0 ; NULL != root && 0 == is_success;)
	{
		is_success = foreach_func(root->data, param);
		root = (0 == is_success) ? root->next : root;
	}

	return is_success;
}



sll_node_t *SLLFind(const sll_node_t *root, sll_ismatch_func_t find_func, void *param)
{
	int is_found = 0;

	assert(root != NULL);

	for (is_found = 0; NULL != root && 0 == is_found;)
	{
		is_found = find_func(root->data, param);
		root = (0 == is_found) ? root->next : root;
	}

	return (sll_node_t*)root;
}



sll_node_t *SLLFlip(sll_node_t *root)
{
	sll_node_t *previous_node = NULL;
	sll_node_t *current_node = root;
	sll_node_t *next_node = NULL;	

	assert(root != NULL);

	for (; NULL != current_node;)
	{
		next_node = current_node->next;
		current_node->next = previous_node;

		previous_node = current_node;
		current_node = next_node;
	}

	return previous_node;
}



int SLLHasLoop(const sll_node_t *root)
{
	sll_node_t *slow_iter = (sll_node_t *)root;	
	sll_node_t *fast_iter = slow_iter;

	assert(root != NULL);
	
	for (slow_iter = root->next, fast_iter = root->next->next;
		 fast_iter != NULL;
		 slow_iter = slow_iter->next, fast_iter = fast_iter->next->next)
	{
		if (slow_iter == fast_iter)
		{
			return 1;
		}
	}

	return 0;
}



sll_node_t *SLLFindIntersection(const sll_node_t *root1, const sll_node_t *root2)
{
	sll_node_t *root1_iter = NULL;
	sll_node_t *root2_iter = NULL;	

	assert(root1 != NULL);
	assert(root2 != NULL);

	for (root1_iter = (sll_node_t*)root1;
		 root1_iter != NULL ;
		 root1_iter = root1_iter->next)
	{
		for (root2_iter = (sll_node_t*)root2;
			 root2_iter != NULL ;
			 root2_iter = root2_iter->next)
		{
			if (root1_iter == root2_iter)
			{
				return root1_iter;
			}
		}
	}
	
	return NULL;
}












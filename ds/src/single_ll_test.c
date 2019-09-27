#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, calloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "single_ll.h" /* sll_node_t */

static void SLLTest();
static sll_node_t *SLLCreateNodeTest(void *data, sll_node_t *next);
void SLLInsertTest(sll_node_t *root);

int main()
{
	SLLTest();
	
	return 0;
}

static void SLLTest()
{
	sll_node_t *list = NULL;
	int num = 123;
	
	list = (sll_node_t *)SLLCreateNodeTest((void *)&num, list);
	
	printf("\nContent SLL test. . . \n");
	
	if (num == *(int *)(list->item))
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("Failure! Item content is: %d\n and not: %d!", *(int *)(list->item), num);
	}
	
	printf("\nFree all test. . . \n");
	
	/***********************/
	SLLInsertTest(list);
	
	
	/***********************/
	SLLFreeAll(list);
}

static sll_node_t *SLLCreateNodeTest(void *data, sll_node_t *next)
{
	printf("\nCreate SLL test. . . \n");
	
	next = SLLCreateNode(data, next);
	
	if (next)
	{
		printf("SUCCESS! A pointer was allocated to first node.\n");
		printf("\nTesting next_node allocation. . .\n");
		
		if (!next->next_node)
		{
			printf("SUCCESS!\n");
			printf("\nTesting data item allocation. . .\n");
			
			if (*(int *)data == *(int *)(next->item))
			{
				printf("SUCCESS!\n");
			}
			else
			{
				printf("Failure! Item content is: %d\n", *(int *)(next->item));
			}
			
		}
		else
		{
			printf("Failure! Pointer was not allocaed to NULL\n");
		}
		
	}
	else
	{
		printf("Failure! Pointer was not allocaed at all\n");
	}
	
	return next;
}

void SLLInsertTest(sll_node_t *root)
{
	sll_node_t *new_node = NULL;
	int num_2 = 456;
	
	new_node = SLLCreateNodeTest((void *)&num_2, new_node);
	printf("\nInsert test. . .\n");
	SLLInsert(root, new_node);
	
	if (*(int *)root->next_node->item == num_2)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("Failure! new item was not inserted\n");
	}
}

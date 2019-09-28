#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, calloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "single_ll.h" /* sll_node_t */

static void SLLTest();
static sll_node_t *SLLCreateNodeTest(int data, sll_node_t *next);
static sll_node_t *SLLInsertTest(sll_node_t *root);
static void SLLInsertAfterTest(sll_node_t *target);
static void SLLHasLoopTest(sll_node_t *root);
static sll_node_t *SLLFlipTest(sll_node_t *root);

static void SLLFindTest(sll_node_t *root);
static int FindIntInList(void *param, void *root);

int main()
{
	SLLTest();
	
	return 0;
}

static void SLLTest()
{
	sll_node_t *list = NULL;
	int num = 123;
	
	list = (sll_node_t *)SLLCreateNodeTest(num, list);
	
	/***********************/
	list = SLLInsertTest(list);
	SLLInsertAfterTest(list);
	SLLHasLoopTest(list);
	SLLFlipTest(list);
	SLLFindTest(list);
	
	/***********************/
	printf("\nFree all test. . . \n");
	SLLFreeAll(list);
}

static sll_node_t *SLLCreateNodeTest(int data, sll_node_t *next)
{
	printf("\nCreate SLL test. . . \n");
	
	next = SLLCreateNode((void *)&data, next);
	
	if (next)
	{
		printf("SUCCESS! A pointer was allocated to first node.\n");
		printf("\nTesting next_node allocation. . .\n");
		
		if (!next->next_node)
		{
			printf("SUCCESS!\n");
			printf("\nTesting data item allocation. . .\n");
			
			if (data == *(int *)(next->item))
			{
				printf("SUCCESS!\n");
				printf("\nTesting data items are matched. . .\n");
				
				if (data == *(int *)(next->item))
				{
					printf("SUCCESS!\n");
				}
				else
				{
					printf("Failure! Item content is: %d\n and not: %d!", *(int *)(next->item), data);
				}
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

sll_node_t *SLLInsertTest(sll_node_t *root)
{
	sll_node_t *new_node = NULL, *new_node_2 = NULL;
	int num_2 = 456, num_3 = 789;
	
	assert(root);
	
	new_node = SLLCreateNode((void *)&num_2, root);
	new_node->item = (void *)&num_2;
	new_node_2 = SLLCreateNode((void *)&num_3, new_node);
	new_node_2->item = (void *)&num_3;
	
	printf("\nInsert test. . .\n");
	new_node = SLLInsert(root, new_node);
	
	if (new_node->next_node == root)
	{
		printf("SUCCESS!\n");
		new_node_2 = SLLInsert(new_node, new_node_2);

		if (*(int *)new_node->item == num_2)
		{
			printf("SUCCESS!\n");
		}
		else
		{
			printf("Failure! new item was not inserted\n");
		}
	}
	else
	{
		printf("Failure! new item was not inserted\n");
	}
	
	return new_node_2;
}

static void SLLInsertAfterTest(sll_node_t *target)
{
	sll_node_t *new_node = NULL;
	int num_4 = 321;
	
	new_node = SLLCreateNode((void *)&num_4, new_node);
	
	printf("\nInsert AFTER test. . .\n");
	new_node = SLLInsertAfter(target, new_node);
	
	if (new_node == target->next_node)
		{
			printf("SUCCESS!\n");
		}
		else
		{
			printf("Failure! Insertion AFTER was not completed.\n");
		}
		
}

static void SLLHasLoopTest(sll_node_t *root)
{
	printf("\nFind loop test: \n");

	if (SLLHasLoop(root))
	{
		printf("SUCCESS!Loop was NOT found\n");
	}
	else
	{
		printf("Failure! Loop was found.\n");
	}
}

static sll_node_t *SLLFlipTest(sll_node_t *root)
{
	sll_node_t *new_root = NULL, *root_cpy = NULL;
	
	root_cpy = root;
	
	printf("\nFlip list test - flip I: \n");
	new_root = SLLFlip(root);
	
	if (NULL == root->next_node)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("Failure! new_root was not flipped.\n");
	}
	
	printf("\nFlip list test - flip II: \n");
	new_root = SLLFlip(new_root);

	if (root_cpy == root)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("Failure! new_root was not flipped back to original root address.\n");
	}
	
	return root;
}

static void SLLFindTest(sll_node_t *root)
{
	sll_node_t *found_node = NULL;
	int num = 789/*, data = 123, data_2 = 456*/;
	void *num_ptr = NULL;
	
	printf("\nFind in list test. . . \n");
	num_ptr = (void *)&num;
	
	found_node = SLLFind((const sll_node_t *)root, (sll_find)FindIntInList, num_ptr);
	
	if (*(int *)found_node->item == num)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("Failure! Could not find item in list.\n");
	}
}

static int FindIntInList(void *list_item, void *param)
{
	int is_found = 0;
	
	printf("\nContent of param is: %d and root item is: %d. \n", *(int *)param, *(int *)list_item);
	if (*(int *)param == *(int *)list_item)
	{
		is_found = 1;
	}
	
	return is_found;
}

static void ForEAchTest(sll_node_t *root)
{
	int incrementor = 10;
	
	SLLForeach(root, (sll_foreach_action)ForEachAdd10, (void *)&incrementor);
}

static int ForEachAdd10(void *data, void *param)
{

}

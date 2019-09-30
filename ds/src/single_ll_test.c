#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, calloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "single_ll.h" /* sll_node_t */

static void SLLTest();
static sll_node_t *SLLCreateNodeTest(int data, sll_node_t *next);
static sll_node_t *SLLInsertTest(sll_node_t *root, sll_node_t *new_node);
static sll_node_t *SLLInsertAfterTest(sll_node_t *target, sll_node_t *new_node);
static void SLLHasLoopTest(sll_node_t *root);
static sll_node_t *SLLFlipTest(sll_node_t *root);

static void SLLFindTest(sll_node_t *root);
static int FindIntInList(void *param, void *root);

static void ForEachTest(sll_node_t *root);
static int ForEachAdd10(void *data, void *param);

static void IntersectionTest(sll_node_t *root);

static sll_node_t *RemoveTest(sll_node_t *target);
static void CounterTest(sll_node_t *root);

int main()
{
	SLLTest();
	
	return 0;
}

static void SLLTest()
{
	sll_node_t *list = NULL, *new_node = NULL, *new_node_2 = NULL, *list_cpy = NULL;
	int num = 123, num_2 = 456, num_3 = 789;
	
	CounterTest(list);
	list = (sll_node_t *)SLLCreateNodeTest(num, list);
	CounterTest(list);
	new_node = SLLCreateNode((void *)&num_2, new_node);
	CounterTest(list);
	new_node_2 = SLLCreateNode((void *)&num_3, new_node);
	/***********************/
	CounterTest(list);
	list = SLLInsertTest(list, new_node);
	CounterTest(list);
	new_node = SLLInsertAfterTest(new_node, new_node_2);
	CounterTest(list);
	SLLHasLoopTest(list);
	SLLFlipTest(list);
	SLLFindTest(list);
	ForEachTest(list);
	IntersectionTest(list);
	CounterTest(list);
	list_cpy = RemoveTest(list);
	CounterTest(list_cpy);
	/***********************/
	printf("\nFree all test. . . \n");
	SLLFreeAll(list_cpy);
}

static sll_node_t *SLLCreateNodeTest(int data, sll_node_t *next)
{
	sll_node_t *new_node = NULL;
	
	printf("\nCreate SLL test. . . \n");
	
	new_node = SLLCreateNode((void *)&data, next);
	
	if (new_node)
	{
		printf("SUCCESS! A pointer was allocated to first node.\n");
		printf("1. Testing next_node allocation. . .\n");
		
		if (!new_node->next_node)
		{
			printf("SUCCESS!\n");
			printf("2. Testing data item allocation. . .\n");
			
			if (data == *(int *)(new_node->item))
			{
				printf("SUCCESS!\n");
				printf("3. Testing data items are matched. . .\n");
				
				if (data == *(int *)(new_node->item))
				{
					printf("SUCCESS!\n");
				}
				else
				{
					printf("Failure! Item content is: %d\n and not: %d!", *(int *)(new_node->item), data);
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
	
	return new_node;
}

static sll_node_t *SLLInsertTest(sll_node_t *root, sll_node_t *new_node)
{
	printf("\nInsert test. . .\n");
	new_node = SLLInsert(root, new_node);
	
	if (new_node->next_node == root)
	{
		printf("SUCCESS!\n");
		/*new_node_2 = SLLInsert(new_node, new_node_2);

		if (*(int *)new_node->item == num_2)
		{
			printf("SUCCESS!\n");
		}
		else
		{
			printf("Failure! new item was not inserted\n");
		}*/
	}
	else
	{
		printf("Failure! new item was not inserted\n");
	}
	
	return new_node;
}

static sll_node_t *SLLInsertAfterTest(sll_node_t *target, sll_node_t *new_node)
{
	printf("\nInsert AFTER test. . .\n");
	target = SLLInsertAfter(target, new_node);
	
	if (new_node == target->next_node)
		{
			printf("SUCCESS!\n");
		}
		else
		{
			printf("Failure! Insertion AFTER was not completed.\n");
		}
		
		return target;
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

static void ForEachTest(sll_node_t *root)
{
	int incrementor = 10;
	int item_cpy = 0;
	
	item_cpy = *(int *)root->item;
	
	printf("\nFor each test. . . \n");
	if (!SLLForeach(root, (sll_foreach_action)ForEachAdd10, (void *)&incrementor))
	{
		printf("SUCCESS!\n");
		printf("Incremented input test:\n");
		
		if (*(int *)root->item == (item_cpy + incrementor))
		{
			printf("SUCCESS!\n");
		}
		else
		{
			printf("Failure! Item was not incremented correctly. Value is: %d and old value is: %d\n", 
					*(int *)root->item, item_cpy);
		}
	}
	
	else
	{
		printf("Failure! Function returned failure status.\n");
	}
}

static int ForEachAdd10(void *data, void *param)
{
	*(int *)data += *(int *)param;
	
	return 0;
}

static void IntersectionTest(sll_node_t *root)
{
	sll_node_t *root2 = NULL, *is_found = NULL;
	int num_5 = 654;
	
	printf("\nIntersection test. . . \n");
	root2 = SLLCreateNode((void *)&num_5, root2);
	root2->next_node = root->next_node;
	is_found = SLLFindIntersection(root, root2);
	
	if (is_found == root->next_node)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("Failure! Could not find intersection although there is supposed to be one.\n");
	}
}

static sll_node_t *RemoveTest(sll_node_t *target)
{
	sll_node_t *target_cpy = NULL;
	
	printf("\nRemove test. . . \n");
	target_cpy = target->next_node;
	target= SLLRemove(target);

	if (target_cpy == target)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("Failure! Target was not removed.\n");
	}
	
	return target;
}

static void CounterTest(sll_node_t *root)
{
	printf("\nCount test shows: %lu nodes.\n", SLLCount(root));
}


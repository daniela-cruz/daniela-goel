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
	sll_node_t *list = NULL, *list2 = NULL,*new_node = NULL, *new_node_2 = NULL, *list_cpy = NULL;
	int num = 123, num_2 = 456, num_3 = 789;
	
	CounterTest(list);
	list = (sll_node_t *)SLLCreateNodeTest(num, list);
	new_node = SLLCreateNode((void *)&num_2, new_node);
	new_node_2 = SLLCreateNode((void *)&num_3, new_node);
	/***********************/
	SLLInsertTest(list, new_node);
	CounterTest(list);
	SLLInsertAfterTest(new_node, new_node_2);
	CounterTest(list);
	SLLHasLoopTest(list);
	SLLFindTest(list);
	/*IntersectionTest(list);*/
	
	CounterTest(list);
	
	printf("\nFlip test. . . \t\t");
	list2 = SLLFlip(list);
	list2 = SLLFlip(list);
	
	if (list2 == list)
	{
		printf("SUCCESS\n");
	}
	else
	{
		printf("FAILURE\n");
	}
	
	ForEachTest(list);
	CounterTest(list);
	CounterTest(list);
	/***********************/
	printf("\nFree all test. . . \n");
	SLLFreeAll(list); 
}

static sll_node_t *SLLCreateNodeTest(int data, sll_node_t *next)
{
	sll_node_t *new_node = NULL;
	
	printf("\nCreate SLL test. . . \n");
	
	new_node = SLLCreateNode((void *)&data, next);
	
	if (new_node)
	{
		printf("SUCCESS! A pointer was allocated to first node.\n");
		printf("1. Testing next_node allocation. . .\t");
		
		if (!new_node->next_node)
		{
			printf("SUCCESS!\n");
			printf("2. Testing data item allocation. . .\t");
			
			if (data == *(int *)(new_node->item))
			{
				printf("SUCCESS!\n");
				printf("3. Testing data items are matched. . .\t");
				
				if (data == *(int *)(new_node->item))
				{
					printf("SUCCESS!\n");
				}
				else
				{
					printf("Failure! Item content is: %d\n and not: %d!\n", *(int *)(new_node->item), data);
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

static void CounterTest(sll_node_t *root)
{
	printf("\nCount test shows: %lu nodes.\n", SLLCount(root));
}

static sll_node_t *SLLInsertTest(sll_node_t *root, sll_node_t *new_node)
{
	sll_node_t *temp = NULL;
	
	temp = root->next_node;
	
	printf("\nInsert test. . .\t");
	new_node = SLLInsert(root, new_node);
	
	if (temp == new_node->next_node)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("Failure! new item was not inserted\n");
	}
	
	return new_node;
}

static sll_node_t *SLLInsertAfterTest(sll_node_t *target, sll_node_t *new_node)
{
	size_t counter = 0; 
	printf("\nInsert AFTER test. . .\t");
	target = SLLInsertAfter(target, new_node);
	counter = SLLCount(target);
	
	if (SLLCount(target) == counter)
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
	printf("\nFind loop test: \t");

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
	int num_3 = 0; 
	
	num_3 = *(int*)root->next_node->next_node->item;
	
	root_cpy = root;
	
	printf("\nFlip list test - flip I: \t");
	new_root = SLLFlip(root);
	
	if (num_3 == *(int*)new_root->item)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("Failure! new_root was not flipped.\n");
	}
	
	printf("\nFlip list test - flip II: \t");
	root_cpy = SLLFlip(new_root);

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
	int num = 789;
	
	printf("\nFind in list test. . . \t");
	
	found_node = SLLFind(root, (sll_find)FindIntInList, (void *)&num);
	
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
	
	printf("\nFor each test. . . \t");
	
	if (!SLLForEach(root, (sll_foreach_action)ForEachAdd10, (void *)&incrementor))
	{
		printf("SUCCESS!\n");
		printf("Incremented input test:\t");
		
		if ((*(int *)root->item) == (item_cpy + incrementor))
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
		printf("Failure! Function returned failure status. \nFunction status is: %d\n", 
				SLLForEach(root, (sll_foreach_action)ForEachAdd10, (void *)&incrementor));
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
	
	printf("\nIntersection test. . . \t");
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
	
	printf("\nRemove test. . . \t");
	target_cpy = target->next_node;
	target = SLLRemove(target);

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

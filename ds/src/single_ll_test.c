#include <stdio.h> /* printf */
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
	sll_node_t *list = NULL, *list_cpy = NULL;
	int num = 123;
	
	list = (sll_node_t *)SLLCreateNodeTest(num, list);
	
	/***********************/
	list = SLLInsertTest(list);
	SLLInsertAfterTest(list);
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
	SLLFreeAll(list);
}

static sll_node_t *SLLCreateNodeTest(int data, sll_node_t *next)
{
	printf("\nCreate SLL test. . . \n");
	
	next = SLLCreateNode((void *)&data, next);
	
	if (next)
	{
		printf("SUCCESS! A pointer was allocated to first node.\n");
		printf("\nTesting next allocation. . .\n");
		
		if (!next->next)
		{
			printf("SUCCESS!\n");
			printf("\nTesting data data allocation. . .\n");
			
			if (data == *(int *)(next->data))
			{
				printf("SUCCESS!\n");
				printf("\nTesting data items are matched. . .\n");
				
				if (data == *(int *)(next->data))
				{
					printf("SUCCESS!\n");
				}
				else
				{
					printf("Failure! Item content is: %d\n and not: %d!", *(int *)(next->data), data);
				}
			}
			else
			{
				printf("Failure! Item content is: %d\n", *(int *)(next->data));
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
	new_node->data = (void *)&num_2;
	new_node_2 = SLLCreateNode((void *)&num_3, new_node);
	new_node_2->data = (void *)&num_3;
	
	printf("\nInsert test. . .\n");
	new_node = SLLInsert(root, new_node);
	
	if (new_node->next == root)
	{
		printf("SUCCESS!\n");
		new_node_2 = SLLInsert(new_node, new_node_2);

		if (*(int *)new_node->data == num_2)
		{
			printf("SUCCESS!\n");
		}
		else
		{
			printf("Failure! new data was not inserted\n");
		}
	}
	else
	{
		printf("Failure! new data was not inserted\n");
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
	
	if (new_node == target->next)
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
	
	if (NULL == root->next)
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
	
	found_node = SLLFind((const sll_node_t *)root, (sll_find_func_t)FindIntInList, num_ptr);
	
	if (*(int *)found_node->data == num)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("Failure! Could not find data in list.\n");
	}
}

static int FindIntInList(void *list_item, void *param)
{
	int is_found = 0;
	
	printf("\nContent of param is: %d and root data is: %d. \n", *(int *)param, *(int *)list_item);
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
	
	item_cpy = *(int *)root->data;
	
	printf("\nFor each test. . . \n");
	if (!SLLForEach(root, (sll_foreach_func_t)ForEachAdd10, (void *)&incrementor))
	{
		printf("SUCCESS!\n");
		printf("Incremented input test:\n");
		
		if (*(int *)root->data == (item_cpy + incrementor))
		{
			printf("SUCCESS!\n");
		}
		else
		{
			printf("Failure! Item was not incremented correctly. Value is: %d and old value is: %d\n", 
					*(int *)root->data, item_cpy);
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
	root2->next = root->next;
	is_found = SLLFindIntersection(root, root2);
	
	if (is_found == root->next)
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
	target_cpy = target->next;
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

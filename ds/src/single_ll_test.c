#include <stdio.h>  /* printf */ 
#include <stdlib.h> /* malloc */

#include "single_ll.h"

int AddNum(void *data, void *num);
int FindNum(const void *data, void *num);

int main()
{
	int a[10] = {0};
	int a2[5] = {0};
	int b = 20;
	int c = 30;
	int find_param = 34;
	int foreach_param = 4;
	int i = 0;
	sll_node_t *root = NULL;
	sll_node_t *root2 = NULL;
	sll_node_t *node = NULL;
	sll_node_t *temp = NULL;
	
<<<<<<< HEAD
	for(i = 0; i < 10; i++)
=======
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
>>>>>>> de2cc824853fa2d6539a60525d791a7b25d80bee
	{
		a[i] = i;
	}
<<<<<<< HEAD
=======
	
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
>>>>>>> de2cc824853fa2d6539a60525d791a7b25d80bee
	
	for(i = 0; i < 5; i++)
	{
		a2[i] = i;
	}

	printf("printing values\n");	
	for(i = 0; i < 10; i++)
	{
		root = SLLCreateNode(&a[i], root);
	}
	
<<<<<<< HEAD
	node = root;
	
	while(NULL != node)
=======
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
>>>>>>> de2cc824853fa2d6539a60525d791a7b25d80bee
	{
		printf("%d, ", *(int *)node->data);
		node = node->next;
	}	
	
	printf("\n");
	
	node = root->next;
	
	printf("\nremoving second node\n");
	SLLRemove(node);
	
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next;
	}
	printf("\nnodes in linked list: %ld\n", SLLCount(root));

<<<<<<< HEAD
	printf("\n\nremoving second's next node\n");
	node = root->next;
	SLLRemoveAfter(node);
	node = root;
	
	while(NULL != node)
=======
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
>>>>>>> de2cc824853fa2d6539a60525d791a7b25d80bee
	{
		printf("%d, ", *(int *)node->data);
		node = node->next;
	}
	printf("\nnodes in linked list: %ld\n\n", SLLCount(root));
	
	printf("inserting node to third node\n");
	node = SLLCreateNode(&b, NULL);
	temp = (root->next)->next;
	SLLInsert(temp, node);
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next;
	}
	printf("\nnodes in linked list: %ld\n", SLLCount(root));
	
	printf("\ninserting node to third' next node\n");
	node = SLLCreateNode(&c, NULL);
	temp = (root->next)->next;
	SLLInsertAfter(temp, node);
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next;
	}
	printf("\nnodes in linked list: %ld\n", SLLCount(root));
	
	printf("\nis there a loop: %d\n", SLLHasLoop(root));
	printf("forcing loop\n");
	temp = root->next;
	node = root;
	
	while(NULL != node->next)
	{
		node = node->next;
	}
	node->next = temp;
	printf("is there a loop: %d\n", SLLHasLoop(root));
	node->next = NULL;
	
	printf("\nadding 4 to every member in linked list\n");
	SLLForEach(root, &AddNum, &foreach_param);	
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next;
	}
	printf("\n");
	
	printf("\nlooking for node that contains 34\n");
	printf("%d\n", *(int *)(SLLFind(root, &FindNum, &find_param)->data));
	
	printf("\nflipping list\n");
	SLLFlip(root);
	node = root;
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next;
	}
	
	printf("\n\ncreating new linked list\n");	
	for(i = 0; i < 5; i++)
	{
		root2 = SLLCreateNode(&a2[i], root2);
	}
	
	node = root2;
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next;
	}
	
	node = root2;
	while(NULL != node->next)
	{
		node = node->next;
	}
	printf("\n\nforcing intersection at last node\n");
	node->next = root->next;
	
	node = root2;
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next;
	}
	
	printf("\n\nlooking for intersection\n");
	printf("%d\n", *(int *)SLLFindIntersection(root, root2)->data);
	
<<<<<<< HEAD
	printf("\nremoving intersection\n");
	node = root2;
	for(i = 0; i < 4; i++)
=======
	printf("\nFor each test. . . \t");
	
	if (!SLLForEach(root, (sll_foreach_action)ForEachAdd10, (void *)&incrementor))
>>>>>>> de2cc824853fa2d6539a60525d791a7b25d80bee
	{
		node = node->next;
	}
	node->next = NULL;
	
	node = root2;
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->data);
		node = node->next;
	}
	
	printf("\n\nfreeing memory\n");
	
	SLLFreeAll(root2);
	SLLFreeAll(root);

	return 0;
}

int AddNum(void *data, void *num)
{
	*(int *)data += *(int *)num;
	return 0;
}

int FindNum(const void *data, void *num)
{
	if(*(int *)data == *(int *)num)
	{
		return 1;
	}
	return 0;
}



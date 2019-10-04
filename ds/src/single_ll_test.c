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
	
	for(i = 0; i < 10; i++)
	{
		a[i] = i;
	}
	
	for(i = 0; i < 5; i++)
	{
		a2[i] = i;
	}

	printf("printing values\n");	
	for(i = 0; i < 10; i++)
	{
		root = SLLCreateNode(&a[i], root);
	}
	
	node = root;
	
	while(NULL != node)
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

	printf("\n\nremoving second's next node\n");
	node = root->next;
	SLLRemoveAfter(node);
	node = root;
	
	while(NULL != node)
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
	
	printf("\nremoving intersection\n");
	node = root2;
	for(i = 0; i < 4; i++)
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



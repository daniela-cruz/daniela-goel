#include <stdio.h>  /* printf */ 
#include <stdlib.h> /* malloc */

#include "single_ll.h"

int AddNum(void *item, void *num);
int FindNum(const void *item, void *num);

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
		printf("%d, ", *(int *)node->item);
		node = node->next_node;
	}	
	
	printf("\n");
	
	node = root->next_node;
	
	printf("\nremoving second node\n");
	SLLRemove(node);
	
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->item);
		node = node->next_node;
	}
	printf("\nnodes in linked list: %ld\n", SLLCount(root));

	printf("\n\nremoving second's next_node node\n");
	node = root->next_node;
	SLLRemoveAfter(node);
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->item);
		node = node->next_node;
	}
	printf("\nnodes in linked list: %ld\n\n", SLLCount(root));
	
	printf("inserting node to third node\n");
	node = SLLCreateNode(&b, NULL);
	temp = (root->next_node)->next_node;
	SLLInsert(temp, node);
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->item);
		node = node->next_node;
	}
	printf("\nnodes in linked list: %ld\n", SLLCount(root));
	
	printf("\ninserting node to third' next_node node\n");
	node = SLLCreateNode(&c, NULL);
	temp = (root->next_node)->next_node;
	SLLInsertAfter(temp, node);
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->item);
		node = node->next_node;
	}
	printf("\nnodes in linked list: %ld\n", SLLCount(root));
	
	printf("\nis there a loop: %d\n", SLLHasLoop(root));
	printf("forcing loop\n");
	temp = root->next_node;
	node = root;
	
	while(NULL != node->next_node)
	{
		node = node->next_node;
	}
	node->next_node = temp;
	printf("is there a loop: %d\n", SLLHasLoop(root));
	node->next_node = NULL;
	
	printf("\nadding 4 to every member in linked list\n");
	if (!SLLForEach(root, &AddNum, &foreach_param))
	{
		node = root;
		
		while (NULL != node)
		{
			printf("%d, ", *(int *)node->item);
			node = node->next_node;
		}
		printf("\n");
	}
	else
	{
		printf("\nForEAch failed!\n");
	}
	
	printf("\nlooking for node that contains 34\n");
	/*printf("%d\n", *(int *)SLLFind(root, &FindNum, &find_param)->item);*/
	node = SLLFind(root, &FindNum, &find_param)->item;
	printf("\nPointer found: %p\n", (void *)node);
	
	printf("\nflipping list\n");
	SLLFlip(root);
	node = root;
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->item);
		node = node->next_node;
	}
	
	printf("\n\ncreating new linked list\n");	
	for(i = 0; i < 5; i++)
	{
		root2 = SLLCreateNode(&a2[i], root2);
	}
	
	node = root2;
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->item);
		node = node->next_node;
	}
	
	node = root2;
	while(NULL != node->next_node)
	{
		node = node->next_node;
	}
	printf("\n\nforcing intersection at last node\n");
	node->next_node = root->next_node;
	
	node = root2;
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->item);
		node = node->next_node;
	}
	
	printf("\n\nlooking for intersection\n");
	printf("%d\n", *(int *)SLLFindIntersection(root, root2)->item);
	
	printf("\nremoving intersection\n");
	node = root2;
	for(i = 0; i < 4; i++)
	{
		node = node->next_node;
	}
	node->next_node = NULL;
	
	node = root2;
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->item);
		node = node->next_node;
	}
	
	printf("\n\nfreeing memory\n");
	
	SLLFreeAll(root2);
	SLLFreeAll(root);

	return 0;
}

int AddNum(void *item, void *num)
{
	*(int *)item += *(int *)num;
	return 0;
}

int FindNum(const void *item, void *num)
{
	if(*(int *)item == *(int *)num)
	{
		return 1;
	}
	return 0;
}

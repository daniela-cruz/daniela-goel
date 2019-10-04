#include <stdio.h> /* printf */
#include "single_ll.h"


int main()
{
	int a[10] = {0};
	int b = 20;
	int c = 30;
	int d[6] = {11, 13, 17, 19, 23, 29};
	int foreach_param = 4;
	int foreach_param2 = -4;
	int find_param = 34;
	int find_param2 = 30;
	int i = 0;
	sll_node_t *root = NULL;
	sll_node_t *node = NULL;
	sll_node_t *temp = NULL;
	sll_node_t *target = NULL;

	
	/***********************************************/
	for(i = 0; i < 10; i++)
	{
		a[i] = i;
	}
	
	/* creating a list from NULL to root */
	printf("printing values\n");	
	for(i = 0; i < 10; i++)
	{
		root = SLLCreateNode(&a[i], root);
	}

	/* printing item from root to NULL */
	for (node = root; NULL != node; node = node->next_node)
	{
		printf("%d, ", *(int *)node->item);
	}	
	
	printf("\n");
	
	
	/***********************************************/
	

	printf("\nnodes in linked list: %ld\n\n", SLLCount(root));

	
	printf("\ninserting node to third node\n");
	
	node = SLLCreateNode(&b, NULL);
	target = (root->next_node)->next_node;
	
	SLLInsert(target, node);
	
	for(node = root; NULL != node; node = node->next_node)
	{
		printf("%d, ", *(int *)node->item);
	}

	printf("\nnodes in linked list: %ld\n", SLLCount(root));

	printf("\ninserting node to third' next_node node\n");
	node = SLLCreateNode(&c, NULL);
	target = (root->next_node)->next_node;
	SLLInsertAfter(target, node);
	node = root;
	
	while(NULL != node)
	{
		printf("%d, ", *(int *)node->item);
		node = node->next_node;
	}
	
	printf("\nnodes in linked list: %ld\n", SLLCount(root));
	
	/***********************************************/
	
	/***********************************************/
	
	SLLFreeAll(root);

	
	return 0;
} 





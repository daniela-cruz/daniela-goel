#include <stddef.h> /*size_t */
#include <stdio.h>  /* printf */

#include "sll.h"

/* data struct for testing*/
typedef struct 
{
	int id;
	float age;
} person_t;

/* Declarations of Functions for Test */
void PrintAllNodes(sll_node_t *root);
int AddAge(void *data,  void *param);
int FindID(const void *data,  void *param);


int main()
{
	sll_node_t* node_1 = NULL;
	sll_node_t* node_2 = NULL;
	sll_node_t* node_3 = NULL;
	sll_node_t* node_4 = NULL;
	sll_node_t* node_5 = NULL;
	sll_node_t* node_6 = NULL;
	sll_node_t* node_2_1 = NULL;
	sll_node_t* node_2_2 = NULL;
	sll_node_t*	node_2_3 = NULL;
	sll_node_t* temp_node =  NULL;

	person_t person1 = {1, 0.1};
	person_t person2 = {2, 0.2};
	person_t person3 = {3, 0.3};
	person_t person4 = {4, 0.4};
	person_t person5 = {5, 0.5};
	person_t person6 = {6, 0.6};

	float age_to_add = 1.0;
	int id_to_find = 4;

/*################################# Create ###################################*/
	node_4 = SLLCreateNode(&person4,NULL);
	node_3 = SLLCreateNode(&person3,node_4);
	node_2 = SLLCreateNode(&person2,node_3);
	node_1 = SLLCreateNode(&person1,node_2);
	node_5 = SLLCreateNode(&person5,NULL);
	node_6 = SLLCreateNode(&person6,NULL);


/*################################## Count ###################################*/
	printf("number of elements: %ld\n", SLLCount(node_1));
	printf("next after node_1 %d\n", (((person_t*)node_1->next->data)->id));
	

/*################################## Remove ##################################*/
	printf("next after node_2 %d\n", (((person_t*)node_2->next->data)->id));
	SLLRemove(node_3);
	printf("\n****Remove****\nnext after node_2 %d\n", (((person_t*)node_2->next->data)->id));
	

/*############################### RemoveAfter ################################*/
	SLLRemoveAfter(node_1);
	printf("\n****RemoveAfter****\nnext after node_1 %d\n", (((person_t*)node_1->next->data)->id));
	printf("number of elements: %ld\n", SLLCount(node_1));
	

/*############################### InsertAfter ################################*/
	printf("\n****InsertAfter****\nBefore:\n");
	PrintAllNodes(node_1);
	SLLInsertAfter(node_3, node_6);
	printf("After:\n");
	PrintAllNodes(node_1);
	printf("number of elements: %ld\n", SLLCount(node_1));
	

/*################################## Insert ##################################*/
	printf("\n****Insert****\nBefore:\n");
	PrintAllNodes(node_1);
	SLLInsert(node_6, node_5);
	printf("After:\n");
	PrintAllNodes(node_1);
	printf("number of elements: %ld\n", SLLCount(node_1));


/*################################# ForEach ##################################*/
	printf("\n****ForEach****\nBefore:\n");
	PrintAllNodes(node_1);
	SLLForEach(node_1, &AddAge, &age_to_add);
	printf("After (values should be +=1):\n");
	PrintAllNodes(node_1);


/*################################### Find ###################################*/
	printf("\n****Find****\nis find = %p\nnode_3 address = %p\n",
		(void*)SLLFind(node_1, &FindID, &id_to_find), (void*)node_3);


/*################################## HasLoop #################################*/
	printf("\n****HasLoop****\ntest 0: no loop = %d\n", SLLHasLoop(node_1));
	temp_node = node_1->next; /* for returning the list to normal state after HasLoop test*/
	node_1->next = node_1;
	printf("test 1: loop node1->node1 = %d\n", SLLHasLoop(node_1));
	node_1->next = temp_node;

	temp_node = node_6->next; /* for returning the list to normal state after HasLoop test*/
	node_6->next = node_1;
	printf("test 2: loop node6->node1 = %d\n", SLLHasLoop(node_1));
	node_6->next = temp_node;

/*################################### Flip ###################################*/
	printf("\n****Flip****\nBefore:\n");
	PrintAllNodes(node_1);
	node_1 = SLLFlip(node_1);
	printf("After:\n");
	PrintAllNodes(node_1);

	SLLFreeAll(node_1);

/*############################# FindIntersection #############################*/
	node_4 = SLLCreateNode(&person4,NULL);
	node_3 = SLLCreateNode(&person3,node_4);
	node_2 = SLLCreateNode(&person2,node_3);
	node_1 = SLLCreateNode(&person1,node_2);

	node_2_3 = SLLCreateNode(&person3,node_3);
	node_2_2 = SLLCreateNode(&person2,node_2_3);
	node_2_1 = SLLCreateNode(&person1,node_2_2);


	printf("\n****FindIntersection****\n");
	printf("test 1: intersection (node 3) = %p <--> node_3 address = %p\n",
			(void*)SLLFindIntersection(node_1, node_2_1), (void*)node_3);

	printf("test 2: intersection reversed input = %p <--> node_3 address = %p\n",
			(void*)SLLFindIntersection(node_2_1, node_1), (void*)node_3);

	node_2_3->next = node_2;
	printf("test 3: intersection (node 2) = %p <--> node_2 address = %p\n",
			(void*)SLLFindIntersection(node_1, node_2_1), (void*)node_2);

/*################################## FreeAll #################################*/
	SLLFreeAll(node_1);
	node_1 = NULL;

	node_2_3->next = NULL; /* for testing */
	SLLFreeAll(node_2_1);
	node_2_1 = NULL;

	return 0;
}


/* Functions for Test */
void PrintAllNodes(sll_node_t *root)
{
	for (; NULL != root; root = root->next)
	{
		printf("id = %d \tage = %.1f\n", (((person_t*)root->data)->id),
			   (((person_t*)root->data)->age));
	}
}



int AddAge(void *data,  void *param)
{
	int is_success = 0;

	((person_t*)data)->age += *(float*)param;

	return is_success;
}



int FindID(const void *data,  void *param)
{
	return (((person_t*)data)->id == *(int*)param) ? 1 : 0;
}









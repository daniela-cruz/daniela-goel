#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "pq.h" /* pq_t and all functions below */

int IsBefore(void *node1, void *node2, void *param);

void CreatePriority();

int main()
{
	CreatePriority();
	
	return 0;
}

void CreatePriority()
{
	int num = 1;
	pq_t *q = NULL;
	
	printf("\nCreate test: \n");
	q = PQCreate(IsBefore, &num);
	(NULL != q) ? printf("New queue was created\n") : printf("FAILURE! Could not create new queue\n");
	
	printf("Insert test: \n");
	
	PQDestroy(q);
}

int IsBefore(void *node1, void *node2, void *param)
{
	return node1 < node2;
}


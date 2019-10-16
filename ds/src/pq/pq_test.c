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
	int num = 1, num2 = 2, num3 = 3;
	pq_t *q = NULL;
	
	printf("\nCreate test: \n");
	q = PQCreate(IsBefore, &num);
	(NULL != q) ? printf("New queue was created\n") : printf("FAILURE! Could not create queue\n");
	(1 == PQIsEmpty(q)) ? printf("SUCCESS! Queue is empty\n") : printf("Failure. Queue is not empty\n");
	
	printf("Insert test: \t\t");
	(1 == PQEnqueue(q, &num)) ? printf("Task successfully enqueued\n") : printf("Failed\n");
	(0 == PQIsEmpty(q)) ? printf("SUCCESS! Queue is not empty\n") : printf("Failure. Queue is empty\n");
	
	printf("Insert test: \t\t");
	(1 == PQEnqueue(q, &num2)) ? printf("Task successfully enqueued\n") : printf("Failed\n");
	
	printf("Insert test: \t\t");
	(1 == PQEnqueue(q, &num3)) ? printf("Task successfully enqueued\n") : printf("Failed\n");
	
	PQDestroy(q);
}

int IsBefore(void *node1, void *node2, void *param)
{
	return node1 < node2;
}


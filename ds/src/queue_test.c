#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "queue.h" /* q_node-t */

int main()
{
	int num = 123, num2 = 456, num3 = 789;
	int n = 321, n2 = 654, n3 = 987;
	void *ptr = NULL;
	queue_t *q1 = NULL, *q2 = NULL, *q1_cpy = NULL;
	
	/**********************CREATE TEST*************************/
	printf("\nCreate test. . .\t");
	q1 = QueueCreate();
	q2 = QueueCreate();
	(q1) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	(q2) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	
	/**********************ENQUEUE TEST**********************/
	printf("\nEnqueue test. . .\t");
	(SUCCESS == QueueEnqueue(q1, (void *)&num)) ? printf("SUCCESS!\t") : printf("FAILURE!\t");
	(SUCCESS == QueueEnqueue(q1, (void *)&num2)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	(SUCCESS == QueueEnqueue(q1, (void *)&num3)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	(SUCCESS == QueueEnqueue(q2, (void *)&n)) ? printf("SUCCESS!\t") : printf("FAILURE!\t");
	(SUCCESS == QueueEnqueue(q2, (void *)&n2)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	(SUCCESS == QueueEnqueue(q2, (void *)&n3)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	
	/**********************ISEMPTY TEST**********************/
	printf("\nIsEmpty test. . .\n");
	printf("Empty = 1, non empty = 0 -- is empty? %d\n", QueueIsEmpty(q1));
	printf("Empty = 1, non empty = 0 -- is empty? %d\n", QueueIsEmpty(q2));
	
	/************************MID CHECK***************************/
	printf("\nPeek test. . .\n");
	ptr = q1->front->next->data;
	printf("Element is: %d\n", n);
	
	/**********************DEQUEUE TEST**********************/
	printf("\nDequeue test. . .\t");
	/*q1_cpy = q1->back.next;
	(q1_cpy = QueueDequeue(q1)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	*/
	/**********************PEEK TEST**********************/
	printf("\nPeek test. . .\n");
	printf("Element is: %d\n", *(int *)QueuePeek(q1));
	
	
	
	return 0;
}


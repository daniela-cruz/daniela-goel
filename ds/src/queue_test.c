#include <stdio.h> /* printf */

#include "q1.h" /* all below */

int main()
{
	queue_t *q1 = NULL, *q2 = NULL;
	int *num_ptr = NULL;
	int size = 3;
	int arr[] = {0, 0, 0}, arr2[] = {0, 0, 0};
	int i = 0;
	
	/****************CREATE TEST********************/
	printf("\nCreate test. . . \t");
	((q1 = QueueCreate()) && (q2 = QueueCreate()) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	
	printf("creating q1\n\n");
	for (i = 0; i < size; i++)
	{
		arr[i] = i + 1;
		arr2[i] = i + 4;
	}
	
	/****************ENQUEUE TEST********************/
	printf("\nEnqueue test. . .\n");
	
	for (i = 0; i < size; i++)
	{
		QueueEnqueue(q1, &arr[i]);
	}
	printf("is list empty: %d\n", QueueIsEmpty(q1));
	printf("items in q1: %lu\n", QueueCount(q1));
	
	num_ptr = QueueDequeue(q1);
	printf("\ndequeue: %d\n", *num_ptr);
	printf("items in q1: %lu\n", QueueCount(q1));
	
	num_ptr = QueueDequeue(q1);
	printf("\ndequeue: %d\n", *num_ptr);
	printf("items in q1: %lu\n", QueueCount(q1));
	
	num_ptr = QueuePeek(q1);
	printf("\npeek: %d\n", *num_ptr);
	printf("items in q1: %lu\n", QueueCount(q1));
	
	printf("\ncreating another q1\n");
	for(i = 0; i < 3; i++)
	{
		printf("enqueue to second q1: %d\n", arr2[i]);
		QueueEnqueue(q2, &arr2[i]);
	}
	
	printf("\nappending queues\n");
	QueueAppend(q1, q2);
	printf("items in q1: %lu\n\n", QueueCount(q1));
	
	for(i = 0; i < 4; i++)
	{
		num_ptr = QueueDequeue(q1);
		printf("dequeue: %d\n", *num_ptr);
	}
	printf("is list empty: %d\n", QueueIsEmpty(q1));
	
	printf("\ndestroying queues\n");
	QueueDestroy(q1);
	QueueDestroy(q2);
	
	return 0;
}


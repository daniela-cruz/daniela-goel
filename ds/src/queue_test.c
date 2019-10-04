#include <stdio.h> /* printf */

#include "queue.h" /* all below */

int main()
{
	queue_t *q1 = NULL, *q2 = NULL;
	int size = 3;
	int arr[] = {0, 0, 0}, arr2[] = {0, 0, 0};
	int i = 0;
	
	/****************CREATE TEST********************/
	printf("\nCreate test. . . \t");
	((q1 = QueueCreate()) && (q2 = QueueCreate())) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	
	/* change values in q1 */
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
	
	/****************ISEMPTY TEST********************/
	printf("\nIsEmpty test. . .\t");
	(!QueueIsEmpty(q1)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");	
	
	/****************ISEMPTY TEST********************/
	printf("\nCount test. . .\t\t");	
	(3 == QueueCount(q1)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	
	/****************DEQUEUE TEST********************/
	printf("\nDequeue test. . .\t");	
	q1 = QueueDequeue(q1);
	(2 == QueueCount(q1)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	q1 = QueueDequeue(q1);
	
	/****************PEEK TEST********************/
	printf("\nPeek test. . .\t\t");	
	(3 == *(int *)QueuePeek(q1)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	printf("items in q1: %lu\n", QueueCount(q1));
	
	/****************APPEND TEST********************/
	printf("\nAppend test. . .\t");	
	
	/* changing values in q2 */
	for (i = 0; i < 3; i++)
	{
		QueueEnqueue(q2, &arr2[i]);
	}
	
	q1 = QueueAppend(q1, q2);
	(4 == QueueCount(q1)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	size = QueueCount(q1);
	
	/****************Destroy TEST********************/
	printf("\nDestroy test. . . check with vlg\n");
	for (i = 0; i < size; i++)
	{
		q1 = QueueDequeue(q1);
	}
	
	QueueDestroy(q1);
	QueueDestroy(q2);
	
	return 0;
}


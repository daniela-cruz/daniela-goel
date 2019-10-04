#include <stdio.h> /* printf */

#include "queue.h" /* all below */

static queue_t *q1 = NULL, *q2 = NULL;
static const int arr_size = 3;
static int arr[] = {0, 0, 0}, arr2[] = {0, 0, 0};
static int i = 0;
	
static void CreateTest() 
{
	printf("\nCreate test. . . \t");
	((q1 = QueueCreate()) && (q2 = QueueCreate())) ? printf("SUCCESS!\n") : printf("FAILURE!\n");

	/* change values in q1 */
	for (i = 0; i < arr_size; i++)
	{
		arr[i] = i + 1;
		arr2[i] = i + 4;
	}
}

static void EnqueueTest() 
{
	printf("\nEnqueue test. . .\n");
	
	for (i = 0; i < arr_size; i++)
	{
		QueueEnqueue(q1, &arr[i]);
	}
}

static void IsEmptyTest() 
{
	printf("\nIsEmpty test. . .\t");
	(!QueueIsEmpty(q1)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");	
}
static void CountTest() 
{
	printf("\nCount test. . .\t\t");	
	(3 == QueueCount(q1)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
}

static void DequeueTest() 
{
	printf("\nDequeue test. . .\t");	
	q1 = QueueDequeue(q1);
	(2 == QueueCount(q1)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	q1 = QueueDequeue(q1);
}

static void PeekTest() 
{
	printf("\nPeek test. . .\t\t");	
	(3 == *(int *)QueuePeek(q1)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
	printf("items in q1: %lu\n", QueueCount(q1));
}

static void AppendTest() 
{
	size_t q_length = 0;
	printf("\nAppend test. . .\t");	
	
	/* changing values in q2 */
	for (i = 0; i < arr_size; i++)
	{
		QueueEnqueue(q2, &arr2[i]);
	}
	
	q_length = QueueCount(q1) + QueueCount(q2);
	q1 = QueueAppend(q1, q2);
	(q_length == QueueCount(q1)) ? printf("SUCCESS!\n") : printf("FAILURE!\n");
}

static void RefillTest1() 
{
	size_t q_length = 0;
	
	printf("\nRefill test. . .\n");
	printf("Count test before dequeue I: %d\n", QueueCount(q1));
	q_length = QueueCount(q1);
	
	for (i = 0; i < q_length; i++)
	{
		q1 = QueueDequeue(q1);
	}

	printf("Count test after dequeue I: %d\n", QueueCount(q1));
	
	for (i = 0; i < arr_size; i++)
	{
		QueueEnqueue(q1, &arr[i]);
	}
	
	printf("Count test after refill: %d\n", QueueCount(q1));
}

static void RefillTest2() 
{
	size_t q_length = 0;
	
	printf("\nRefill II test. . .\n");
	
	q_length = QueueCount(q1);
	
	for (i = 0; i < q_length; i++)
	{
		q1 = QueueDequeue(q1);
	}
	
	printf("Count test after dequeue II: %d\n", QueueCount(q1));
	
	for (i = 0; i < arr_size; i++)
	{
		QueueEnqueue(q1, &arr[i]);
	}
	printf("Count test after refill II: %d\n", QueueCount(q1));
	q_length = QueueCount(q1);
	
	printf("\nContent test. . .\n");
	for (i = 0; i < q_length; i++)
	{
		printf("%d\n", *(int*)QueuePeek(q1));
		q1 = QueueDequeue(q1);
	}
	
	printf("Count test after last dequeue: %d\n", QueueCount(q1));
	
}

int main()
{	
	CreateTest();
	
	EnqueueTest();
	
	IsEmptyTest();
	
	CountTest();
	
	DequeueTest();
	
	AppendTest();

	RefillTest1();
/*
	RefillTest2();
*/
	/****************Destroy TEST********************/
	printf("\nDestroy test. . . check with vlg\n");
	QueueDestroy(q1);
	QueueDestroy(q2);
	
	return 0;
}


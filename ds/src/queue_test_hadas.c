#include <stdio.h>  /* printf */

#include "queue.h" 

typedef struct student
{
	char *name;
	int id;
}student_t;

int main()
{
	queue_t *my_q = QueueCreate();
	queue_t *new_q = QueueCreate();
	
	student_t a = {"Hadas", 23435};
	student_t b = {"Gabriel", 33333};
	student_t c = {"Daniela", 12677};
	student_t *test =NULL;
	
	printf("testing Enqueue:\n");
	QueueEnqueue(my_q, &a);
	QueueEnqueue(my_q, &b);
	if (QueueCount(my_q) == 2)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}

	printf("\n testing peek\n");
	test = QueuePeek(my_q);
	printf("the first in line : name = %s  id= %d \n", test->name,test->id);
	
	printf("\n testing append\n");
	QueueEnqueue(new_q, &c);
	QueueAppend(my_q, new_q);
	
	if(QueueCount(my_q) == 3)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}
	
	printf("\n testing Dequeue\n");
	printf("printing the values\n");
	test = QueueDequeue(my_q);
	printf("the first out : name = %s  id= %d \n", test->name,test->id);

	test = QueueDequeue(my_q);
	printf("the secound out : name = %s  id= %d \n", test->name,test->id);

	test = QueueDequeue(my_q);
	printf("the third out : name = %s  id= %d \n", test->name,test->id);
	
	printf("\ntesting count\n");
	if(QueueCount(my_q) == 0)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}
	
	QueueEnqueue(my_q, &c);
	if(QueueCount(my_q) == 1)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}
	
	printf("\ntesting IsEmpty\n");
	if(QueueIsEmpty(my_q) == 0)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}
	
	QueueDequeue(my_q);
	if(QueueIsEmpty(my_q) == 1)
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");
	}
	

	QueueDestroy(my_q);
	QueueDestroy(new_q);
	
	return 0;
}


#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <string.h> /* strlen */

#include "vector.h" /* vector_t */

static void VectorCreateTest();
static vector_t *PushTest(vector_t *ptr, int *new_data);

int main()
{
	/*VectorCreateTest();*/
	
	vector_t *vector = VectorCreate(4,15);
	int a = 20;
	int *p = NULL;
	int i = 0;
	
	printf("\nvector SIZE test: %ld\n", VectorSize(vector));
	printf("\nvector CAPACITY test: %ld\n", VectorCapacity(vector));
	
	for(i = 0; i < 10; i++)
	{
		p = VectorGetItemAddress(vector, i);
		*p = i + 1;
	}
	printf("\n");
	
	printf("push 20\n\n");
	VectorPushBack(vector, &a);
	
	printf("\nvector SIZE test: %ld\n", VectorSize(vector));
	printf("\nvector CAPACITY test: %ld\n", VectorCapacity(vector));
	
	for(i = 0; i < 10; i++)
	{
		p = VectorGetItemAddress(vector, i);
		printf("item value: %d\n", *p);
	}
	printf("\n");
	
	printf("pop\n");
	VectorPopBack(vector);
	
	printf("\nvector SIZE test: %ld\n", VectorSize(vector));
	printf("\nvector CAPACITY test: %ld\n", VectorCapacity(vector));
	
	printf("\n");
	
	printf("push 20\n\n");
	VectorPushBack(vector, &a);
	
	printf("vector size: %ld\n", VectorSize(vector));
	printf("vector capacity: %ld\n\n", VectorCapacity(vector));
	/*
	p = VectorGetItemAddress(vector, 16);
	
	printf("last item inserted by push value: %d\n\n", *p);
*/
	printf("vector size: %ld\n", VectorSize(vector));
	printf("vector capacity: %ld\n\n", VectorCapacity(vector));
	
	VectorReserve(vector, 1);
	printf("reserved 1 memory\n\n");
	
	printf("vector size: %ld\n", VectorSize(vector));
	printf("vector capacity: %ld\n\n", VectorCapacity(vector));
	
	VectorReserve(vector, 100);
	printf("reserved 100 slot\n\n");
	
	printf("vector size: %ld\n", VectorSize(vector));
	printf("vector capacity: %ld\n", VectorCapacity(vector));
	
	VectorDestroy(vector);
	
	return 0;
}

static void VectorCreateTest()
{
	vector_t *vector_ptr = NULL;
	size_t ele_size = sizeof(int), size = 3;
	int data_int = 123;
	int *retreived_data = NULL;
	
	vector_ptr = VectorCreate(ele_size, size);
	
	printf("\nCreate test. . . \n");
	
	if (vector_ptr)
	{
		printf("SUCCESS! A pointer was allocated.\n");
	}
	else
	{
		printf("Failure! Pointer was not allocaed\n");
	}
	
	PushTest(vector_ptr, &data_int);
	
	retreived_data = (int *)VectorGetItemAddress(vector_ptr, 0);
	*retreived_data = 123; 
	printf("\nGet item test: %d\n", *retreived_data);
	
	PushTest(vector_ptr, &data_int);
	
	retreived_data = (int *)VectorGetItemAddress(vector_ptr, 1);
	printf("\nGet item test: %d\n", *retreived_data);
	
	PushTest(vector_ptr, &data_int);
	
	printf("\nArray size: %ld\n", VectorSize(vector_ptr));
	printf("\nCapacity is: %ld\n", VectorCapacity(vector_ptr));
	
	retreived_data = (int *)VectorGetItemAddress(vector_ptr, 0);
	printf("\nGet item test: %d\n", *retreived_data);
	
	
	PushTest(vector_ptr, &data_int);
	printf("\nArray size: %ld\n", VectorSize(vector_ptr));
	
	printf("\nCapacity is: %ld\n", VectorCapacity(vector_ptr));
	
	retreived_data = (int *)VectorGetItemAddress(vector_ptr, 0);
	printf("\nGet item test: %d\n", *retreived_data);
	
	PushTest(vector_ptr, &data_int);
	
	retreived_data = (int *)VectorGetItemAddress(vector_ptr, 0);
	printf("\nGet item test: %d\n", *retreived_data);
	
	printf("\nPop test. . . \n");
	data_int = VectorPopBack(vector_ptr);
	
	if (!data_int)
	{
		printf("SUCCESS! Pop succeeded.\n");
	}
	else
	{
		printf("Failure! Push failed\n");
	}
	
	printf("\nDestroy test. . . \n");
	VectorDestroy(vector_ptr);
	
	if (NULL == vector_ptr)
	{
		printf("SUCCESS! The pointer was freed.\n");
	}
	else
	{
		printf("Failure! Pointer was not freed\n");
	}
}

static vector_t *PushTest(vector_t *ptr, int *new_data)
{
	printf("\nPush to vector test. . . \n");
	
	if (!VectorPushBack(ptr, new_data))
	{
		printf("SUCCESS! New data was pushed.\n");
	}
	else
	{
		printf("Failure! Could not push data\n");
	}
	
	return ptr;
}

#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <string.h> /* strlen */

#include "vector.h" /* vector_t */

static void VectorCreateTest();
static vector_t *PushTest(vector_t *ptr, int *new_data);

int main()
{
	VectorCreateTest();
	
	return 0;
}

static void VectorCreateTest()
{
	vector_t *vector_ptr = NULL;
	size_t ele_size = sizeof(int), size = 3;
	int data_int = 123, retreived_data = 0;
	
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
	
	retreived_data = *(int *)VectorGetItemAddress(vector_ptr, 1);
	printf("\nGet item test: %d\n", retreived_data);
	
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

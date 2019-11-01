#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "vsa.h"

typedef struct 
{
	char *name;
	char *last_name;
	int age;
}person_t;

static void InitTest();
static void AllocateTest();

int main()
{
	/*InitTest();*/
	AllocateTest();
	return 0;
}

static void InitTest()
{
	void *buffer = NULL;
	size_t buff_size = 67;
	vsa_t *vsa = NULL;
	
	printf("\nInit Test:\t");
	buffer = malloc(buff_size);
	vsa = VSAInit(buffer, buff_size);
	(NULL != vsa) ? printf("Initiated vsa successfully\n") : printf("Could not initiate buffer\n");
	(56 == VSAMaxFreeBlock(vsa)) ? printf("Correct buffer size\n") : printf("ERROR: buffer size is: %ld\n", VSAMaxFreeBlock(vsa));
}

static void AllocateTest()
{
	void *buffer = NULL;
	size_t buff_size = 72;
	vsa_t *vsa = NULL;
	person_t *michal = NULL;
	person_t *sigal = NULL;
	int num1 = 1, num2 = 2;
	int *num_container = NULL, *num_container2 = NULL;
	
	printf("\nAllocate Test:\t");
	buffer = malloc(buff_size);
	vsa = VSAInit(buffer, buff_size);
	printf("Get max: %ld\n\n", VSAMaxFreeBlock(vsa));
	
	michal = VSAAlloc(vsa, sizeof(person_t));
	(NULL != michal) ? printf("Allocated Michal successfully\n") : printf("Could not allocate Michal\n");
	printf("Get max: %ld\n\n", VSAMaxFreeBlock(vsa));
	
	num_container = VSAAlloc(vsa, sizeof(*num_container));
	(NULL != num_container) ? printf("Allocated num_container successfully\n") : printf("Could not allocate num_container\n");
	printf("Get max: %ld\n\n", VSAMaxFreeBlock(vsa));
	
	sigal = VSAAlloc(vsa, sizeof(person_t));
	(NULL != sigal) ? printf("Allocated sigal successfully\n") : printf("Could not allocate sigal\n");
	
	printf("\nFreeing num_container\n");
	VSAFree(num_container);
	printf("Get max: %ld\n\n", VSAMaxFreeBlock(vsa));
	
	sigal = VSAAlloc(vsa, sizeof(person_t));
	(NULL != sigal) ? printf("Allocated sigal successfully\n") : printf("Could not allocate sigal\n");
	printf("Get max: %ld\n\n", VSAMaxFreeBlock(vsa));
	
	/*num_container = VSAAlloc(vsa, sizeof(*num_container));
	(NULL != num_container) ? printf("Allocated num_container successfully\n") : printf("Could not allocate num_container\n");
	printf("Get max: %ld\n\n", VSAMaxFreeBlock(vsa));*/
	
	num_container2 = VSAAlloc(vsa, sizeof(*num_container));
	(NULL != num_container) ? printf("Allocated num_container2 successfully\n") : printf("Could not allocate num_container2\n");
	printf("Get max: %ld\n\n", VSAMaxFreeBlock(vsa));
}

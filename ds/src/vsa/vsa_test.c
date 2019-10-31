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
	size_t buff_size = 64;
	vsa_t *vsa = NULL;
	person_t *michal = NULL;
	person_t *sigal = NULL;
	
	printf("\nAllocate Test:\t");
	buffer = malloc(buff_size);
	vsa = VSAInit(buffer, buff_size);
	michal = VSAAlloc(vsa, sizeof(person_t));
	(NULL != michal) ? printf("Allocated Michal successfully\n") : printf("Could not allocate Michal\n");
	
	/*sigal = VSAAlloc(vsa, sizeof(person_t));
	(NULL != sigal) ? printf("Allocated sigal successfully\n") : printf("Could not allocate sigal\n");*/
	
	printf("\nGet max: %ld\t", VSAMaxFreeBlock(vsa));
}

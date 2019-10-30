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

int main()
{
	InitTest();
	
	return 0;
}

static void InitTest()
{
	void *buffer = NULL;
	size_t buff_size = 64;
	vsa_t *vsa = NULL;
	
	printf("\nInit Test:\t");
	buffer = malloc(buff_size);
	vsa = VSAInit(buffer, buff_size);
	(NULL != vsa) ? printf("Initiated vsa successfully\n") : printf("Could not initiate buffer\n");
	(56 == VSAMaxFreeSize(vsa)) ? printf("Correct buffer size\n") : printf("ERROR: buffer size is: %ld\n", VSAMaxFreeSize(vsa));
}

static void AllocateTest()
{
	void *buffer = NULL;
	size_t buff_size = 64;
	vsa_t *vsa = NULL;
	person_t *michal = NULL;
	
	printf("\nAllocate Test:\t");
	buffer = malloc(buff_size);
	vsa = VSAInit(buffer, buff_size);
	
}

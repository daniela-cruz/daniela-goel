#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free*/

#include "cir_buffer.h"

char *word = "hey I am the new buffer";
cir_buffer_t *new_circle = NULL;

static void CreateTest();
static void WriteTest();
static void GetFreeTest();
static void ReadTest();
static void CapacityTest();
static void IsEmptyTest();

int main()
{
	CreateTest();
	IsEmptyTest();
	WriteTest();
	IsEmptyTest();
	GetFreeTest();
	/*ReadTest();*/
	GetFreeTest();
	CapacityTest();
	IsEmptyTest();
	WriteTest();
	GetFreeTest();
	WriteTest();
	GetFreeTest();
	/*ReadTest();
	ReadTest();
	ReadTest();*/
	GetFreeTest();
	CapacityTest();
	IsEmptyTest();
	
	return 0;
}

static void CreateTest()
{
	printf("Create test. . .\t");
	new_circle = CBCreate(9);
	(NULL != new_circle) ? printf("SUCCESS!\n") : printf("Failure\n");
}

static void WriteTest()
{
	printf("Write test. . .\t\t");
	(5 == CBWrite(new_circle, word, 5)) ? printf("SUCCESS! ") : printf("Failure");
	printf("Wrote %ld more bytes.\n", CBCapacity(new_circle) - CBGetFreeSpace(new_circle));
}

static void GetFreeTest()
{
	printf("Get free test. . .\t");
	printf("Free space is: %ld\n", CBGetFreeSpace(new_circle));
}

static void ReadTest()
{
	char *read_data = malloc(10);
	printf("Read test I. . .\t");
	printf("Read: %ld more bytes\n", CBRead(new_circle, read_data, 6));
	printf("data is: %s\n", read_data);
	printf("Read test II. . .\t");
	printf("Read: %ld more bytes\n", CBRead(new_circle, read_data, 4));
	printf("data is: %s\n", read_data);
	free(read_data);
}

static void CapacityTest()
{
	printf("Capacity is: %ld\n", CBCapacity(new_circle));
}

static void IsEmptyTest()
{
	printf("Is buffer empty? %d\n", CBIsEmpty(new_circle));
}

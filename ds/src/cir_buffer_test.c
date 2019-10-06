#include <stdio.h> /* printf */

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
	GetFreeTest();
	ReadTest();
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
	(12 == CBWrite(new_circle, word, 12)) ? printf("SUCCESS!\n") : printf("Failure\n");
}

static void GetFreeTest()
{
	printf("Get free test. . .\t");
	printf("Free space is: %ld\n", CBGetFreeSpace(new_circle));
}

static void ReadTest()
{
	printf("Read test I. . .\t\t");
	(6 ==CBRead(new_circle, 6)) ? printf("SUCCESS!\n") : printf("Failure\n");
	printf("Read test II. . .\t\t");
	printf("Read: %ld more bytes\n", CBRead(new_circle, 6));
}

static void CapacityTest()
{
	printf("Capacity is: %ld\n", CBCapacity(new_circle));
}

static void IsEmptyTest()
{
	printf("Is buffer empty? %d\n", CBIsEmpty(new_circle));
}

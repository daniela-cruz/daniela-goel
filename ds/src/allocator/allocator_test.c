#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "allocator.h"

typedef struct 
{
	char *name;
	char *last_name;
	size_t age;
} person_t;

static void SuggestedTest();
static void InitTest();
static void AllocTest(fsa_t *allocator);

int main()
{
	/*SuggestedTest();*/
	InitTest();
	
	return 0;
}

static void SuggestedTest()
{
	size_t blocks_num = 10;
	size_t block_size = sizeof(void *);
	size_t suggested_size = 0;
	
	printf("\nSuggested test:\n");
	
	suggested_size = FSASuggest(blocks_num, block_size);
	
	printf("Suggested size for person struct is: %ld bytes for a buffer\n", suggested_size);
}

static void InitTest()
{
	size_t blocks_num = 7;
	size_t block_size = sizeof(char *);
	size_t suggested_size = 0;
	void *buffer = NULL;
	fsa_t *allocator = NULL;
	void *michal, *potas2, *robin3, *jupi4, *shahar5, *dani6, *potal7;
	
	printf("\nInit test:\n");
	
	suggested_size = FSASuggest(blocks_num, block_size);
	buffer = malloc(suggested_size);
	(NULL != buffer) ? printf("Allocated buffer with address of: %p\n", buffer) : 
		printf("Couldn't allocate buffer\n"); 
	
	allocator = FSAInit(buffer, suggested_size, block_size);
	(NULL != buffer) ? printf("Initialized allocator with address of: %p\n", allocator) : 
		printf("Couldn't initiate allocator\n"); 
	
	printf("Number of free blocks: %ld\n", FSACountFree(allocator));
	
	AllocTest(allocator);
		
	free(allocator);
}

static void AllocTest(fsa_t *allocator)
{
	void *michal, *potas2, *robin3, *jupi4, *shahar5, *dani6, *potal7;
	
	printf("\nAllocation test:\n");
	
	michal = FSAAlloc(allocator);
	printf("Number of free blocks: %ld\n", FSACountFree(allocator));
	(NULL != michal) ? printf("Allocated Michal with address of: %p\n", michal) : 
		printf("Couldn't allocate Michal\n");
	
	potas2 = FSAAlloc(allocator);
	(NULL != potas2) ? printf("Allocated Potas with address of: %p\n", potas2) : 
		printf("Couldn't allocate Michal\n");
	
	robin3 = FSAAlloc(allocator);
	(NULL != robin3) ? printf("Allocated Robin with address of: %p\n", robin3) : 
		printf("Couldn't allocate Michal\n");
	
	jupi4 = FSAAlloc(allocator);
	(NULL != jupi4) ? printf("Allocated Jupiter with address of: %p\n", jupi4) : 
		printf("Couldn't allocate Michal\n");
	
	shahar5 = FSAAlloc(allocator);
	(NULL != shahar5) ? printf("Allocated Shahar with address of: %p\n", shahar5) : 
		printf("Couldn't allocate Michal\n");
	
	dani6 = FSAAlloc(allocator);
	(NULL != dani6) ? printf("Allocated me with address of: %p\n", dani6) : 
		printf("Couldn't allocate Michal\n");
	
	potal7 = FSAAlloc(allocator);
	(NULL != potal7) ? printf("Allocated Potal with address of: %p\n", potal7) : 
		printf("Couldn't allocate Michal\n");
	
	printf("Number of free blocks before freeing: %ld\n", FSACountFree(allocator));
	FSAFree(michal);
	printf("Number of free blocks after freeing: %ld\n", FSACountFree(allocator));
}

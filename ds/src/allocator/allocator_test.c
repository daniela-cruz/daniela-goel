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

int main()
{
	/*SuggestedTest();*/
	InitTest();
	
	return 0;
}

static void SuggestedTest()
{
	size_t blocks_num = 10;
	size_t block_size = sizeof(person_t);
	size_t suggested_size = 0;
	
	printf("\nSuggested test:\n");
	
	suggested_size = FSASuggest(blocks_num, block_size);
	
	printf("Suggested size for person struct is: %ld bytes for a buffer\n", suggested_size);
}

static void InitTest()
{
	size_t blocks_num = 10;
	size_t block_size = sizeof(person_t);
	size_t suggested_size = 0;
	void *buffer = NULL;
	fsa_t *allocator = NULL;
	
	printf("\nInit test:\n");
	
	suggested_size = FSASuggest(blocks_num, block_size);
	buffer = malloc(suggested_size);
	(NULL != buffer) ? printf("Allocated buffer with address of: %p\n", buffer) : 
		printf("Couldn't allocate buffer\n"); 
	
	allocator = FSAInit(buffer, suggested_size, block_size);
	(NULL != buffer) ? printf("Initialized allocator with address of: %p\n", allocator) : 
		printf("Couldn't initiate allocator\n"); 
	
	printf("Number of free blocks: %ld\n", FSACountFree(allocator));
	
	free(allocator);
}

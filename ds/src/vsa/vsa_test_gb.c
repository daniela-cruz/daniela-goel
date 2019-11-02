#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

#include "vsa.h"

#define ADD_RED printf("\033[1;31m")
#define END_RED printf("\033[0m")

const size_t wordsize = sizeof(size_t);

vsa_t *VSAInitTest(void *block, size_t size, size_t expected_result_debug, size_t expected_result_release);
void VSAMaxFreeBlockTest(vsa_t *vsa, size_t expected_result);
void VSAAllocTest(vsa_t *vsa, size_t alloc_size);
void VSAFreeTest(vsa_t *vsa);
static size_t CalculateAlignedBlockSize(size_t block_size);

int main()
{
	void *pool = NULL;
	vsa_t *vsa = NULL;
	
	printf("Testing: Init stage.\n\n");

	pool = malloc(540);
	if(NULL == pool)
	{
		return 1;
	}
	printf("stage 1: \n");
	VSAInitTest(pool, 520, 480, 504);
	printf("stage 2: \n");
	VSAInitTest(pool, 535, 488, 512);	
	printf("stage 3: \n");
	vsa = VSAInitTest(pool, 523, 480, 504);
	printf("\n");
	
	
	printf("Testing: Alloc and Free stage.\n\n");
	printf("stage 1: \n");
	VSAAllocTest(vsa, 20);
	printf("stage 2: \n");
	VSAAllocTest(vsa, 2);
	printf("stage 3: \n");
	VSAAllocTest(vsa, 16);
	
	free(pool);

	return 0;
}

vsa_t *VSAInitTest(void *block, size_t size, size_t expected_result_debug, size_t expected_result_release)
{
	vsa_t *vsa = NULL;
	vsa = VSAInit(block, size);
	printf("VSAInitTest:				");
	NULL != vsa ? printf("SUCCESS\n") : (ADD_RED, printf("FAILURE\n"), END_RED);
	#ifndef NDEBUG
	(void) expected_result_release;
	VSAMaxFreeBlockTest(vsa, expected_result_debug);
	#else
	(void) expected_result_debug;
	VSAMaxFreeBlockTest(vsa, expected_result_release);
	#endif
	
	return vsa;
}

void VSAMaxFreeBlockTest(vsa_t *vsa, size_t expected_result)
{
	printf("FSACountFreeTest:			");
	expected_result == VSAMaxFreeBlock(vsa) ? printf("SUCCESS\n") : (ADD_RED, printf("FAILURE\n"), END_RED);
}

void VSAAllocTest(vsa_t *vsa, size_t alloc_size)
{
	void *block = NULL;
	void *block2 = NULL;
	size_t count = 0;

	count = VSAMaxFreeBlock(vsa);
	block = VSAAlloc(vsa, alloc_size);
	
	alloc_size = CalculateAlignedBlockSize(alloc_size);
	
	printf("VSAAllocTest:				");
	NULL != block ? printf("SUCCESS\n") : (ADD_RED, printf("FAILURE\n"), END_RED);
	
	#ifndef NDEBUG
	VSAMaxFreeBlockTest(vsa, count - alloc_size - 16);
	#else
	VSAMaxFreeBlockTest(vsa, count - alloc_size - 8);
	#endif
	
	printf("VSAFreeTest:				");
	VSAFree(block);
	VSAMaxFreeBlock(vsa) == count ? printf("SUCCESS\n") : (ADD_RED, printf("FAILURE\n"), END_RED);
	
	printf("VSAAllocTest:				");
	block = VSAAlloc(vsa, count - 8);
	VSAMaxFreeBlock(vsa) == 0 ? printf("SUCCESS\n") : (ADD_RED, printf("FAILURE\n"), END_RED);

	printf("VSAFreeTest:				");
	VSAFree(block);
	VSAMaxFreeBlock(vsa) == count ? printf("SUCCESS\n") : (ADD_RED, printf("FAILURE\n"), END_RED);
	
	printf("VSAAllocNullTest:			");
	block = VSAAlloc(vsa, count);
	VSAAlloc(vsa, 10) == NULL && VSAMaxFreeBlock(vsa) == 0 ? printf("SUCCESS\n") : (ADD_RED, printf("FAILURE\n"), END_RED);
	
	printf("VSAFreeTest:				");
	VSAFree(block);
	VSAMaxFreeBlock(vsa) == count ? printf("SUCCESS\n") : (ADD_RED, printf("FAILURE\n"), END_RED);
	
	printf("VSAAllocTest:				");
	count = VSAMaxFreeBlock(vsa);
	VSAAlloc(vsa, alloc_size);
	block = VSAAlloc(vsa, alloc_size);
	block2 = VSAAlloc(vsa, alloc_size);
	NULL != block ? printf("SUCCESS\n") : (ADD_RED, printf("FAILURE\n"), END_RED);
	
	#ifndef NDEBUG
	VSAMaxFreeBlockTest(vsa, count - (3 * (alloc_size + 16)));
	#else
	VSAMaxFreeBlockTest(vsa, count - (3 * (alloc_size + 8)));
	#endif
	
	printf("VSAFreeTest:				");
	VSAFree(block);
	printf("SUCCESS\n");
	
	#ifndef NDEBUG
	VSAMaxFreeBlockTest(vsa, count - (3 * (alloc_size + 16)));
	#else
	VSAMaxFreeBlockTest(vsa, count - (3 * (alloc_size + 8)));
	#endif
	
	VSAFree(block2);
}

static size_t CalculateAlignedBlockSize(size_t block_size)
{
	size_t alignement = 0;
	
	if(0 != block_size % wordsize)
	{
		alignement = wordsize - block_size % wordsize;
	}
	
	return block_size + alignement;
}


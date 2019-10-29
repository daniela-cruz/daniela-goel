/*OL76 fsa
developer name: Matan Albilia
reviewer: daniela
date: 29/11/19
status: sent
*/

#include <stdlib.h> /*malloc*/
#include <stdio.h>	/*printf*/
#include "allocator.h"

int TestInit();
void TestSuggest();
void TestCountFree();
int TestAlloc();
void TestFree();

int main()
{
	TestSuggest();
	TestInit();
	TestCountFree();
	TestAlloc();
	TestFree();

	return 0;
}

int TestInit()
{
	size_t nblocks = 4;
	size_t block_size = sizeof(size_t);
	size_t buff_size = 0;
	char *buff1 = NULL;
	fsa_t *fsa1 = NULL;
	fsa_t *fsa2 = NULL;
	char *curr = NULL;	
	size_t exp[] = {24, 40, 56, 1};
	size_t i = 0;
	char buff2[72] = {0};

	puts("TestInit");

	buff_size = FSASuggest(nblocks, block_size);

	buff1 = (char *)malloc(buff_size);

	if (NULL == buff1)
	{
		return 1;
	}

	/*test dynamic allocation*/
	fsa1 = FSAInit(buff1, buff_size, block_size);

	if (fsa1 == NULL)
	{
		printf("ERROR, LINE:%d\n",__LINE__);
		return 1;
	}

	/*test static allocation*/
	fsa2 = FSAInit(buff2, buff_size, block_size);

	if (fsa2 == NULL)
	{
		printf("ERROR, LINE:%d\n",__LINE__);
		return 1;
	}

	/*white box test*/

	curr = (char *)fsa2 + 8;

	while (curr < (char *)fsa2 + buff_size)
	{
		if(*(size_t *)curr != exp[i])
		{
			printf("ERROR, LINE:%d\nres = %ld,exp = %ld\n",__LINE__,*(size_t *)curr, exp[i]);
		}
		curr += 16;
		++i;
	}	

	return 0;
}

void TestSuggest()
{
	size_t nblocks = 0;
	size_t block_size = 0;
	size_t res = 0;
	size_t exp = 0;

	puts("TestSuggest");

	/*case 1 - simple case */
	nblocks = 10;
	block_size = 8;

	res = FSASuggest(nblocks, block_size);
	exp = 168;

	if (res != exp)
	{
		printf("ERROR, LINE:%d\nres = %ld,exp = %ld\n",__LINE__,res, exp);
	}

	/*case 2 - block size not WORD aligned*/

	nblocks = 10;
	block_size = 6;
	res = FSASuggest(nblocks, block_size);
	exp = 168;

	if (res != exp)
	{
		printf("ERROR, LINE:%d\nres = %ld,exp = %ld\n",__LINE__,res, exp);
	}

	/*case 3 - 1 block , block_size word_aligned*/

	nblocks = 1;
	block_size = 16;
	res = FSASuggest(nblocks, block_size);
	exp = 32;

	if (res != exp)
	{
		printf("ERROR, LINE:%d\nres = %ld,exp = %ld\n",__LINE__,res, exp);
	}

	/*case 4 - 1 block , block_size not word_aligned*/

	nblocks = 1;
	block_size = 7;
	res = FSASuggest(nblocks, block_size);
	exp = 24;

	if (res != exp)
	{
		printf("ERROR, LINE:%d\nres = %ld,exp = %ld\n",__LINE__,res, exp);
	}
}

void TestCountFree()
{
	size_t block_size1 = sizeof(size_t);
	fsa_t *fsa1 = NULL;
	size_t buff_size1 = 72;
	char buff1[72] = {0};
	void *alloc = NULL;

	size_t res = 0;
	size_t exp = 0;

	puts("TestCountFree");

	fsa1 = FSAInit(buff1, buff_size1, block_size1);

	res = FSACountFree(fsa1);
	exp = 4;

	if (res != exp)
	{
		printf("ERROR, LINE:%d\nres = %ld,exp = %ld\n",__LINE__,res, exp);
	}

	alloc = FSAAlloc(fsa1);
	res = FSACountFree(fsa1);

	exp = 3;

	if (res != exp)
	{
		printf("ERROR, LINE:%d\nres = %ld,exp = %ld\n",__LINE__,res, exp);
	}

	alloc = FSAAlloc(fsa1);
	alloc = FSAAlloc(fsa1);
	alloc = FSAAlloc(fsa1);

	res = FSACountFree(fsa1);
	exp = 0;

	if (res != exp)
	{
		printf("ERROR, LINE:%d\nres = %ld,exp = %ld\n",__LINE__,res, exp);
	}

	(void)alloc;
}

int TestAlloc()
{
	size_t block_size1 = sizeof(size_t);
	fsa_t *fsa1 = NULL;
	size_t buff_size1 = 72;
	char buff1[72] = {0};
	size_t *alloc = NULL;


	puts("TestAlloc");

	fsa1 = FSAInit(buff1, buff_size1, block_size1);

	alloc = FSAAlloc(fsa1);

	if(alloc == NULL)
	{
		printf("ERROR, LINE:%d\n",__LINE__);
	}

	alloc = FSAAlloc(fsa1);
	alloc = FSAAlloc(fsa1);
	alloc = FSAAlloc(fsa1);
	alloc = FSAAlloc(fsa1);

	if(alloc != NULL)
	{
		printf("ERROR, LINE:%d\n",__LINE__);
	}

	return 0;
}

void TestFree()
{
	size_t block_size1 = sizeof(size_t);
	fsa_t *fsa1 = NULL;
	size_t buff_size1 = 72;
	char buff1[72] = {0};
	size_t *alloc = NULL;
	size_t *alloc2 = NULL;
	size_t *alloc3 = NULL;

	size_t exp = 0;
	size_t res = 0;


	puts("TestFree");

	fsa1 = FSAInit(buff1, buff_size1, block_size1);
	alloc = FSAAlloc(fsa1);

	res = FSACountFree(fsa1);
	FSAFree(alloc);
	res = FSACountFree(fsa1);

	exp = 4;

	if (res != exp)
	{
		printf("ERROR, LINE:%d\nres = %ld,exp = %ld\n",__LINE__,res, exp);
	}

	alloc2 = FSAAlloc(fsa1);
	alloc3 = FSAAlloc(fsa1);

	FSAFree(alloc2);

	res = FSACountFree(fsa1);
	exp = 3;

	if (res != exp)
	{
		printf("ERROR, LINE:%d\nres = %ld,exp = %ld\n",__LINE__,res, exp);
	}

	FSAFree(alloc3);
}


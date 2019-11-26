#include <stdio.h>		/*i/o operations*/
#include <string.h>		/*strcmp*/	

#include "hash.h"		/*API*/

/*printf color macros*/
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"

/*test funcs declerations*/
static void TestCreatDestroyEmpty(void);
static void TestInsertDestroyFull(void);
static void TestFind(void);
static void TestRemove(void);
static void TestSize(void);
static void TestIsEmpty(void);
static void TestForEach(void);
/*call back funcs declerations*/
static size_t HashFunc(const void* key);
static int HashCmp(const void* data1, const void* data2);
static int ActionFunc(void* data, void* param);
/********************************************************/			
/********************************************************/
int main()
{
	puts("\n***************************************************");
	printf("\n%s 	**TESTS FOR HASH TABLE FUNCS**%s\n", KGRN, KNRM);
	puts("\n***************************************************");

	TestCreatDestroyEmpty();
	TestInsertDestroyFull();
	TestFind();
	TestRemove();
	TestSize();
	TestIsEmpty();
	TestForEach();

	printf("%s***************************************************%s\n\n", KRED, KNRM);
	return 0;
}

/********************************************************/
/*CREATE & DESTROY*/												
/********************************************************/
static void TestCreatDestroyEmpty(void)
{
	hash_t *hash = NULL;

	printf("%s***************************************************\n", KRED);
	printf("%s    TEST CREATE AND DEASTROY EMPTY HASH", KNRM);
	printf("%s\n***************************************************\n", KRED);

    hash = HASHCreate(HashFunc, HashCmp, 10);
    HASHDestroy(hash);

}

/********************************************************/
/*INSERT & DESTROY*/												
/********************************************************/
static void TestInsertDestroyFull(void)
{
	hash_t *hash = NULL;
	char *insert[] = {"a", "b", "c", "d"};
	size_t i = 0;
	size_t count = 4;

	printf("%s***************************************************\n", KRED);
	printf("%s    TEST INSERT AND DEASTROY FULL HASH", KNRM);
	printf("%s\n***************************************************\n", KRED);

    hash = HASHCreate(HashFunc, HashCmp, 10);

	for ( i = 0; i < count; i++)
	{
		if (0 != HASHInsert(hash, insert[i]))
		{
			printf("\n%sinsert for i = %lu failed%s", KRED, i, KNRM);
		}
		
	}
	
    HASHDestroy(hash);
}

/********************************************************/
/*CREATE & DESTROY*/												
/********************************************************/
static void TestFind(void)
{
	hash_t *hash = NULL;
	char *insert[] = {"a", "b", "c", "d"};
	size_t i = 0;
	size_t count = 4;

	printf("%s***************************************************\n", KRED);
	printf("%s    TEST FIND IN HASH", KNRM);
	printf("%s\n***************************************************\n", KRED);

    hash = HASHCreate(HashFunc, HashCmp, 10);

	/*insert*/
	for ( i = 0; i < count; i++)
	{
		if (0 != HASHInsert(hash, insert[i]))
		{
			printf("\n%sinsert for i = %lu failed%s", KRED, i, KNRM);
		}
		
	}

	/*find*/
	for ( i = 0; i < count; i++)
	{
		if (insert[i] != HASHFind(hash, insert[i]))
		{
			printf("\n%sinsert for i = %lu failed%s", KRED, i, KNRM);
		}
		
	}
	
    HASHDestroy(hash);
}

/********************************************************/
/*REMOVE*/												
/********************************************************/
static void TestRemove(void)
{
	hash_t *hash = NULL;
	char *insert[] = {"a", "b", "c", "d"};
	size_t i = 0;
	size_t count = 4;

	printf("%s***************************************************\n", KRED);
	printf("%s    TEST REMOVE FROM HASH", KNRM);
	printf("%s\n***************************************************\n", KRED);

    hash = HASHCreate(HashFunc, HashCmp, 10);

	/*insert*/
	for ( i = 0; i < count; i++)
	{
		if (0 != HASHInsert(hash, insert[i]))
		{
			printf("\n%sinsert for i = %lu failed%s", KRED, i, KNRM);
		}
		
	}

	/*remove*/
	for ( i = 0; i < count; i++)
	{
		HASHRemove(hash, insert[i]);
	
	}
	
    HASHDestroy(hash);
}

/********************************************************/
/*SIZE*/												
/********************************************************/
static void TestSize(void)
{
	hash_t *hash = NULL;
	char *insert[] = {"a", "b", "c", "d"};
	size_t i = 0;
	size_t count = 4;

	printf("%s***************************************************\n", KRED);
	printf("%s    TEST SIZE HASH", KNRM);
	printf("%s\n***************************************************\n", KRED);

    hash = HASHCreate(HashFunc, HashCmp, 10);

	for ( i = 0; i < count; i++)
	{
		if (0 != HASHInsert(hash, insert[i]))
		{
			printf("\n%sinsert for i = %lu failed%s", KRED, i, KNRM);
		}
		if ((i + 1) != HASHSize(hash))
		{
			printf("\n%size for i = %lu is wrong%s", KRED, i, KNRM);
		}
		
	}
	
    HASHDestroy(hash);
}

/********************************************************/
/*IS EMPTY*/												
/********************************************************/
static void TestIsEmpty(void)
{
	hash_t *hash = NULL;
	char *insert[] = {"a", "b", "c", "d"};
	size_t i = 0;
	size_t count = 4;

	printf("%s***************************************************\n", KRED);
	printf("%s    TEST IS EMPTY HASH", KNRM);
	printf("%s\n***************************************************\n", KRED);

    hash = HASHCreate(HashFunc, HashCmp, 10);

	if (1 != HASHIsEmpty(hash))
	{
		printf("\n%sis empty is not as expected line %d%s", KRED, __LINE__, KNRM);
	}
	
	for ( i = 0; i < count; i++)
	{
		if (0 != HASHInsert(hash, insert[i]))
		{
			printf("\n%sinsert for i = %lu failed%s", KRED, i, KNRM);
		}
		if (0 != HASHIsEmpty(hash))
		{
			printf("\n%sis empty is not as expected line %d%s", KRED, __LINE__, KNRM);
		}
		
	}
	
    HASHDestroy(hash);
}

/********************************************************/
/*FOR EACH*/												
/********************************************************/
static void TestForEach(void)
{
	hash_t *hash = NULL;
	char *insert[] = {"a", "b", "c", "d", "ab"};
	size_t i = 0;
	size_t count = 5;

	printf("%s***************************************************\n", KRED);
	printf("%s    TEST FOR EACH HASH", KNRM);
	printf("%s\n***************************************************\n", KRED);

    hash = HASHCreate(HashFunc, HashCmp, 10);
	
	for ( i = 0; i < count; i++)
	{
		if (0 != HASHInsert(hash, insert[i]))
		{
			printf("\n%sinsert for i = %lu failed%s", KRED, i, KNRM);
		}	
	}

	puts("");
	if (0 != HASHForEach(hash, ActionFunc, NULL))
	{
		printf("\n%sreturn value from for each is not ok%s", KRED, KNRM);
	}
	puts("");
	
	
    HASHDestroy(hash);
}

/********************************************************/			
/********************************************************/
static size_t HashFunc(const void* key)
{
    return (size_t)(*(char *)key%10);
}

/********************************************************/
static int HashCmp(const void* data1, const void* data2)
{
    return !strcmp((const char *)data1, (const char *)data2);
}

/********************************************************/
static int ActionFunc(void* data, void* param)
{
	printf("%s%s, %s", KGRN, (char *)data, KNRM);

	return 0;
}

/********************************************************/			
/********************************************************/

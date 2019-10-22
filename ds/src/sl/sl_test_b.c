#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "sl.h" /* for all tests below */

static void CreateAndDestroyTest();
static void InsertTests();
void MergeTest();

int IsBefore(void *node1, void *node2, void *param);

void PrintList(sl_t *list);

int main()
{
	/*CreateAndDestroyTest();*/
	InsertTests();
	/*MergeTest();*/
	return 0;
}

/*******System Tests:	*******/
static void CreateAndDestroyTest()
{
	sl_t *sl = NULL;
	int param = 123;
	
	printf("\n\nCreate and destroy test. . .\n");	
	
	printf("Creating new list: \t\t");
	sl = SLCreate(IsBefore, &param);
	(NULL != sl) ? printf("SUCCESS!\n") : printf("FAILURE\n");
	
	printf("IsEmpty test: \t\t\t");
	(1 == SLIsEmpty(sl)) ? printf("SUCCESS!\n") : printf("FAILURE\n");
	printf("Number of elements in list: %ld\n", SLSize(sl));
	
	SLDestroy(sl);
}

static void InsertTests()
{
	sl_t *sl = NULL;
	sl_iter_t iterator;
	int num1 = 1, num2 = 4, num3 = 7, num4 = 9;
	
	printf("\n\nPUSH test. . .\n");	
	sl = SLCreate(IsBefore, (void *)&num1);
	printf("Number of elements in list: %ld\n", SLSize(sl));
	printf("IsEmpty test: \t\t\t");
	(1 == SLIsEmpty(sl)) ? printf("SUCCESS!\n") : printf("FAILURE\n");
	
	
	printf("Insert test. . . \n");
	iterator = SLInsert(sl, (void *)&num4);
	printf("Number of elements in list: %ld\n", SLSize(sl));
	printf("Data element is: %d\n",*(int*)SLGetData(iterator));
	
	iterator = SLInsert(sl, (void *)&num2);
	printf("Number of elements in list: %ld\n", SLSize(sl));
	printf("Data element is: %d\n",*(int*)SLGetData(iterator));
	
	iterator = SLInsert(sl, (void *)&num3);
	printf("Number of elements in list: %ld\n", SLSize(sl));
	printf("Data element is: %d\n",*(int*)SLGetData(iterator));
	
	iterator = SLInsert(sl, (void *)&num1);
	printf("Number of elements in list: %ld\n", SLSize(sl));
	printf("Data element is: %d\n",*(int*)SLGetData(iterator));
	
	printf("IsEmpty test: \t\t\t");
	(0 == SLIsEmpty(sl)) ? printf("SUCCESS!\n") : printf("FAILURE\n");
	
	printf("\nPrinting list:\n");
	for (iterator = SLBegin(sl); !SLIsEqual(iterator, SLEnd(sl)); iterator = SLIterNext(iterator))
	{
		printf("%d \n", *(int*)SLGetData(iterator));
	}
		
	printf("Data element is: %d\n",*(int*)SLGetData(iterator));
	printf("Popped data element is: %d\n",*(int*)SLPopBack(sl));
	
	printf("IsEmpty test: \t\t\t");
	(0 == SLIsEmpty(sl)) ? printf("SUCCESS!\n") : printf("FAILURE\n");
	printf("Number of elements in list: %ld\n", SLSize(sl));
	iterator = SLBegin(sl);
	printf("Data element is: %d\n",*(int*)SLGetData(iterator));
	
	iterator = SLIterNext(iterator);
	printf("Data element is: %d\n",*(int*)SLGetData(iterator));
	
	iterator = SLIterNext(iterator);
	printf("Data element is: %d\n",*(int*)SLGetData(iterator));
	
	printf("\nPrinting list:\n");
	for (iterator = SLBegin(sl); !SLIsEqual(iterator, SLEnd(sl)); iterator = SLIterNext(iterator))
	{
		printf("%d ", *(int*)SLGetData(iterator));
	}
	
	SLDestroy(sl);
}

void MergeTest()
{
	sl_t *sl1 = NULL;
	sl_t *sl2 = NULL;
	sl_iter_t iterator1, iterator2;
	int num1 = 1, num2 = 4, num3 = 7;
	int num4 = 2, num5 = 3, num6 = 8;
	
	printf("\nMerge Test:\n");
	sl1 = SLCreate(IsBefore, (void *)&num1);
	iterator1 = SLBegin(sl1);
	iterator1 = SLInsert(sl1, (void *)&num2);
	iterator1 = SLInsert(sl1, (void *)&num3);
	iterator1 = SLInsert(sl1, (void *)&num1);

	printf("\nPrinting list I:\n");
	for (iterator1 = SLBegin(sl1); !SLIsEqual(iterator1, SLEnd(sl1)); iterator1 = SLIterNext(iterator1))
	{
		printf("%d ", *(int*)SLGetData(iterator1));
	}
		
	sl2 = SLCreate(IsBefore, (void *)&num1);
	iterator2 = SLInsert(sl2, (void *)&num4);
	iterator2 = SLInsert(sl2, (void *)&num6);
	iterator2 = SLInsert(sl2, (void *)&num5);
	
	printf("\nPrinting list II:\n");
	for (iterator2 = SLBegin(sl2); !SLIsEqual(iterator2, SLEnd(sl2)); iterator2 = SLIterNext(iterator2))
	{
		printf("%d ", *(int*)SLGetData(iterator2));
	}
	printf("\n\n");
	
	iterator1 = SLMerge(sl1, sl2);
	printf("\nNumber of elements in list: %ld\n", SLSize(sl1));
	printf("\nPrinting merged list:\n");
	for (iterator1 = SLBegin(sl1); !SLIsEqual(iterator1, SLEnd(sl1)); iterator1 = SLIterNext(iterator1))
	{
		printf("%d \n", *(int*)SLGetData(iterator1));
	}
	
	SLDestroy(sl1);
	SLDestroy(sl2);
}

/***************************************
 * 			Functions Tests:			*
***************************************/

/***************************************
 * 			internal functions			*
 **************************************/
 
void PrintList(sl_t *list)
{
	sl_iter_t it;
	
	printf("Printing list:\n");
	for (it = SLBegin(list); !SLIsEqual(SLBegin(list), SLEnd(list)); it = SLIterNext(it))
	{
		printf("%d ", *(int*)SLGetData(it));
	}
}

int IsBefore(void *node1, void *node2, void *param)
{
	return *(int*)node1 < *(int*)node2;
}


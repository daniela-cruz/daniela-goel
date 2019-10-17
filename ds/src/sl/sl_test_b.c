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
	/*InsertTests();*/
	MergeTest();
	return 0;
}

/***************************************
 * 			System Tests:				*
***************************************/
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
	int num1 = 123, num2 = 456, num3 = 789;
	
	printf("\n\nPUSH test. . .\n");	
	sl = SLCreate(IsBefore, (void *)&num1);
	iterator = SLIterNext(SLBegin(sl));
	printf("Number of elements in list: %ld\n", SLSize(sl));
	
	printf("Insert test. . . \n");
	iterator = SLInsert(iterator, (void *)&num1);
	printf("IsEmpty test: \t\t\t");
	(0 == SLIsEmpty(sl)) ? printf("SUCCESS!\n") : printf("FAILURE\n");
	printf("Number of elements in list: %ld\n", SLSize(sl));
	
	iterator = SLIterNext(iterator);
	iterator = SLInsert(iterator, (void *)&num2);
	printf("Number of elements in list: %ld\n", SLSize(sl));
	printf("Data element is: %d\n",*(int*)SLGetData(iterator));
	printf("Popped data element is: %d\n",*(int*)SLPopBack(sl));
	
	iterator = SLBegin(sl);
	iterator = SLIterNext(iterator);
	iterator = SLIterNext(iterator);
	iterator = SLInsert(iterator, (void *)&num3);
	printf("IsEmpty test: \t\t\t");
	(0 == SLIsEmpty(sl)) ? printf("SUCCESS!\n") : printf("FAILURE\n");
	printf("Number of elements in list: %ld\n", SLSize(sl));
	printf("Data element is: %d\n",*(int*)SLGetData(iterator));
	
	iterator = SLBegin(sl);
	iterator = SLIterNext(iterator);
	printf("Data element is: %d\n",*(int*)SLGetData(iterator));
	
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
	iterator1 = SLInsert(iterator1, (void *)&num1);
	iterator1 = SLInsert(iterator1, (void *)&num2);
	SLInsert(iterator1, (void *)&num3);

	printf("\nPrinting list:\n");
	for (iterator1 = SLBegin(sl1); !SLIsEqual(iterator1, SLEnd(sl1)); iterator1 = SLIterNext(iterator1))
	{
		printf("%d ", *(int*)SLGetData(iterator1));
	}
		
	sl2 = SLCreate(IsBefore, (void *)&num1);
	iterator2 = SLBegin(sl2);
	iterator2 = SLInsert(iterator2, (void *)&num4);
	iterator2 = SLInsert(iterator2, (void *)&num5);
	iterator2 = SLInsert(iterator2, (void *)&num6);
	
	printf("\nPrinting list:\n");
	for (iterator2 = SLBegin(sl2); !SLIsEqual(iterator2, SLEnd(sl2)); iterator2 = SLIterNext(iterator2))
	{
		printf("%d ", *(int*)SLGetData(iterator2));
	}
	
	iterator1 = SLMerge(sl1, sl2);
	printf("\nPrinting list:\n");
	for (iterator1 = SLBegin(sl1); !SLIsEqual(iterator1, SLEnd(sl1)); iterator1 = SLIterNext(iterator1))
	{
		printf("%d \n", *(int*)SLGetData(iterator1));
	}
	
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
	return node1 < node2;
}


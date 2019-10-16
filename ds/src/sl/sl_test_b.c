#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "sl.h" /* for all tests below */

static void CreateAndDestroyTest();
static void InsertTests();


int IsBefore(void *node1, void *node2, void *param);

int main()
{
	/*CreateAndDestroyTest();*/
	InsertTests();
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



/***************************************
 * 			Functions Tests:			*
***************************************/

/***************************************
 * 			internal functions			*
 **************************************/

int IsBefore(void *node1, void *node2, void *param)
{
	return node1 > node2;
}


#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "sl.h" /* for all tests below */

static void CreateTest();
int IsBefore(void *node1, void *node2, void *param);

static sl_t *new_sl = NULL;
sl_iter_t iterator = {NULL};
int num = 123;

int main()
{
	CreateTest();
	return 0;
}

static void CreateTest()
{
	printf("\nCreate test. . .\t");
	new_sl = SLCreate((sl_is_before_t)IsBefore);
	(NULL != new_sl) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}

/*
static void InsertTest(int num)
{
	SLInsert(new_sl, iterator, (void *)&num);
}
*/
/**************************************************
 * internal functions
 *************************************************/

int IsBefore(void *node1, void *node2, void *param)
{
	return node1 > node2;
}


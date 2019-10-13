#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "sl.h" /* for all tests below */

static void CreateTest();
int IsBefore(void *node1, void *node2, void *param);

static sl_t *new_sl = NULL;

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

int IsBefore(void *node1, void *node2, void *param)
{
	return node1 > node2;
}

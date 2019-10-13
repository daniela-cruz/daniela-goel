#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "sl.h" /* for all tests below */

static void CreateTest();

static sl_t *new_sl = NULL;

int main()
{
	CreateTest();
	return 0;
}

static void CreateTest()
{
	printf("\nCreate test. . .\t");
	(NULL != new_sl) ? printf("SUCCESS!\n"): printf("FAILURE!\n");
}

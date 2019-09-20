#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t, ptrdiff_t */
#include <assert.h> /* assert */
#include <string.h> /* strlen */

#include "itoa.h" /* for all functions bellow */

static void ItoaTest();

static void AtoiBase10Test();

static void AtoiBase36Test();

/* turn an int to char */
char Itoa(const int n)
{
	char ch = '0';
	
	if (('A' <= n) || ('Z' >= n))
	{
		ch = (char)n + 'A';
	}
	else if (('a' <= n) || ('z' >= n))
	{
		ch = (char)n + 'a';
	}
	else
	{
		ch = '0';
	}
	
	return ch;
}

static void ItoaTest()
{
	int num_char = 31;
	
	printf("\nitoa test\nInteger was: %d and now it is: %c\n", num_char, Itoa(num_char));
}

/* turn abc chars to integers */
int AtoiBase10(const char *nptr)
{
	int n = 0;
	
	if (('A' <= *nptr) && ('Z' >= *nptr))
	{
		n = *nptr - 'A';
	}
	else if (('a' <= *nptr) && ('z' >= *nptr))
	{
		n = *nptr - 'a';
	}
	else
	{
		n = 0;
	}
	
	return n;
}

static void AtoiBase10Test()
{
	char *char_num = "blabla";
	
	printf("\nitoa test\nCharacter was: %c and now it is: %d\n", *char_num, AtoiBase10(char_num));
}

/* turn abc chars and numeric chars to integers */
int AtoiBase36(const char *nptr)
{
	int n = 0;
	
	if (('A' <= *nptr) && ('Z' >= *nptr))
	{
		n = *nptr - 'A' + 10;
	}
	else if (('a' <= *nptr) && ('z' >= *nptr))
	{
		n = *nptr - 'a' + 10;
	}
	else if (('0' <= *nptr) && ('9' >= *nptr))
	{
		n = *nptr - '0';
	}
	else
	{
		n = 0;
	}
	
	return n;
}

static void AtoiBase36Test()
{
	ptrdiff_t from = 0, to = 36;
	char *ch_to_int = "0123456789abcdefghijklmmopqrstuvwxyz";
	char *ch_z = "zxy";
	
	for (; from <= to; from++, ch_to_int++)
	{
		printf("%d\n", AtoiBase36(ch_to_int));
	}
	
	printf("%d\n", AtoiBase36(ch_z));
}

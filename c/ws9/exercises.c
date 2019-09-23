#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t, ptrdiff_t */
#include <assert.h> /* assert */
#include <string.h> /* memset */
#include <stdint.h> /* uint16_t */

#include "itoa.h" /* itoa */

#define IS_LITTLE_ENDIAN *(&"1") ? 1 : 0

size_t IsLittleEndian();
static void PrintIdenticalChars(const char *s1, const char *s2, const char *s3);
static void PrintIdenticalCharsTest();

int main()
{
	IsLittleEndian();
	printf("\nIs little endian macro: %d\n", IS_LITTLE_ENDIAN);
	PrintIdenticalCharsTest();
	
	return 0;
}

size_t IsLittleEndian()
{
	size_t i = 1; 
	char *ch = (char*)&i; 
	size_t is_little = 0;
	
	if (*ch)     
	{
		printf("Little endian\n"); 
		is_little = 1;	
	}
	else
	{
		printf("Big endian\n"); 
	}
	
	return is_little;
}

static void PrintIdenticalChars(const char *s1, const char *s2, const char *s3)
{
	size_t i = 0, j =0;
	size_t abc_len = 'Z' - 'A' + 1;
	char *letters = NULL;
	
	assert(s1);
	assert(s2);
	assert(s3);
	
	letters = malloc(abc_len + 1);
	assert(letters);
	
	/* initialize letters arr to zeros */
	for (; i < abc_len; i++)
	{
		*(letters + i) = '0';
	}
	
	*(letters + abc_len + 1) = '\0';
	
	for (i = 0; i < strlen(s1); i++)
	{
		for (j = 0; j < abc_len; j++)
		{
			if ('A' + j == *(s1 + i))
			{
				*(letters + j) = '1';
			}
		}
	}
	
	for (i = 0; i < strlen(s2); i++)
	{
		for (j = 0; j < abc_len; j++)
		{
			if (('A' + j == *(s2 + i)) && ('1' == *(letters + j)))
			{
				*(letters + j) = '2';
			}
		}
	}
	
	for (i = 0; i < strlen(s3); i++)
	{
		for (j = 0; j < abc_len; j++)
		{
			if (('A' + j == *(s3 + i)) && ('2' == *(letters + j)))
			{
				*(letters + j) = '3';
			}
		}
	}
	
	for (i = 0; i < abc_len; i++)
	{	
		if ('2' == *(letters + i))
		{		
			printf("%c\n", Itoa(i));
		}
	}
	
	free(letters);
}

static void PrintIdenticalCharsTest()
{
	char *s1 = "ABCB", *s2 = "BCDEF", *s3 = "CDGH";
	PrintIdenticalChars(s1, s2, s3);
}


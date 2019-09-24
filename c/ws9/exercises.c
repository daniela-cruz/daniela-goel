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
static void ItoaTest();
static void Atoi10Test();
static void Atoi36Test();


int main()
{
	IsLittleEndian();
	printf("\nIs little endian macro: %d\n", IS_LITTLE_ENDIAN);
	PrintIdenticalCharsTest();
	ItoaTest();
	Atoi10Test();
	Atoi36Test();
	
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
	
	if (NULL == letters)
	{
		perror("Malloc failed");
	}
	
	/* initialize letters arr to zero charachters */
	for (; i < abc_len; i++)
	{
		*(letters + i) = 0;
	}
	
	*(letters + abc_len) = '\0';
	
	for (i = 0; i < strlen(s1); i++)
	{
		if (0 == letters[*(s1 + i) - 'A'])
		{
			letters[*(s1 + i) - 'A']++;
		}
	}
	
	for (i = 0; i < strlen(s2); i++)
	{
		if (1 == letters[*(s2 + i)  - 'A'])
		{
			letters[*(s2 + i)  - 'A']++;
		}
	}
	
	for (i = 0; i < strlen(s3); i++)
	{
		if (2 == letters[*(s3 + i)  - 'A'])
		{
			letters[*(s3 + i)  - 'A']++;
		}
	}
	
	for (i = 0; i < abc_len; i++)
	{	
		if (2 == *(letters + i))
		{		
			printf("%c\n", (i + 'A'));
		}
	}
	
	free(letters);
}

static void PrintIdenticalCharsTest()
{
	char *s1 = "ABCB", *s2 = "BCDEF", *s3 = "CDGH";
	
	printf("\n3 arrays test:\n");
	
	PrintIdenticalChars(s1, s2, s3);
}

static void ItoaTest()
{
	char *dest = NULL;
	int num_src = 123456789;
	
	dest = malloc(11);
	dest = Itoa(dest, num_src);
	
	printf("\nItoa test\n");
	printf("Integers is: %d and char is: %s\n", num_src, dest);
	
	free(dest); dest = NULL;
}

static void Atoi10Test()
{
	int num = 0;
	char *dest = "987654";
	
	num = AtoiBase10(dest);
	
	printf("\nAtoi10 test\n");
	printf("Integers is: %d and char is: %s\n", num, dest);
}

static void Atoi36Test()
{
	int num = 0;
	int src = 123456789;
	char *dest = NULL;
	
	dest = malloc(11);
	dest = AtoiBase36(src, dest, 16);
	
	printf("\nAtoi36 test\n");
	printf("Source is: %d and dest is: %s\n", src, dest);
	free(dest); dest = NULL;
}

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t, ptrdiff_t */
#include <assert.h> /* assert */
#include <string.h> /* memset */

size_t IsLittleEndian();
static void PrintIdenticalChars(const char *s1, const char *s1, const char *s3);

int main()
{
	IsLittleEndian();
	
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

static void PrintIdenticalChars(const char *s1, const char *s1, const char *s3)
{
	size_t i = 0, j =0;
	char *letters = NULL;
	
	assert(s1);
	assert(s2);
	assert(s3);
	
	letters = malloc(27);
	assert(letters);
	
	/* initialize letters arr to zeros */
	for (; i < 'Z' - 'A' + 1; i++)
	{
		*(letters + i) = 0;
	}
	
	for (i = 0; i < strlen(s1); i++, s1++)
	{
		for (j = 0; j < strlen(letters); j++)
		{
			if ('A' + j == *s1)
			{
				*(letters + j) = 1;
			}
		}
	}
	
	for (i = 0; i < strlen(s2); i++, s2++)
	{
		for (j = 0; j < strlen(letters); j++)
		{
			if (('A' + j == *s2) && (1 == *(letters + j)))
			{
				*(letters + j) = 2;
			}
		}
	}
	
	for (i = 0; i < strlen(s3); i++, s3++)
	{
		for (j = 0; j < strlen(letters); j++)
		{
			if (('A' + j == *s3) && (2 == *(letters + j)))
			{
				*(letters + j) = 3;
			}
		}
	}
	
	for (i = 0; i < strlen(letters); letters++)
	{	
		if (2 == *(letters + i))
		{		
			printf("%c\n", i + 'A');
		}
	}
	
	free(letters);
}

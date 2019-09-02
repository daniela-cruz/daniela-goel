#include <stdio.h> /*printf*/
#include <stdlib.h> /*free*/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include <string.h> /*strlen*/
#include <strings.h>

#include "String.h" /*string reimplementation*/

static void StrLenTest();
static void StrCmpTest();
static void StrCpyTest();
static void StrNcpyTest();
static void StrCaseCmpTest();
static void StrChrTest();
static void StrDupTest();
static void StrCatTest();
static void StrNcatTest();
static void StrStrTest();
static void StrSpnTest();

int main()
{
	StrLenTest();
	StrCmpTest();
	StrCpyTest();
	StrNcpyTest();
	StrCaseCmpTest();
	StrChrTest();
	StrDupTest();
	StrCatTest();
	StrNcatTest();
	StrStrTest();
	StrSpnTest();
	
	return 0;
}

static void StrLenTest()
{
	size_t arr_size = 3;
	char *str[] = {"hello", "hell o!", "  "};
	size_t expected_result[] = {5, 7, 2};
	size_t i = 0;
	
	printf("\nStrLen test:\n");
	
	for (; i < arr_size; i++)
	{
		if (expected_result[i] == StrLen(str[i]))
		{
			printf("\033[1;36m");
			printf("SUCCESS!\n");
			printf("\033[0m");
		}
		else
		{
			printf("\033[1;31m");
			printf("FAILURE! Received size is %ld\n", StrLen(str[i]));
			printf("\033[0m");
		}
	}
}

static void StrCmpTest()
{
	char *str1 = "hello";
	char *str2[] = {"hello", "heLlo"};
	int expected_result[] = {0, 32};
	size_t test_num = 2;
	size_t i = 0;
	
	printf("\nStrCmp test:\n");
	printf("string 1 is: %s and string 2 is: %s\n", str1, *str2);
	
	for (; i < test_num; i++)
	{
		if (expected_result[i] == StrCmp(str1, str2[i]))
		{
			printf("\033[1;36m");
			printf("SUCCESS!\n");
			printf("\033[0m");
		}
		else
		{
			printf("\033[1;31m");
			printf("FAILURE! Received size is %d\n", StrCmp(str1, str2[i]));
			printf("\033[0m");
		}
	}
}

static void StrCpyTest()
{
	const char *source = "hello";
	char *destination = NULL;
	size_t string_len = 0;
	
	string_len = strlen(source);
	destination = (char *)malloc((string_len + 1) * sizeof(char));
	
	if (NULL == destination)
	{
		fprintf(stderr, "Failed to allocate memory to destination pointer\n");
		exit(1);
	}
	
	printf("\nStrCpy test:\n");
	
	assert(NULL != destination);
	destination = StrCpy(destination, source);
	printf("Destination is %s\n", destination);
	
	free(destination); destination = NULL;
}

static void StrNcpyTest()
{
	const char *source = "hello";
	char destination[100];
	char *dest = NULL;
	char *expected_string[] = {"hel", "h", "", "hello", '\0'};
	char *expected = NULL;
	size_t i = 1;
	size_t length_arr[] = {3, 1, 0, 7, 0};
	size_t *length = NULL;
	
	dest = destination;
	expected = *expected_string;
	length = length_arr;
	
	assert(NULL != dest);
	assert(NULL != expected);
	
	printf("\nStrNcpy test:\n");
	
	for (; 5 > i; i++)
	{
		printf("Expected string is: %s\n", expected);
		dest = StrNcpy(dest, source, *length);
		
		if(0 == strcmp(dest, expected))
		{
			printf("\033[1;36m");
			printf("SUCCESS! Destination is: %s\n", dest);
			printf("\033[0m");
		}
		else
		{
			printf("\033[1;31m");
			printf("Failure! Destination is: %s\n", dest);
			printf("\033[0m");
		}
		
		expected = expected_string[i];
		length++;
		dest = destination;
	}
}

static void StrCaseCmpTest()
{
	const char *s1 = "Hello";
	const char *str2[] = {"HeLlo", " hello", "hello ", "kello"};
	char *s2 = NULL;
	int expected_result[] = {0, 72, 0, -3};
	size_t i = 0;
	
	printf("\nStrCaseCmp test:\n");
	
	for (; 4 > i; i++)
	{
		s2 = (char *)str2[i];
		
		if (expected_result[i] == StrCaseCmp(s1, s2))
		{
			printf("\033[1;36m");
			printf("SUCCESS!\n");
			printf("\033[0m");
		}
		else
		{
			printf("\033[1;31m");
			printf("Failure, received value is: %d!\n", StrCaseCmp(s1, s2));
			printf("\033[0m");
		}
	}
}

static void StrChrTest()
{
	const char *str = "bbab";
	char *found_ptr = NULL;
	int c_arr[] = {0x61, 0x41, 0x00};
	int *c = 0x00;
	char ch = 0;
	size_t i = 0;
	
	printf("\nStrChr test:\n");
	
	c = c_arr;
	
	for (; 3 > i; i++)
	{
		
		found_ptr = StrChr(str, *c);
		ch = (char)*c;
		printf("\nString is: %s and requested character is: %c:\n", str, ch);
		
		if (ch == *found_ptr)
		{
			printf("\033[1;36m");
			printf("Found it!\n");
			printf("\033[0m");
		}
		else
		{
			printf("\033[1;35m");
			printf("Received character is not found!\n");
			printf("\033[0m");
		}
		
		c++;
	}
}

static void StrDupTest()
{
	const char *source = "Hell oh!";
	char *destination = NULL;
	
	destination = StrDup(source);
	
	printf("\nDuplicant is: %s\n", destination);
	
	free(destination);
}

static void StrCatTest()
{
	const char *source = " Yes! I'm added!";
	char *destination = "Am I added?";
	char buffer[100];
	char *dest = NULL;
	
	dest = buffer;
	dest = strcpy(dest, destination);
	destination = StrCat(dest, source);
	
	printf("\nConcatinated string is: %s\n", destination);
}

static void StrNcatTest()
{
	char *src = " I am the added string!";
	char *destination = "Are you the added string?";
	char buffer[100];
	char *dest = NULL;
	size_t chr_amount = 30;
	
	dest = strcpy(buffer, destination);
	dest = StrNcat(dest, src, chr_amount);
	
	printf("\nConcatinated N string is: %s\n", dest);
}

static void StrStrTest()
{
	const char *long_string[] = {"I aM a long string, can you find my substring?", "bababbbaaa", "dan daniela", ""};
	char *sub_string[] = {"I", "am", " am!", "!", "can", "bba", "daniela", ""};
	char **sub = NULL;
	const char **long_ptr = NULL;
	
	printf("\nStrStr test:\n");
	
	long_ptr = long_string;
	sub = sub_string;
	
	while ('\0' != **long_ptr)
	{
		while ('\0' != **sub)
		{
			printf("Desired substring is: %s\n", *sub);
			*sub = StrStr(*long_ptr, *sub);
			printf("Found substring: %s\n", *sub);
			
			sub++;
		}
		
		long_ptr++; 
	}
}

static void StrSpnTest()
{
	char *s1 = "Can you find me in there?";
	char *accept_str[] = {"Can", "an", "can!!!", "lala", ""};
	char **accepted = NULL;
	size_t expected_result[] = {3, 2, 2, 0, 0};
	size_t *expected_res = NULL;
	
	printf("\nStrSpan test:\n");
	
	accepted = (char **)accept_str;
	expected_res = expected_result;
	
	while ('\0' != **accepted)
	{
		printf("\033[01;33m");
		printf("\nS1 is: %s and ACCEPTED STRING is: %s\n", s1, *accepted);
		printf("\033[0m");	
		
		if (*expected_res == StrSpn(s1, *accepted))
		{
			printf("\033[1;36m");
			printf("SUCCESS!\n");
			printf("\033[0m");
		}
		else
		{
			printf("\033[1;31m");
			printf("StrSpn calculated %ld but expected result is: %ld!\n", 
					StrSpn(s1, *accepted), *expected_res);
			printf("\033[0m");
		}
		
		accepted++;
		expected_res++;
	}
}

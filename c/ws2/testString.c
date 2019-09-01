#include <stdio.h> /*printf*/
#include <stdlib.h> /*link String.h*/
#include <assert.h> /*assert*/
#include <string.h> /*strlen*/

#include "String.h" /*string reimplementation*/

static void StrLenTest();
static void StrCmpTest();
static void StrCpyTest();
static void StrNcpyTest();
static void StrCaseCmpTest();
static void StrChrTest();

int main()
{
	/*StrLenTest();*/
	/*StrCmpTest();*/
	/*StrCpyTest();*/
	/*StrNcpyTest();*/
	StrCaseCmpTest();
	
	return 0;
}

static void StrLenTest()
{
	size_t arr_size = 3;
	char *str[] = {"hello", "hell o!", "  "};
	size_t expected_result[] = {5, 7, 2};
	size_t i = 0;
	
	for (; i < arr_size; i++)
	{
		if (expected_result[i] == StrLen(str[i]))
		{
			printf("SUCCESS!\n");
		}
		else
		{
			printf("FAILURE! Received size is %ld\n", StrLen(str[i]));
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
	
	
	printf("string 1 is: %s and string 2 is: %s\n", str1, *str2);
	
	for (; i < test_num; i++)
	{
		if (expected_result[i] == StrCmp(str1, str2[i]))
		{
			printf("SUCCESS!\n");
		}
		else
		{
			printf("FAILURE! Received size is %d\n", StrCmp(str1, str2[i]));
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
	
	printf("Source is: %s and expected is: %s\n", source, expected);
	
	for (; 5 > i; i++)
	{
		printf("Expected string is: %s\n", expected);
		
		dest = StrNcpy(dest, source, *length);
		
		if(0 == strcmp(dest, expected))
		{
			printf("SUCCESS! Destination is: %s\n", dest);
		}
		else
		{
			printf("Failure! Destination is: %s\n", dest);
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
	
	
	
	for (; 4 > i; i++)
	{
		s2 = (char *)str2[i];
		
		if (expected_result[i] == StrCaseCmp(s1, s2))
		{
			printf("SUCCESS!\n");
		}
		else
		{
			printf("Failure, received value is: %d!\n", StrCaseCmp(s1, s2));
		}
	}	
}

static void StrChrTest()
{
	const char *str = "bbab";
	char c = 'b';
}

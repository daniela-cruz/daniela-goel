#include <stdio.h> /*printf*/
#include <stdlib.h> /*link String.h*/
#include <assert.h> /*assert*/

#include "String.h" /*string reimplementation*/

static void StrLenTest();
void StrCmpTest();

int main()
{
	/*StrLenTest();*/
	StrCmpTest();
	
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

void StrCmpTest()
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

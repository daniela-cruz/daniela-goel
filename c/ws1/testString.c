#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#include "String.h" /*string reimplementation*/

static void StrLenTest();

int main()
{
	StrLenTest();
	
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

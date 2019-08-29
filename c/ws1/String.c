#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#include "String.h" /*StrLen*/

int main()
{
	char *str = "hello";
	
	printf("%ld\n", StrLen(str));
	
	return 0;
}

size_t StrLen(const char *str)
{
	char ch_number = 0;
	
	assert(NULL != str);
	while ('\0' != *str)
	{
		str++;
		ch_number++;
	}
	
	return ch_number;
}

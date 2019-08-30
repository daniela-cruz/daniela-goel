#include <stdio.h> /*printf*/
#include <stdlib.h> /*linkage*/
#include <assert.h> /*assert*/

#include "String.h" /*StrLen*/


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

int StrCmp(const char *str1, const char *str2)
{
	int difference = 0;
	
	assert(NULL != str1);
	assert(NULL != str2);
	
	while (('\0' != *str1) && ('\0' != *str2) && (0 == difference)) 
	{
		difference = *str1 - *str2;
		str1++;
		str2++;
	}
	
	return difference;
}

char *StrCpy(char *destination, const char *source)
{
	char *dest_start = NULL;
	char *src = NULL;
	
	assert(NULL != source);
	assert(NULL != destination);
	
	dest_start = destination;
	src = (char *)source;
	
	while ('\0' != *src)
	{
		*destination = *src;
		src++;
		destination++;
	}
	
	*destination = '\0';
	
	return dest_start;
}


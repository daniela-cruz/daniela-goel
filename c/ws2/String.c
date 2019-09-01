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

char *StrNcpy(char *destination, const char *source, size_t n)
{
	char *dest_start = NULL;
	char *src = NULL;
	
	assert(NULL != source);
	assert(NULL != destination);
	dest_start = destination;
	src = (char *)source;
	
	while (0 < n)
	{
		if ('\0' != *src)
		{
			*destination = *src;
			src++;
		}
		else
		{
			*destination = '\0';
		}
		
		destination++;
		n--;
	}
	
	*destination = '\0';
	
	return dest_start;
}

int StrCaseCmp(const char *s1, const char *s2)
{
	char ch1 = 0, ch2 = 0;
	char *str1 = NULL, *str2 = NULL;
	char case_convert = 0x20;
	int diff = 0;
	
	assert(NULL != s1);
	assert(NULL != s2);
	str1 = (char *)s1;
	str2 = (char *)s2;
	ch1 = *str1;
	ch2 = *str2;
	
	while (('\0' != *str1) && ('\0' != *str2))
	{
		if ('A' <= ch1 && 'Z' >= ch1)
		{
			ch1 += case_convert;
		}
		if ('A' <= ch2 && 'Z' >= ch2)
		{
			ch2 += case_convert;
		}
		/*exit loop when difference is found:*/
		if (0 != ch1 - ch2)
		{
			break;
		}
		
		str1++;
		str2++;
	}
	
	return ch1 - ch2;
}

char *StrChr(const char *str, int c)
{
	char *find_ch = NULL;
	
	assert(NULL != str);
	find_ch = (char *)str;
	
	while ('\0' != *find_ch)
	{
		if (c == *find_ch)
		{
			return find_ch;
		}
		
		find_ch++;
	}
	
	return find_ch;
}

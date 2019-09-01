#ifndef NDEBUG
#include <assert.h> /* assert */
#endif
#include <stdlib.h> /* malloc */
#include <stddef.h> /* size_t */

#include "String.h" /* StrLen */

size_t StrLen(const char *str)
{
	char str_len = 0;
	
	assert(NULL != str);
	while ('\0' != *(str + str_len))
	{
		str_len++;
	}
	
	return str_len;
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
	char ch = 0x00;
	
	assert(NULL != str);
	ch = (char)c;
	
	while ('\0' != *str)
	{
		if (ch == *str)
		{
			return (char *)str;
		}
		
		str++;
	}
	
	return (char *)str;
}

char *StrDup(const char *source)
{
	char *duplicant = NULL;
	char *dup_start = NULL;
	size_t str_length = 0;
	
	assert(NULL != source);
	str_length = StrLen(source) ;
	
	duplicant = (char *)malloc((str_length + 1) * sizeof(char));
	dup_start = duplicant;
	
	while ('\0' != *source)
	{
		*duplicant = *source;
		
		source++;
		duplicant++;
	}
	
	*duplicant = '\0';
	
	return dup_start;
}

char *StrCat(char *destination, const char *source)
{
	char *dest_start = NULL;
	
	assert(NULL != source);
	assert(NULL != destination);
	dest_start = destination;
	
	while ('\0' != *destination)
	{
		destination++;
	}
	
	destination = StrCpy(destination, source);
	
	return dest_start;
}

char *StrNcat(char *dest, const char *src, size_t n)
{
	char *dest_start = NULL;
	
	assert(NULL != src);
	dest_start = dest;
	
	while ('\0' != *dest)
	{
		dest++;
	}
	
	while ((0 < n) && ('\0' != *src))
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	
	*dest = '\0';
	
	return dest_start;
}



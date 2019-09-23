#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t, ptrdiff_t */
#include <assert.h> /* assert */
#include <string.h> /* strlen */

#include "itoa.h" /* for all functions bellow */

static void Reverse (char *buffer);

static void AtoiBase10Test();

static void AtoiBase36Test();

/* turn an int to char */
char *Itoa(char *dest, int num_src)
{
	ptrdiff_t i = 0;
	int to_char = 0; /* int thar holde a char value */
	char * dest_cpy = dest; 
	int base = 10;
	
	if (0 == num_src)
	{
		return "0";
	}
		
	if (0 > num_src)
	{
		num_src = -num_src;
		*dest = (char) '-'; 
		dest++;
	}
	
	for (i = 0 ; num_src != 0 ; i++,  num_src /= base)
	{
		to_char = num_src % 10;
		to_char += '0';
		*(dest + i) = (char)(to_char); 
	}
	
	Reverse(dest);
	
	return dest_cpy;
}

static void Reverse (char *buffer)
{
	char temp;
	size_t i = 0;
	size_t len = 0;
	
	len = strlen(buffer) -1;
	
	for (; i <= len / 2 ; i++)
	{
		temp = *(buffer + i);
		*(buffer + i) = *(buffer + len - i);
		*(buffer + len - i) = temp;
	}	
}	

/* turn abc chars to integers */
int AtoiBase10(const char *nptr)
{
	int int_value = 0;
	size_t i = 0;
	size_t len = 0;
 	int sign = 1;
 	int base = 10;
	
	len = strlen(nptr);
	
	if (*nptr == '-')
	{
		sign = -1;  
		nptr++;
	}
	
	for (; i < len; i++)
	{
		if ('9' < (*(nptr + i)) || ('0' > *(nptr + i)))  
		{
			break;
		}
		
		int_value = int_value * base + (*(nptr + i) - '0');
	}
	
	return int_value*sign;
}

/* turn abc chars and numeric chars to integers */
int AtoiBase36(char *dest, const char *nptr, int base)
{
	int int_value = 0;
	size_t i = 0;
	size_t len = 0;
 	int sign = 1;
	
	len = strlen(nptr);
	
	if (*nptr == '-')
	{
		sign = -1;  
		nptr++;
	}
	
	for (; i < len; i++)
	{
		if ('9' < (*(nptr + i)) || ('0' > *(nptr + i)))  
		{
			break;
		}
		
		int_value = int_value * base + (*(nptr + i) - '0');
	}
	
	return int_value*sign;
}


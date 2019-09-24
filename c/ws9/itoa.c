#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t, ptrdiff_t */
#include <assert.h> /* assert */
#include <string.h> /* strlen */

#include "itoa.h" /* for all functions bellow */

static void ReverseDigits (char *dest);

/* turn an int to char */
char *Itoa(char *dest, int num_src)
{
	ptrdiff_t i = 0;
	int to_char = 0; /* int that holds a char value */
	char * dest_cpy = dest; 
	int base = 10;
	
	assert(dest);
	
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
	
	ReverseDigits(dest); 
	
	return dest_cpy;
}

static void ReverseDigits (char *dest)
{
	char temp;
	size_t i = 0;
	size_t len = 0;
	
	assert(dest);
	
	len = strlen(dest) -1;
	
	for (; i <= len / 2 ; i++)
	{
		temp = *(dest + i);
		*(dest + i) = *(dest + len - i);
		*(dest + len - i) = temp;
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
	
	assert(nptr);
	len = strlen(nptr);
	
	if ('-' == *nptr)
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
char *AtoiBase36(int num, char *dest, int base)
{
	ptrdiff_t i = 0;
	int digit_sum = 0;
	char * dest_copy = NULL; 
	
	assert(dest);
	dest_copy = dest;
	
	if (0 > num)
	{
		num *= -1;
		*dest = (char) '-';  
		dest++; 
	}
	
	for (i = 0 ; num != 0 ; i++, num /= base)
	{
		digit_sum = num % base; /* get lsd of number in new base */
		digit_sum +=  ((digit_sum >= 0) && (digit_sum <= 9)) ? '0' : '7';	 
		*(dest + i) = (char)(digit_sum);   
	}
	
	ReverseDigits(dest);
	
	return dest_copy;
}


#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t, ptrdiff_t */
#include <assert.h> /* assert */
#include <string.h> /* memset */

size_t IsLittleEndian();

int main()
{
	IsLittleEndian();
	
	return 0;
}

size_t IsLittleEndian()
{
	size_t i = 1; 
	char *ch = (char*)&i; 
	size_t is_little = 0;
	
	if (*ch)     
	{
		printf("Little endian\n"); 
		is_little = 1;	
	}
	else
	{
		printf("Big endian\n"); 
	}
	
	return is_little;
}

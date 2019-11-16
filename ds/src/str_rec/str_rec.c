#include <stdio.h> /* printf*/
#include <stdlib.h> /* malloc free */

int RecFibonacci(int num);
static size_t RecStrLen(char *str);
void RecStrCpy(char *dest, char *src);

char dest[] = "hello, blah";
char src[] = "Hey";

int main()
{
    /*size_t  len = 0;*/
    int num = 3;

    
    printf("Fibonacci of %d is: %d\n", num, RecFibonacci(num));

    /*len = RecStrLen(str);
    printf("size is: %ld\n", len);*/
    
    /*RecStrCpy(dest, src);
    printf("new string is: %s\n", dest);*/

    return 0;
}

/********************
 *  FUNCTIONS       *
********************/
int RecFibonacci(int num)
{
    static size_t num0 = 0, num1 = 1;

    if (1 >= num)
    {
        return num;
    }
    
    return RecFibonacci(num - 1) + RecFibonacci(num - 2);
}

size_t RecStrLen(char *str)
{
    if ('\0' == *str)
    {
        return 0;
    }
    else 
    {
        return 1 + RecStrLen(str + 1);
    }
}

void RecStrCpy(char *dest, char *src)
{
	*dest = *src;
	
	if ('\0' == *src) 
	{
		dest--;
        *dest = '\0';
        return; 
	}
	
	RecStrCpy(src + 1, dest + 1);
}

int RecStrCmp(const char* s1, const char* s2)
{
	char* str1 = (char*) s1;
	char* str2 = (char*) s2;

	if (('\0' == *str1) && ('\0' == *str2))
	{
		return 0; 
	}

	if (*str1 != *str2)
	{
		return 1;
	}

	str1++; str2++;

	return RecStrCmp(str1, str2);
}

char* StrCatRec(char* dest, const char* src)
{
	char* d = NULL, * s = NULL;
	
	d = dest;
	s = (char*)src;

	if (d + StrLen(dest) == d)
	{
		*d = *s;

		if ('\0' == *s)
		{
			return d;
		}

		return StrCatRec(++d, ++s) - 1;
	}

	d++;

	return StrCatRec(d, s) - 1;
}


#include <stdio.h> /* printf*/
#include <stdlib.h> /* malloc free */

char dest[] = "hello, blah";
char src[] = "Hey";

static size_t RecStrLen(char *str);
void RecStrCpy(char *dest, char *src);

int main()
{
    /*size_t  len = 0;

    len = RecStrLen(str);
    printf("size is: %ld\n", len);*/
    RecStrCpy(dest, src);
    printf("new string is: %s\n", dest);

    return 0;
}

static size_t RecStrLen(char *str)
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

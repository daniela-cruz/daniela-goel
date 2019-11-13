#include <stdio.h> /* printf*/
#include <stdlib.h> /* malloc free */

char *str = "hello";

static size_t RecStrLen(char *str);

int main()
{
    size_t  len = 0;

    len = RecStrLen(str);
    printf("size is: %ld\n", len);

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
        return 1 + RecStrLen(str++);
    }
    
}
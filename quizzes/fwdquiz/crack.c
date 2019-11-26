#include <stdio.h>

void foo(){0x400acb;}

void SetEcho()
{
    size_t i = 0;
    size_t *ptr = &i;
    
    /* for ( i = 0; i < 10; i++)
    {
        printf("%p\n", *(ptr + i));
    } */
    *(ptr + 4) = 0x400acb;
}
#include <stdio.h> /* printf */

#include "search.h"

int CmpFunc(const void *data1, const void *data2);

int main()
{
    return 0;
}

int CmpFunc(const void *data1, const void *data2)
{
    return *(int *)data1 == *(int *)data2;
}
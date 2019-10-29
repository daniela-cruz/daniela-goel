#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "vsa.h"

int main()
{
	size_t magic = ~(0);
	printf ("%lu\n",magic);
	return 0;
}

#include <stdio.h> /* printf */
#include "swap.h" /* swap */

#define INT_PTR int*

SWAP_DEF(INT_PTR)

int main()
{
	
	return 0;
}

static void swapTest()
{
	int *p1, *p2;
	int num1 = 3, num2 = 5;
	
	p1 = &num1; p2 = &num2;
	Swap_INT_PTR(&p1, &p2);
	
	printf("ptr1 holds now: %d and ptr2 holds: %d\n", *p1, *p2);
}

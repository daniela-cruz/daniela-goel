#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

#define BASE  10.00
#define DELTA 0.0001

void HelloWorld();
float Power(int exp); 
int Flip(int num); 
void Swap(int *ptr_1, int *ptr_2);

/*TESTS:*/
void TestPower();
void TestFlip(); 
void TestSwap();

int main()
{
	HelloWorld();
	TestPower();		
	TestFlip();
	TestSwap();
	
	exit(0);	
}

/*EXERCISES:*/
void HelloWorld()
{
	char i = 0, char_arr[] = {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 
		0x72, 0x6c, 0x64, 0x21, 0x00}, *p = char_arr;
	
	while (*p != '\0')
	{
		printf("%c", *p);		
		p++;
	}
	printf("\n");
}

float Power(int exp)
{
	float base = BASE, result = 1.00;
	int i = 0;
	
	if (exp < 0)
	{
		base = 1 / base;
		exp = -exp;
	}
	
	for (i = 0; i < exp; i++)
	{
		result *= base;
	}
	
	return result;
}

int Flip(int num)
{
	int result = 0;

	while (num != 0)
	{
		result *= 10;
		result += num % 10;
		num /= 10;
	}	
	
	return result;
}

void Swap(int *ptr_1, int *ptr_2)
{
	int temp = *ptr_1;
	
	*ptr_1 = *ptr_2;
	*ptr_2 = temp;
}

/*TESTS:*/
void TestPower()
{
	int exp_arr[] = {1, 0, -5, 3}, *p = exp_arr, i = 0, size = 4;
	
	for (i = 0; i < size; i++)
	{
		assert(abs((pow(BASE, *p)) - (Power(*p))) <= 0.99 * Power(*p));
	}
}

void TestFlip()
{
	int num_arr[] = {1234, -9876, 7890, 1000, 0}, *p = num_arr, size = 5, 
					flip_arr[] = {4321, -6789, 987, 1, 0}, *pf = flip_arr, i = 0;
	
	while (i < size)
	{
		assert (Flip(*p) == *pf);
		printf("%d to %d\n", *p, *pf);
		p++;
		pf++;
		i++;
	}
}

void TestSwap()
{
	int a = 13, b = 31;
	int *ptr_1 = &a, *ptr_2 = &b;
	
	printf("The values are: ptr 1 = %d, ptr 2 = %d before swap.\n", 
			*ptr_1, *ptr_2);
			
	Swap(ptr_1, ptr_2);
	
	printf("After swap: ptr 1 = %d and ptr 2 = %d!\n", 
			*ptr_1, *ptr_2);
}


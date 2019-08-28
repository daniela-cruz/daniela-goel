#include <stdio.h> /*printf*/
#include <stdlib.h>
#include <assert.h> /*assert*/

#define BASE  10

static void HelloWorld();
static double Power(int exp); 
static int Flip(int num); 
static void Swap(int *ptr_1, int *ptr_2);

/*TESTS:*/
static void TestPower();
static void TestFlip(); 
static void TestSwap();

int main()
{
	TestSwap();
	/*TestPower();
	HelloWorld();		
	TestFlip();*/
	
	return 0;	
}

/*EXERCISES:*/
void HelloWorld()
{
	const char hello_world[] = {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 
						 0x72, 0x6c, 0x64, 0x21, 0x00};
	
	printf("%s\n", hello_world);
}

double Power(int exp)
{
	float base = BASE;
	double result = 1.0;
	int i = 0;
	
	if (0 > exp)
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

void TestPower()
{
	int tested_input[] = {1, 0, -5, 3};
	double expected_result[] = {10, 1, 0.00001, 10000};
	size_t tests_number = 4;
	int i = 0;
	
	for ( ; i < tests_number; i++)
	{
		printf("Test produced this result: %f\n", Power(tested_input[i]));
				
		if ( 0.99 * Power(tested_input[i]) <=  expected_result[i])
		{
			printf("Test succeeded!\n\n");
		}
		else
		{
			printf("Test failed!\n\n");
		}
	}
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

void TestFlip()
{
	int num_arr[] = {1234, -9876, 7890, 1000, 0}; 
	int flip_arr[] = {4321, -6789, 987, 1, 0}; 
	int *p = num_arr, *pf = flip_arr;
	size_t size = 5, i = 0;
	
	while (i < size)
	{
		assert (Flip(*p) == *pf);
		printf("%d to %d\n", *p, *pf);
		p++;
		pf++;
		i++;
	}
}

void Swap(int *ptr_1, int *ptr_2)
{
	int temp = *ptr_1;
	
	*ptr_1 = *ptr_2;
	*ptr_2 = temp;
}

void TestSwap()
{
	int a = 13, b = 31;
	int *ptr_1 = &a, *ptr_2 = &b;
	
	printf("The values are: ptr 1 = %d, ptr 2 = %d before swap.\n", *ptr_1, *ptr_2);
			
	Swap(ptr_1, ptr_2);
	
	printf("After swap: ptr 1 = %d and ptr 2 = %d!\n", *ptr_1, *ptr_2);
}

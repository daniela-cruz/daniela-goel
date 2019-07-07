#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
	char i = 0, char_arr[] = {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 
						0x6c, 0x64, 0x21, '\0'};
	
	while (char_arr != '\0')
	{
		printf("%c", *(char_arr+i));		
		i++;
	}
	printf("\n");

}

float Power(int exp)
{
	float base = BASE, result = 1.00;
	int i = 0;
	
	if (exp < 0)
	{
		base = 1/BASE;
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
		result *=10;
		result += num%10;
		num /=10;
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
	int exp_arr[] = {1, 0, -5, 3}, i = 0, size = 4;
	
	for (i = 0; i < size; i++)
	{
		if((pow(BASE, exp_arr[i])) - (Power(exp_arr[i])) <= DELTA)	
		{
			printf("GREAT SUCCESS!!\n");
		}

		else
		{
			printf("FAILURE!!\n");
		}
	}
}

void TestFlip()
{
	int num_1 = 1234, num_2 = 01234, num_3 = -9876, num_4 = 7890,
		num_5 = 7089;
	
	Flip(num_1);
	Flip(num_2);
	Flip(num_3);
	Flip(num_4);
	Flip(num_5);
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


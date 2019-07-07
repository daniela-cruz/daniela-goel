#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BASE  10.00
#define DELTA 0.0001

/*EXERCISES:*/
void HelloWorld(); /*ECERCISE 3- calculate exp*/
float Power(int exp); /*ECERCISE 4- calculate exp*/
int Flip(int num); /*ECERCISE 5- flip numbers*/
void Swap(int *ptr_1, int *ptr_2); /*ECERCISE 6- swap values*/

/*TESTS:*/
void TestPower(int exp); /*Test exe 4*/
void TestFlip();  /*Test exe 5*/

int main()
{
	int num_1 = 2, num_2 = 190;

	HelloWorld();
	TestPower(-5);		
	TestFlip();
	Swap(&num_1, &num_2);
	exit(0);	
}

/*EXERCISES:*/

/*===exe 3 - Hello world!===*/
void HelloWorld()
{
	char char_arr[] = {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, '\0'};
	int i = 0;
	
	while(char_arr[i] != '\0')
	{
		printf("%c", char_arr[i]);		
		i++;
	}
	printf("\n");

}
/*===exe 4 - Power===*/
float Power(int exp)
{
	float base = BASE, result = 1.00;
	int i;
	
	if (exp < 0)
	{
		base = 1/BASE;
		exp = -exp;
	}
	
	for(i=0; i<exp; i++)
	{
		result *= base;
	}
	
	return result;
}

/*===exe 5 - Flip====*/
int Flip(int num)
{
	int result = 0;

	printf("I used to be just %d but... \n", num);	
	while(num)
	{
		result *=10;
		result += num%10;
		num /=10;
	}	
	printf("I am now %d!\n", result);
	return result;
}

/*===exe 6 - Swap===*/
void Swap(int *ptr_1, int *ptr_2)
{
	int temp = *ptr_1;
	
	*ptr_1 = *ptr_2;
	*ptr_2 = temp;
	
	printf("Ptr1 = %d and ptr2 = %d\n", *ptr_1, *ptr_2);
	
	return;
}

/*TESTS:*/

/*Test exe 4*/
void TestPower(int exp)
{
	if((pow(BASE, exp)) - (Power(exp)) <= DELTA)	
	{
		printf("GREAT SUCCESS!!\n");
	}
	
	else
	{
		printf("FAILURE!!\n");
	}
	
	return;
}
/*Test exe 5*/
void TestFlip()
{
	int num_1 = 1234, num_2 = 01234, num_3 = -9876, num_4 = 7890,
		num_5 = 7089;
	
	Flip(num_1);
	Flip(num_2);
	Flip(num_3);
	Flip(num_4);
	Flip(num_5);
	
	return;
}


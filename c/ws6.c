#include <stdio.h> /*printf*/
#include <stdlib.h>
#include <math.h> /*pow*/
#include <assert.h> /*assert*/

double Pow2(unsigned int x, int y);/*tested*/
static void TestPow2(); 
int IsPow2(unsigned int n); /*tested*/
static void TestIsPow();
int IsPowBoolean(unsigned int n); /*tested*/
static void TestIsPowBoolean();
unsigned int AddBitwise (unsigned int x); /*tested*/
static void TestAddBitwise();
void PrintIf3BitsOn(unsigned int *numbers_array,
	 size_t numbers_arr_length); /*NOT TESTED YET*/
static void TestPrintIs3BitsOn();
unsigned int Is2and6(unsigned char ch); /*tested*/
static void TestIs2and6();
unsigned int Is2or6(unsigned char ch); /*tested*/
static void TestIs2or6();
unsigned int Swap3and5(unsigned char ch); /*tested*/
static void TestSwap3and5(); 
unsigned int ClosestNumberTo16(unsigned int number);/*tested*/
static void TestClosestNumberTo16();
void SwapBitwise(unsigned int *num1, unsigned int *num2);
static void TestSwap();
unsigned char CountSetBits(int number); /*tested*/
static void TestCountSetBits();

int main()
{
	/*TestPow2();*/
	/*TestIsPow();*/
	/*TestIsPowBoolean();*/
	/*TestAddBitwise();*/
	/*TestPrintIs3BitsOn();*/
	/*TestIs2and6();*/
	/*TestIs2or6();*/
	/*TestSwap();*/
	TestClosestNumberTo16();
	/*TestSwap();*/
	/*TestCountSetBits();*/
	
	return 0;
} 

double Pow2(unsigned int x, int y)
{	
	if (0 > y)
	{
		y = -y;
		x >>= (y - 1);
	}
	else
	{
		x <<= y;
	}
	
	return x;
}


static void TestPow2()
{
	unsigned int expected_5 = 0.25;	
	
	if (Pow2(0, 2) == 0)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
	}
	
	if (Pow2(1, 3) == 8)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Pow2(1, 3));
	}
	
	if (Pow2(2, 4) == 32)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Pow2(2, 4));
	}
	
	if (Pow2(3, 2) == 12)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Pow2(3,2));
	}
	
	if (Pow2(2, -3) == expected_5)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Pow2(2, -3));
	}
}

int IsPow2(unsigned int n)
{
	unsigned int power = 0;
	unsigned int bitwise = 1;
	
	while (n >= (bitwise << power))
	{
		if (n == bitwise << power)
		{
			return 1;
		}
		
		power++;
	}
		
	return 0;
}


static void TestIsPow()
{
	if (IsPow2(0) == 0)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", IsPow2(0));
	}
	
	if (IsPow2(1) == 1)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", IsPow2(1));
	}
	
	if (IsPow2(2) == 1)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", IsPow2(2));
	}
	
	if (IsPow2(16) == 1)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", IsPow2(16));
	}
	
	if (IsPow2(17) == 0)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", IsPow2(17));
	}
}

int IsPowBoolean(unsigned int n)
{
	return n && (!(n & (n-1)));
}


static void TestIsPowBoolean()
{
	if (IsPowBoolean(17) == 0)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", IsPowBoolean(17));
	}
	
	if (IsPowBoolean(16) == 1)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", IsPowBoolean(16));
	}
	
	if (IsPowBoolean(0) == 0)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", IsPowBoolean(0));
	}
	
	if (IsPowBoolean(1) == 1)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", IsPowBoolean(1));
	}
}

unsigned int AddBitwise (unsigned int x)
{
	unsigned int carry = 1;
	unsigned int shifted_number = 0;	
	
	shifted_number = x;
	
	while (0 != (shifted_number & carry))
	{
		x ^= carry;
		carry <<= 1;
		shifted_number >>= carry;
		shifted_number = x;
	}

	
	return x | carry;
}

static void TestAddBitwise()
{
	unsigned int x_1 = 0;
	unsigned int x_2 = 1;
	unsigned int x_3 = 13;
	unsigned int x_4 = 7;
	unsigned int expected_1 = 1;
	unsigned int expected_2 = 2;
	unsigned int expected_3 = 14;	
	unsigned int expected_4 = 8;
	
	if (AddBitwise(x_1) == expected_1)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
	}
	
	if (AddBitwise(x_2) == expected_2)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
	}
	
	if (AddBitwise(x_3) == expected_3)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
	}
	
	if (AddBitwise(x_4) == expected_4)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", AddBitwise(x_4));		
	}
	
}

void PrintIf3BitsOn(unsigned int *numbers_array, 
	size_t numbers_arr_length)
{ 
    unsigned int *number = NULL;
    unsigned int mask = 7;
    int is_equal_to_mask = 0;
    
    assert(NULL != numbers_array);
	number = numbers_array;	
    
    while (0 < numbers_arr_length) 
    /*the numbers of elements reviewed has to be smaller than the array length*/
    {   
        while (0 < *number)
        {
            if (0 == ((*number & mask) ^ mask))   
            {
                is_equal_to_mask = 1;
                
            }
            
            *number >> 1;
        }
        
        if (is_equal_to_mask)
        {
        	printf("%u", *number);
        	is_equal_to_mask = 0;
        }
        
        number++;  
        numbers_arr_length--; 
    }
}


static void TestPrintIs3BitsOn()
{
	unsigned int numbers[] = {0, 1, 2, 7, 13};
	PrintIf3BitsOn(numbers, 5);
}

unsigned int Is2and6(unsigned char ch)
{
	
	return ((ch >> 2) & (ch >> 6) & 1);
}


static void TestIs2and6()
{	
	if (Is2and6(68) == 1)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Is2and6(68));
	}
	
	if (Is2and6(4) == 0)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Is2and6(4));
	}
	
	if (Is2and6(5) == 0)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Is2and6(5));
	}
}

unsigned int Is2or6(unsigned char ch)
{
	return (((ch >> 2) | (ch >> 6))  &  1);
}


static void TestIs2or6()
{
	if (Is2or6(68) == 1)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Is2or6(68));
	}
	
	if (Is2or6(4) == 1)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Is2or6(4));
	}
	
	if (Is2and6(8) == 0)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Is2or6(8));
	}
}

unsigned int Swap3and5(unsigned char ch)
{
	
	return (ch & 0xD7) | (((ch & 8) << 2) | ((ch & 32) >> 2));
}

static void TestSwap3and5()
{
	if (Swap3and5(32) == 8)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Swap3and5(8));
	}
	
	if (Swap3and5(40) == 40)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Swap3and5(40));
	}
	
	if (Swap3and5(7) == 7)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Swap3and5(7));
	}
}

unsigned int ClosestNumberTo16(unsigned int number)
{
	unsigned int sifted_sixteen = 16;
	
	while (number >= (sifted_sixteen << 1))
	{
		sifted_sixteen <<= 1;
	}
	
	return (sifted_sixteen <= number)? sifted_sixteen : 0;
}

static void TestClosestNumberTo16()
{
	unsigned int number_1 = 32;
	unsigned int number_2 = 33;
	unsigned int number_3 = 0;
	unsigned int expected_1 = 32;
	unsigned int expected_2 = 32;
	unsigned int expected_3 = 0;
	/*
	assert(32 == ClosestNumberTo16(32));
	assert(32 == ClosestNumberTo16(33));
	assert(0 == ClosestNumberTo16(0));
	assert(0 == ClosestNumberTo16(1));
	assert(64 == ClosestNumberTo16(65));*/
	
	if (ClosestNumberTo16(65) == 64)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", ClosestNumberTo16(65));
	}
	
	if (ClosestNumberTo16(32) == 32)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", ClosestNumberTo16(32));
	}
	
	if (ClosestNumberTo16(33) == 32)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", ClosestNumberTo16(33));
	}
}

void SwapBitwise(unsigned int *num1, unsigned int *num2)
{
	*num1 = *num1 ^ *num2; 
    *num2 = *num1 ^ *num2;
    *num1 = *num1 ^ *num2;
}

static void TestSwap()
{
	unsigned int num1 = 5;
	unsigned int num2 = 3;
	
	SwapBitwise(&num1, &num2);
	
	if (3 == num1 && 5 == num2)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("FAILURE!\n");
	}
	
}


unsigned char CountSetBits(int number)
{
	unsigned char counter = 0;
	unsigned int mask = 1;
	
	while (0 < number)
	{
		if (1 == (number & mask))
		{
			counter++;
		}
		
		number >>= 1;
	}
	
	return counter;
}

static void TestCountSetBits()
{
	assert(3 == CountSetBits(7));
	assert(0 == CountSetBits(0));
	assert(1 == CountSetBits(1));	
	assert(3 == CountSetBits(13));		
}

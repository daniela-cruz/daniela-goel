#include <stdio.h> /*printf*/
#include <stdlib.h>
#include <math.h> /*pow*/
#include <assert.h> /*assert*/

#define BITS_IN_BYTE 8

double Pow2(unsigned int base, int power);/*tested*/
static void TestPow2(); 
int IsPow2(unsigned int number); /*tested*/
static void TestIsPow();
int IsPowBoolean(unsigned int number); /*tested*/
static void TestIsPowBoolean();
unsigned int AddBitwise (unsigned int x); /*tested*/
static void TestAddBitwise();
unsigned int MirrorNumberLoop(unsigned int number);/**/
static void TestMirrorNumberLoop();
void PrintIf3BitsOn(unsigned int *numbers_array,
	 size_t numbers_arr_length); /*tested*/
static void TestPrintIs3BitsOn();
unsigned int Is2And6(unsigned char binary_number); /*tested*/
static void TestIs2and6();
unsigned int Is2Or6(unsigned char binary_number); /*tested*/
static void TestIs2or6();
unsigned int Swap3and5(unsigned char binary_number); /*tested*/
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
	/*TestMirrorNumberLoop();*/
	/*TestPrintIs3BitsOn();*/
	/*TestIs2and6();*/
	/*TestIs2or6();*/
	/*TestSwap();*/
	/*TestClosestNumberTo16();*/
	TestSwap();
	/*TestCountSetBits();*/
	
	return 0;
} 

double Pow2(unsigned int base, int power)
{	
	if (0 > power)
	{
		power = -power;
		base >>= power;
	}
	else
	{
		base <<= power;
	}
	
	return base;
}


static void TestPow2()
{
	unsigned int expected_5 = 0.125;	
	
	if (Pow2(1, -3) == expected_5)
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
	
	if (Pow2(1024, -3) == 128)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Pow2(2, -3));
	}
}

int IsPow2(unsigned int number)
{
	unsigned int power = 0;
	unsigned int bitwise = 1;
	
	while (number >= (bitwise << power))
	{
		if (number == bitwise << power)
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

int IsPowBoolean(unsigned int number)
{
	return number && (!(number & (number-1)));
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
	unsigned int shifted_number = x;	
	
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
    
    assert(NULL != numbers_array);
	number = numbers_array;	
    
    while (0 < numbers_arr_length)
    {
		if (3 == CountSetBits(*number))
		{
			printf("%u\n", *number);
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


unsigned int MirrorNumberLoop(unsigned int binary_number) 
{ 
    unsigned char number_of_system_bits = BITS_IN_BYTE; 
    unsigned int mirrored_number = 0; 
    unsigned char i = 0; /*also used as a moving mask*/
     
    for (; i < number_of_system_bits; i++) 
    { 
    	/* 
    	If the original number AND'ed with mask moved by i bits left:
    	OR mirrored number with moving mask*/
        if ((binary_number & (1 << i))) 
        {
	        mirrored_number |= 1 << ((number_of_system_bits - 1) - i);
        }
   } 
   
    return mirrored_number; 
} 

static void TestMirrorNumberLoop()
{
	unsigned int numbers[] = {128, 0x01, 0x02, 0x09, 0x07, 0x10};	
	size_t numbers_array_size = 6;
	size_t i = 0;
	
	for (; i < numbers_array_size; i++)
	{
		size_t mirrored = MirrorNumberLoop(numbers[i]);
		printf("Index is: %u\n", i);
		printf("Unmirror output is: %u\n", mirrored);
		assert(numbers[i] == MirrorNumberLoop(mirrored));
		printf("SUCCESS!\n");
	}
}


unsigned int Is2And6(unsigned char binary_number)
{
	size_t bits_to_shift_a = 2;
	size_t bits_to_shift_b = 6;	
	
	return ((binary_number >> bits_to_shift_a) & 
			(binary_number >> bits_to_shift_b) & 1);
}


static void TestIs2and6()
{	
	if (Is2And6(68) == 1)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Is2And6(68));
	}
	
	if (Is2And6(4) == 0)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Is2And6(4));
	}
	
	if (Is2And6(5) == 0)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Is2And6(5));
	}
}

unsigned int Is2Or6(unsigned char binary_number)
{
	size_t bits_to_shift_a = 2;
	size_t bits_to_shift_b = 6;	
	
	return (((binary_number >> bits_to_shift_a) | 
			(binary_number >> bits_to_shift_b))  &  1);
}


static void TestIs2or6()
{
	if (Is2Or6(68) == 1)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Is2Or6(68));
	}
	
	if (Is2Or6(4) == 1)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Is2Or6(4));
	}
	
	if (Is2And6(8) == 0)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
		printf ("\033[0;31m%u\n\033[0m", Is2Or6(8));
	}
}

unsigned int Swap3and5(unsigned char binary_number)
{
	size_t mask = 0xD7;
	size_t right_mask = 8;
	size_t left_mask = 32;
	size_t bits_shifter = 2;
	
	return (binary_number & mask) | 
			(((binary_number & right_mask) << bits_shifter) | 
			((binary_number & left_mask) >> bits_shifter));
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
	unsigned int sixteen_denomenator = 16;
	
	while (number >= (sixteen_denomenator << 1))
	{
		sixteen_denomenator <<= 1;
	}
	
	return (sixteen_denomenator <= number) ? sixteen_denomenator : 0;
}

static void TestClosestNumberTo16()
{
	
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
	if (num1 != num2)
	{
		*num1 = *num1 ^ *num2; 
		*num2 = *num1 ^ *num2;
		*num1 = *num1 ^ *num2;
	}
}

static void TestSwap()
{
	unsigned int num1 = 5;
	unsigned int num2 = 3;
	
	SwapBitwise(&num1, &num1);
	
	if (5 == num1 && 3 == num2)
	{
		printf("GRRREAT SUCCESS!\n");
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

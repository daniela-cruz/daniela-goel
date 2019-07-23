#include <stdio.h> /*printf*/
#include <stdlib.h>
#include <math.h> /*pow*/
#include <assert.h> /*assert*/

double Pow2(unsigned int x, int y);
int IsPow2(unsigned int n);
int IsPowBoolean(unsigned int n);
unsigned int AddBitwise (unsigned int x); /*tested*/
static void TestAddBitwise();
void PrintIf3BitsOn(unsigned int *numbers_array, unsigned int numbers_arr_length);
unsigned int Is2and6(unsigned char ch);
unsigned int Is2or6(unsigned char ch);
unsigned int Swap3and5(unsigned char ch);
unsigned int ClosestNumberTo16(unsigned int number);/*tested*/
static void TestClosestNumberTo16();

int main()
{
	TestAddBitwise();
	/*TestClosestNumberTo16();*/
	
	return 0;
} 

double Pow2(unsigned int x, int y)
{	
	if (0 > y)
	{
		y = -y;
		x >> y;
	}
	else
	{
		x << y;
	}
	
	return x;
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


int IsPowBoolean(unsigned int n)
{
	return n && (!(n & (n-1)));
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
	unsigned int numbers_arr_length)
{ 
    unsigned int *number = NULL;
    unsigned int mask = 7, moving_mask = 7;
    
    assert(NULL != numbers_array);
	number = numbers_array;	
    
    while (number - numbers_array < numbers_arr_length) 
    /*the numbers of elements reviewed has to be smaller than the array length*/
    {
        moving_mask = mask;
        
        while (0 != (*number & moving_mask))
        {
            if ((*number & mask) == mask)   
            {
                printf("%u", *number);
                break;
            }
            
            moving_mask <<1;  
        }
        
        number++;   
    }
}

unsigned int Is2and6(unsigned char ch)
{
	
	return ((ch >> 0x01) & (ch >> 0x05) & 0x01);
}


unsigned int Is2or6(unsigned char ch)
{
	return ~(((ch >> 1) | (ch >> 5))  &  0x01);
}

unsigned int Swap3and5(unsigned char ch)
{
	
	return (ch & 0xEB) | (((ch & 0x04) << 2) | ((ch & 0x1) >> 2));
}

unsigned int ClosestNumberTo16(unsigned int number)
{
	unsigned int shifted = 1;
	
	while (number >= shifted)
	{
		shifted <<= 4;
	}
	
	return (shifted <= number)? shifted : 0;
}

static void TestClosestNumberTo16()
{
	unsigned int number_1 = 32;
	unsigned int number_2 = 33;
	unsigned int number_3 = 0;
	unsigned int expected_1 = 32;
	unsigned int expected_2 = 32;
	unsigned int expected_3 = 0;
	
	if (ClosestNumberTo16(number_1) == expected_1)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf ("\033[0;31mFAILURE!\n\033[0m");
	}
	
	if (ClosestNumberTo16(number_2) == expected_2)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("FAILURE!\n");
	}
	
	if (ClosestNumberTo16(number_3) == expected_3)
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("FAILURE!\n");
	}
}

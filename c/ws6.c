#include <stdio.h>
#include <stdlib.h>
#include <math.h> /*pow*/
#include <assert.h> /*assert*/

double Pow2(unsigned int x, int y);
/*int IsPow2(unsigned int n);*/
int IsPowBoolean(unsigned int n);
int AddBitwise (unsigned int x);
void PrintIf3BitsOn(unsigned int *numbers_array, unsigned int numbers_arr_length);
unsigned int Is2and6(unsigned char ch);
unsigned int Is2or6(unsigned char ch);
unsigned int Swap3and5(unsigned char ch);

int main()
{
	unsigned char x = 0x22;
	
	printf("%u\n", Is2and6(x));
	/*printf("%f", Pow2(x, y));*/
	/*printf("%d",IsPow2(x));*/ 
	
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

/*
int IsPow2(unsigned int n)
{
	int is_exp = 0;
	unsigned int base = 2;
	unsigned int power = 0;
	double exp = 1.;
	unsigned int bitwise = 1;
	
	bitwise = n;
	exp = n;
	
	while (0 < (n >> power))
	{
		if ((exp / (pow(base, power))) == (bitwise >> power))
		{
			is_exp = 1;
			power++;
		}
		else
		{
			return 0;
		}
	}
		
	return is_exp;
}

*/
int IsPowBoolean(unsigned int n)
{
	return n && (!(n & (n-1)));
}


int AddBitwise (unsigned int x)
{
  unsigned int carry = 1;
  int is_in_loop = 0;
  
	while (0 != (x & carry))
	{
		carry <<= 1;
		is_in_loop = 1;
	}
	
	if (is_in_loop)
	{
		
		x |= carry;
	}
	
	carry = 1;
	  
  return x ^ carry;
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

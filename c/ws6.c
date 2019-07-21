#include <stdio.h>
#include <stdlib.h>
#include <math.h> /*pow*/

double Pow2(unsigned int x, int y);
int IsPow2(unsigned int n);

int main()
{
	unsigned int x = 32;
	int y = -2;
	
	/*printf("%f", Pow2(x, y));*/
	/*printf("%d",IsPow2(x));*/ 
	
	return 0;
} 

double Pow2(unsigned int x, int y)
{
	double result = x;
	
	if (0 > y)
	{
		y = -y;
		
		result = x >> y;
	}
	else
	{
		result = x << y;
	}
	
	return result;
}


int IsPow2(unsigned int n)
{
	int is_exp = 0;
	int base = 2;
	double power = 0;
	double exp = 1;
	int bitwise = 1;
	
	bitwise = n;
	exp = n;
	
	while (0 < n)
	{
		if ((exp / (pow(2, power))) == (bitwise >> power))
		{
			is_exp = 1;
			power++;
		}
		else
		{
			return 0;
		}
		
		exp = (exp / (pow(2, power)));
	}
		
	return is_exp;
}


int IsPowBoolean(unsigned int n)
{
	return n && (!(n & (n-1)));
}

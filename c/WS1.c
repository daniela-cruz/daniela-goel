#include <stdio.h>
#include <stdlib.h>

float BASE = 10.00;

float power(int power); //ECERCISE 4- calculate result of powers of BASE

void main()
{
	float exe4 = power(3);
	
	printf("10 to the power of 3 is: %f\n", exe4);
	
	exit(0);	
}

//===EXIERCISE 4===
float power(int power)
{
	float result = 1.00;
	
	if (power < 0)
	{
		BASE = 1/BASE;
		power = -power;
	}
	
	for(int i=0; i<power; i++)
	{
		result *= BASE;
	}
	
	return result;
}

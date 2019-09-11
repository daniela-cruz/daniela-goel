#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#define BASE 2

static long Pow2(unsigned int x, unsigned y);
static void Pow2Test();

static size_t IsPowerOf2 (unsigned int n);
static void IsPowerOf2Test();

int main()
{
	Pow2Test();
	IsPowerOf2Test();
	
	return 0;
}

static long Pow2(unsigned int x, unsigned int y)
{
	return x << y;
}

static void Pow2Test()
{
	long expected_results[4][4] = {	{0, 0, 0, 0},
												{1, 2, 4, 8}, 
												{2, 4, 8, 16}, 
												{3, 6, 12, 24}};
	size_t x[] = {0, 1, 2, 3};
	size_t y[] = {0, 1, 2, 3};
	size_t i = 0, j = 0;
	
	printf("\nPow2 test:\n");
	
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (expected_results[i][j] == Pow2(x[i], y[j]))
			{
				printf("SUCCESS!!\n");
			}
			else
			{
				printf("Failed test. Returned value is %d\n");
			}
		}
	}
}

static size_t IsPowerOf2 (unsigned int n)
{
	float num = (float)n;
	size_t result = 1;
	size_t i = 1;
	
	for (; i <= n / 2; i++)
	{
		if ((n >> i) != (num / (i * BASE)))
		{
			result = 0;
			break;
		}
		
		num /= (i * BASE);
	}
	
	return result;
}

static void IsPowerOf2Test()
{
	printf("Is 7 power of 2? 0 = no, 1 = yes. Answer: %ld\n", IsPowerOf2(7));
}

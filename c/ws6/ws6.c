#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#define BASE 2

static long Pow2(unsigned int x, unsigned y);
static size_t IsPowerOf2 (unsigned int n);
static void IsPowerOf2Test();

int main()
{
	/* test */
	IsPowerOf2Test();
	
	return 0;
}

static long Pow2(unsigned int x, unsigned int y)
{
	return x << y;
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

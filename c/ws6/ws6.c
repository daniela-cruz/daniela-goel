#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#define BASE 2
#define BITS_IN_BYTE sizeof(size_t) * 8


static long Pow2(unsigned int x, unsigned y);
static void Pow2Test();

static size_t IsPowerOf2 (unsigned int n);
static size_t IsOowerOf2NoLoop(unsigned int n);
static void IsPowerOf2Test();

static size_t AddBitwise(size_t num);
static void AddBitwiseTest();

static void FindNumsWith3BitsOn(size_t num_arr[], size_t arr_size);
static size_t CountBits(size_t num);
static void FindNumsWith3BitsOnTest();

static unsigned int MirrorLoopBitwise(unsigned int binary_number);
static void TestMirrorNumberLoop();

static size_t AreBits2And6On(size_t num);
static size_t AreBits2Or6On(size_t num);
static void AreBits2And6OnTest();

static unsigned int Swap3and5(unsigned char binary_number);
static void Swap3and5Test();

int main()
{
	Pow2Test();
	IsPowerOf2Test();
	AddBitwiseTest();
	FindNumsWith3BitsOnTest();
	TestMirrorNumberLoop();
	AreBits2And6OnTest();
	Swap3and5Test();
	
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
	printf("Is 7 power of 2? 0 = no, 1 = yes. Answer: %ld\n", IsOowerOf2NoLoop(8));
}

static size_t IsOowerOf2NoLoop(unsigned int n)
{
	return (((n - 1) & n) == 0) ? 1:0;
}

static size_t AddBitwise(size_t num)
{
	size_t mask = 0xFFFF;
	size_t lsb_mask = 0x01;
	
	while (0 != (num & lsb_mask))
	{
		mask <<= 1;
		lsb_mask <<= 1;
	}
	
	return (num & mask) | lsb_mask;
}

static void AddBitwiseTest()
{
	size_t num = 27;
	size_t expected_result = 28;
	
	
	if (expected_result == AddBitwise(num))
	{
		printf("SUCCESS!!\n");
	}
	else
	{
		printf("Failure. Result is: %ld but expected is: %ld\n", AddBitwise(num), expected_result);
	}
}

static void FindNumsWith3BitsOn(size_t num_arr[], size_t arr_size)
{
	size_t num_ptr = 0;
	size_t i = 0;
	const size_t bit_limit = 3;
	size_t mask = 1;
	
	assert(num_arr);
	
	for (; i < arr_size; i++)
	{
		num_ptr = num_arr[i];
		if (bit_limit == CountBits(num_arr[i]))
		{
			printf("The number %ld has exactly %ld bits on.\n", num_ptr, bit_limit);
		}
	}
}

static size_t CountBits(size_t num)
{
	size_t bit_counter = 0;
	size_t mask = 1;
	
	while (0 < num)
	{
		if (1 == (num & mask))
		{
			bit_counter++;
		}
		
		num >>= 1;
	}
	
	return bit_counter;
}

static void FindNumsWith3BitsOnTest()
{
	size_t num_arr[] = {0, 1, 7, 22, 201};
	size_t arr_size = 5;
	
	FindNumsWith3BitsOn(num_arr, arr_size);
}

static unsigned int MirrorLoopBitwise(unsigned int binary_number)
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
		size_t mirrored = MirrorLoopBitwise(numbers[i]);
		printf("Index is: %u\n", i);
		printf("Unmirror output is: %u\n", mirrored);
		assert(numbers[i] == MirrorLoopBitwise(mirrored));
		printf("SUCCESS!\n");
	}
}

static size_t AreBits2And6On(size_t num)
{
	size_t mask = 68;
	
	return ((num & mask) == mask) ? 1 : 0;
}

static size_t AreBits2Or6On(size_t num)
{
	size_t mask_2 = 4;
	size_t mask_6 = 64;
	
	return (((num & mask_2) == mask_2) || ((num & mask_6) == mask_6)) ? 1 : 0;
}

static void AreBits2And6OnTest()
{
	printf("\nBits 2 and 6 test:\n");
	if (1 == AreBits2And6On(70))
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("Failure, received result is: %ld\n", AreBits2And6On(70));
	}
	
	printf("\nBits 2 OR 6 test:\n");
	if (1 == AreBits2Or6On(6))
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("Failure, received result is: %ld\n", AreBits2Or6On(6));
	}
}

static unsigned int Swap3and5(unsigned char binary_number)
{
	size_t mask = 0xD7;
	size_t right_mask = 8;
	size_t left_mask = 32;
	size_t bits_shifter = 2;
	
	return (binary_number & mask) | 
			(((binary_number & right_mask) << bits_shifter) | 
			((binary_number & left_mask) >> bits_shifter));
}

static void Swap3and5Test()
{
	printf("\nSwap 3 and 5 test:\n");
	if (32 == Swap3and5(8))
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("Failure, received result is: %d\n", Swap3and5(8));
	}
}

static void PrintFloat(float num)
{
	struct float_t
	{
		size_t m:23;
		size_t e:8;
		size_t s:1;
	};
	
	printf("\nFloat is: %ld%d%d\n", float_t.s, float_t.e, float_t.m);
}

static size_t Denominator16(size_t num)
{
	size_t bit_shifter = 4;
	size_t denominator = 1;
	
}

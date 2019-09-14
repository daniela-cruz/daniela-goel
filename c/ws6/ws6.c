#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#define BASE 2
#define BITS_IN_BYTE sizeof(size_t) * 8

static const size_t BitReverseTable256[256] = 
{
#   define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#   define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#   define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
    R6(0), R6(2), R6(1), R6(3)
};

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
static size_t MirrorBitwiseNoLoop(size_t num);
static void TestMirrorNumberLoop();

static size_t AreBits2And6On(size_t binary_number);
static size_t AreBits2Or6On(size_t binary_number);
static void AreBits2And6OrTest();

static unsigned int Swap3and5(unsigned char binary_number);
static void Swap3and5Test();

static size_t Denominator16(size_t num);

static void SwapBitwise(unsigned int *num1, unsigned int *num2);
static void SwapBitwiseTest();

static void PrintFloat(float num);

int main()
{/*
	Pow2Test();
	IsPowerOf2Test();
	AddBitwiseTest();
	FindNumsWith3BitsOnTest();*/
	TestMirrorNumberLoop();
	/*AreBits2And6OrTest();
	Swap3and5Test();
	SwapBitwiseTest();
	Denominator16(49);*/
	PrintFloat(-79.89998);
	
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
	
	printf("\nLoopMirror test:\n");
	for (; i < numbers_array_size; i++)
	{
		size_t mirrored = MirrorLoopBitwise(numbers[i]);
		printf("Index is: %lu\n", i);
		printf("Unmirror output is: %lu\n", mirrored);
		assert(numbers[i] == MirrorLoopBitwise(mirrored));
		printf("SUCCESS!\n");
	}
	
	printf("\nNo loop Mirror test:\n");
	for (; i < numbers_array_size; i++)
	{
		size_t mirrored = MirrorBitwiseNoLoop(numbers[i]);
		printf("Index is: %lu\n", i);
		printf("Unmirror output is: %lu\n", mirrored);
		assert(numbers[i] == MirrorBitwiseNoLoop(mirrored));
		printf("SUCCESS!\n");
	}
}

static size_t MirrorBitwiseNoLoop(size_t num)
{
	size_t reverse_32_bit_val; /* will reverse 8 bits at a time */
	size_t mirrored = 0; 
	
	mirrored = num;
	
	/* using the LUT: */
	mirrored = 	(BitReverseTable256[reverse_32_bit_val & 0xff] << 24) | 
						(BitReverseTable256[(reverse_32_bit_val >> 8) & 0xff] << 16) | 
						(BitReverseTable256[(reverse_32_bit_val >> 16) & 0xff] << 8) |
						(BitReverseTable256[(reverse_32_bit_val >> 24) & 0xff]);
	
	return mirrored;
}

static size_t AreBits2And6On(size_t binary_number)
{
	size_t bits_to_shift_a = 2;
	size_t bits_to_shift_b = 6;	
	
	return ((binary_number >> bits_to_shift_a) & 
			(binary_number >> bits_to_shift_b) & 1);
}

static size_t AreBits2Or6On(size_t binary_number)
{
	size_t bits_to_shift_a = 2;
	size_t bits_to_shift_b = 6;	
	
	return (((binary_number >> bits_to_shift_a) | 
			(binary_number >> bits_to_shift_b))  &  1);
}

static void AreBits2And6OrTest()
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

static size_t Denominator16(size_t num)
{ 
	size_t denominator = 4;
	
	return num >> 4;
	
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

static void SwapBitwiseTest()
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

static void PrintFloat(float num)
{
    struct float_structure
    {
        size_t mantissa : 23;
        size_t exponent : 8;
        size_t is_signed: 1;
    };
    struct float_structure *float_segment = (struct float_structure *)&num;

    printf("Decimal point value: %1$u\n",float_segment->mantissa);
    printf("Exponent value: %1$u\n",float_segment->exponent);
    printf("Signed bit: %1$u\n",float_segment->is_signed);
}


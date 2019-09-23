#include <stddef.h> /* size_t */
#include <string.h> /* strcat */
#include <limits.h> /* UCHAR_MAX */
#include <stdio.h>

#include "bitarray.h"

static void BitArrCountLUTInit();
static void BitArrMirrorLUTInit();

typedef unsigned char lut_bits;
static lut_bits count_lut[UCHAR_MAX + 2] = {0};
static lut_bits mirror_lut[UCHAR_MAX + 2] = {0};

const size_t wordsize = sizeof(bit_arr_t) * 8;

int main()
{
	bit_arr_t arr = 3;
	
	arr = BitArrMirrorLUT(arr);
	printf("%lu\n", arr);
	
	arr = BitArrMirrorLUT(arr);
	
	printf("%lu\n", BitArrMirrorLUT(arr));
	
	return 0;
}

bit_arr_t BitArrCountOnLUT(bit_arr_t arr)
{	
	int count = 0;
	bit_arr_t mask = UCHAR_MAX - 1;

	if (0 == (count_lut[UCHAR_MAX + 1]))
	{
		BitArrCountLUTInit();
	}
	
	for (;arr != 0; arr >>= sizeof(bit_arr_t))
	{
		count += count_lut[arr & mask];
	}
	
	return count;
}

bit_arr_t BitArrMirrorLUT(bit_arr_t arr)
{
	bit_arr_t new_arr = 0;
	unsigned char start = 0;
	unsigned char end = wordsize - sizeof(bit_arr_t);
	
	if(mirror_lut[UCHAR_MAX + 1] == 0)
	{
		BitArrMirrorLUTInit();
	}
	
	for (start = 0 ; start < end ; start += wordsize / sizeof(bit_arr_t), end -= wordsize / sizeof(bit_arr_t))
	{
		bit_arr_t start_mask = 255;
		bit_arr_t end_mask = 255;
		
		start_mask &= arr;
		end_mask &= arr >> end;
		
		new_arr |= (bit_arr_t) mirror_lut[start_mask] << end;
		new_arr |= (bit_arr_t) mirror_lut[end_mask] << start;
	}
		
	return new_arr;
}


static void BitArrCountLUTInit()
{
	int i = 0;
		
	for(; i < UCHAR_MAX; i++)
	{
		count_lut[i] = BitArrCountOn(i);
	}
	
	count_lut[UCHAR_MAX + 1] = 1;
}

static void BitArrMirrorLUTInit()
{
	size_t i = 0;
	bit_arr_t mask = 0;
		
	for(; i < UCHAR_MAX; i += (wordsize / 8))
	{
		bit_arr_t temp_arr = i;
		size_t j = 0;
		for(j = 1; j < wordsize / 8; j++)
		{
			temp_arr <<= 8;
			temp_arr += i+j;
		}
		
		temp_arr = BitArrMirror(temp_arr);
		
		mask = 255;
		
		for(j = 0; j < wordsize / 8; j++)
		{
			mask &= temp_arr;
			mirror_lut[i+j] = (unsigned char) mask;
			mask = 255;
			temp_arr >>= 8;
		}
		
	}
	mirror_lut[UCHAR_MAX + 1] = 1;
}


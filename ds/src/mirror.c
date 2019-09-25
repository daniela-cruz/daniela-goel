#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#define __STDC_WANT_IEC_60559_BFP_EXT__
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <string.h> /* strlen */
#include <limits.h> /* UCHAR_MAX */

#include "bitarray.h" /* all bit array functions below */

bit_arr_t BitArrMirrorLUT2(bit_arr_t arr);
static void BitArrMirrorInitLUT2();
static char BitArrMirrorFlipperLUT2(char arr);
static char BitArrSetLUT2(char arr, size_t bit_location, int is_set);

static bit_arr_t bit_mirror_LUT[UCHAR_MAX + 2] = {0};
const size_t word_size = sizeof(bit_arr_t) * CHAR_BIT;

static void MirrorLUTTest();

int main()
{
	MirrorLUTTest();
	return 0;
}

bit_arr_t BitArrMirrorLUT2(bit_arr_t arr)
{
	if (1 != bit_mirror_LUT[UCHAR_MAX + 1])
	{
		BitArrMirrorInitLUT2();
	}
	
	return bit_mirror_LUT[arr];
}


static void BitArrMirrorInitLUT2()
{
	bit_arr_t arr = 0;
	bit_arr_t mask = 0xFF;
	bit_arr_t temp = 0;
	size_t i = 0 , j = 0;

	for (i = 0; i < UCHAR_MAX; i ++)
	{
		for (j = 1; j < CHAR_BIT; j++)
		{
			arr = i;
			arr >>= CHAR_BIT * j;
			arr &= mask;
			arr = BitArrMirrorFlipperLUT2(arr);
			/*temp |= arr;*/
			/*temp <<= CHAR_BIT * j;*/
			bit_mirror_LUT[i] = arr;
		}
		
		temp = 0;
	}

	bit_mirror_LUT[UCHAR_MAX + 1] = 1; /* last sentinel to mark the LUT is already initialized */
}


/* Exactly like BitArrMirro but function receives char */
static char BitArrMirrorFlipperLUT2(char arr)
{
	char mask_r = 1;
	char mask_l = 1;
	int first = 0, last = 0;
	size_t arr_size = CHAR_BIT;
	size_t i = 0;
	
	mask_l <<= (arr_size - 1); /* mask_l is pushed left to msb */
	
	for (i = 0; i < arr_size / 2 ; i++, mask_r <<= 1, mask_l >>= 1)
	{
		first = ((arr & mask_r) == mask_r); /* first will receive arr's lsb value, 1 if the bit is on 0 if off */
		last = ((arr & mask_l) == mask_l); /* last will receive arr's msb value, 1 if the bit is on 0 if off */
		
		arr = BitArrSetLUT2(arr, i, last); /* move value of last to first */
		arr = BitArrSetLUT2(arr, (arr_size - i - 1), first); /* move value of first to last */
	}
		
	return arr;
}

/* set on a single bit within the array */
static char BitArrSetLUT2(char arr, size_t bit_location, int is_set)
{
	bit_arr_t mask = 1;
	
	mask <<= bit_location;
	
	if (0 == is_set)
	{
		arr &= ~mask;
		
		return arr;
	}
	
	return arr |= mask;
}

static void MirrorLUTTest()
{
	size_t i = 0;
	bit_arr_t arr[] = {1, 0, 3, 255};
	char *dest = NULL;
	
	dest = malloc(65);
	
	printf("\nMirror LUT test:\n");
	
	BitArrMirrorLUT2(arr[i]);
	
	for (i = 0; i < 4; i++)
	{
		arr[i] = BitArrMirrorLUT2(arr[i]);
		dest = BitArrToString(dest, arr[i]);
		printf("Mirror of %ld is: %s\n", i, dest);
	}
	
	free(dest);
}

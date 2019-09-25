#include <stdio.h> /* printf */
#define __STDC_WANT_IEC_60559_BFP_EXT__
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <string.h> /* strlen */
#include <limits.h> /* UCHAR_MAX */


#include "bitarray.h" /* all bit arr functions below */

size_t BitArrCountOnLUT(bit_arr_t arr);
static void BitArrInitLUT(); /* will init on first BitArrCountOnLUT call */
static void Reverse (char *buffer);

bit_arr_t BitArrMirrorLUT(bit_arr_t arr);
static void BitArrMirrorInitLUT();
static unsigned char BitArrMirrorFlipperLUT2(char arr);
static char BitArrSetLUT2(char arr, size_t bit_location, char is_set);

static unsigned char CharMirror(unsigned char byte);
static void BitArrInitMirrorLUT(); /* will init on first BitArrMirrorLUT call */
static char BitArrSetLUT(char arr, size_t bit_location, int is_set);

static bit_arr_t bit_arr_LUT[UCHAR_MAX + 2] = {0};
static bit_arr_t bit_mirror_LUT[UCHAR_MAX + 2] = {0};
const size_t word_size = sizeof(bit_arr_t) * CHAR_BIT;

/* create a LUT that contains number of set bits of each number from 0 to 255 */
static void BitArrInitLUT()
{
	bit_arr_t i = 0, j = 0, count = 0;
	bit_arr_t arr = 0;
	bit_arr_t mask = 0xFF;

	for (i = 0; i < UCHAR_MAX + 2; i++)
	{
		arr = i;
		
		for (j = 0; j < ((word_size / CHAR_BIT) - 1); j++)
		{
			arr &= mask;
			count += BitArrCountOn(arr);
			arr >>= CHAR_BIT;
		}
		
		bit_arr_LUT[i] = count;
		count = 0;
	}
	
	bit_arr_LUT[UCHAR_MAX + 1] = 1;
}

size_t BitArrCountOnLUT(bit_arr_t arr)
{
	if (1 != bit_arr_LUT[UCHAR_MAX + 1])
	{
		BitArrInitLUT();
	}
	
	return bit_arr_LUT[arr];
}

/*
*	LUT for Mirror bit arr initialization: 
*/
bit_arr_t BitArrMirrorLUT(bit_arr_t arr)
{
	if (1 != bit_mirror_LUT[UCHAR_MAX + 1])
	{
		BitArrMirrorInitLUT2();
	}
	
	/*
	* MIRROR BYTE BY BYTE USING THE LUT TABLE
	*/
	
	return arr;
}

static void BitArrMirrorInitLUT()
{
	unsigned char arr = 0;
	size_t i = 0;

	for (i = 1; i < CHAR_BIT; i++)
	{
		arr = i;
		arr = BitArrMirrorFlipperLUT2(arr); /* TODO: check if flipper works*/
		bit_mirror_LUT[i] = arr;
	}

	bit_mirror_LUT[UCHAR_MAX + 1] = 1; /* last sentinel is set to 1 indicating lut is initialized*/
}

/* Exactly like BitArrMirror but function receives char */
static unsigned char BitArrMirrorFlipperLUT2(char arr)
{
	char mask_r = 1;
	char mask_l = 1;
	char first = 0, last = 0;
	size_t arr_size = 0; 
	size_t i = 0;
	
	arr_size = CHAR_BIT;
	mask_l <<= (arr_size - 1); /* mask_l is pushed left to msb */
	
	for (; i < arr_size / 2 ; i++, mask_r <<= 1, mask_l >>= 1)
	{
		first = ((arr & mask_r) == mask_r); /* first will receive arr's lsb value, 1 if the bit is on 0 if off */
		last = ((arr & mask_l) == mask_l); /* last will receive arr's msb value, 1 if the bit is on 0 if off */
		
		arr = BitArrSetLUT2(arr, i, last); /* move value of last to first */
		arr = BitArrSetLUT2(arr, (arr_size - i - 1), first); /* move value of first to last */
	}
		
	return arr;
}

/* set on a single bit within the array */
static char BitArrSetLUT2(char arr, size_t bit_location, char is_set)
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

static unsigned char CharMirror(unsigned char byte)
{
	int is_on_r = 0, is_on_l = 0;
	size_t mask_r = 1, mask_l = 1;
	int i = 0;

	mask_l <<= (CHAR_BIT - 1);

	for (; i < CHAR_BIT / 2; i++, mask_r <<= 1, mask_l >>= 1)
	{
		is_on_r = ((mask_r & byte) == mask_r);
		is_on_l = ((mask_l & byte) == mask_l);

		byte = BitArrSet(byte, i, is_on_l);
		byte = BitArrSet(byte, CHAR_BIT -1 - i, is_on_r);
	}
 
	return byte;
}

static size_t *BitArrInitMirrorLUT()
{
	size_t i = 0;

	for (; UCHAR_MAX + 2 > i; i++)
	{
		bit_mirror_LUT[i] = CharMirror(i);
	}
	
	bit_mirror_LUT[UCHAR_MAX + 1] = 1;
}


bit_arr_t BitArrMirrorLUT(bit_arr_t arr)
{
	unsigned char lsb = 0, msb = 0;
	size_t mask_r = 0xFF, mask_l = 0xFF;
	int i = 0;

	for (i = 0; i < CHAR_BIT / 2; i++)
	{
		lsb = bit_mirror_LUT[mask_r & (arr >> i * CHAR_BIT)];
		msb = bit_mirror_LUT[mask_l & (arr >> (UCHAR_MAX + 1 - i * CHAR_BIT))];

		arr = arr & ~(mask_r << i* CHAR_BIT);
		arr = arr | (msb << (i * CHAR_BIT));

		arr = arr & ~(mask_l << UCHAR_MAX + 1 - i * CHAR_BIT);
		arr = arr | (lsb << (UCHAR_MAX + 1 - i * CHAR_BIT));
	}
 
	return arr;
}


/* 1 if a particular bit is set on else 0 */
int BitArrIsOn(bit_arr_t arr, int bit_location)
{
	bit_arr_t mask = 1;

	mask <<= bit_location;
	
	return (arr & mask) ? 1 : 0;
}


/* 1 if a particular bit is set off else 0 */
int BitArrIsOff(bit_arr_t arr, int bit_location)
{
	bit_arr_t mask = 1;
	
	mask <<= bit_location;
	
	return (~(arr & mask)) ? 1 : 0;
}

/* set on a single bit within the arr */
bit_arr_t BitArrSet(bit_arr_t arr, size_t bit_location, int is_set)
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

/* set on all bits in arr */
bit_arr_t BitArrSetAll(bit_arr_t arr)
{
	arr |= ~0;
	
	return arr;
}

/* set off all bits in arr*/
bit_arr_t BitArrResetAll(bit_arr_t arr)
{
	arr &= 0;
	
	return arr;
}

/* set a particular bit on */
bit_arr_t BitArrSetOn(bit_arr_t arr, int n)
{
	bit_arr_t mask = 1;
	
	mask <<= n;
	arr |= mask;
	
	return arr;
}

/* set a particular bit off. If the user provided wrong input there's an undefined behavior */
bit_arr_t BitArrSetOff(bit_arr_t arr, int n)
{
	bit_arr_t mask = 1;
	
	mask <<= n;
	arr &= (~mask);
	
	return arr;
}

/* rotate arr left n times */
bit_arr_t BitArrRotL(bit_arr_t arr, size_t n)
{
	bit_arr_t temp = 0;
	bit_arr_t mask = 0;
	size_t arr_size = 0;
	size_t i = 0;
	
	arr_size =  sizeof(bit_arr_t) * 8;
	n %= arr_size;
	
	/* create a mask with word - n bits */
	for (; i < arr_size - n; i++)
	{
		mask = 1;
		mask <<= 1;
	}
	
	/* shift temp n times left */
	temp <<= n;
	
	/* get n portion of arr using  arr AND mask */
	temp = mask & arr;
	
	/* shift arr n times right */
	arr <<= arr_size - n;
	
	return temp | arr;
}

/* rotate arr right n times */
bit_arr_t BitArrRotR(bit_arr_t arr, size_t n)
{
	bit_arr_t temp = 0;
	bit_arr_t mask = 0;
	size_t arr_size = 0;
	size_t i = 0;
	
	arr_size =  sizeof(bit_arr_t) * 8;
	n %= arr_size;
	
	/* create a mask with word - n bits */
	for (; i < arr_size - n - 1; i++)
	{
		mask = 1;
		mask <<= 1;
	}
	
	/* get n portion of arr using  arr AND mask */
	temp = mask & arr;
	
	/* shift temp n times left */
	temp <<= n;
	
	/* shift arr n times right */
	arr >>= arr_size - n;
	
	return temp | arr;
}

/* flip a single bit */
bit_arr_t BitArrFlip(bit_arr_t arr, int bit_location)
{
	bit_arr_t mask = 1;
	
	mask <<= bit_location;
	mask &= arr;
	
	if (0 != mask)
	{
		mask = ~mask;
		arr &= mask;
	}
	else
	{
		arr |= mask;
	}
	
	return arr;
}

/* count number of set bits */
size_t BitArrCountOn(bit_arr_t arr)
{
	bit_arr_t mask = 1;
	size_t counter = 0;

	while (0 < arr)
	{
		if (1 == (arr & mask))
		{
			counter++;
		}
		
		arr >>= 1;
	}

	return counter;
}

/* count number of off bits */
size_t BitArrCountOff(bit_arr_t arr)
{
	bit_arr_t mask = 1;
	size_t counter = 0;
	
	while (0 < arr)
	{
		if (0 == (arr & mask))
		{
			counter++;
		}
		
		arr >>= 1;
	}
	
	return counter;
}

/* mirror bit arr */
bit_arr_t BitArrMirror(bit_arr_t arr)
{
	bit_arr_t mask_r = 1;
	bit_arr_t mask_l = 1;
	int first = 0, last = 0;
	size_t arr_size = 0;
	size_t i = 0;
	
	arr_size =  sizeof(bit_arr_t) * 8; 
	mask_l <<= (arr_size - 1); /* mask_l is pushed left to msb */
	
	for (i = 0; i < arr_size / 2 ; i++, mask_r <<= 1, mask_l >>= 1)
	{
		first = ((arr & mask_r) == mask_r); /* first will receive arr's lsb value, 1 if the bit is on 0 if off */
		last = ((arr & mask_l) == mask_l); /* last will receive arr's msb value, 1 if the bit is on 0 if off */
		
		arr = BitArrSet(arr, i, last); /* move value of last to first */
		arr = BitArrSet(arr, (arr_size - i - 1), first); /* move value of first to last */
	}
		
	return arr;
}

/* convert arr to a string */
char *BitArrToString(char *dest, bit_arr_t src)
{
	size_t i = 0;
	size_t arr_size = 0;
	
	arr_size =  sizeof(bit_arr_t) * 8; 
	
	for (i = 0 ; i < arr_size ; i++)
	{
		*(dest + i) = (src % 2) + '0' ;
		src /= 2;
	}
	
	Reverse(dest);
	
	return dest;	
}

static void Reverse (char *buffer)
{
	char temp;
	size_t i = 0;
	size_t len = 0;
	
	len = strlen(buffer) -1;
	
	for (i=0 ; i <= len / 2 ; i++)
	{
		temp = *(buffer + i);
		*(buffer + i) = *(buffer + len - i);
		*(buffer + len - i) = temp;
	}	
}	
	



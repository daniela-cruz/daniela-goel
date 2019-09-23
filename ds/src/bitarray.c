#include <assert.h> /* assert */
#include <stddef.h> /* size_t */

#include "bitarray.h" /* all bit array functions below */

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

/* set on a single bit within the array */
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

/* set on all bits in array */
bit_arr_t BitArrSetAll(bit_arr_t arr)
{
	arr |= ~0;
	
	return arr;
}

/* set off all bits in array*/
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
	for (; i < arr_size - n; i++)
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

/* mirror bit array */
bit_arr_t BitArrMirror(bit_arr_t arr)
{
	bit_arr_t mask_r = 1;
	bit_arr_t mask_l = 1;
	int first = 0, last = 0;
	size_t arr_size = 0;
	size_t i = 0;
	
	arr_size =  sizeof(bit_arr_t) * 8; 
	mask_l <<= (arr_size - 1); /* mask_l is pushed left to msb */
	
	for (i = 0; i < arr_size / 2 ; i++)
	{
		first = ((arr & mask_r) == mask_r); /* first will receive arr's lsb value, 1 if the bit is on 0 if off */
		last = ((arr & mask_l) == mask_l); /* last will receive arr's msb value, 1 if the bit is on 0 if off */
		
		arr = BitArrSet(arr, i, last); /* move value of last to first */
		arr = BitArrSet(arr, (arr_size - i - 1), first); /* move value of first to last */
		
		mask_r <<= 1; /* forward mask_r to left bit */
		mask_l >>= 1; /* forward mask_l to right bit */
	}
		
	return arr;
}

/* convert array to a string */
char *BitArrToString(char *dest, bit_arr_t src)
{
	size_t i = 0;
	size_t arr_size = 0;
	
	arr_size =  sizeof(bit_arr_t) * 8; 
	
	for (i = 0 ; i < arr_size ; i++)
	{
		*(dest + i) = (arr % 2) + '0' ;
		arr /= 2;
	}
	
	reverse(dest);
	
	return dest;	
}

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <limits.h> /* UCHAR_MAX */

#include "bitarray.h" /* all bit array functions below */

static void IsOnTest();
static void IsOffTest();

static void SetAllTest();
static void ResetAllTest();
static void SetOnTest();
static void SetOffTest();
static void SetTest();

static void CountOnTest();
static void CountOffTest();

static void RotLTest();
static void RotRTest();
static void FlipTest();
static void MirrorTest();
static void ToStringTest();

static void IntitLutTest();

int main()
{
	/*IsOnTest();
	IsOffTest();
	SetAllTest();
	ResetAllTest();
	SetOnTest();
	SetOffTest();
	SetTest();
	CountOnTest();
	CountOffTest();
	RotLTest();
	RotRTest();
	FlipTest();
	MirrorTest();
	ToStringTest();*/
	IntitLutTest();
	
	return 0;
}

static void IsOnTest()
{
	bit_arr_t arr[] = {11, 15};
	int expected_resul[] = {0, 1};
	size_t i = 0, arr_size = 0;
	
	arr_size = sizeof(arr) / sizeof(bit_arr_t);
	
	printf("\nIsOn test is on...\n");
	
	for (; i < arr_size; i++)
	{
		if ((BitArrIsOn(arr[i], 2)) == expected_resul[i])
		{
			printf("SUCCESS!\n");
		}
		else
		{
			printf("Failure!\n");
			printf("Received result is: %d\n", BitArrIsOn(arr[i], 2));	
		}
	}
	
}

static void IsOffTest()
{
	bit_arr_t arr = 11;
	
	printf("\nIsOn test is off...\n");
	printf("%d\n", BitArrIsOff(arr, 2));
}

static void SetAllTest()
{
	bit_arr_t arr = 2;
	
	printf("%ld\n", BitArrSetAll(arr));
}


static void ResetAllTest()
{
	bit_arr_t arr = 15;
	
	printf("%ld\n", BitArrResetAll(arr));
	
}

static void SetOnTest()
{
	bit_arr_t arr = 0;
	
	printf("%ld\n", BitArrSetOn(arr, 7));
	
}

static void SetOffTest()
{
	bit_arr_t arr = 7;
	
	printf("%ld\n", BitArrSetOff(arr, 3));
	
}

static void SetTest()
{
	bit_arr_t arr = 15;
	
	printf("%ld\n", BitArrSet(arr, 2, 0));
}

static void CountOnTest()
{
	printf("\nCount on bits test is on...\n");
	printf("%ld\n", BitArrCountOn(11));
}

static void CountOffTest()
{
	printf("\nCount off bits test:\n");
	printf("%ld\n", BitArrCountOff(11));
}

static void RotLTest()
{
	bit_arr_t arr = 1024;
	size_t n = 63;
	
	printf("\nRotate left test:\n");
	printf("%ld\n", BitArrRotL(arr, n));
}

static void RotRTest()
{
	bit_arr_t arr = 1024;
	size_t n = 63;
	
	printf("\nRotate right test:\n");
	printf("%ld\n", BitArrRotR(arr, n));
}

static void FlipTest()
{
	bit_arr_t arr = 31;
	
	printf("\nFlip bit test:\n");
	printf("%ld\n", BitArrFlip(arr, 3));

}

static void MirrorTest()
{
	bit_arr_t arr = 57552;
	
	printf("\nMirror bit test:\n");
	printf("%ld\n", BitArrMirror(arr));
}

static void ToStringTest()
{
	bit_arr_t src = 57552;
	char *dest = NULL;
	
	dest = malloc(65);
	
	printf("\nToString bit test:\n");
	printf("%s\n", BitArrToString(dest, src));
	
	free(dest); dest = NULL;
}

/* LUT tests: */
static void IntitLutTest()
{
	size_t i = 0;
	size_t set_bits = 0;
	bit_arr_t arr[] = {1, 2, 3, 4, 5, 6, 15};
	
	printf("\nIniti LUT test:\n");
	
	for (; i < 7; i++)
	{
		set_bits = BitArrCountOnLUT(arr[i]);
		printf("%ld\n", set_bits);
	}
}

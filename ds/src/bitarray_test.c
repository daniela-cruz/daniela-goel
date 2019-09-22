#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

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

int main()
{
	IsOnTest();
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
	
	return 0;
}

static void IsOnTest()
{
	bit_arr_t arr = 11;
	
	printf("\nIsOn test is on...\n");
	printf("%d\n", BitArrIsOn(arr, 2));	
	
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

#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "bitarray.h"

void Test();

void TestBitArrSetAll();
void TestBitArrResetAll();
void TestBitArrSetOnAndIsOn();
void TestBitArrSetOffAndIsOff();
void TestBitArrBitArrSet();
void TestBitArrBitArrFlip();
void TestBitArrRot();
void TestBitArrCount();
void TestBitArrCountOnLUT();
void TestBitArrMirrorLUT();


int main()
{
	TestBitArrSetAll();
	TestBitArrResetAll();
	TestBitArrSetOnAndIsOn();
	TestBitArrSetOffAndIsOff();
	TestBitArrBitArrSet();
	TestBitArrBitArrFlip();
	TestBitArrRot();
	TestBitArrCount();
	Test();
	TestBitArrCountOnLUT();
	TestBitArrMirrorLUT();



	return 0;
}

void Test()
{
	bit_arr_t test_bit_arr = 8;
	char *arr_str = NULL;

	arr_str = (char*)malloc(sizeof(bit_arr_t) * 8 + 1);
	assert(NULL != arr_str);

	arr_str = BitArrToString(arr_str, test_bit_arr);
	printf("%s\n", arr_str);

	

	test_bit_arr = 1596485987;
	arr_str = BitArrToString(arr_str, test_bit_arr);
	printf("\n%s\n", arr_str);
	test_bit_arr = BitArrMirror(test_bit_arr);
	arr_str = BitArrToString(arr_str, test_bit_arr);
	printf("%s\n", arr_str);


	free(arr_str);
	arr_str = NULL;
}

void TestBitArrSetAll()
{
	bit_arr_t test_bit_arr = 0;

	test_bit_arr = BitArrSetAll(test_bit_arr);
	if (18446744073709551615 == test_bit_arr)
	{
		printf("BitArrSetAll - SUCCSESS\n"); 
	}
	else
	{
		printf("BitArrSetAll - FAIL\n"); 
	}
}

void TestBitArrResetAll()
{
	bit_arr_t test_bit_arr = 0;

	test_bit_arr = BitArrResetAll(test_bit_arr);
	if (0 == test_bit_arr)
	{
		printf("BitArrResetAll - SUCCSESS\n"); 
	}
	else
	{
		printf("BitArrResetAll - FAIL\n"); 
	}
}

void TestBitArrSetOnAndIsOn()
{
	bit_arr_t test_bit_arr = 0;
	int is_on = 0;

	/* test BitArrSetOn */
	test_bit_arr = BitArrSetOn(test_bit_arr, 4);
	if (16 == test_bit_arr)
	{
		printf("BitArrSetOn - SUCCSESS\n"); 
	}
	else
	{
		printf("BitArrSetOn - FAIL\n"); 
	}

	/* test BitArrIsOn */
	is_on = BitArrIsOn(test_bit_arr, 4);
	if (1 == is_on)
	{
		printf("BitArrIsOn - SUCCSESS\n"); 
	}
	else
	{
		printf("BitArrIsOn - FAIL\n"); 
	}
}

void TestBitArrSetOffAndIsOff()
{
	bit_arr_t test_bit_arr = 18446744073709551615;
	int is_off = 0;

	/* test BitArrSetOff */
	test_bit_arr = BitArrSetOff(test_bit_arr, 0);
	if (18446744073709551614 == test_bit_arr)
	{
		printf("BitArrSetOff - SUCCSESS\n"); 
	}
	else
	{
		printf("BitArrSetOff - FAIL\n"); 
	}

	/* test BitArrIsOff */
	is_off = BitArrIsOff(test_bit_arr, 0);
	if (1 == is_off)
	{
		printf("BitArrIsOff - SUCCSESS\n"); 
	}
	else
	{
		printf("BitArrIsOff - FAIL\n"); 
	}
}


void TestBitArrBitArrSet()
{
	bit_arr_t test_bit_arr = 0;
	bit_arr_t expected_results[2] = {4, 0};
	int set_bits[2] = {1, 0};
	int i = 0;

	for (i = 0; 2 > i; i++)
	{
		test_bit_arr = BitArrSet(test_bit_arr, 2, set_bits[i]);
		if (expected_results[i] == test_bit_arr)
		{
			printf("BitArrSet - test no.%d SUCCSESS\n", i); 
		}
		else
		{
			printf("BitArrSet - test no.%d FAIL\n", i); 
		}
		
	}
}

void TestBitArrBitArrFlip()
{
	bit_arr_t test_bit_arr = 0;
	bit_arr_t expected_results[2] = {512, 0};
	int i = 0;

	for (i = 0; 2 > i; i++)
	{
		test_bit_arr = BitArrFlip(test_bit_arr, 9);
		if (expected_results[i] == test_bit_arr)
		{
			printf("BitArrFlip - test no.%d SUCCSESS\n", i); 
		}
		else
		{
			printf("BitArrFlip - test no.%d FAIL\n", i); 
		}
		
	}
}

void TestBitArrRot()
{
	bit_arr_t test_bit_arr = 23;

	test_bit_arr = BitArrRotR(test_bit_arr, 3);
	if (0xE000000000000002 == test_bit_arr)
	{
		printf("BitArrRotR - SUCCSESS\n"); 
	}
	else
	{
		printf("BitArrRotR - FAIL\n"); 
	}

	/* test BitArrCountOff */
	test_bit_arr = BitArrRotL(test_bit_arr, 4);
	if (46 == test_bit_arr)
	{
		printf("BitArrRotL - SUCCSESS\n"); 
	}
	else
	{
		printf("BitArrRotL - FAIL\n"); 
	}
}




void TestBitArrCount()
{
	bit_arr_t test_bit_arr = 21;
	unsigned int count_bits_on = 0, count_bits_off = 0;

	/* test BitArrCountOn */
	count_bits_on = BitArrCountOn(test_bit_arr);
	if (3 == count_bits_on)
	{
		printf("BitArrCountOn - SUCCSESS\n"); 
	}
	else
	{
		printf("BitArrCountOn - FAIL\n"); 
	}

	/* test BitArrCountOff */
	count_bits_off = BitArrCountOff(test_bit_arr);
	if (61 == count_bits_off)
	{
		printf("BitArrCountOff - SUCCSESS\n"); 
	}
	else
	{
		printf("BitArrCountOff - FAIL\n"); 
	}
}

void TestBitArrCountOnLUT()
{
	bit_arr_t test_arr[] = {0, 1, 255, 1023, 1024, 18446744073709551615};
	bit_arr_t expected_results[] = {0, 1, 8, 10 ,1 , 64};
	int i = 0;

	printf("\n"); 

	for (i = 0; 6 > i; i++)
	{
		if (expected_results[i] == BitArrCountOnLUT(test_arr[i]))
		{
			printf("BitArrCountOnLUT - test no.%d SUCCSESS\n", i); 
		}
		else
		{
			printf("BitArrCountOnLUT - test no.%d FAIL\n", i); 
		}
	}
}


void TestBitArrMirrorLUT()
{
	int i = 0;
	bit_arr_t test_arr[] = {0, 1, 255 , 1023, 1024, 0x4000000000000080, 
							0xFFFFFFFFFFFFFFFF};
	bit_arr_t expected_results[] = {0, 0x8000000000000000, 0xFF00000000000000,
			 				 0xFFC0000000000000 ,0x0020000000000000,
		 					0x0100000000000002 , 0xFFFFFFFFFFFFFFFF};

	printf("\n"); 
	for (i = 0; 7 > i; i++)
	{
		if (expected_results[i] == BitArrMirrorLUT(test_arr[i]))
		{
			printf("BitArrMirrorLUT - test no.%d SUCCSESS\n", i); 
		}
		else
		{
			printf("BitArrMirrorLUT - test no.%d FAIL\n", i);
		}
	}
}









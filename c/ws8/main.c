#include <stdio.h>

#include "ws8.h"

static void TestPolimorphism();

int main()
{
	TestPolimorphism();
	return 0;
}

static void TestPolimorphism()
{
	data_t arr[3];
	data_t *arr_ptr;
	int i_data = 3;
	float f_data = 12.7;
	char *s_data = "hell";
	
	printf("\nPolimorphism test:\n");
	printf("\nSetting values. . .\n");
	
	arr_ptr = arr;
	SetVal(arr_ptr, INT, &i_data);
	arr_ptr++;
	SetVal(arr_ptr, FLOAT, &f_data);
	arr_ptr++;
	SetVal(arr_ptr, STRING, &s_data);
	
	printf("\nPrinting values:\n");
	PrintVal(arr_ptr--);
	PrintVal(arr_ptr--);
	PrintVal(arr_ptr);
	
	printf("\nAdding values. . .\n");
	AddVal(arr_ptr++, &i_data);
	AddVal(arr_ptr++, &f_data);	
	AddVal(arr_ptr, s_data);	
	
	printf("\nPrinting values:\n");
	PrintVal(arr_ptr--);
	PrintVal(arr_ptr--);
	PrintVal(arr_ptr);
}


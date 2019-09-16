#include <stdio.h>
#include <stdlib.h>

#include "ws8.h"

data_t arr[3];

static void TestPolimorphism();

int main()
{
	TestPolimorphism();
	return 0;
}

static void TestPolimorphism()
{
	data_t *arr_ptr;
	int i_data = 3, new_i = 57; 
	float f_data = 12.7, new_f = 2.1817;
	char *new_s = malloc(20);
	char *s_data = "yo";
	
	printf("\nPolimorphism test:\n");
	printf("\nSetting values. . .\n");
	
	arr_ptr = arr;
	SetVal(&arr[0], INT, &i_data);
	arr_ptr++;
	SetVal(&arr[1], FLOAT, &f_data);
	arr_ptr++;
	SetVal(&arr[2], STRING, s_data);
	
	printf("\nPrinting values:\n");
	PrintVal(arr_ptr--);
	PrintVal(arr_ptr--);
	PrintVal(arr_ptr);
	
	printf("\nAdding values. . .\n");
	AddVal(arr_ptr++, 12);
	AddVal(arr_ptr++, 12);	
	AddVal(arr_ptr, 12);	
	
	printf("\nPrinting values:\n");
	PrintVal(arr_ptr--);
	PrintVal(arr_ptr--);
	PrintVal(arr_ptr);
	
	printf("\nGetting values. . .\n");
	GetVal(arr_ptr++, &new_i);
	GetVal(arr_ptr++, &new_f);
	GetVal(arr_ptr, new_s);
	printf("%s\n", new_s);
	
	printf("\nPrinting values:\n");
	PrintVal(arr_ptr--);
	PrintVal(arr_ptr--);
	PrintVal(arr_ptr);
	
	printf("\nFree values. . . \n");
	FreeVal(&arr[2]);
}


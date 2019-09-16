#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

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
	data_t arr[3];
	int i_data = 3;
	float f_data = 12.7;
	char s_data[7] = "yo";
	size_t i = 0;
	void *new_s = NULL;
	
	new_s = malloc(20);
	assert(new_s);
	
	printf("\nPolimorphism test:\n");
	printf("\nSetting values. . .\n");

	SetVal(&arr[0], INT, &i_data);
	SetVal(&arr[1], FLOAT, &f_data);
	SetVal(&arr[2], STRING, s_data);
	
	printf("\nPrinting values:\n");
	for (; i < 3; i++)
	{
		PrintVal(&arr[i]);
	}
	
	printf("\nAdding values. . .\n");
	
	for (i = 0; i < 3; i++)
	{
		AddVal(&arr[i], 12.7);
	}
	
	printf("\nPrinting values:\n");
	for (i = 0; i < 3; i++)
	{
		PrintVal(&arr[i]);
	}
	
	printf("\nGetting values. . .\n");
	GetVal(&arr[2], new_s);
	printf("%s", new_s);
	
	printf("\nFree values. . . \n");
	for (i = 0; i < 3; i++)
	{
		FreeVal(&arr[i]);
	}
	
	free(new_s);
}


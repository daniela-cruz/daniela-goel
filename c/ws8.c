#include <stdio.h> /*realloc*/
#include <stdlib.h> /*printf*/
#include <string.h> /*strcat*/

#define DUMMY_VALUE 10

typedef struct add_data 
{ 
	void *data();
	void (*add_f)(void);
	void (*print)(void);
	void (*free_memory)(void);
} Add_Data;

int *AddInt(int *number);
float *AddFloat(float *number);

void PrintInt(int  *number);
void PrintFloat(float  *number);
void PrintString(char  *string);

FreeString;

int main() 
{
    return 0;
}

Add_Data *InitializeDAtaStruct(char struct_elements_number) 
{
    Add_Data type_functions = 
					{{(int *)number, (int *)AddInt, PrintInt, FreeNumber}, 
					{(float *)number, (float *)AddFloat, PrintFloat, FreeNumber},
					{(char *)string, (char *)strcat, PrintString, FreeString}};
    

    return type_functions;
}

/*Addition functions:*/
int *AddInt(int *number)
{
	*number += DUMMY_VALUE;
	
	return  number;	
}

float *AddFloat(float *number)
{
	*number += DUMMY_VALUE;
	
	return  number;	
}

/*Print functions:*/
void PrintInt(int  *number)
{
	printf("%d", *number);
}

void PrintFloat(float  *number)
{
	printf("%f", *number);
}

void PrintString(char  *string)
{
	printf("%s", string);
}

FreeString
{
	free(string);
}

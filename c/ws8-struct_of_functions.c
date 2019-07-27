#include <stdio.h> /*realloc*/
#include <stdlib.h> /*printf*/
#include <string.h> /*strcat*/

enum data_type_t {Int, Float, String};
enum operation_t {Add, Print, Free};

typedef struct add_data 
{ 
	void *data;
	void (*add_f)(void);
	void (*print)(void);
	void (*free_memory)(void);
} Add_Data;

Add_Data *InitializeDataStruct() ;

int *AddInt(int *number);
float *AddFloat(float *number);

void PrintInt(int  *number);
void PrintFloat(float  *number);
void PrintString(char  *string);

void FreeString(char *string);

int main() 
{
    return 0;
}

Add_Data *InitializeDataStruct() 
{
    char type_amount = 3;
    Add_Data type_functions[3] = 
					{{(int *)number, (int *)AddInt, PrintInt, FreeNumber}, 
					{(float *)number, (float *)AddFloat, PrintFloat, FreeNumber},
					{(char *)string, (char *)strcat, PrintString, FreeString}};
    
	data_type_t input_type;
	operation_t operation;
	int operations_amount = 3;

	printf("Please choose the data type input:\n");
	printf("choose 0 for int\nchoose 1 for float \nchoose 2 for string \n");
	scant("%d", &input_type);
	/*assign value to pointer:*/
	type_functions(input_type).data = type_functions(input_type).add_f();
/*
	printf("Please select operation:\n");
	printf("choose 1 - add\nchoose 2 - print \nchoose 3 - free \n");
	scanf("%d", &operation);

	type_functions[input_type]
*/
	return type_functions;
}

int *ScanInt()
{
	int number;
	
	
	
	return &number;
}

/*Addition functions:*/
int *AddInt()
{
	int number;
	int new_number = 0;
	
	printf("Please enter an integer:\n");
	scanf("%d", &number);
	new_number += number;
	
	return  &new_number;	
}

float *AddFloat()
{
	float number;
	float new_number = 0;
	
	printf("Please enter a float:\n");
	scanf("%f", &number);
	new_number += number;
	
	return  &new_number;		
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

void FreeString(char *string)
{
	free(string);
}

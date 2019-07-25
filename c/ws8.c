#include <stdio.h> /*realloc*/
#include <stdlib.h> /*printf*/
#include <string.h> /*strcat*/

typedef struct add_data 
{ 
	void *data();
	void (*add_f)(void);
	void (*print)(void);
	void (*free_memory)(void);
} Add_Data;


int main() 
{
    return 0;
}

Add_Data *InitializeDAtaStruct(char struct_elements_number) 
{
    Add_Data type_functions = 
					{{(int)number, (int)AddInt, PrintInt, FreeNumber}, 
					{(char *)string, (char *)strcat, PrintString, FreeString},
					{(float)number, (float *)AddFloat, PrintFloat, FreeNumber}};
    

    return type_functions;
}


int AddInt(int number)
{
	
	return number;	
}

#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strcat */

#include "ws8.h" /* data_t */

void SetVal(data_t *arr_ptr, data_type_t type /* data_t.dt */, void *data /* data_t.d */)
{
	assert(arr_ptr);
	
	arr_ptr->dt = type;
	
	switch (type)
	{
		case INT:
			arr_ptr->dt = INT;
			arr_ptr->d.i_var = *(int *)data;
			break;
			
		case FLOAT:
			arr_ptr->dt = FLOAT;
			arr_ptr->d.f_var = *(float *)data;
			break;
			
		case STRING:
			arr_ptr->dt = STRING;
			arr_ptr->d.s_var = (char *)data;
			break;
			
		default:
			break;
	}
}

void *GetVal(data_t *arr_ptr)
{
	assert(arr_ptr);
	
	switch (arr_ptr->dt)
	{
		case INT:
			return (void*)&arr_ptr->d.i_var;
		
		case FLOAT:
			return (void*)&arr_ptr->d.f_var;
		
		case STRING:
			return (void*)&arr_ptr->d.s_var;
	}
	
	return NULL;
}

void PrintVal(data_t *arr_ptr)
{
	switch (arr_ptr->dt)
	{
		case INT:
			printf("Int is: %d\n", (int )arr_ptr->d.i_var);
			break;
		
		case FLOAT:
			printf("Float is: %f\n", (float )arr_ptr->d.f_var);
			break;
		
		case STRING:
			printf("String is: %s\n", (char *)&arr_ptr->d.i_var);
			break;
		
		default:
			printf("Error: no value can be printed.\n");
			break;
	}
}

void AddVal(data_t *arr_ptr, void *add_value)
{
	switch (arr_ptr->dt)
	{
		case (INT):
			arr_ptr->d.i_var += *(int *)add_value;
			break;
		
		case (FLOAT):
			arr_ptr->d.f_var += *(float *)add_value;
			break;
		
		case (STRING):
			strcat(arr_ptr->d.s_var, (char *)add_value);
			break;
		
		default:
			printf("Error: cannot perform addition.\n");
			break;
	}
}


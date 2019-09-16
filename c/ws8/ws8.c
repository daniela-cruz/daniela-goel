#include <stdio.h> /* printf */
#include <assert.h> /* assert */

typedef enum {INT, FLOAT, STRING} data_type_t;

typedef union DataVar
{
	int i_var;
	float f_var;
	char *s_var;
} data_var_t;

typedef struct 
{
	data_type_t dt; /* data type the user requests */
	data_var_t d; /* the val itself */
} data_t;

void SetVal(data_t *arr, data_type_t type /* data_t.dt */, void *data /* data_t.d */)
{
	assert(arr);
	
	arr_ptr->dt = type;
	
	switch (type)
	{
		case INT:
			(void *)&arr_ptr->d.i_var = (int)data;
			break;
			
		case FLOAT:
			(void *)&arr_ptr->d.f_var = (float)data;
			break;
			
		case STRING:
			(void *)&arr_ptr->d.s_var = (char *)data;
			break;
			
		default:
			break;
	}
}

void *GetVal(data_t *arr_ptr)
{
	assert(arr);
	
	data_t type = arr_ptr->dt;
	
	switch (type)
	{
		case INT:
			return (void*)&arr_ptr->d.i_var;
		
		case FLOAT:
			return (void*)&arr_ptr->d.f_var;
		
		case STRING:
			return (void*)&arr_ptr->d.s_var;
	}
	
}

void PrintVal(data_t *arr_ptr)
{
	data_t type = arr_ptr->dt;
	
	switch (type)
	{
		case INT:
			printf("%d\n", (int)&arr_ptr->d.i_var);
			break;
		
		case FLOAT:
			printf("%lf\n", (float)&arr_ptr->d.f_var);
			break;
		
		case STRING:
			printf("%s\n", (char *)&arr_ptr->d.i_var);
			break;
		
		default:
			printf("Error: no value can be printed.\n");
			break;
	}
}

void *AddVal(data_t *arr_ptr, void *add_value)
{
	data_t type = arr_ptr->dt;
	
	switch (type)
	{
		case INT:
			return ((int)&arr_ptr->d.i_var + (int)add_value);
		
		case FLOAT:
			return ((float)&arr_ptr->d.f_var + (float)add_value);
		
		case STRING:
			return strcat((char *)&arr_ptr->d.s_var, (char *)add_value);
		
		default:
			printf("Error: cannot perform addition.\n");
			break;
	}
}

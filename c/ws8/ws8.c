#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* strcat */

#include "ws8.h" /* data_t */

void SetVal(data_t *val, data_type_t type /* data_t.dt */, void *data /* data_t.d */)
{
	assert(val);
	
	val->dt = type;
	
	switch (type)
	{
		case INT:
			val->d.i_var = *(int *)data;
			break;
			
		case FLOAT:
			val->d.f_var = *(float *)data;
			break;
			
		case STRING:
			val->d.s_var = malloc(strlen((char *) data) + 1);
			strcpy(val->d.s_var, (char *)data);
			break;
			
		default:
			break;
	}
}

void PrintVal(data_t *val)
{
	switch (val->dt)
	{
		case INT:
			printf("Int is: %d\n", (int)val->d.i_var);
			break;
		
		case FLOAT:
			printf("Float is: %f\n", (float)val->d.f_var);
			break;
		
		case STRING:
			printf("String is: %s\n", (char *) val->d.s_var);
			break;
		
		default:
			printf("Error: no value can be printed.\n");
			break;
	}
}

void AddVal(data_t *val, int add_value) /* turn add vl to*/
{
	char *buffer = NULL;
	switch (val->dt)
	{
		case (INT):
			val->d.i_var += add_value;
			break;
		
		case (FLOAT):
			val->d.f_var += add_value;
			break;
		
		case (STRING):
			buffer = malloc(10); /* max int digits possible */
			
			sprintf(buffer, "%d", add_value);
			
			val->d.s_var = realloc(val->d.s_var, strlen(val->d.s_var) + strlen(buffer) + 1);
			val->d.s_var = strcat(val->d.s_var, buffer);
			
			free(buffer); buffer = NULL;
			
			break;
		
		default:
			printf("Error: cannot perform addition.\n");
			break;
	}
}

void GetVal(data_t *val, void *new_data)
{
	switch (val->dt)
	{
		case (INT):
			*(int *)new_data = val->d.i_var;
			break;
		
		case (FLOAT):
			*(float *)new_data = val->d.f_var;
			break;
		
		case (STRING):
			new_data = strcpy((char *)new_data, (char *)val->d.s_var);
			break;
		
		default:
			printf("Error: cannot asign.\n");
			break;
	}
}

data_type_t GetType(data_t *val)
{
	assert(val);
	
	return val->dt;
}

void FreeVal(data_t *val)
{
	switch (val->dt)
	{
		case (INT):
			val->d.i_var = 0;
			break;
		
		case (FLOAT):
			val->d.f_var = 0;
			break;
		
		case (STRING):
			free(val->d.s_var); val->d.s_var = NULL;
			break;
		
		default:
			printf("Error: cannot asign new value.\n");
			break;
	}
}

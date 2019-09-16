#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* strcat */

#include "ws8.h" /* data_t */

void SetVal(data_t *var, data_type_t type /* data_t.dt */, void *data /* data_t.d */)
{
	assert(var);
	
	var->dt = type;
	
	switch (type)
	{
		case INT:
			var->dt = INT;
			var->d.i_var = *(int *)data;
			break;
			
		case FLOAT:
			var->dt = FLOAT;
			var->d.f_var = *(float *)data;
			break;
			
		case STRING:
			var->dt = STRING;
			var->d.s_var = malloc(strlen((char *)data) + 1);
			var->d.s_var = strcpy(var->d.s_var, (char *)data);
			break;
			
		default:
			break;
	}
}

extern void GetVal(data_t *val, void *new_data)
{
	assert(var);
	
	switch (var->dt)
	{
		case INT:
			return (void*)&var->d.i_var;
		
		case FLOAT:
			return (void*)&var->d.f_var;
		
		case STRING:
			return (void*)&var->d.s_var;
	}
	
	return NULL;
}

void PrintVal(data_t *var)
{
	switch (var->dt)
	{
		case INT:
			printf("Int is: %d\n", (int)var->d.i_var);
			break;
		
		case FLOAT:
			printf("Float is: %f\n", (float)var->d.f_var);
			break;
		
		case STRING:
			printf("String is: %s\n", (char *)&var->d.s_var);
			break;
		
		default:
			printf("Error: no value can be printed.\n");
			break;
	}
}

void AddVal(data_t *var, void *add_value) /* turn add vl to*/
{
	switch (var->dt)
	{
		case (INT):
			var->d.i_var += *(int *)add_value;
			break;
		
		case (FLOAT):
			var->d.f_var += *(float *)add_value;
			break;
		
		case (STRING):
			var->d.s_var = malloc(strlen(var->d.s_var) + strlen((char *)add_value) + 1);
			var->d.s_var = strcat(var->d.s_var, (char *)add_value);
			break;
		
		default:
			printf("Error: cannot perform addition.\n");
			break;
	}
}


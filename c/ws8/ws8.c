#include <>

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
	if (NULL == arr_ptr)
	{
		return NULL;
	}
	
	arr_ptr->dt = type;
	
	switch(type)
		case INT:
			(void *)&arr_ptr->d.i_var = data;
			break;
		case FLOAT:
			(void *)&arr_ptr->d.f_var = data;
			break;
		case STRING:
			(void *)&arr_ptr->d.s_var = data;
			break;
		default:
			break;
}

void *GetVal(data_t *arr, size_t index)
{
	return arr.d;
}

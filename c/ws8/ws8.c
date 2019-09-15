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
	data_type_t dt;
	data_var_t d;
} data_t;

void SetVal(data_t *arr, data_type_t type /* data_t.dt */, void *data /* data_t.d */)
{
	
}

void *GetVal(data_t *arr, )
{
	
	return /**/;
}

data_t arr[5];

arr.d = {int,float. char*}
arr.dt = {INT,FLOAT,STRING};

void *GetVal(data_t *arr, size_t index)
{
	return arr.d;
}

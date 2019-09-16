#ifndef __WS8_H__
#define __WS8_H__

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

extern void SetVal(data_t *arr, data_type_t type /* data_t.dt */, void *data /* data_t.d */);

extern void *GetVal(data_t *arr_ptr);

extern void PrintVal(data_t *arr_ptr);

extern void AddVal(data_t *arr_ptr, void *add_value);

#endif

#ifndef __WS8_H__
#define __WS8_H__

typedef enum {INT, FLOAT, STRING} data_type_t;

typedef union
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

/* set values to data_t struct */
extern void SetVal(data_t *val, data_type_t type /* data_t.dt */, void *data /* data_t.d */);

extern void PrintVal(data_t *val);

/* add additional value or string to existing value */
extern void AddVal(data_t *val, int add_value);

/* pute value from struct in another pointer */
extern void GetVal(data_t *val, void *new_data);

/* returns the type of struct member */
extern data_type_t GetType(data_t *val);

extern void FreeVal(data_t *val);

#endif

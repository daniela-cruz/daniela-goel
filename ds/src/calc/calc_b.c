#include <stdlib.h>    /* stdtod, malloc, free */
#include <string.h>  	/* strcspn */
#include <limits.h>    /* uchar_max */

#include "vector.h"    /* vector_t */

/*********TYPEDEFs*********/
typedef char* (*operator_handler_t)(char *);
typedef int precedence_LUT_t;
typedef double (*calc_func_t)(double, double);

/**Forward declarations:**/
void CalcExecute();

int InitCalculator();
void InicCalcFuncsLUT();
void InitOperatorsPrecedenceLUT();
void InitOperatorsHandlersLUT();

char *DummyOpFunc(char *exp);
char *GetNumFromExp(char *exp);
char *ExecuteOperators(char *exp);
char *OpDecrement(char *exp);
char *OpIncrement(char *exp);
char *ParanthesesOpen(char *exp);
char *ParanthesesClosed(char *exp);

static double CalcDecrement(double f1, double f2);
static double CalcIncrement(double f1, double f2);
static double CalcMultiply(double f1, double f2);
static double CalcDivide(double f1, double f2);

/**********STACKs**********/
static vector_t *num_stk;
static vector_t *operators_stk;

/**********LUTs***********/
static operator_handler_t handlersLUT[UCHAR_MAX + 1];
static precedence_LUT_t precedenceLUT[UCHAR_MAX + 1];
static calc_func_t calc_funcLUT[UCHAR_MAX + 1];

/********Other***********/
/*  determines if following expression is 
 *  pushed to num_stk or operator_stk       */
static int is_number = 1; 

/*************************
 *      CALC FUNCS:      *
*************************/
double Calculator(char *exp, int *err)
{
    double result = 0;

    *err = InitCalculator();
    
    while ('\0' != *exp)
    {
        exp = handlersLUT[(int)*exp](exp);
    }

    while (1 < VectorSize(operators_stk))
    {
        CalcExecute();
    }

    result = *(double *)VectorGetItemAddress(num_stk, VectorSize(num_stk) - 1);
    VectorDestroy(num_stk);
    VectorDestroy(operators_stk);

    return result;
}

void CalcExecute()
{
    char operator = 0;
    double operand1 = 0, operand2 = 0;
    double result = 0;

    operator = *(char *)VectorGetItemAddress(operators_stk, VectorSize(operators_stk) - 1);
    VectorPopBack(VectorGetItemAddress(operators_stk, VectorSize(operators_stk) - 1));

    operand2 = *(double *)VectorGetItemAddress(num_stk, VectorSize(num_stk) - 1);
    VectorPopBack(VectorGetItemAddress(num_stk, VectorSize(num_stk) - 1));

    operand1 = *(double *)VectorGetItemAddress(num_stk, VectorSize(num_stk) - 1);
    VectorPopBack(VectorGetItemAddress(num_stk, VectorSize(num_stk) - 1));

    result = calc_funcLUT[(int)operator](operand1, operand2);
    VectorPushBack(num_stk, &result);
}

void PushOpenParantheses()
{
    VectorPushBack(operators_stk, &precedenceLUT[(int)'(']);
}

void CalcPopClosedParntheses()
{
    while ('(' != (*(char *)VectorGetItemAddress(operators_stk, 
        VectorSize(operators_stk) - 1)))
    {
        CalcExecute(num_stk, operators_stk);
    }

    VectorPopBack(operators_stk);
}


/*************************
 *     INITIALIZERS:     *
*************************/
int InitCalculator()
{
    int is_failure = 0;

    do
    {
        InicCalcFuncsLUT();
        InitOperatorsPrecedenceLUT();
        InitOperatorsHandlersLUT();
        
        num_stk = VectorCreate(sizeof(double), 2);
        if (NULL == num_stk)
        {
            is_failure = 1;
            break;
        }
        
        operators_stk = VectorCreate(sizeof(double), 3);
        if (NULL == operators_stk)
        {
            is_failure = 1;
            break;
        }
        
    } while (0);
    
    if (is_failure && (NULL != num_stk)) /* cleanup*/
    {
        free(num_stk); num_stk = NULL;
    }
    
    return is_failure;
}

void InicCalcFuncsLUT()
{
    calc_funcLUT['-'] = CalcDecrement;
    calc_funcLUT['+'] = CalcIncrement;
    calc_funcLUT['*'] = CalcMultiply;
    calc_funcLUT['/'] = CalcDivide;
}

void InitOperatorsPrecedenceLUT()
{
    int i = 0;

    for ( i = 0; i <= UCHAR_MAX + 1; i++)
    {
        precedenceLUT[i] = -1;
    }

    precedenceLUT[(int)'('] = 0;
    precedenceLUT[(int)'-'] = 1;
    precedenceLUT[(int)'+'] = 1;
    precedenceLUT[(int)'*'] = 2;
    precedenceLUT[(int)'/'] = 2;
    precedenceLUT[(int)')'] = 3;
}

void InitOperatorsHandlersLUT()
{
    int i = 0;

    for ( i = '0'; i <= '9' + 1; i++)
    {
        handlersLUT[i] = GetNumFromExp;
    }

    handlersLUT[39] = DummyOpFunc;
    handlersLUT['('] = ParanthesesOpen;
    handlersLUT[')'] = ParanthesesClosed;
    handlersLUT['-'] = ExecuteOperators;
    handlersLUT['+'] = ExecuteOperators;
    handlersLUT['*'] = ExecuteOperators;
    handlersLUT['/'] = ExecuteOperators;
}

/*************************
 *   Handlers Funcs:     *
*************************/
char *DummyOpFunc(char *exp)
{
    return NULL;
}

char *GetNumFromExp(char *exp)
{
    double number = 0;
   
    number = strtod(exp, &exp); VectorPushBack(num_stk, &number);

    is_number = !is_number;

    return exp;
}

char *ExecuteOperators(char *exp)
{
    char precedence = 0;
    char last_operator = 0;

    last_operator = *(char *)VectorGetItemAddress(operators_stk, VectorSize(operators_stk)-1);
    precedence = precedenceLUT[(int)*exp];

    while (precedence <= precedenceLUT[(int)last_operator])
    {
        CalcExecute(num_stk, operators_stk);
        last_operator = *(char *)VectorGetItemAddress(operators_stk, VectorSize(operators_stk)-1);
    }

    VectorPushBack(operators_stk, &calc_funcLUT[(int)*exp]);
    is_number = 1;

    return (char *)exp + 1;
}

char *ParanthesesOpen(char *exp)
{
    return NULL;
}

char *ParanthesesClosed(char *exp)
{
    return NULL;
}

/*************************
 *   Operator Funcs:     *
*************************/
static double CalcDecrement(double f1, double f2)
{
    return f1 - f2;
}

static double CalcIncrement(double f1, double f2)
{
    return f1 + f2;
}

static double CalcMultiply(double f1, double f2)
{
    return f1 * f2;
}

static double CalcDivide(double f1, double f2)
{
    return f1 / f2;
}
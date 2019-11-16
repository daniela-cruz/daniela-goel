#include <stdio.h>		/* sscanf */
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

operator_handler_t EmptyOperator(char *exp);
operator_handler_t NumberFunc(char *exp);
operator_handler_t OpDecrement(char *exp);
operator_handler_t OpIncrement(char *exp);
operator_handler_t OpMultiply(char *exp);
operator_handler_t OpDivide(char *exp);

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
        handlersLUT[i] = NumberFunc(NULL);
    }

    handlersLUT[39] = EmptyOperator(NULL);
    handlersLUT['('] = EmptyOperator(NULL);
    handlersLUT[')'] = EmptyOperator(NULL);
    handlersLUT['-'] = OpDecrement(NULL);
    handlersLUT['+'] = OpIncrement(NULL);
    handlersLUT['*'] = OpMultiply(NULL);
    handlersLUT['/'] = OpDivide(NULL);
}

/*************************
 *   Handlers Funcs:     *
*************************/
operator_handler_t EmptyOperator(char *exp)
{
    return NULL;
}

operator_handler_t NumberFunc(char *exp)
{
    return NULL;
}

operator_handler_t OpDecrement(char *exp)
{
    return NULL;
}

operator_handler_t OpIncrement(char *exp)
{
    return NULL;
}

operator_handler_t OpMultiply(char *exp)
{
    return NULL;
}

operator_handler_t OpDivide(char *exp)
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
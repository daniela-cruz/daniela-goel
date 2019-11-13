#include <stdio.h>
#include <stdlib.h>     /* stdtod, malloc, free */
#include <limits.h>     /* uchar_max */

#include "vector.h"     /* vector_t */

double (*Operator_LUT_t)(float, float, int);
double (*Precedence_LUT_t)(char operator, float operand, int is_operator);

typedef struct calc_stack1
{
    vector_t *stack1;
} calc_stack1_t;

typedef struct calc_stack2
{
    vector_t *stack2;
} calc_stack2_t;

/************************/
double Calculator(char *expression, int *err);
vector_t *FillStack1(char *expression);
void InitOperators();

/************************/
static double OpDecrement(float f1, float f2, int is_operator);
static double OpIncrement(float f1, float f2, int is_operator);
static double OpMultiply(float f1, float f2, int is_operator);
static double OpDivide(float f1, float f2, int is_operator);
static double EmptyOperator(float f1, float f2, int is_operator);

/************************/
double Operator_LUT[UCHAR_MAX + 1];


/*************************
 *      CALCULATOR:      *
*************************/
void InitOperators()
{
    int i = 0;

    for ( i = 0; i < UCHAR_MAX + 1; i++)
    {
        Operator_LUT[i] = EmptyOperator(0,0,0);
    }
    
    Operator_LUT['`'] = EmptyOperator(0,0,0);
    Operator_LUT['-'] = OpDecrement(0,0,0);
    Operator_LUT['+'] = OpIncrement(0,0,0);
    Operator_LUT['*'] = OpMultiply(0,0,0);
    Operator_LUT['/'] = OpDivide(0,0,0);
}

double Calculator(char *expression, int *err)
{
    double op1 = 0;
    vector_t *stack1 = NULL;

    stack1 = FillStack1(expression);

    op1 = VectorSize(stack1);
    
    return op1;
}

/* separate between operands and operators using both stacks */
vector_t *FillStack1(char *expression)
{
    vector_t *stack1 = NULL;
    char *arr = NULL;

    arr = malloc(sizeof(*arr) * 4);
    stack1 = VectorCreate(sizeof(double), 4);

    while ('\0' != *expression)
    {
        double operand = 0;

        operand = strtod(arr, &expression);
        VectorPushBack(stack1, &operand);
    }

    return stack1;
}

/*************************
 *      OPERATORS:       *
*************************/
static double OpDecrement(float f1, float f2, int is_operator)
{
    return f1 - f2;
}

static double OpIncrement(float f1, float f2, int is_operator)
{
    return f1 + f2;
}

static double OpMultiply(float f1, float f2, int is_operator)
{
    return f1 * f2;
}

static double OpDivide(float f1, float f2, int is_operator)
{
    return f1 / f2;
}

static double EmptyOperator(float f1, float f2, int is_operator)
{
    /* first in operators fifo stack
     * should call operand and perform 
     * last calculation and provide a sum */

    return /**/0;
}
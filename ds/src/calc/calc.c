#include <stdio.h>
#include <stdlib.h>     /* stdtod, malloc, free */
#include <limits.h>     /* uchar_max */

#include "vector.h"     /* vector_t */

typedef double (*Operator_LUT_t)(char *, int);
typedef double (*Precedence_LUT_t)(char operator);
typedef void (*precedence_exe_func_t)(char *);

typedef struct calc_nums
{
    vector_t *stack;
} calc_stack_t;

typedef struct calc_operators
{
    vector_t *op_stack;
} calc_operators_t;

/************************/
double Calculator(char *expression, int *err);
void InitOperators();
calc_stack_t *FillNumsStack(char *expression);
calc_operators_t *FillOperatorsStack(char *expression, calc_stack_t *nums_stack);

/************************/
static double OpParatheses(calc_stack_t *nums, calc_operators_t *operators);

/************************/
static Operator_LUT_t NumberFunc(char *exp, int is_operator);
static Operator_LUT_t EmptyOperator(char *exp, int is_operator);
static Operator_LUT_t ParenthesisOpen(char *exp, int is_operator);
static Operator_LUT_t ParenthesisClose(char *exp, int is_operator);
static Operator_LUT_t OpDecrement(char *exp, int is_operator);
static Operator_LUT_t OpIncrement(char *exp, int is_operator);
static Operator_LUT_t OpMultiply(char *exp, int is_operator);
static Operator_LUT_t OpDivide(char *exp, int is_operator);

/************************/
static Operator_LUT_t Operator_LUT[UCHAR_MAX + 1];
static Precedence_LUT_t PrecedenceLUT[UCHAR_MAX + 1];
static calc_stack_t *nums_stack = NULL;
static calc_stack_t *operators_stack = NULL;

/*************************
 *     INITIALIZERS:     *
*************************/
void InitOperators()
{
    int i = 0;

    for ( i = '0'; i <= '9' + 1; i++)
    {
        Operator_LUT[i] = NumberFunc(NULL, 0);
    }

    Operator_LUT['39'] = EmptyOperator(NULL, 0);
    Operator_LUT['('] = EmptyOperator(NULL, 0);
    Operator_LUT[')'] = EmptyOperator(NULL, 0);
    Operator_LUT['-'] = OpDecrement(NULL, 0);
    Operator_LUT['+'] = OpIncrement(NULL, 0);
    Operator_LUT['*'] = OpMultiply(NULL, 0);
    Operator_LUT['/'] = OpDivide(NULL, 0);
}

void InitPrecedenceLut()
{
    int i = 0;

    for ( i = 0; i <= UCHAR_MAX + 1; i++)
    {
        PrecedenceLUT[i] = -1;
    }

    PrecedenceLUT['39'] = 10;
    PrecedenceLUT['('] = 0;
    PrecedenceLUT['-'] = 1;
    PrecedenceLUT['+'] = 1;
    PrecedenceLUT['*'] = 2;
    PrecedenceLUT['/'] = 2;
    PrecedenceLUT[')'] = 3;
}

calc_operators_t *InitNewStack()
{
    calc_operators_t *stack = NULL;

    stack = malloc(sizeof(*stack));
    if (NULL == stack)
    {
        return NULL;
    }
    
    stack->op_stack = VectorCreate(sizeof(double), 3);
    if (NULL == stack->op_stack)
    {
        free(stack);
        return NULL;
    }

    VectorPushBack(stack->op_stack, EmptyOperator);
    InitOperators();

    return stack;
}

/*************************
 *      CALCULATOR:      *
*************************/
double Calculator(char *expression, int *err)
{
    int is_operator = 0; /* when 1 a function would calculate and then add to stack*/
    char *str_end = NULL;
    double sum = 0;

    nums_stack = InitNewStack();
    operators_stack = InitNewStack();

    while ('\0' != *expression)
    {
        Operator_LUT[*expression](expression, is_operator);
        strtod(expression, str_end);
        is_operator = !is_operator;
    }

    while (1 < VectorSize(nums_stack->stack))
    {
        /* sum = empty stack somehow */
    }
    
    return sum;
}

/*************************
 *       HANDLERS:       *
*************************/
static precedence_exe_func_t ReadOpFromString(char *exp)
{
    size_t curr_idx = 0;
    size_t num_idx;
    double op1 = 0, op2 = 0;

    curr_idx = VectorSize(operators_stack->stack);

    while (PrecedenceLUT[*(int *)VectorGetItemAddress(operators_stack->stack, 
        curr_idx)] > PrecedenceLUT[*exp] && (1 < curr_idx))
    {
        num_idx = VectorSize(nums_stack->stack);
        op2 = *(double *)VectorGetItemAddress(nums_stack->stack, num_idx);
        VectorPopBack(nums_stack->stack); num_idx--;
        op1 = *(double *)VectorGetItemAddress(nums_stack->stack, num_idx);
        VectorPopBack(nums_stack->stack); num_idx--;
        
        /* adding the new result to numbers_stack */
        VectorPushBack(nums_stack->stack, 
        Operator_LUT[*(int *)VectorGetItemAddress(operators_stack->stack, 
        curr_idx)]);
        
        curr_idx--;
    }
    

}

static Operator_LUT_t NumberFunc(char **exp, int is_operator)
{
    double num = strtod(*exp, exp);
    VectorPushBack(nums_stack->stack, &num);
    
    return 0;
}

static Operator_LUT_t EmptyOperator(char *exp, int is_operator)
{
    return 0;
}

static Operator_LUT_t ParenthesisOpen(char *exp, int is_operator)
{
    return 0;
}

static Operator_LUT_t ParenthesisClose(char *exp, int is_operator)
{
    /* calculate all the way to  ( */
}

static Operator_LUT_t OpDecrement(char *exp, int is_operator)
{
    double op1 = 0, op2 = 0;
    double sum = 0;
    size_t index = 0;

    if (is_operator)
    {
        VectorPushBack(operators_stack->stack, exp);
    }
    else
    {
        index = VectorSize(nums_stack);
        op2 = *(double *)VectorGetItemAddress(nums_stack->stack, index);
        VectorPopBack(nums_stack->stack);
        op1 = *(double *)VectorGetItemAddress(nums_stack->stack, index - 1);
        VectorPopBack(nums_stack->stack);
        sum = CalcDecrement(op1, op2);
        
        return sum; 
        
    }

}
static Operator_LUT_t OpIncrement(char *exp, int is_operator)
{
    
}
static Operator_LUT_t OpMultiply(char *exp, int is_operator);
static Operator_LUT_t OpDivide(char *exp, int is_operator);

/*************************
 *      OPERATORS:       *
*************************/
static double CalcDecrement(float f1, float f2)
{
    return f1 - f2;
}

static double CalcIncrement(float f1, float f2)
{
    return f1 + f2;
}

static double CalcMultiply(float f1, float f2)
{
    return f1 * f2;
}

static double CalcDivide(float f1, float f2)
{
    return f1 / f2;
}

static double CalcEmptyOperator(float f1, float f2)
{

    return /**/0;
}

static double CalcNumberFunc(float f1, float f2)
{
    return 0;
}
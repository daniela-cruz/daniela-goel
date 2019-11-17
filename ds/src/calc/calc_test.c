#include <stdio.h> /* printf */

#include "calc.h"


int main()
{
    char *expression = "1+2*3";
    /* double expected = 6; */
    double op = Calculator(expression, 0);
    
    printf("Number of numbers is: %f\n", op);

    return 0;
}
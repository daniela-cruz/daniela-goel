#include <stdio.h> /* printf */

#include "calc.h"

char *expression = "1+2-3*4/4=";

int main()
{
    double op = Calculator(expression, 0);

    /*printf("Number of numbers is: %f\n", op);*/

    return 0;
}
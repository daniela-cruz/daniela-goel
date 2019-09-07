#include <stdio.h> /* printf */
#include <time.h> /* show data type NULL */
 
#define type_name(expr) \
    (_Generic((expr), \
              char: "char", unsigned char: "unsigned char", signed char: "signed char", \
              short: "short", unsigned short: "unsigned short", \
              int: "int", unsigned int: "unsigned int", \
              long: "long", unsigned long: "unsigned long", \
              long long: "long long", unsigned long long: "unsigned long long", \
              float: "float", \
              double: "double", \
              long double: "long double", \
              void*: "void*", \
              default: "?"))
 
int main() 
{
    enum { foo, bar };
    
    printf("%s is of type %s\n", "'a'", type_name('a'));
    printf("%d is of type %s\n", 42, type_name(42));
    printf("%f is of type %s\n", 1.5, type_name(1.5));
    printf("%s is of type %s\n", "foo", type_name(foo));
    printf("%s is of type %s\n", "foo", type_name(foo));
    printf("\n");
    printf("%s is of type %s\n", "NULL", type_name(NULL));
    printf("%s is of type %s\n", "sizeof foo", type_name(sizeof foo));
    printf("%s is of type %s\n", "time(NULL)", type_name(time(NULL)));
    
    return 0;
}

#ifndef __ITOA_H__
#define __ITOA_H__

/*
* The user will proivde an integer input and receive a pointer to a string
* the string will contain the exact same digits as in the original number
*/
char *Itoa(char *dest, int num_src);

/*
* The user will provide a string of digits and the function will convert them to an actual integer
* please note the maximum amount of digits an int type can contain is 10 and review the maximum
* value an int type can contain to avoid unwanted results
*/
int AtoiBase10(const char *nptr);


/*
* Same as above, this function allows you to choose the desired base for conversion, up to 36 base
*/
char *AtoiBase36(int num, char *dest, int base);

#endif

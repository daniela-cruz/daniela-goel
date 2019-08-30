#include <stdio.h> 
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <string.h> /*strlen, strcpy, puts*/

void TestStringFunc(char *str1, char *str2);

int main(int argc, char **argv)
{
	char *str1, *str2;
	
	str1 = *argv;
	argv++;
	str2 = *argv;
	TestStringFunc(str1, str2);
	
	return 0;
}

void TestStringFunc(char *str1, char *str2)
{
	char *cat_str = NULL;
	
	assert((NULL != str1) && (NULL != str2));
	cat_str = (char *)malloc((strlen(str1) + strlen(str2) - 1) * sizeof(char *));
	assert(NULL != cat_str);
	puts(cat_str);
	
	free(cat_str);
	cat_str = NULL;
}



#include <stdio.h> /*standard input-output*/
#include <stdlib.h> /*basic functions, allocations, null etc.*/
#include <string.h> /*string functions*/

#include "String.h" /*This file's declarations*/

#define SIZE 4

void DerUltimateTester();
void StrlenTest();
void StrcmpTest();
void StrcpyTest();
char *MyStrchr(const char *str, int character);
/*MyStrchr test function here*/
char *MyStrdup(const char *string);
/*MyStrdup test function here*/

int main()
{
	DerUltimateTester();
	
	return 0;
}

/*===EXERCISES:===*/
/*STRING.H RE-IMPLEMENTATION:*/
size_t MyStrlen(char *str)
{
	int counter = 0;
	
	while (str[counter] != '\0')
	{
		counter++;
	}
	
	return (size_t)counter;
}

int MyStrcmp(char *str_1, char *str_2)
{	
	while ((*str_1 != '\0' && *str_2 != '\0') && (*str_1 - *str_2 == 0))
	{
		str_1++;
		str_2++;
	}
	
	return *str_1 - *str_2;
}

char* MyStrcpy(char *dest, char *source)
{
	int i = 0;
	
		while (source[i] != '\0')
		{
			dest[i] = source[i];
			i++;
		}
	
	return dest;
}

/*No tests yet:*/
char *MyStrchr(const char *str, int character)
{	
	while ((*str != '\0') && (*str != character))
	{
		str++;
	}
	
	return	(*str == character) ? (char *) str : NULL;
}

char *MyStrdup(const char *string)
{
	int size = strlen(string);
	char *p = (char *)malloc(size * sizeof(char));
	
	while (*string != '\0')
	{
		*p = *string;
		p++;
		string++;
	}
	
	return p;
}

/*===TESTS:===*/
void DerUltimateTester()
{
	int size = SIZE, i = 0;
	/*int compared[] = {32, 32, 0, -32};
	int *com = compared;*/
	char *p_arr[] = {"word", "Hello", "hello", "hello"};
	char *p_cmp[] = {"woRd", "HellO", "hello", "hello "};
	
	StrlenTest();
	
	
}
void StrlenTest() /*MORE CASES NEEDED!! I need to create an array of stirngs!*/
{
	char str[] = "word";
	printf("I gots da %ld characters, yas!\n", MyStrlen(str));
}

void StrcmpTest()
{
	int size = SIZE, i = 0;
	int compared[] = {32, 32, 0, -32};
	int *com = compared;
	char *p_arr[] = {"word", "Hello", "hello", "hello"};
	char *p_cmp[] = {"woRd", "HellO", "hello", "hello "};
	char **p1 = p_arr, **p2 = p_cmp; /*the content of the p_ arrays is an array //
										of pointers*/

	for (i = 0; i < size; i++)
	{
		*p1 = *p_arr[i] ;
		*p2 = *p_cmp[i];
		while (size > 0)
		{
			assert (MyStrcmp(p1, p2) == compared);
			p1++;
			p2++;
			com++;
			size--;
		}
	}
}

void StrcpyTest()
{
	char const str[] = "word", 
	char location[] = {'0', '0', '0', '0', '0', '0', '0', '\0'};
	char *p = MyStrcpy(location, str);
	
	assert ();
}


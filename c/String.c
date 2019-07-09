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
	/*DerUltimateTester();*/
	
	return 0;
}

/*===EXERCISES:===*/
/*STRING.H RE-IMPLEMENTATION:*/
size_t MyStrlen(char *str)
{	
	size_t counter = 0;
	
	while (*str != '\0')
	{
		str++;
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
		while (*source != '\0')
		{
			*dest = *source;
			dest++;
			source++;
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

/*No test yet:*/
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
	size_t size = SIZE, i = 0;
	/*int compared[] = {32, 32, 0, -32};
	int *com = compared;*/
	char arr_1[] = {"word"}, arr_2[] = {"Hello"}, arr_3[] = {"hello"}, 
			arr_4[] = {"hello"};
	char arr_a[] = {"woRd"}, arr_b[] = {"HellO"}, arr_c[] = {"hello"}, 
			arr_d[] = {"hello "};
	char *ptr_arr[] = {arr_1, arr_2, arr_3, arr_4};
	int cmp_arr[] = {arr_a, arr_b, arr_c, arr_d};
	char **p_1 = *ptr_arr[i], **p_2 = cmp_arr[i];
	
	StrlenTest();
	
	
}
void StrlenTest() /*MORE CASES NEEDED!! I need to create an array of stirngs!*/
{
	char str[] = "word";
	printf("I gots da %ld characters, yas!\n", MyStrlen(str));
}

void StrcmpTest()
{
	
	/*char *p1 = p_arr, *p2 = p_cmp; /*points to individual strings*/*/
/*
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
	*/
}

void StrcpyTest()
{
	char const str[] = "word", 
	char location[] = {'0', '0', '0', '0', '0', '0', '0', '\0'};
	char *p = MyStrcpy(location, str);
	
	assert ();
}


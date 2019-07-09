#include <stdio.h> /*standard input-output*/
#include <stdlib.h> /*basic functions, allocations, null etc.*/
#include <string.h> /*string functions*/
#include <assert.h> /*assert*/

#include "String.h" /*This file's declarations*/

#define SIZE 4

void DerUltimateTester();
void StrchrTest();
void StrlenTest();/*need to correct test*/
void StrcmpTest();/*need to correct test*/
void StrcpyTest();/*need to correct test*/
void StrdupTest();/*TEST NOT WORKING!!!*/
char *MyStrcat(char *dest, const char *src);/**/
void CatTest();/*in progress*/
char *Mystrstr(const char *haystack, const char *needle);/**/
void StrstrTest();/*in progress*/

int main()
{
	DerUltimateTester();
	
	return 0;
}

/*===EXERCISES:===*/
/*STRING.H RE-IMPLEMENTATION:*/
size_t MyStrlen(const char *str)
{	
	size_t counter = 0;
	
	while (*str != '\0')
	{
		str++;
		counter++;
	}
	
	return counter;
}

int MyStrcmp(const char *str_1, const char *str_2)
{	
	while ((*str_1 != '\0' && *str_2 != '\0') && (*str_1 - *str_2 == 0))
	{
		str_1++;
		str_2++;
	}
	
	return *str_1 - *str_2;
}

char* MyStrcpy(char *dest, const char *src)
{
	char *ptr = dest;
	
	assert((dest && src));
	
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	
	*dest = '\0';
	
	return ptr;
}

char *MyStrchr(const char *str, int character)
{	
	int size = MyStrlen(str);
	char *ptr = (char *)malloc((size + 1)*sizeof(char));
	
	MyStrcpy(ptr, str);
	
	assert(ptr != NULL);
	
	while ((*ptr != '\0') && (*ptr != (char)character))
	{
		ptr++;
	}
	
	if (*ptr == character)
	{
		return ptr;
	}
	
	return NULL;
}

char *MyStrdup(const char *str)
{
	int size = strlen(str);
	char *p = (char *)malloc((size * sizeof(char))+1);
	
	return MyStrcpy(p, str);
}

char *MyStrcat(char *dest, const char *src)
{
	int size = MyStrlen(src);
	char *new_dest = dest;
	char *source = (char*)malloc(size * sizeof(char));
	
	while (*dest != '\0')
	{
		dest++;
		new_dest++;
	}
	
	MyStrcpy(dest, source);
	
	return new_dest;
}

char *Mystrstr(const char *haystack, const char *needle)
{
	int hay_size = MyStrlen(haystack);
	int nee_size = MyStrlen(needle);
	char p = haystack;
	
	while (hay_size >= nee_size)
	{	
		p = haystack;

		while (MyStrcmp(haystack, needle) == 0)
		{
			needle++;
			nee_size--;	
			haystack++;	
			
			if (hay_size - nee_size == 0)
			{
				return p;
			}
		}
		hay_size--;
	}
	
	return NULL;
}

/*===TESTS:===*/
void DerUltimateTester()
{	
	StrstrTest();
	
	StrlenTest();
}

void StrlenTest()
{
	char *str_2 = "";
	size_t size = 7;
	
	assert((strlen(str_2)) != (size_t)NULL);
	if (size == (MyStrlen(str_2)))
	{
		printf("Success, ladies and gent's! It's: %lx\n", MyStrlen(str_2));
	}
	else
	{
		printf("This is a failure, I repeat - your code's broken! Add one!");
	}
}

/*
void StrcmpTest()
{
	
	size_t size = SIZE, i = 0;
	int compared[] = {32, 32, 0, -32};
	int *com = compared;
	char arr_1[] = {"word"}; , arr_2[] = {"Hello"}, arr_3[] = {"hello"}, 
			arr_4[] = {"hello"};
	char arr_a[] = {"woRd"}, arr_b[] = {"HellO"}, arr_c[] = {"hello"}, 
			arr_d[] = {"hello "};
	char *src = arr_1;
	char *dest = arr_a;

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
*/
void StrcpyTest()
{
	char *src = "word"; 
	char arr[] = {'0', '0', '0', '0', '0', '0', '0', '\0'}, *dest = arr;
	
	dest = MyStrcpy(dest, src);
	
	if(MyStrcmp(src, dest) == 0)
	{
		printf("Successful comparison!\n");
	}
	else
	{
		printf("Failed comparison :(\n");
	}
}

void StrchrTest()
{
	int letter = 87;
	char *str = "lala";
	
	assert(MyStrchr(str, letter) == strchr(str, letter));
}

void StrdupTest()
{
	const char *str = "this is a test";
	char *p = MyStrdup(str);
	
	assert(strcmp(str, p) == strcmp(str, p));
	
	free(p);
}

void CatTest()
{
	char *source = " Satan!";
	char *destination = "Hello again,";
	char *new_ptr = MyStrcat(destination, source);
	
	printf("%c", *new_ptr);
}

void StrstrTest()
{
	const char *hay = "jvbhjhbSatanfghfkjghk";
	const char *needle = "Satan";
	char *p = MyStrstr(hay, needle);
	
	if (p != NULL)
	{
		printf("SUCCESS!!!\n");
	}
	else
	{
		printf("Failure\n");
	}
}

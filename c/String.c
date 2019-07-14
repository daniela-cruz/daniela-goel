#include <stdio.h> /*standard input-output*/
#include <stdlib.h> /*basic functions, allocations, null etc.*/
#include <string.h> /*string functions*/
#include <assert.h> /*assert*/
#include <ctype.h> /*lower case strings*/

#include "String.h" /*This file's declarations*/

#define SIZE 4

static void DerUltimateTester();
static void StrchrTest();
static void StrlenTest();
static void StrcmpTest();
static void StrcpyTest();
static void StrnTest();
static void StrdupTest();
static void CatTest();
static void CatnTest();
static void StrstrTest();
static void CaseTest();


int main()
{
	DerUltimateTester();
	
	return 0;
}

/*STRING.H RE-IMPLEMENTATION:*/
size_t MyStrlen(const char *str)
{	
	size_t counter = 0;
	
	assert(str != NULL);
	
	while ('\0' != *str)
	{
		str++;
		counter++;
	}
	
	return counter;
}

int MyStrcmp(const char *src_1, const char *src_2)
{	
	assert (src_1 != NULL && src_2 != NULL);
	
	while ('\0' != (*src_1) && (*src_1 == *src_2))
	{
		src_1++;
		src_2++;
	}
	
	return *src_1 - *src_2;
}


int MyStrcasecmp(const char *src, const char *str)
{
	assert (src != NULL && str != NULL);
	
	while ('\0' != *src && (tolower(*src) == tolower(*str)))
	{		
		src++;
		str++;
	}	
	
	return tolower(*src) - tolower(*str);
}

char* MyStrcpy(char *dest, const char *src)
{
	char *start = dest;
	
	assert(src != NULL && dest != NULL);
	
	while ('\0' != *src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	
	*dest = '\0';
	
	return start;
}

char *MyStrncpy(char *dest, const char *src, size_t size) 
{
	char *start = dest;
	
	assert(src != NULL);
	
	while (0 < size)
	{
		if ('\0' != *src)
		{
			*dest = *src;
			src++;
		}
		else
		{
			*dest = '\0';
		}
		
		dest++;
		size--;	
	}
	
	return start;
}

char *MyStrchr(const char *string, int character)
{	
	const char *str = string;
	
	assert(str != NULL);
	
	do
	{
		if (*str == character)
		{
			return (char *)str;
		}
		
		str++;
		
	} while ('\0' != *str);
	
	return NULL;
}

char *MyStrdup(const char *str)
{
	int size = strlen(str);
	char *p = "";
	
	assert(str != NULL && size != 0);
	
	p = (char *)malloc(((size + 1) * sizeof(char)));
	
	return MyStrcpy(p, str);
}

char *MyStrcat(char *dest, const char *src)
{
	size_t size = strlen(dest);
	
	MyStrcpy(dest + size, src);
	
	return dest;
}


char *MyStrncat(char *dest, const char *src, size_t size)
{
	char *p = dest;
	
	assert(size > (size_t)0 && *src != '\0');
	
	while ('\0' != *dest)
	{
		dest++;
		size--;
	}
	
	if(MyStrncpy(dest, src, size) == dest)
	{
		return p;
	}
	
	return NULL;
}

char *MyStrstr(const char *haystack, const char *needle)
{
	size_t size = strlen(needle);
	
	assert((needle != NULL) && (haystack != NULL));
	
	while (*haystack != '\0') 
	{	
		if (strncmp(haystack, needle, size) == 0)
		{
			return (char *)haystack;
		}
		
		haystack++;
	}
	
	return NULL;
}

/*===TESTS:===*/
void DerUltimateTester()
{	
	/*CaseTest();
	
	CatnTest();

	StrdupTest();
	
	StrcmpTest();
	
	StrcpyTest();
	
	StrchrTest();
	
	StrnTest();

	CatTest();*/
	
	StrstrTest();
	
	StrlenTest();
}

void StrlenTest()
{
	char arr[SIZE] = {'a', 'b', 'c','\0'}, *str_2 = arr;
	size_t size = 1;
	
	assert((MyStrlen(str_2)) != (size_t)NULL);
	
	if (size == (MyStrlen(str_2)))
	{
		printf("Success, ladies and gent's! It's: %lx\n", MyStrlen(str_2));
	}
	else
	{
		printf("This is a failure, I repeat - your code's broken!\t"); 
		printf("Add %ld more space(s)!\n", MyStrlen(str_2) - size);
	}
}


void StrcmpTest()
{
	const char *src = "word"; 
	char arr[] = {'0', '0', '0', '0', '0', '0', '0', '\0'}, *dest = arr;
	
	if(MyStrcmp(src, dest) == 0)
	{
		printf("Successful comparison");
	}
	else
	{
		printf("Unequal: %d\n", MyStrcmp(src, dest));
	}
}


void CaseTest()
{
	char *src = "Hell";
	char *str = "hello";
	int result = MyStrcasecmp(src, str);
	
	if (result > 0)
	{
		printf("Source is higher: %d\n", result);
	}
	
	else
	{
		printf("String is either higher or same as source: %d\n", result);
	}
}

void StrcpyTest()
{
	const char *src = "word"; 
	char arr[7], *dest = arr;
	
	if(dest == MyStrcpy(dest, src))
	{
		printf("%s\n", MyStrcpy(dest, src));
	}
	else
	{
		printf("Failed copy :(\n");
	}
}


void StrnTest()
{
	const char *src = "loolah";
	char dest[6] = {0};
	size_t size = SIZE;

	if(MyStrncpy(dest, src, size) != NULL)
	{
		printf("%s\n", MyStrncpy(dest, src, size));
	}
	else
	{
		printf("Not enough roon in destination :(\n");
	}
}


void StrdupTest()
{
	const char *str = "Duplicated!";
	char *p = MyStrdup(str);
	
	if (MyStrlen(str) >= 1)
	{
		printf("%s\n", p);
	}
	else
	{
		printf("Empty array\n");
	}
	
	free(p);
}


void StrchrTest()
{
	int letter = 87;
	char *str = "lala";
	
	assert(MyStrchr(str, letter) == strchr(str, letter));
}

void CatTest()
{
	char *source = " Satan!";
	char destination[100] = "Hello again,";
	char *new_ptr = MyStrcat(destination, source);
	
	printf("%s\n", new_ptr);
}

void CatnTest()
{
	const char *source = "Satan!";
	char destination[30] = "Heya, ";
	char *dest = destination;
	size_t location = 6;
	
	printf("%s\n", MyStrncat(dest, source, location));
}

void StrstrTest()
{
	const char *str = "da daniela";
	const char *sub = "dan";
	const char *str_2 = "bbba";
	const char *sub_2 = "bba";
	char *p = MyStrstr(str, sub);
	
	if (p != NULL)
	{
		printf("SUCCESS!!!\n");
		printf("%s\n", MyStrstr(str, sub));
	}
	else
	{
		printf("Failure\n");
	}
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*STRING LIB RE-IMPLEMENTATIONS:*/
int MyStrlen(char *str);
void StrlenTest();
int MyStrcmp(char *str_1, char *str_2);
void StrcmpTest();
char* MyStrcpy(char *dest, char *source);
void StrcpyTest();

/*OTHER EXERCISES:*/
int IsPalindrome(const char *str);
void SevenBoom(int fron, int to);
void IsPalindromeTest();

int main()
{
	StrlenTest();
	StrcpyTest();
	StrcmpTest();
	
	exit (0);
}
/* MyStrlenTest:*/
void StrlenTest()
{
	char str[] = "word";
	printf("I gots da %d characters, yas!\n", MyStrlen(str));
}

/**/
void StrcmpTest()
{
	char *p_1 = "word", *p_2 = "woRd"; 
	int compared = MyStrcmp(p_1, p_2);
	
	printf("The result of comparison is: %d\n", compared);
}

/* MyStrcpyTest:*/
void StrcpyTest()
{
	char str[] = "word", location[] = {'0', '0', '0', '0', '0', '0', '0', '\0'};
	
	MyStrcpy(location, str);
}
/*EXERCISES:*/
/*STRLEN RE-IMPLEMENTATION:*/
int MyStrlen(char *str)
{
	int counter = 0;
	
	while (str[counter] != '\0')
	{
		counter++;
	}
	
	return counter;
}

/*strcmp re-implementation:*/
int MyStrcmp(char *str_1, char *str_2)
{	
	while ((*str_1 != '\0' && *str_2 != '\0') && *str_1 - *str_2 == 0)
	{
		str_1++;
		str_2++;
	}
	
	return *str_1 - *str_2;
}

/*STRCPY RE-IMPLEMENTATION:*/
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

int IsPalindrome(const char *str)
{
	int size = strlen(str), flag = -1, i;

	for (i=0; i<size/2; i++)
	{
		if (str[i] == str[size-i-1])
		{
			flag = 0;
		}
		else
		{
			break;
		}
	}
	
	return flag;
}

/*
void SevenBoom(int from, int to)
{

}
*/

/*===TESTS:===*/
void IsPalindromeTest()
{
	char word_arr[] = {'m', 'a', 'a', 'm'};
	const char *str = word_arr; 
	
	if(IsPalindrome(str) == 0)
	{
		printf("Yasss!\n");
	}
	else
	{
		printf("Ney!\n");
	}
}


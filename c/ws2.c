#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*STRING LIB RE-IMPLEMENTATIONS:*/
int MyStrlen(char *str); /*strlen*/
int MyStrcpy(char *location, char *source);/*strcpy*/

/*OTHER EXERCISES:*/
int IsPalindrome(const char *str);
void SevenBoom(int fron, int to);
void IsPalindromeTest();

int main()
{
	/* MyStrlenTest + MyStrcpyTest:*/
	char str[] = "word", location[] = {'0', '0', '0', '0', '0', '0', '0', '\0'};
	
	printf("I gots da %d characters, yas!\n", MyStrlen(str));
	MyStrcpy(location, str);


	exit (0);
}

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
	int result = *str_1 - *str_2;
	
	while ((*str_1 != '\0' && *str_2 !- '\0') && result == 0)
	{
		str_1++;
		str_2++;
	}
	
	reutrn reuslt;
}
/*STRCPY RE-IMPLEMENTATION:*/
int MyStrcpy(char *location, char *source)
{
	int loc_size = strlen(location), i = 0;
	if (loc_size >= strlen(source))
	{
		while (source[i] != '\0')
		{
			location[i] = source[i];
			i++;
		}
		return 0;
	}
	return -1;
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

void SevenBoom(int fron, int to)
{

}


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


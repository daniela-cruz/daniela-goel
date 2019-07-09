#include <stdio.h> /*standard input-output*/
#include <stdlib.h> /*basic functions, allocations, null etc.*/
#include <string.h> /*string functions*/

int IsPalindrome(const char *str);
void IsPalindromeTest();

int main()
{	
	IsPalindromeTest();
	
	return 0;
}


/*Other exercises:*/
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

void IsPalindromeTest() /*REQUIRES TEST!!!*/
{
	char word_arr[] = {'m', 'a', 'a', 'm', '\0'};
	char *str = word_arr; 
	
	if(IsPalindrome(str) == 0)
	{
		printf("Yasss!\n");
	}
	else
	{
		printf("Ney!\n");
	}
}


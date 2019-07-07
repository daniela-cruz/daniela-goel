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
	char str[] = "word", location[] = {'0', '0', '0', '0', '0', '0', '0', '\0'};
	
	printf("I gots da %d characters, yas!\n", MyStrlen(str));
	MyStrcpy(location, str);

/*	IsPalindromeTest();*/
	exit (0);
}


/*===EXERCISES:===*/

/*STRING LIBRARY RE-IMPLEMENTATOION:*/
int MyStrlen(char *str)
{
/*PSEUDO:*/
/*
1. receive pointer to a char array
2. declare counter = 0
3. while the array in location counter is different than '\0' 
		--> increment counter by 1
4. return counter.

*/
	int counter = 0;
	
	while(*(str+counter) != '\0')
	{
		counter++;
	}
	
	return counter;
}

int MyStrcpy(char *location, char *source)
{
/*PSEUDO:*/
/*
1. Get pointer to desired location
2. get pointer to source string
3. set index to zero
?4. get source string length
5. check if there's enough space:
	- if location array size is >= source string size: 
		- as long as index is smaller than source length:
			copy the character in location index 
			to the location string in location index
		- after that return 0
	- else: return -1

*/
	int loc_size = strlen(location), i = 0;
	if(loc_size >= strlen(source))
	{
		while(*(source+i) != '\0')
		{
			*(location+i) = *(source+i);
			printf("%c", *(location+i));
			i++;
		}
		return 0;
	}
	return -1;
}

/*===exe 5 - IsPalindrome===*/
int IsPalindrome(const char *str)
{
	int size = strlen(str), flag = -1, i;
/*PSEUDO:
1. get a string pointer
2. get arr length
3. set a flag to negative 1 (not a palindrom)
4. Run while 1 is <= to strlen/2:
	-if str_arr[i] == str_len[strlen-i] --> flag is 0 
	-else --> return -1
5. return flag
*/	

	for(i=0; i<size/2; i++)
	{
	printf("%c", *(str+i));
		if(*(str+i) == *(str+size-i-1))
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

/*===exe 6 - SevenBoom===*/
void SevenBoom(int fron, int to)
{
/*PSEUDO:
1. Receive a start and end point
2. calc range size
3. define a string as "BOOM"
4. while we're inside the range of numbers:
	4.1. Check if current number divides by 7 with no residue:
		- if not, then:
			- turn number to string
			- if the string contains '7'
	b. if it doesn't --> print number
	- else --> print "BOOM!"

*/
}
/*===TESTS:===*/
/*IsPalindromeTest*/
void IsPalindromeTest()
{
	char word_arr[] = {'k', 'a', 'k', 'i'};
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

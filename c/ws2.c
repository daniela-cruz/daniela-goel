#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h> /*isspace*/

#define BOOM 7

char *nonsense(char *first, char *last);

static int IsPalindrome(const char *str);
static void IsPalindromeTest();

static void SevenBoom(int from, int to);
static int IsDigit(int num, int residue);
static void BoomTest();

static void Swap(int **ptr_1, int **ptr_2);

static char *RmSpaces(char *str);
char *MoveRmSpaces(char *dest, char *src, size_t spaces_number);
static void TestRmSpaces();

/*ONLINE SOLUTIONS:*/
char *LeftTrim(char *string);
char *RightTrim(char *string);
char *Trim(char *string);
/**/
int main()
{
	/*TestRmSpaces();*/
	
	/*BoomTest();*/
	
	/*IsPalindromeTest();*/
	
	Trim("  lalala fdgjfdg	ffkjdlfkgjd  ");
	
	return 0;
}
/*

WHITE SPACES REMOVER ONLINE:

*/

char *LeftTrim(char *string)
{
	size_t string_length = 0;
	char *current_char = NULL;

	assert(NULL != string);
	current_char = string;
	string_length = strlen(string);
	
	while ('\0' != *string) 
	{
		string_length = strlen(string);
		current_char = string;

		while('\0' != *current_char && isspace(*current_char))
		{
			++current_char, --string_length;
		}

		if(string != current_char)
		{
			memmove(string, current_char, string_length + 1);
		}
	}

	return string;
}

/* Remove trailing whitespaces */
char *RightTrim(char *string)
{
        size_t string_length;
        char *current_char;

        if(string && *string) {
                string_length = strlen(string);
                current_char = string + string_length - 1;

                while(current_char != string && isspace(*current_char))
                        --current_char, --string_length;

                current_char[isspace(*current_char) ? 0 : 1] = '\0';
        }

        return string;
}

/* Remove leading and trailing whitespaces */
char *Trim(char *string)
{
        RightTrim(string);
        LeftTrim(string);

        return string;
}


/**/


/*Exercises:*/
int IsPalindrome(const char *str)
{ 
	const char *start = str;
	const char *end = start + strlen(str) - 1;

	while (end > start)
	{	
		if(*start == *end)
		{
			start++;
			end--;
		}
		else
		{
			return 0;
		}
	}
	
	return 1;
}


void SevenBoom(int from, int to)
{
	int boom = BOOM;
	
	while (from <= to)
	{
		if ((from % boom == 0) || (IsDigit(from, boom) == 1))
		{
			printf("BOOM! ");
		}
		else
		{
			printf("%d ", from);
		}
		
		from++;
	}
	
	printf("\n");
}


static void Swap(int **ptr_1, int **ptr_2)
{
	int *temp = *ptr_1;
	
	*ptr_1 = *ptr_2;
	*ptr_2 = temp;
}


/*7BOOM Internal function:*/
int IsDigit(int num, int residue) /*for 7BOOM*/
{
	while (0 != num)
	{
		if (num % 10 == residue)
		{
			return 1;
		}
		else
		{
			num /= 10;
		}
	}
	
	return 0;
}


char *RmSpaces(char *str)
{
	char *start_str = NULL;
	char *dest = NULL;
	size_t is_wspace = 0;
	
	assert(NULL != str);
	start_str = str;
	dest = str;
	
	while ('\0' != *str)
	{	
		if ('\t' == *str || ' ' == *str)/*count spaces*/
		{
			is_wspace++;
			
			if (start_str == str)
			{
				is_wspace++;
			}
			
			*dest = *str;
		}
		
		is_wspace--;
		str++;
	}
	
	*str = '\0';
	
	return start_str;
}

char *MoveRmSpaces(char *dest, char *src, size_t spaces_number)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	dest = strncpy(dest, src, spaces_number);

	return dest;
}

/*===TESTS:===*/
void IsPalindromeTest()
{
	char *word = "ABABA";
	const char *str = word; 
	
	if(IsPalindrome(str) == 0)
	{
		printf("Yasss!\n");
	}
	else
	{
		printf("Ney!\n");
	}
}


void BoomTest()
{
	SevenBoom(289, 123);
}

void TestRmSpaces()
{
	char *str = "asdf adfafdga";
	char *str2 = "asdf  adfafdga";
	char *str3 = "asdf 	adfafdga";
	char *str4 = "	asdf adfafdga  ";
	
	printf("%s", RmSpaces(str));
	printf("%s", RmSpaces(str2));
	printf("%s", RmSpaces(str3));
	printf("%s", RmSpaces(str4));
}


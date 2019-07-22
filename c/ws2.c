#include <stdio.h> /*print*/
#include <stdlib.h>
#include <string.h> /*strlen*/
#include <assert.h> /*assert*/
#include <ctype.h> /*isspace*/

#define BOOM 7

static int IsPalindrome(const char *str);
static void IsPalindromeTest();

static void SevenBoom(int from, int to);
static int IsDigit(int num, int residue);
static void BoomTest();

static void Swap(int **ptr_1, int **ptr_2);

static char *RmSpaces(char *str);
char *MoveRmSpaces(char *dest, char *src, size_t spaces_number);
static void TestRmSpaces();

int main()
{
	/*TestRmSpaces();*/
	
	/*BoomTest();*/
	
	/*IsPalindromeTest();*/
	
	char *test = "  lalala fdgjfdg	ffkjdlfkgjd  ";
	
	test = RmSpaces(test);
	
	printf("%s", test);
	
	return 0;
}


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
	char *dest = NULL;
	char *dest_start = NULL;
	size_t dest_length = 0;
	
	assert(NULL != str);
	dest_length = strlen(str);
	dest = str;
	dest_start = str;
	str += 1;
	
	while ('\0' != *str) /*rewrite if more than one white space from current char*/
	{	
		if   (0 != ((isspace(*dest)) && (isspace(*str))))
		{	
			dest_start = strcpy(dest, str);
			dest_length--;
		}
		
		dest++;
		str++;
	}
	
	/*use dest length to get back to the beginning of the string*/
	
	while ('\0' != *dest)
	{
		if (0 != isspace(*dest_start))
		{
			dest_start = strcpy(dest_start, dest);
		}
		
		dest++;
	}

	return dest_start;
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


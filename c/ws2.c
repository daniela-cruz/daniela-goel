#include <stdio.h> /*print*/
#include <stdlib.h>
#include <string.h> /*strlen*/
#include <assert.h> /*assert*/
#include <ctype.h> /*isspace*/

#define BOOM 7
#define MAX_ARR_SIZE 100

static int IsPalindrome(const char *str);
static void IsPalindromeTest();

static void SevenBoom(int from, int to);
static int IsDigit(int num, int residue);
static void BoomTest();

static void Swap(int **ptr_1, int **ptr_2);

static char *RmSpaces(char *str);
static void TestRmWhiteSpaces();

int main()
{
	TestRmWhiteSpaces();
	
	/*BoomTest();*/
	
	/*IsPalindromeTest();*/
	
	
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
	char *start_dest = NULL;
	char *start_source = NULL;
	char dest[100] = {0};
	
	assert(NULL != str);
	start_dest = dest;
	start_source = str;
	
	/*FIX EXESS WS AT THE BEGINNING OF THE STRING:*/
	while ( 0 != (isspace(*dest)))
	{
	    if (start_dest == dest)
	    {
			start_dest = strcpy(start_dest, (start_dest + 1));
	    }
	    
	    start_dest++;
	}
	
	/*FIX EXESS WS MID STRING:*/
	while ('\0' != *start_source)
	{	
		if (0 != ((isspace(*start_source) && isspace(*(start_source + 1)))))
		{
			start_source++;
			*start_dest = *start_source;
		}
		else
		{
		    *start_dest = *start_source;
		}
		start_dest++;
		start_source++;
	}
	
	start_dest = dest;
	
	/*FIX EXESS WS AT THE END OF THE STRING:*/
	while ('\0' != *start_dest)
	{
		if (isspace(*start_dest) && ('\0' == *(start_dest + 1)))
		{
			/*start_dest--;*/
			*start_dest = '\0';	
		}
		
		start_dest++;
	}
	
	start_dest = dest;
	
	return start_dest;
}


static void TestRmWhiteSpaces()
{
	char *test1 = "		lalala	fdgjfdg		ffkjdlfkgjd		";
	char *test2 = "lalala		fdgjfdg	ffkjdlfkgjd  ";
	char *test3 = "		lalala		fdgjfdg		ffkjdlfkgjd";
	char buff[100] = {0};
	char *post_removed_spaces = buff;
	
	printf("%s- before\n", test1);
	post_removed_spaces = RmSpaces(test1);
	printf("%s- after\n", post_removed_spaces);
	
	printf("%s- before\n", test2);
	post_removed_spaces = RmSpaces(test2);
	printf("%s- after\n", post_removed_spaces);
	
	printf("%s- before\n", test3);
	post_removed_spaces = RmSpaces(test3);
	printf("%s- after\n", post_removed_spaces);
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


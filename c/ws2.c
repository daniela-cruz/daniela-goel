#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BOOM 7

char *nonsense(char *first, char *last);

static int IsPalindrome(const char *str);
static void IsPalindromeTest();
static void SevenBoom(int from, int to);
static int IsDigit(int num, int residue);
static void BoomTest();
static void Swap(int *ptr_1, int *ptr_2);

int main()
{
	
	/*BoomTest();*/
	
	IsPalindromeTest();
	
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
	int i = from;
	
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


void Swap(int **ptr_1, int **ptr_2)
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


void RmSpaces(char *str)
{
	char *str_sart = str;
	char *spaces = "	 "; /*contains both tab and space characters*/
	size_t is_wspace = strspn(str, spaces);
	size_t size = strlen(str);
	
	while ('\0' != *str)
	{
		if ((1 < is_wspace && (str != (str_start && str + size - 1))) || 
			(0 < is_wspace && (str == ((str_start) || ( str + size - 1)))))
		{
			/*move left the string and add 0 at the end*/
		}
		
	}
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




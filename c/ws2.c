#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LSD 10 /*change Least Significant Digit*/
#define BOOM 7
#define STR "BOOM"

const char *str = STR;

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
	int size = strlen(str) -1; 
	int i = 0;
	char *start = (char *)str;
	char *end = start + size;

	for (i = 0; i < size / 2; i++)
	{	
		if(*start == *end)
		{
			start++;
			end--;
		}
		else
		{
			return -1;
		}
	}
	
	return 0;
}


void SevenBoom(int from, int to)
{
	int boom = BOOM;
	int i = from;
	
	if (to < from) /*if user gave wrong input*/
	{
		i = to;
		to = from;
		from = i;
	}
	
	for (i = from; i <= to; i++)
	{
		if ((i % boom == 0) || (IsDigit(i, boom) == boom))
		{
			printf("%s! ", STR);
		}
		else
		{
			printf("%d ", i);
		}
	}
	
	printf("\n");
}


void Swap(int *ptr_1, int *ptr_2)
{
	int *temp = ptr_1;
	
	ptr_1 = ptr_2;
	ptr_2 = temp;
	
	return;
}


/*Internal functions:*/
int IsDigit(int num, int residue) /*for 7BOOM*/
{
	while (num != 0)
	{
		if (num % LSD == residue)
		{
			return residue;
		}
		else
		{
			num /= LSD;
		}
	}
	
	return num;
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




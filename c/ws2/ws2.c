#include <stdio.h> /*print*/
#include <string.h> /*strlen*/
#include <assert.h> /*assert*/
#include <ctype.h> /* isspace */

#include "ws2.h" /* for current exercise */

#define BOOM 7
enum true_false_t {FALSE = 0, TRUE = 1};


static void IsPalindromeTest();

static int IsDigit(int num, int residue);
static void BoomTest();

static void SwapTest();

static char *SkipWhitespaces(char *str, char *start_str);
static void RmSpacesTest();

int main()
{
	/*IsPalindromeTest();
	BoomTest();
	SwapTest();*/
	RmSpacesTest();
	
	return 0;
}

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
			return FALSE;
		}
	}
	
	return TRUE;
}

static void IsPalindromeTest()
{
	const char *word[] = {"ABABA", "1234543", "abbb a", "98765456789", ""};
	const char **str = NULL; 
	int result_arr[] = {TRUE, FALSE, FALSE, TRUE};
	int *result = NULL;
	
	str = word;
	result = result_arr;
	
	while ('\0' != **str)
	{
		if(IsPalindrome(*str) == *result)
		{
			printf("Success! \n");
		}
		else
		{
			printf("Unexpected result for: %s\n", *str);
		}
		
		str++;
		result++;
	}
}

void SevenBoom(int from, int to)
{
	int boom = BOOM;
	
	while (from <= to)
	{
		if ((0 == from % boom ) || (1 == IsDigit(from, boom)))
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

/*7BOOM Internal function:*/
static int IsDigit(int num, int residue) 
{
	while (0 != num)
	{
		if (residue == num%10)
		{
			return TRUE;
		}
		else
		{
			num /= 10;
		}
	}
	
	return FALSE;
}

static void BoomTest()
{
	SevenBoom(289, 123);
	printf("\n");
	SevenBoom(7, 123);
	printf("\n");
	SevenBoom(-2, 123);
	printf("\n");
	SevenBoom(0, 0);
}

void Swap(int ***pp1, int ***pp2)
{
	int **temp = *pp1;
	
	temp = *pp1;
	*pp1 = *pp2;
	*pp2 = temp;
}

static void SwapTest()
{
	int num = 3;
	int *ptr1 = &num, *ptr2 = &num;
	int **p1 = &ptr1, **p2 = &ptr2;
	
	printf("Number is: %d and num address is: %p\n", **p1, &num);
	printf("Address of ptr1 is: %p saved address on p1: %p \nAddress of ptr2 is: %p saved address on p2: %p \n", &ptr1, p1, &ptr2, p2);
	
	Swap(&p1, &p2);
	
	printf("Post swap - address of ptr1 is: %p saved address on p1: %p \nAddress of ptr2 is: %p saved address on p2: %p \n", &ptr1, p1, &ptr2, p2);
}

void RmSpaces(char *str)
{
    char *runner = NULL;
    char *str_cpy = NULL;
    char *start = NULL;
    int last_space_count = 0;
	
	start = str;
	runner = str;
	str_cpy = str;
	
    while ('\0' != *runner) 
    {
        while ((0 != isspace(*runner)) && (1 < last_space_count))
        {
        		runner++;
        }
        
        if (isspace(*runner)) 
        {
            if (!last_space_count) 
            {
                *str_cpy++ = *runner;
                last_space_count = 1;
            }
        } 
        else 
        {
            *str_cpy++ = *runner;
            last_space_count = 0;
        }
        ++runner;
    }
    *str_cpy = '\0';
    
}

void RmSpacesTest()
{
	char test[] = "      word  longer word     encyclopedia        ";
	
	printf("--%s-- before\n", test);
	RmSpaces(test);
	printf("--%s-- after\n", test);
	/*
	while ('\0' != **test_ptr)
	{
		printf("--%s-- before\n", *test_ptr);
		RmSpaces(*test_ptr);
		printf("--%s-- after\n", *test_ptr);
		
		test_ptr++;
	}
	*/
}

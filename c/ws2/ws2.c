#include <stdio.h> /*print*/
#include <stdlib.h> /* free */
#include <string.h> /*strlen*/
#include <strings.h> /*strdup*/
#include <assert.h> /*assert*/
#include <ctype.h> /* isspace */

#include "ws2.h" /* for current exercise */
#include "String.h" /* strdup */

#define BOOM 7
enum true_false_t {FALSE = 0, TRUE = 1};


static void IsPalindromeTest();

static int IsDigit(int num, int residue);
static void BoomTest();

static void SwapTest();

static char *SkipWhitespaces(char *str, char *start_str);
static void RmSpacesTest();

static char *FindLastChar(char *num);
static int GetDigitsSum(char num1, char num2, int carry, char *sum);
static void AdderTest();

int main()
{
	/*IsPalindromeTest();
	BoomTest();
	SwapTest();
	RmSpacesTest();*/
	AdderTest();
	
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
	
	assert(NULL != str);
	start = str;
	runner = str;
	str_cpy = str;
	
	/* remove from start */
    while (('\0' != *runner) && (0 != isspace(*runner)))
    {
    	runner++;
    }
    
    /* remove excess spaces */
    while ('\0' != *runner) 
    {
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
        runner++;
    }
    
    *str_cpy = '\0';
    
    /* remove whitespaces from end */
    str_cpy--;
    
    while (0 != isspace(*str_cpy))
    {
		*str_cpy = '\0';
		str_cpy--;
    }
}

void RmSpacesTest()
{
	char test[] = "      word  longer word     encyclopedia        ";
	char *test_ptr = NULL;                  
	
	test_ptr = test;
	printf("--%s-- before\n", test_ptr);
	RmSpaces(test_ptr);
	printf("--%s-- after\n", test_ptr);
}

char *Adder(const char *num1, const char *num2, char *sum)
{
	size_t len1 = 0, len2 = 0;
	size_t sum_len = 0;
	int carry = 0;
	char *sum_start = NULL;
	char lsd = 0;
	char *n1 = NULL, *n2 = NULL;
	
	
	n1 = (char *)num1; n2 = (char *)num2;
	sum_start = sum;
	sum_len = strlen(sum);
	len1 = strlen(num1);
	len2 = strlen(num2);
	
	if (len1 < len2)
	{
		n1 = (char *)num2; n2 = (char *)num1;
	}
	
	/* move pointers to last char --lsd-- on both string numbers */
	n1 = FindLastChar(n1);
	n2 = FindLastChar(n2);
	sum = FindLastChar(sum);
	printf("sum is: %s, digit1 is: %c and digit2 is: %c\n", sum, *n1, *n2);
	/* add digit by digit until the smaller number runs out of digits */
	
	while ((0 < len1) || (0 < carry))
	{
		if (0 < len1)
		{
			if (0 < len2)
			{
				carry = GetDigitsSum(*n1, *n2, carry, sum);
				n2--;
				len2--;
			}
			else if (0 < len1)
			{
				carry = GetDigitsSum(*n1, '0', carry, sum);
			}
			
			n1--;
			len1--;
			sum--;
		}
		
		else
		{
			carry = GetDigitsSum('0', '0', carry, sum);
			break;
		}
		
		printf("carry is: %d and sum is: %s\n", carry, sum);
		
		sum_len--;
	}
	
	/* pad remaining msd with zeros */
	while ((sum_start <= sum) && (0 == carry))
	{
		sum--;
		*sum = '0';
	}
	
	return sum_start;
}

static char *FindLastChar(char *num)
{
	while ('\0' != *num)
	{
		num++;
	}
	
	num--;
	
	return num;
}

static int GetDigitsSum(char num1, char num2, int carry, char *sum)
{
	int digits_sum = 0;
	char *sum_start = NULL;
	
	sum_start = sum;
	
	/* calc lsd and carry */
	if ('0' < num2)
	{
		digits_sum = carry + (num1 - '0') + (num2 - '0');
	}
	else
	{
		digits_sum = carry + (num1 - '0');
	}
	printf("digits sum is: %d \n", digits_sum);
	
	if (9 < digits_sum)
	{
		carry = 1;
		digits_sum -= 10;
		*sum = (digits_sum % 10) + '0'; /*add new digits sum*/
	}
	else
	{
		carry = 0;
		*sum = (digits_sum) + '0' ; /*add new digits sum*/
	}
	
	printf("Sum in DigitSum is: %s \n", sum);
	
	return carry;
}

static void AdderTest()
{
	char high_sum[] = "9999";
	char *sum = NULL;
	char *num1 = "923", *num2 = "187";
	
	sum = high_sum;
	sum = Adder(num1, num2, sum);
	
	printf("new sum is: %s\n", sum);
}

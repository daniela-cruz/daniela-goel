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

char *Adder(char *num1, char *num2, char *sum)
{
	char digit1 = 0, digit2 = 0;
	size_t len1 = 0, len2 = 0;
	int lsd = 0; /* least significant digit */
	int carry = 0;
	char *sum_start = NULL;
	char *temp_sum = NULL;
	
	sum_start = sum;
	len1 = strlen(num1);
	len2 = strlen(num2);
	
	/* move pointers to lsd on both */
	while ('\0' != *num1)
	{
		num1++;
	}
	
	while ('\0' != *num2)
	{
		num2++;
	}
	
	/* add digit by digit until the smaller number runs out of digits */
	while ((0 < len1--) && (0 < len2--))
	{
		lsd = carry + (int)(*num1 + *num2);
		
		if (9 < lsd)
		{
			carry = 1;
			lsd -= 10;
		}
		
		temp_sum = (char *)strdup(sum);
		temp_sum = strcpy(temp_sum, sum);
		*sum = (char)lsd;
		sum = strcat(sum, temp_sum);
		
		num1--;
		num2--;
		sum++;
		
		free(temp_sum);
	}
	
	return sum_start;
}

static void AdderTest()
{
	char high_sum[100] = {0};
	char *sum = NULL;
	char *num1 = "123", *num2 = "987";
	
	sum = high_sum;
	sum = Adder(num1, num2, sum);
	
	printf("new sum is: %s\n", sum);
}

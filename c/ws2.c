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

char *RmSpaces(const char *source);
char *RemoveSpaceFromEnd(char *source);
char *RemoveExtraSpacesFromMid(char *destination);
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


char *RmSpaces(const char *source)
{
    char *destination;
    char *destination_start;
    
    assert(NULL != source);

    destination = (char *)malloc((strlen(source) + 1) * sizeof(char));
    destination = strcpy(destination, source);
    destination_start = destination;
    
    while ('\0' != *destination && (0 != (isspace(*destination))))
    {
        destination++;
    }
    
    /*destination_start = strcpy(destination_start, destination);*/
    destination = RemoveSpaceFromEnd(destination);
    destination = destination_start;
    
    while ('\0' != *destination)
    {
        if (0 != (isspace(*destination) && isspace(*(destination + 1))))
        {
            destination = RemoveExtraSpacesFromMid(destination);
        }
        
        destination++;
    }
    
    return destination_start;
}


char *RemoveExtraSpacesFromMid(char *destination)
{
    char *next_char;
    char *destination_start;
    
    assert(NULL != destination);
    destination_start = destination;
    next_char = destination + 1;
    
    while ('\0' != *next_char)
    {
        *destination = *next_char;
        destination++;
        next_char++;
    }
    
    *destination = '\0';
    
    return destination_start;
}

char *RemoveSpaceFromEnd(char *source)
{
    size_t string_length;
    char *end;
    
    assert(NULL != source);
    string_length = strlen(source);

    if (!string_length)
    {
        return source;
    }

    end = source + string_length - 1;
    
    while (end >= source && 0 != isspace(*end))
    {
        end--;
    }
    
    end++;
    *end = '\0';

    while ('\0' != *source && 0 != isspace(*source))
    {
        source++;
    }

    return source;
}


static void TestRmWhiteSpaces()
{
	char test_length = 3;
    char *test[] = {"      word  longer word     encyclopedia        ",
                     " word     longer word encyclopedia    ",
                      "        word    longer word     encyclopedia", '\0'};
    char *post_removed_spaces;
    char i = 0;

    for (; i < test_length; i++)
    {
        printf("%s- before\n", *(test + i));
        post_removed_spaces = RmSpaces(test[i]);
        printf("%s- after\n", post_removed_spaces);
        free(post_removed_spaces);
        
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


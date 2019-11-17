#include <stdio.h> /* printf*/
#include <stdlib.h> /* malloc free */

#include "stack.h" /* */

int RecFibonacci(int num);
static size_t RecStrLen(char *str);
void RecStrCpy(char *dest, char *src);
stack_t *RecStackSort(stack_t *stk);

void RecStkSortTest(size_t size);
void PrintArr(int *array, size_t size);

char dest[] = "hello, blah";
char src[] = "Hey";

int main()
{
    /*size_t  len = 0;*/
    int num = 3;

    
    /*printf("Fibonacci of %d is: %d\n", num, RecFibonacci(num));*/

    /*len = RecStrLen(str);
    printf("size is: %ld\n", len);*/
    
    /*RecStrCpy(dest, src);
    printf("new string is: %s\n", dest);*/

    RecStkSortTest(5);

    return 0;
}

/********************
 *  FUNCTIONS       *
********************/


int RecFibonacci(int num)
{
    static size_t num0 = 0, num1 = 1;

    if (1 >= num)
    {
        return num;
    }
    
    return RecFibonacci(num - 1) + RecFibonacci(num - 2);
}

size_t RecStrLen(char *str)
{
    if ('\0' == *str)
    {
        return 0;
    }
    else 
    {
        return 1 + RecStrLen(str + 1);
    }
}

void RecStrCpy(char *dest, char *src)
{
	*dest = *src;
	
	if ('\0' == *src) 
	{
		dest--;
        *dest = '\0';
        return; 
	}
	
	RecStrCpy(src + 1, dest + 1);
}

int RecStrCmp(const char* s1, const char* s2)
{
	char* str1 = (char*) s1;
	char* str2 = (char*) s2;

	if (('\0' == *str1) && ('\0' == *str2))
	{
		return 0; 
	}

	if (*str1 != *str2)
	{
		return 1;
	}

	str1++; str2++;

	return RecStrCmp(str1, str2);
}

const char* RecStrStr(const char* dest, const char* src)
{
	int i = 0;

    if (*src == '\0')
		return dest;

	for (i = 0; i < RecStrLen((char* )dest); i++)
	{
		if (*(dest + i) == *src) 
		{
			char* ptr = (char* )RecStrStr((char* )dest + i + 1, src + 1);
			return (NULL != ptr) ? ptr - 1 : NULL;
		}
	}

	return NULL;
}
/*
sll_node_t* RecReverse(sll_node_t* node)
    {
        static sll_node_t *head = NULL;
        sll_node_t *node1 = NULL;
        static int counter = 0;

        if (0 == counter)
        {
            head = node;
            counter++;
        }
        
        if (node == NULL)
        {
            return NULL;
        }

        if (node->next == NULL) 
        {
            head = node;
            return node;
        }

        node1 = RecReverse(node->next);
        node1->next = node;
        node->next = NULL;
        
        return node;
    }*/

  stack_t *RecStackSort(stack_t *stk)
  {
    int num1, num2;

    if (1 == StkCount(stk))
    {
        return stk;
    }
    
    num1 = *(int *)StkPeek(stk); StkPop(stk);
    RecStackSort(stk);
    num2 = *(int *)StkPeek(stk);  

    if (num1 > num2)
    {
        StkPop(stk);
        StkPush(stk, &num1);
        StkPush(stk, &num2);
    }
    else
    {
        StkPush(stk, &num1);
    }

    return stk;
  }  

/********************
 *  Internal funcs *
********************/ 
void RecStkSortTest(size_t size)
{
    stack_t *stk = NULL;
    int i = 0;
    int arr[5] = {73, 1, -7, 2, 0};

    stk = StkCreate(size, sizeof(int));

    for ( i = 0; i < size; i++)
    {
        StkPush(stk, &arr[i]);
    }

    printf("Peek shows: %d\n", *(int*)StkPeek(stk));
    /*PrintArr(arr, size);*/
    printf("Printing array:\n");

    for ( i = 0; i < size; i++)
    {
        printf("%d\n", *(arr + i));
    }

    RecStackSort(stk);
    /*PrintArr(arr, size);*/
     printf("Printing array:\n");

    for ( i = 0; i < size; i++)
    {
        printf("%d\n", *(arr + i));
    }

}
/*
void PrintArr(int *array, size_t size)
{
    int i = 0;

    printf("Printing array:\n");

    for ( i = 0; i < size; i++)
    {
        printf("%d\n", *(array + i));
    }
}*/
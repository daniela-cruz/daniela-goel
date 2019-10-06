#include <stdio.h> /*printf*/
#include <stdlib.h> /*escape*/
#include <string.h> /*getchar*/

#define A 65
#define T 84
#define ESC 27

#define ALL_FUNCTIONS 256 /* for the LUT array of functions */

static void PrintOrDieIfElse();
static void PrintOrDieSwitchCase();
static void PrintOrDieLookUpTable();

/* LUT initializations & sub functions: */
static void GetInputKey(void (**FunctionsForLookupTable)(void));
static void InitFuncArray(void (**FunctionsForLookupTable)(void));
static void DummyFunction(); /*dummy function for initializer*/
static void PrintA();
static void PrintT();
static void EscapeFunction();

static PrintOrDieTest();

int main()
{
	system("stty -icanon -echo");
	
	/*PrintOrDieIfElse();*/
	
	/*PrintOrDieSwitchCase();*/
	
	PrintOrDieLookUpTable();
	
	/*PrintOrDieTest();*/
	
	return 0;
}

/*
static PrintOrDieTest()
{
	int i = 0;
	void (*print_functions_ptr)(void) = NULL;
	
	system("stty -icanon -echo");
	
	print_functions_ptr[0] = PrintOrDieIfElse();
	print_functions_ptr[1] = PrintOrDieSwitchCase();
	print_functions_ptr[2] = PrintOrDieLookUpTable();
	
	for (; i < 3; i++)
	{
		print_functions_ptr[i](void);
	}
}
*/

/* Print using IF/ELSE: */
void PrintOrDieIfElse()
{
	char user_input = 0;
	
	printf("Enter character: \n");
	
	while (ESC != user_input)
	{
   		user_input = getchar();
   		
		if (A == user_input)
		{
			PrintA();
		}
		else if (T == user_input)
		{
			PrintT();
		}
		else if (ESC == user_input)
		{
			break;
		}
		else 
		{
			DummyFunction();
		}
	}
	
	EscapeFunction();
}

void PrintOrDieSwitchCase()
{
	char user_input = 0;
	
	printf("Enter character: \n");
	
	while (ESC != user_input)
	{
		user_input = getchar();
		
		switch (user_input)
		{
			case A:
				PrintA();
				break;
		
			case T:
				PrintT();
				break;
				
			case ESC:
				break;
		
			default:
				DummyFunction();
				break;
		}
	}
	
	EscapeFunction();
}

/* LUT */
void PrintOrDieLookUpTable() 
{
	void (*FunctionsForLookupTable[ALL_FUNCTIONS])(void);
	
	InitFuncArray(FunctionsForLookupTable);
	
	GetInputKey(FunctionsForLookupTable);
}

void InitFuncArray(void (**FunctionsForLookupTable)(void))
{
	int i = 0;
	
	for(; i < ALL_FUNCTIONS; i++)
	{
		FunctionsForLookupTable[i] = &DummyFunction;
	}
	
	FunctionsForLookupTable[ESC] = &EscapeFunction;
	FunctionsForLookupTable[A] = &PrintA;
	FunctionsForLookupTable[T] = &PrintT;
}

void GetInputKey(void (**FunctionsForLookupTable)(void))
{
	unsigned char user_input = 0;
	
	printf("Enter character: \n");
	
	while (1)
	{
		user_input = (unsigned char)getchar();
		FunctionsForLookupTable[user_input]();
	}
}

void PrintA()
{
	printf("A pressed\n");
}

void PrintT()
{
	printf("T pressed\n");
}

void EscapeFunction()
{
	printf("Now it's time to die! G'bye!\n");
	system("stty icanon echo");
	
	return 0;
}

void DummyFunction() /*empty function to initialize function array with*/
{
	printf("Wrong key!\n");
}


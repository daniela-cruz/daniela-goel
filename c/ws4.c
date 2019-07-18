#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A 65
#define T 84
#define ESC 27

#define ALL_FUNCTIONS 256 /*for the array of functions*/

void PrintOrDieIfElse();
void PrintOrDieSwitchCase();
void PrintOrDieLookUpTable();
/*LUT initializations & sub functions:*/
void GetInputKey(void (**FunctionsForLookupTable)(void));
void InitFuncArray(void (**FunctionsForLookupTable)(void));
void DummyFunction(); /*dummy function for initializer*/
void PrintA();
void PrintT();
void EscapeFunction();

int main()
{
	system("stty -icanon -echo");
	
	/*PrintOrDieIfElse();*/
	
	/*PrintOrDieSwitchCase();*/
	
	PrintOrDieLookUpTable();
	
	return 0;
}

void GetInputKey(void (**FunctionsForLookupTable)(void))
{
	int user_input = 0;
	
	printf("Enter character: \n");
	
	while (1)
	{
		user_input = getchar();
		FunctionsForLookupTable[user_input]();
	}
}

void PrintOrDieIfElse()
{
	int user_input = 0;
	
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
		else
		{
			DummyFunction();
		}
	}
	
	EscapeFunction();
}

void PrintOrDieSwitchCase()
{
	int user_input = 0;
	
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
		
			default:
				DummyFunction();
				break;
		}
	}
	
	EscapeFunction();
}

void PrintOrDieLookUpTable() /*LUT*/
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
	
	exit(0);
}

void DummyFunction() /*empty function to initialize function array with*/
{
	printf("Wrong key!\n");
}


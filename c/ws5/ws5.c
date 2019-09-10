#include <stdio.h> /* printf */
#include <stdlib.h> /* escape */
#include <string.h> /* getchar */

enum operations {TOP, COUNT, REMOVE, EXIT, APPEND}

struct log_module_t 	
{	
	char *user_input;
	enum function_module(char *user_input, FILE *file_name);
};

void Logger();

int main()
{
	Logger();
	
	return 0;
}

void Logger()
{
	char *str = NULL;
	FILE *file_name = NULL;
	struct log_module_t[] = 	{{"<", AddToTop},
										{"-count", CountLines},
										{"-remove", RemoveFIle},
										{"-exit", Escape},
										{"", Append}};
	enum i = 0;
	
	while (1)
	{
		Printf("Please enter your string\n");
		str = fgets();
		
		for (; i < APPEND; i++)
	{
		if (str == log_module_t[i].user_input)
		{
			log_module_t[i].function_module(str, file_name);
		}
	}
}


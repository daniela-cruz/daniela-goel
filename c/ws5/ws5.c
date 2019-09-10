#ifndef NDEBUG
#define DEBUG_PRINT(s) printf(s)
#endif

#include <stdio.h> /* printf */
#include <stdlib.h> /* escape */
#include <string.h> /* getchar */

#define MODULES_SIZE 2

enum status_t {SUCCESS, ERR_FOPEN};

struct log_module_t 	
{	
	char *user_input;
	enum status_t (*function_module)(const char *user_input, const char *file_name);
};

void Logger();

enum status_t Append(const char *user_input, const char *file_name);
enum status_t EscapeFunction(const char *user_input, const char *file_name);

int main()
{
	Logger();
	
	return 0;
}

void Logger()
{
	char *str = NULL;
	char *file_name = NULL;
	struct log_module_t operations[] = {	/*{"<", AddToTop},
														{"-count", CountLines},
														{"-remove", RemoveFIle},*/
														{"-exit", EscapeFunction},
														{"", Append}};
	int i = 0;
	
	printf("Give your file a name:\n");
	gets(file_name);
	
	while (1)
	{
		Printf("Please enter your string\n");
		gets(str);
		
		for (; i < MODULES_SIZE; i++)
	{
		if (0 == strcmp(str, operations[i].user_input))
		{
			operations[i].function_module(str, file_name);
		}
	}
}

enum status_t Append(const char *user_input, const char *file_name)
{
	FILE *file = NULL;
	
	/*DEBUG_PRINT("Append parsing succeeded!\n")*/
	
	if (NULL == (file = fopen(file_name, "a+")))
	{
		fprintf (stderr, "%s: Couldn't open file %s.\n", file_name);
		return ERR_FOPEN;
	}
	
	fprintf(file, "%s", user_input);
	
	fclose(file_name);
	
	return SUCCESS;
}

enum status_t EscapeFunction(const char *user_input, const char *file_name)
{
	printf("Now it's time to die! G'bye!\n");
	system("stty icanon echo");
	
	exit(0);
}

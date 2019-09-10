#ifndef NDEBUG
#define DEBUG_PRINT(s) printf(s)
#endif

#include <stdio.h> /* printf */
#include <stdlib.h> /* escape */
#include <string.h> /* getchar */

#define MODULES_SIZE 2
#define STR_MAX 100

enum status_t {SUCCESS, FAILURE};

struct operation 	
{	
	char *action_request;
	enum status_t (*action)(const char *, const char *);
};

static void Logger();
static enum status_t Parser(const char *user_input, const char* action_req, size_t index);

static enum status_t Append(const char *user_input, const char *path);
static enum status_t TrueFunction();

static enum status_t EscapeFunction(const char *user_input, const char *path);

int main(int argc, char **argv)
{
	Logger(argv[1]);
	
	(void) argc;
	return 0;
}

void Logger(char *path_input)
{
	char user_input[STR_MAX] = {0};
	char *path = path_input;
	struct operation operations[] = {	/*{"<", AddToTop},
														{"-count", CountLines},
														{"-remove", RemoveFIle},*/
														{"-exit", EscapeFunction},
														{"", Append}};
	size_t i = 0;
	
	while (SUCCESS == operations[i].action(user_input, path))
	{
		printf("Please enter your string\n");
		fgets(user_input, STR_MAX, stdin);
		
		for (; i < MODULES_SIZE; i++)
		{
			if (SUCCESS == Parser(user_input, operations[i].action_request, i))
			{
				operations[i].action(user_input, path);
				break;
			}
		}
	}
}

enum status_t Parser(const char *user_input, const char* action_req, size_t index)
{
	enum status_t status = SUCCESS;
	
	printf("I am the PARSER!\n");
	
	if (0 == index)
	{
		status = SUCCESS;
	}
	else if (index == 1)
	{
		status = TrueFunction();
	}
	else
	{
		status = FAILURE;
	}
	
	return status;
}

enum status_t Append(const char *user_input, const char *path)
{
	FILE *file = NULL;
	
	printf("I am the APPENDER!!\n");
	file = fopen(path, "a+");
	
	if (NULL == file)
	{
		fprintf (stderr, "%s: Couldn't open file %s.\n", "ERROR", path);
		return FAILURE;
	}
	
	fprintf(file, "%s", user_input);
	fclose(file);
	
	return SUCCESS;
}

enum status_t TrueFunction()
{
	return SUCCESS;
}

enum status_t EscapeFunction(const char *user_input, const char *path)
{
	printf("Now it's time to die! G'bye!\n");
	
	exit(0);
} 

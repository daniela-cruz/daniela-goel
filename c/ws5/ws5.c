#ifndef NDEBUG
#define DEBUG_PRINT(s) printf(s)
#endif

#include <stdio.h> /* printf */
#include <stdlib.h> /* escape */
#include <string.h> /* getchar */
#include <assert.h> /* assert */

#define MODULES_SIZE 4
#define STR_MAX 100

typedef enum status {SUCCESS, FAILURE} status_t;

struct operation 	
{	
	char *action_request;
	status_t (*action)(const char *, const char *);
};

static void Logger();
static status_t Parser(const char *user_input, const char* path);

static status_t EscapeFunction(const char *user_input, const char *path);

static status_t Append(const char *user_input, const char *path);
static status_t TrueFunction();

static status_t PushToTop(const char *user_input, const char *path);

static status_t RemoveFile(const char *user_input, const char *path);

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
	size_t i = 0;
	size_t compare = 0;
	status_t status = SUCCESS;
	struct operation operations[] = {	{"<", PushToTop},
														/*{"-count", CountLines},*/
														{"-remove", RemoveFile},
														{"-exit", EscapeFunction},
														{"", Append}};
	
	while (FAILURE != Parser(user_input, path))
	{
		printf("Please enter your string\n");
		fgets(user_input, STR_MAX, stdin);
		/*
		for(; i < )
		{
		
		}*/
	}
}

status_t Parser(const char *user_input, const char* path)
{
	size_t i = 0;
	size_t compare = 0;
	char ch = 0;
	status_t status = SUCCESS;
	struct operation operations[] = {	{"<", PushToTop},
														/*{"-count", CountLines},*/
														{"-remove", RemoveFile},
														{"-exit", EscapeFunction},
														{"", Append}};
	
	printf("I am the PARSER!\n");
	
	ch = *user_input;
	
	switch(ch)
	{
		case '<':
			status = PushToTop(user_input, path);
			break;
		
		case '-':
			{
				compare = strlen(user_input);
				(0 == strncmp(user_input, "-exit", compare)) ? status = EscapeFunction(user_input, path): status;
				
			}
			break;
		
		default:
			status = Append(user_input, path);
			break;
	
	}
		/*
		if ('<' == *user_input)
		{
			PushToTop(user_input, path);
		}
		else if (strlen(operations[i].action_request) + 1 == strlen(user_input))
		{
			printf("I am the first exit condition!\n");
			
			if (0 == strncmp(user_input, operations[i].action_request, compare))
			{
				printf("I am the second exit condition!\n");
				EscapeFunction(user_input, path);
			}
			
			break;
		}
		else if (user_input)
		{
			Append(user_input, path);
			break;
		}
		else
		{
			status = FAILURE;
		
	}*/

	return status;
}

static status_t PushToTop(const char *user_input, const char *path)
{
	FILE *temp_file = NULL;
	FILE *file = NULL;
	char ch = 0;
	
	assert(NULL != user_input);
	user_input++;
	file = fopen(path, "a+");
	temp_file = fopen("temp_file", "w");
	
	if (path == NULL)
	{
	  printf("Error! Can't open file!\n");
	  exit(1);
	}
	
	/*go to the beginnig of the file and send back a pointer*/	
	Append(user_input, "temp_file");
	temp_file = fopen("temp_file", "a+");
	
	while(1)
	{
		ch = fgetc(file);

		if (ch == EOF)
		{
			break;
		}
		putc(ch, temp_file);
	} 

	RemoveFile("-remove", path);
	rename("temp_file", path);
	fclose(temp_file);
	
	return SUCCESS;
}

status_t RemoveFile(const char *user_input, const char *path)
{
	int status = remove(path);
	
	if (status == 0)
	{
		printf("%s file deleted successfully.\n", path);
	}
	else
	{
		printf("Unable to delete the file\n");
		/*ERROR NEEDED HERE*/
	}
	
	return SUCCESS;
}

status_t Append(const char *user_input, const char *path)
{
	FILE *file = fopen(path, "a+");
	
	printf("I am the APPENDER!!\n");
	
	if (NULL == file)
	{
		fprintf (stderr, "%s: Couldn't open file %s.\n", "ERROR", path);
		return FAILURE;
	}
	
	fprintf(file, "%s", user_input);
	fclose(file);
	
	return SUCCESS;
}

status_t TrueFunction()
{
	return SUCCESS;
}

status_t EscapeFunction(const char *user_input, const char *path)
{
	printf("Now it's time to die! G'bye!\n");
	/*exit(0);*/
	
	return FAILURE;
} 

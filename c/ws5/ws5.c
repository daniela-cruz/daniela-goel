#ifndef NDEBUG
#define DEBUG_PRINT(s) printf(s)
#endif

#include <stdio.h> /* printf */
#include <stdlib.h> /* escape */
#include <string.h> /* getchar */
#include <assert.h> /* assert */

#define MODULES_SIZE 5
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
static status_t PushToTop(const char *user_input, const char *path);
static status_t RemoveFile(const char *user_input, const char *path);
static status_t CountLines(const char *user_input, const char *path);

static void TestLogger();

int main(int argc, char **argv)
{
	/*Logger(argv[1]);*/
	TestLogger();
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
	
	while (SUCCESS == Parser(user_input, path))
	{
		printf("Please enter your string\n");
		fgets(user_input, STR_MAX, stdin);
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
	
	ch = *user_input;
	
	switch(ch)
	{
		case '<':
			status = PushToTop(user_input, path);
			break;
		
		case '-':
			{
				compare = strlen(user_input) - 1;
				(0 == strncmp(user_input, "-exit", compare)) ? status = EscapeFunction(user_input, path): status;
				(0 == strncmp(user_input, "-remove", compare)) ? status = RemoveFile(user_input, path): status;
				(0 == strncmp(user_input, "-count", compare)) ? status = CountLines(user_input, path): status;
			}
			break;
		
		default:
			status = Append(user_input, path);
			break;
	}

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

status_t CountLines(const char *user_input, const char *path)
{
	FILE *file = NULL;
    char line[STR_MAX];
    size_t counter = 0; /*Number of lines*/
    status_t status = SUCCESS;

    file = fopen(path, "r");
   
    if (file == NULL)
    {
        fprintf(stderr, "Error: Unable to open file");
        status = FAILURE;
    }


    while(fgets(line, sizeof(line), file) != NULL)
    {
        counter++;
    }

    printf("Number of lines in the file is %ld\n", counter);
    
    fclose(file);
    
    return status;
}

status_t Append(const char *user_input, const char *path)
{
	FILE *file = fopen(path, "a+");
	
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
	
	return FAILURE;
} 

static void TestLogger()
{
	const char *path = "file_1.txt";
	const char *user_inpt[] = {"blahblah\n", "lala\n", "-count\n", "<I'm on top!\n", "-remove", "-exit"};
	size_t i = 0;
	
	for (; i < MODULES_SIZE + 1; i++)
	{
		if (!Parser(user_inpt[i], path))
		{
			printf("Test no %ld is successful!\n", i + 1);
		}
		else
		{
			printf("Test no. %ld is a failure! Well... if we're here and it's number 6 then it's a SUCCESS!!!\n", i + 1);
		}
	}
}

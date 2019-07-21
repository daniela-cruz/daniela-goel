#include <stdio.h> /*stdin*/
#include <stdlib.h> /*printf*/
#include <string.h> /*strcmp*/

#define MAX 100

enum logfunc {APPEND, COUNT, REMOVE, PUSHANDAPPEND, EXIT, ERROR};

void Logger(char *file_name);
int CompareString(const char *user_string, const char *string);
int TrueFunction(const char *new_file, const char *string);

struct module
{
	const char *string;
	int (*compare)(const char *, const char *);
	enum logfunc (*operation)(const char *new_file, const char *string);
};

enum logfunc WriteToFile(const char *new_file, const char *string);
enum logfunc CountLines(const char *new_file, const char *string);
enum logfunc RemoveFile(const char *new_file, const char *string);
enum logfunc PushAndWriteToFile(const char *new_file, const char *string);
enum logfunc EscapeFunction(const char *new_file, const char *string);

int main()
{
	Logger("new_file");
		
	return 0;
}

void Logger(char *file_name)
{
	
	size_t modules_number = 0; /*sizeof(operation_arr) / sizeof(OPERATION);*/
	char user_string[MAX] = {0};
	FILE *new_file = fopen(file_name, "w");
	
	struct module logfunc[] =	{{"-count", strcmp, CountLines},
 									 	{"", TrueFunction, WriteToFile}, 
										{"-remove", strcmp, RemoveFile},
									 	{"<", strcmp, PushAndWriteToFIle},
									 	{"-exit", strcmp, EscapeFunction}};
	
	modules_number = 5;
	
	while (1)
	{
		size_t i = 0;
		
		fgets(user_string, MAX, stdin);
		i = CompareString(user_string, logfunc[i].string);
		
		while (i < modules_number)
		{
			logfunc[i].operation(file_name, user_string);
			break;
		}
    }

}

/*File handling:*/
int CompareString(const char *user_string, const char *string)
{
	int is_equal = 0;
	
	if (0 == strcmp(user_string, string))
	{
		is_equal = 1;
	}
	
	return is_equal;
}


int TrueFunction(const char *new_file, const char *string)
{
	return 1;
}

enum logfunc WriteToFile(const char *new_file, const char *string)
{
	FILE *file_name = fopen(new_file, "a");	
	
	if(file_name == NULL)
	{
	  printf("Error!");
	  exit(1);
	}

	fprintf(file_name,"%s", string);
	fclose(file_name);
	
	return APPEND;
}

enum logfunc CountLines(const char *new_file, const char *string)
{
	int lines_counter = 0;
	int ch = 0;
	FILE *file_ptr = fopen(new_file, "r");
	
	while(!feof(file_ptr))
	{
		ch = fgetc(file_ptr);
		
		if(ch == '\n')
		{
			lines_counter++;
		}
	}
	
	fclose(file_ptr);
	
	return COUNT;
}



enum logfunc RemoveFile(const char *new_file, const char *string)
{
	int status = remove(new_file);
	
	if (status == 0)
	{
		printf("%s file deleted successfully.\n", new_file);
	}
	else
	{
		printf("Unable to delete the file\n");
		/*ERROR NEEDED HERE*/
	}
 
	return REMOVE;
}

enum logfunc PushAndWriteToFile(const char *new_file, const char *string)
{
	const char *start = NULL;
	FILE *beginning_of_file = NULL;
	
	assert(NULL != string);
	start = string++; /*remove the < sign*/
	
	if(new_file == NULL)
	{
	  printf("Error! Can't open file!\n");
	  exit(1);
	}
	
	/*go to the beginnig of the file and send back a pointer*/
	WriteToFile(new_file, start);
	
	return PUSHANDAPPEND;
}

enum logfunc EscapeFunction(const char *new_file, const char *string)
{
	printf("G'bye!\n");
	
	exit(0);
}



#include <stdio.h> /*stdin*/
#include <stdlib.h> /*printf*/
#include <string.h> /*strcmp*/
#include <assert.h> /*assert*/

#define MAX 100

enum log_function {APPEND, COUNT, REMOVE, PUSHANDAPPEND, EXIT, ERROR};

struct module
{
    const char *string;
    int (*compare)(const char *, const char *);
    enum log_function (*operation)(const char *new_file, const char *string);
};

void Logger(const char *file_name);
int IsOpen(const char *file_name);
int CompareString(const char *user_string, const char *string);
int CompareChar(const char *user_string, const char *string);
int TrueFunction(const char *new_file, const char *string);
enum log_function WriteToFile(const char *new_file, const char *string);
enum log_function CountLines(const char *file_name, const char *string);
enum log_function RemoveFile(const char *new_file, const char *string);
enum log_function PushAndWriteToFile(const char *new_file, const char *string);
enum log_function EscapeFunction(const char *new_file, const char *string);

int main()
{
    Logger("new_file");
        
    return 0;
}

void Logger(const char *file_name)
{
    
    size_t modules_number = 0; /*sizeof(operation_arr) / sizeof(OPERATION);*/
    char user_string[MAX] = {0};
    
    struct module log_function[] =    {{"-count\n", CompareString, CountLines},
                                        {"-remove\n", CompareString, RemoveFile},
                                         {"<", CompareChar, PushAndWriteToFile},
                                         {"-exit\n", CompareString, EscapeFunction},
                                         {"", TrueFunction, WriteToFile}};
    
    modules_number = 5;
    
    while (1)
    {
        size_t i = 0;    
        
        printf("type your command here:\n");
        fgets(user_string, MAX, stdin);
        
        
        while (i < modules_number)
        {
            if (log_function[i].compare(user_string, log_function[i].string))
            {
                log_function[i].operation(file_name, user_string);
                break;
            }
            
            i++;
        }
        
    }

}


int CompareString(const char *user_string, const char *string)
{
    int is_equal = 0;
    
    if (0 == strcmp(user_string, string))
    {
        is_equal = 1;
    }
    
    return is_equal;
}


int IsOpen(const char *file_name)
{
	int is_open = 1;
	FILE *opened_file = NULL;
	
	assert(NULL != file_name);
	opened_file = fopen(file_name, "a+"); 
	
	if(opened_file == NULL)
    {
      printf("Error! Unable to open file\n");
      is_open = 0;
    }
	
	return is_open;
}

int CompareChar(const char *user_string, const char *string)
{
    int is_equal = 0;
    
    if (*string == *user_string)
    {
        is_equal = 1;
    }
    
    return is_equal;
}

int TrueFunction(const char *new_file, const char *string)
{
    return 1;
}

enum log_function WriteToFile(const char *new_file, const char *string)
{
    FILE *file_name = fopen(new_file, "a+");    
    
    if(!IsOpen(new_file))
    {
      printf("Error! Unable to write to file.\n");
      exit(1); /*return -APPEND*/
    }

    fprintf(file_name,"%s", string);
    fclose(file_name);
    
    return APPEND;
}

enum log_function CountLines(const char *file_name, const char *string)
{
    int lines_counter = 0;
    int ch = 0;
    FILE *file_ptr = NULL;
    
    assert(NULL != file_name);
    file_ptr = fopen(file_name, "r");
    
    if(!IsOpen(file_name))
    {
      printf("Error! Unable to count lines on file\n");
      exit(1); /*return -COUNT*/
    }
    
    ch = fgetc(file_ptr);
    
    while(ch != EOF)
    {    
        if(ch == '\n')
        {
            lines_counter++;
        }
        
        ch = fgetc(file_ptr);
    }
    
    fclose(file_ptr);
    
    printf("The file contains %d lines.\n", lines_counter);
    
    return COUNT;
}



enum log_function RemoveFile(const char *new_file, const char *string)
{
    int status = remove(new_file);
    
    if (status == 0)
    {
        printf("%s file deleted successfully.\n", new_file);
    }
    else
    {
        printf("Unable to delete the file\n");
        /*return -REMOVE*/
    }
 
    return REMOVE;
}


enum log_function PushAndWriteToFile(const char *file_name, const char *string)
{
    FILE *beginning_of_file = NULL;
    FILE *beginning_of_temp = NULL;
    char ch = 0;
    
    assert(NULL != string);
    
    if(!IsOpen(file_name))
    {
      printf("Error! Can't push string up!\n");
      exit(1); /*return -PUSHANDAPPEND*/
    }
    
    string++;
    beginning_of_file = fopen(file_name, "a+");
    beginning_of_temp = fopen("temp_file", "w");
    /*go to the beginnig of the file and send back a pointer*/    
    WriteToFile("temp_file", string);
    beginning_of_temp = fopen("temp_file", "a+");
    
    while(1)
    {
        ch = fgetc(beginning_of_file);

        if (ch == EOF)
        {
            break;
        }
        putc(ch, beginning_of_temp);
    }

    RemoveFile(file_name, "-remove");
    rename("temp_file", file_name);
    fclose(beginning_of_temp);
    
    return PUSHANDAPPEND;
}


enum log_function EscapeFunction(const char *new_file, const char *string)
{
    printf("G'bye!\n");
    
    exit(0);
}





#include <stdio.h>
#include <string.h>

static void Logger(); 
static FILE *OpenFile();/*CORRECT THE PATH TO UBUNTU'S!!!*/
static FILE *WriteToFile(FILE *new_file, char *string);/*CHECK WHEN TO FCLOSE!!*/
int CountLines(FILE *new_file);
void Infrastructure();

enum functions_array = {Remove, Count, Exit, MoveUp, ERROR};



int main()
{
	Logger();
	
	return 0;
}

void Logger()
{
	struct logger_module 
	{
		char *string; 
		int strcmp(string, const char *input);
		int functions_array;
	};
	
	Infrastructure();
}

void Infrastructure()
{
	char *string = "";
	/*Get input from user*/
	while (1)
	{
		FILE *new_file = OpenFile();
		
		while (RemoveFile)
		{
			/*write to file*/
			WriteToFile(new_file, string);
			CountLines(new_file);
		}
	}
}

int CountLines(FILE *new_file)
{
	int lines_counter = 0;
	int ch = 0;
	
	assert(NULL != string);
	
	while(!feof(new_file))
	{
		ch = fgetc(new_file);
		
		if(ch == '\n')
		{
			lines_counter++;
		}
	}
	
	return lines_counter;
}

/*File handling:*/
FILE *OpenFile()
{
	int num;
	FILE *new_file;
	
	new_file = fopen("C:\\program.txt","w");
   	
   	if(new_file == NULL)
	{
		printf("Error!");   
		exit(1);             
	}
   
   return new_file;
}

FILE *WriteToFile(FILE *new_file, char *string)
{
	assert(NULL != string);
	
   	fprintf(new_file,"%s",string);
   	fclose(new_file);
   
   return new_file;
}

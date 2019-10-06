#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void CopyEnvp(char** envp);
char* CopyLower(char* envp, char* buffer);
void Free(char ** buffer);

int main(int argc, char* argv[], char* envp[])
{
	CopyEnvp(envp);

	return 0;
}

void CopyEnvp(char** envp)
{
	int i, j, k;
	char **buffer = NULL;
	char **buffer_start = NULL;
	
	for (i = 0; *(envp+i) != NULL; i++);
	
	buffer = (char**)malloc(i + 1);
	buffer_start = buffer;

	for (i = 0; envp[i] != NULL; i++)
	{
		/*for (j = 0; envp[i][j] != '\0'; j++);*/
		j = strlen(*(envp + i));
		buffer[i] = (char *)malloc((j + 1) * sizeof(char));
		buffer[i]= CopyLower(envp[i], buffer[i]); 
		
	}

	buffer[i + 1] = NULL;
	
	for (k = 0; k < i; k++)
	{
		printf("%s\n" ,*(buffer + k));
	}
	
	Free (buffer);
	/*free(buffer);*/

}

char* CopyLower(char* envp, char* buffer)
{
	char* start = NULL;
	
	start = buffer;
	while (*envp)
	{
		*buffer = tolower(*envp);
		buffer++;
		envp++;
	}
	
	buffer++;
	*buffer = '\0';
	
	return start;
}

void Free(char ** buffer)
{
	int i =0;
	
	for (i=0; buffer[i] != NULL ; i++)
		free (buffer[i]);
	
}


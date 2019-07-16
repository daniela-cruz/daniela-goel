#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/
#include <string.h>	/*strcpy*/
#include <ctype.h> /*tolower*/
#include <assert.h> /*assert*/

/*EXERCISE 1:*/
static void ShowEnvironment(const char **envp);/**/
size_t GetEnvironmentLength(const char **envp);/**/
static char **AllocateEmptyEnvitonment(const char **envp, size_t envp_length);/**/
static char **CopyLowerEnvironment(const char **envp, char **lower_case_envp, 
								   size_t envp_length);/**/
static void PrintEnvironment(const char **lower_case_envp, size_t string_number);/**/
void FreeLowerEnvironment(char **lower_case_envp, size_t string_number);/**/

/*EXERCISE 2:*/
static size_t SwordStory(size_t soldiers_number);
static size_t FIndNextAlive(int *sword, size_t soldier_index, size_t field_size);
static void TestSwordStory();

int main(int argc, char *argv[], char **envp)
{
	ShowEnvironment((const char **)envp);
	
	/*TestSwordStory();*/
	
	return 0;
}

/*EXERCISE 1:*/
static void ShowEnvironment(const char **envp)
{
	size_t envp_length = 0;
	char **lower_case_envp = NULL;
	
	assert(envp != NULL);
	
	/*1. get envp's number of strings*/
	envp_length = GetEnvironmentLength(envp);
	
	/*2. allocate proper space*/
	lower_case_envp = AllocateEmptyEnvitonment(envp, envp_length);
	
	/*3. go over each string and copy + to lower each char*/
	lower_case_envp = CopyLowerEnvironment(envp, lower_case_envp, envp_length);
	
	/*4. print strings*/
	PrintEnvironment((const char **)lower_case_envp, envp_length);
	
	/*5. free each string*/
	FreeLowerEnvironment(lower_case_envp, envp_length);

}


void FreeLowerEnvironment(char **lower_case_envp, size_t string_number)
{
	while (0 < string_number)
	{
		free(*lower_case_envp);
		lower_case_envp = NULL;
		lower_case_envp++;
		string_number--;
	}
}

static char **AllocateEmptyEnvitonment(const char **envp, size_t envp_length)
{
	char **buffer = NULL;
	
	buffer = (char **)malloc(envp_length * sizeof(char *));
	
	while (0 < envp_length)
	{
		*buffer = (char *)malloc((strlen(*envp) + 1) * sizeof(char));
		envp++;
		buffer++;
		envp_length--;
	}
	
	return buffer;
}

static void PrintEnvironment(const char **lower_case_envp, size_t string_number)
{
	assert(lower_case_envp != NULL);
	
	while (0 < string_number)
	{
		while ('\0' != *lower_case_envp)
		{
			printf("%s", *lower_case_envp);
			*lower_case_envp++;
		}
		
		printf("\n");
		lower_case_envp++;
		string_number--;
	}	
}

static char **CopyLowerEnvironment(const char **envp, char **lower_case_envp, 
								   size_t envp_length)
{
	/*char **start_of_lower_envp = lower_case_envp;*/
	assert(lower_case_envp != NULL);
	
	while (0 < envp_length)
	{
		while ('\0' != *envp)
		{
			**lower_case_envp = tolower(**envp);
			*lower_case_envp++;
			*envp++;
		}
		
		**lower_case_envp = '\0';
		envp++;
		envp_length--;
	}
	
	*lower_case_envp = '\0';
	
	return lower_case_envp -= envp_length;
}

size_t GetEnvironmentLength(const char **envp)
{
	size_t num_of_strings = 0;
	
	assert(envp != NULL);
	
	while ('\0' != envp)
	{	
		num_of_strings++;
		envp++;
	}
	
	return num_of_strings;
}

/*EXERCISE 2:*/
static size_t SwordStory(size_t battle_field_size)
{
	int *soldiers = (int *)calloc(battle_field_size, sizeof(int)); /*an array of zeros*/
	int is_stabbed = 0; /*zero if it's kill time*/
	size_t dead_soldiers_number = 0;
	size_t i = 0; /*soldier number is i + 1*/
	
	while (dead_soldiers_number + 1 < battle_field_size)
	{
		i = FIndNextAlive(soldiers, i + 1, battle_field_size);
		
		if (0 == is_stabbed) /*if we find a live soldier*/
		{
			*(soldiers + i - 1) = 1;
			is_stabbed = 1;/*mark as killed*/
			dead_soldiers_number++;
		}
		
		i = FIndNextAlive(soldiers, i + 1, battle_field_size);
		is_stabbed = 0;/*sword passed to next live soldier*/
		/*sword = soldiers + soldier_index;*/
	}
	
	free(soldiers);
	
	return i + 1; 
}

static size_t FIndNextAlive(int *soldiers, size_t soldier_index, size_t field_size)
{
	
	if (soldier_index == field_size) /*makes sure to check within the field*/
	{
		soldier_index = 1;
	}
	if (soldier_index > field_size) /*makes sure to check within the field*/
	{
		soldier_index = 2;
	}
	
	for (; soldier_index <= field_size; soldier_index++)
	{	
		
		if (*(soldiers + soldier_index - 1) == 0) /*if zero -> soldier is alive*/
		{
			return soldier_index;
		}
		
		if (soldier_index == field_size) /*makes sure to check within the field*/
		{
			soldier_index = 1;
		}
	}
	
	return soldier_index;	
}


static void TestSwordStory()
{
	size_t soldiers_number = 4, soldiers_number_2 = 100;
	size_t last_soldier = SwordStory(soldiers_number);
	
	printf("Location of soldier is %lu\n", last_soldier);
	
	last_soldier = SwordStory(soldiers_number_2);
	
	printf("Location of soldier is %lu\n", last_soldier);
}

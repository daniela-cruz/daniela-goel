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
static void PrintEnvironment(const char **lower_case_envp, size_t envp_length);/**/
void FreeLowerEnvironment(char **lower_case_envp, size_t envp_length);/**/

/*EXERCISE 2:*/
static size_t SwordStory(size_t soldiers_number);
static size_t FIndNextAlive(int *sword, size_t soldier_index, size_t field_size);
static void TestSwordStory();

int main(int argc, char *argv[], char **envp)
{
	/*ShowEnvironment((const char **)envp);*/
	
	TestSwordStory();
	
	(void)argc;
	(void)argv;
	
	return 0;
}

/*EXERCISE 1:*/
static void ShowEnvironment(const char **envp)
{
	size_t envp_length = 0;
	char **lower_case_envp = NULL;
	
	assert(envp != NULL);

	envp_length = GetEnvironmentLength(envp);
	
	lower_case_envp = AllocateEmptyEnvitonment(envp, envp_length);
	
	lower_case_envp = 	CopyLowerEnvironment(envp, lower_case_envp, 
						envp_length);
	
	PrintEnvironment((const char **)lower_case_envp, envp_length);
	
	
	FreeLowerEnvironment(lower_case_envp, envp_length);
	

}

size_t GetEnvironmentLength(const char **envp)
{
	size_t num_of_strings = 0;
	
	while ('\0' != **envp)
	{	
		num_of_strings++;
		envp++;
	}
	
	return num_of_strings;
}


static char **AllocateEmptyEnvitonment(const char **envp, 
			size_t envp_length)
{
	char **buffer_start = NULL;
	char **buffer = NULL;
	
	assert(0 < envp_length);
	
	buffer = (char **)malloc(envp_length * sizeof(char *));
	buffer_start = buffer;
	
	assert(buffer != NULL);
	
	while ('\0' != **envp)
	{
		*buffer = (char *)malloc(strlen((*envp) + 1) * sizeof(char));
		envp++;
		buffer++;
	}
	
	return buffer_start;
}

static void PrintEnvironment(const char **lower_case_envp, size_t envp_length)
{
	assert(lower_case_envp != NULL);
	
	/*envp_length = 3;*/
	
	while ('\0' != **lower_case_envp)
	{
		printf("%s\n", *lower_case_envp);
		lower_case_envp++;
	}	
	
	printf("\n");
}

static char **CopyLowerEnvironment(const char **envp, char **lower_case_envp, size_t envp_length)
{
	size_t i = 0, j = 0;
	
	assert(lower_case_envp != NULL);
	
	envp_length = 3; /*TEST*/
	
	for (i = 0; i < envp_length; i++)
	{
		while ('\0' != envp[i][j])
		{
			lower_case_envp[i][j] = tolower(envp[i][j]);
			j++;
		}
		
		lower_case_envp[i][j] = '\0';
		envp_length--;
	}
	
	lower_case_envp[i][j] = '\0';
	
	return lower_case_envp;
}

void FreeLowerEnvironment(char **lower_case_envp, size_t envp_length)
{
	while (0 < envp_length)
	{
		free(*lower_case_envp);
		lower_case_envp = NULL;
		lower_case_envp++;
		envp_length--;
	}
	
	free(lower_case_envp);
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

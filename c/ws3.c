#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/
#include <string.h>	/*strcpy*/
#include <ctype.h> /*tolower*/
#include <assert.h> /*assert*/

size_t string_number = 0;
size_t string_length = 0;

void ShowEnvironment(const char **envp);
char **AllocateEmptyEnvitonment(const char **envp);
char **CopyLowerEnvironment(const char **envp, char **lower_case_envp);
void PrintEnvironment(const char **lower_case_envp);

size_t SwordStory(size_t soldiers_number);
size_t FIndNextAlive(int *sword, size_t soldier_index, size_t field_size);
void TestSwordStory();

int main(int argc, char *argv[], char **envp)
{
	ShowEnvironment((const char **)envp);
	
	/*TestSwordStory();*/
	
	return 0;
}

/*EXERCISE 1:*/
void ShowEnvironment(const char **envp)
{
	size_t envp_length = 0;
	char **lower_case_envp = NULL;
	const char *test_string[] = {"nonsense", "test2", "test3", "test4", '\0'};
	
	assert(envp != NULL);
	
	/*allocate proper space*/
	lower_case_envp = AllocateLowerEnvironment(envp);
	
	/*go over each string and copy + to lower each char*/
	lower_case_envp = CopyLowerEnvironment(envp, lower_case_envp);
	
	/*print strings*/
	PrintEnvironment((const char **)lower_case_envp);
	
	/*free*/
	free(lower_case_envp);

}

char **AllocateEmptyEnvitonment(const char **envp)
{
	size_t counter = 0;
	size_t string_number = 1;
	size_t string_length = 0;
	char **buffer = NULL;
	
	while ('\0' != envp)
	{
		envp++;
		string_number++;
	}
	
	buffer = (char **)malloc(string_number * sizeof(char *));
	
	while ('\0' != *envp)
	{
		*buffer = malloc((strlen(*envp) + 1) * sizeof(char));
		envp++;
		buffer++;
	}
	
	return buffer;
}

void PrintEnvironment(const char **lower_case_envp)
{
	int counter = 0; /*TEST VARIABLE!*/
	
	assert(lower_case_envp != NULL);
	
	while (/*'\0' != lower_case_envp*/ counter < 4)
	{
		while ('\0' != *lower_case_envp)
		{
			printf("%s", *lower_case_envp);
			*lower_case_envp++;
			counter++; 
		}
		
		printf("\n");
		lower_case_envp++;
	}	
}

char **CopyLowerEnvironment(const char **envp, char **lower_case_envp)
{
	char **start_of_lower_envp = lower_case_envp;
	
	assert(lower_case_envp != NULL);
	
	while ('\0' != envp)
	{
		while ('\0' != *envp)
		{
			**lower_case_envp = tolower(**envp);
			*lower_case_envp++;
			*envp++;
		}
		
		**lower_case_envp = '\0';
		envp++;
	}
	
	*lower_case_envp = '\0';
	
	return start_of_lower_envp;
}
/*
size_t GetEnvironmentLength(const char **envp)
{
	size_t total_envp_size = 0;
	size_t j = 1, num_of_strings = 1, largest_string = 0;
	
	assert(envp != NULL);
	
	while ('\0' !=envp)
	{
		while ('\0' != *envp)
		{
			j++;
		}
		
		if (largest_string < j)
		{
			largest_string = j;
		}
		
		num_of_strings++;
		envp++;
	}
	
	largest_string++;
	
	return total_envp_size = num_of_strings * largest_string;
}

*/
/*EXERCISE 2:*/
size_t SwordStory(size_t battle_field_size)
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

size_t FIndNextAlive(int *soldiers, size_t soldier_index, size_t field_size)
{
	
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


void TestSwordStory()
{
	size_t soldiers_number = 3, soldiers_number_2 = 100;
	size_t last_soldier = SwordStory(soldiers_number);
	
	printf("Location of soldier is %lu\n", last_soldier);
	
	last_soldier = SwordStory(soldiers_number_2);
	
	printf("Location of soldier is %lu\n", last_soldier);
}

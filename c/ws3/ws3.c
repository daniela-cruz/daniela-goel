#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */
#include <ctype.h> /* tolower */

#define UNUSED (void)

static void MirrorEnvp(const char **envp);
static char *LowStr(const char *str, char *str_lower);
static size_t GetEnvpLength(const char **envp);
static void PrintMirrorEnvp(const char **envp_mirror);
static void FreeLowerEnvp(char **lower_envp, size_t mirr_len);

size_t Josephus(size_t n, size_t k) ;
static size_t SwordStory(size_t battle_field_size);
static size_t FindNextAlive(size_t *soldiers, size_t soldier_index, size_t field_size);
static size_t KeepInCircle(size_t *soldiers, size_t soldier_index, size_t field_size);
static void TestSwordStory();

int main(int argc, char *argv[], char **envp)
{
	UNUSED argc;
	UNUSED argv;
	
	/*MirrorEnvp((const char **)envp);*/
	
	TestSwordStory();
	
	return 0;
}

/* ENVP */
static void MirrorEnvp(const char **envp)
{
	char **envp_mirror = NULL;
	char **mirror_start = NULL;
	size_t mirr_len = 0;
	
	mirr_len = GetEnvpLength(envp);
	envp_mirror = (char **)malloc((mirr_len + 1) * sizeof(char *));
	mirror_start = envp_mirror;
	
	/*allocate for each string*/
	while (*envp)
	{
		*envp_mirror = (char *)malloc(strlen((char *)*envp) * sizeof(char));
		LowStr(*envp++, *envp_mirror++);
	}
	
	envp_mirror = mirror_start;
	
	PrintMirrorEnvp((const char **)envp_mirror);

	FreeLowerEnvp(envp_mirror, mirr_len);
	
	mirror_start = envp_mirror;
	free(envp_mirror); envp_mirror = NULL;
}

static size_t GetEnvpLength(const char **envp)
{
	size_t envp_len = 0;
	char **envp_cpy = NULL;
	
	envp_cpy = (char **)envp;
	
	while (*envp_cpy)
	{
		envp_len++;
		envp_cpy++;
	}
	
	return envp_len;
}

static char *LowStr(const char *str, char *str_lower)
{
	char *str_start = NULL;
	
	str_start = str_lower;
	
	while ('\0' != *str++)
	{
		*str_lower = tolower(*str);
		str_lower++;
	}
	
	return str_start;
}

static void PrintMirrorEnvp(const char **envp_mirror)
{
	while (*envp_mirror)
	{
		printf("%s\n", *envp_mirror++);
	}
}

static void FreeLowerEnvp(char **lower_envp, size_t mirr_len)
{
	while (mirr_len--)
	{
		free(*lower_envp++);
	}
}

/* JOSEPHUS PROBLEM */
/***************************************/
size_t Josephus(size_t n, size_t k) 
{ 
  if (n == 1) 
    return 1; 
  else
    /* The position returned by josephus(n - 1, k) is adjusted because the 
       recursive call josephus(n - 1, k) considers the original position  
       k%n + 1 as position 1 */
    return (Josephus(n - 1, k) + k-1) % n + 1; 
} 

static size_t SwordStory(size_t battle_field_size)
{
	size_t *soldiers = NULL; /*an array of zeros*/
	size_t *sword = NULL;
	size_t is_stabbed = 0; /*zero if it's kill time*/
	size_t dead_soldiers_number = 0;
	size_t soldier_location = 0; /*soldier number is soldier_location + 1*/
	
	soldiers = (size_t *)calloc(battle_field_size, sizeof(size_t));
	sword = soldiers; /* point to first soldier */
	
	while (dead_soldiers_number + 1 < battle_field_size)
	{
		soldier_location = FindNextAlive(soldiers, soldier_location + 1, battle_field_size);
		sword = soldiers + soldier_location;
			
		if (0 == is_stabbed)
		{
			*sword = 1; /* kill soldier in this location */
			dead_soldiers_number++;
			is_stabbed = 1;
		}
		else
		{
			is_stabbed = 0;
		}
	}
	
	while (0 != *sword)
	{
		soldier_location = FindNextAlive(soldiers, soldier_location + 1, battle_field_size);
		sword = soldiers + soldier_location;
	}
	
	free(soldiers); soldiers = NULL;
	
	return soldier_location;
}

static size_t FindNextAlive(size_t *soldiers, size_t soldier_index, size_t field_size)
{
	soldier_index = KeepInCircle(soldiers, soldier_index, field_size);
	
	while (soldier_index < field_size)
	{	
		
		if (0 == *(soldiers + soldier_index)) /* if zero : live soldier found */
		{
			
			return soldier_index;
		}
		soldier_index = KeepInCircle(soldiers, soldier_index, field_size);
		soldier_index++;
	}
	
	return soldier_index;	
}

static size_t KeepInCircle(size_t *soldiers, size_t soldier_location, size_t field_size)
{
	if (soldier_location  == field_size) 
	{
		soldier_location = 0;
	}
	
	if (soldier_location > field_size)
	{
		soldier_location = 1;
	}
	
		return soldier_location;
}

static void TestSwordStory()
{
	size_t soldiers_number = 4, soldiers_number_2 = 100;
	size_t last_soldier = 0;
	
	/*
	last_soldier = Josephus(soldiers_number, last_soldier) ;
	printf("Location of soldier is %lu\n", last_soldier);
	
	last_soldier = Josephus(soldiers_number_2, last_soldier) ;
	printf("Location of soldier is %lu\n", last_soldier);
	*/
	
	last_soldier = SwordStory(soldiers_number);
	printf("Location of soldier is %lu\n", last_soldier);
	
	last_soldier = SwordStory(soldiers_number_2);
	printf("Location of soldier is %lu\n", last_soldier);
	
}

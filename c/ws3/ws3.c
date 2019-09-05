#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */
#include <ctype.h> /* tolower */

#define UNUSED (void)

static void MirrorEnvp(const char **envp);
static char **GetLowerEnvp(const char **envp, char **mirror_envp);
static char *LowStr(const char *str, char *str_lower);
static size_t GetEnvpLength(const char **envp);
static void PrintMirrorEnvp(const char **envp_mirror);
static void FreeLowerEnvp(char **lower_envp, size_t mirr_len);

int main(int argc, char *argv[], char **envp)
{
	UNUSED argc;
	UNUSED argv;
	
	MirrorEnvp((const char **)envp);
	
	return 0;
}

static void MirrorEnvp(const char **envp)
{
	char **envp_mirror = NULL;
	char **mirror_start = NULL;
	size_t mirr_len = 0;
	
	mirr_len = GetEnvpLength(envp);
	envp_mirror = (char **)malloc((mirr_len + 1) * sizeof(char *));
	mirror_start = envp_mirror;
	
	/*allocate for each string*/
	while (0 < mirr_len--)
	{
		*envp_mirror = (char *)malloc(strlen((char *)*envp++) * sizeof(char));
		envp_mirror++;
	}
	
	envp_mirror = NULL;
	envp_mirror = mirror_start;
	
	envp_mirror = GetLowerEnvp(envp, envp_mirror);
	
	PrintMirrorEnvp((const char **)envp_mirror);
	
	FreeLowerEnvp(envp_mirror, mirr_len);
	
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

static char **GetLowerEnvp(const char **envp, char **mirror_envp)
{
	char **mirorr_start = NULL;
	
	mirorr_start = mirror_envp;
	
	while (envp)
	{
		while (*envp)
		{
			mirror_envp = (char **)*envp;
			*mirror_envp = LowStr(*envp, *mirror_envp);
			
		}
		
		mirror_envp++;
		envp++;
	}
	
	return mirorr_start;
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
	
	*str_lower = '\0';
	
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
		free(lower_envp++);
	}
}

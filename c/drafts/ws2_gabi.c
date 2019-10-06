#include <stdio.h>

char *StrTok(char *str, const char *delim)
{
	/* static char * sentence_rest;*/
	char *temp = NULL;
	
	temp = str;

	/* if (str == NULL)
	{
		str = sentence_rest;
	}*/
	
	printf("str is: %s\n", str);
	
	while ('\0' != *temp)
	{
		printf("temp is: %s\n", temp);
		if (*temp == *delim)
		{
			str = temp;
			break;
		}
		
		temp++;
	}
	
	temp--;
	*temp = '\0';
	/* sentence_rest = temp + 1;*/
	str++;
	
	return str;
}

int main()
{
	char *word = "blah nonsense blah kishkoosh!";
	char *delimiter = "hb ks";
	char *str_tok = NULL;
	
	str_tok = StrTok(word, delimiter);
	
	printf("%s\n", str_tok);
	
	return 0;
}

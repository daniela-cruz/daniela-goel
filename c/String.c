
/*===EXERCISES:===*/
/*STRING.H RE-IMPLEMENTATION:*/
size_t MyStrlen(char *str)
{
	int counter = 0;
	
	while (str[counter] != '\0')
	{
		counter++;
	}
	
	return (size_t)counter;
}

int MyStrcmp(char *str_1, char *str_2)
{	
	while ((*str_1 != '\0' && *str_2 != '\0') && (*str_1 - *str_2 == 0))
	{
		str_1++;
		str_2++;
	}
	
	return *str_1 - *str_2;
}

char* MyStrcpy(char *dest, char *source)
{
	int i = 0;
	
		while (source[i] != '\0')
		{
			dest[i] = source[i];
			i++;
		}
	
	return dest;
}

char *MyStrchr(const char *str, int character)
{	
	while ((*str != '\0') && (*str != character))
	{
		str++;
	}
	
	return	(*string == character) ? (char *) s : NULL;
}

char *MyStrdup(const char *string)
{
	int size = strlen(string);
	char *p = *malloc(size * sizeof(char));
	
	while (*stirng != '\0')
	{
		*p = *string;
		p++;
		string++;
	}
	
	return p;
}



/*Other exercises:*/
int IsPalindrome(const char *str)
{
	int size = strlen(str), flag = -1, i;

	for (i=0; i<size/2; i++)
	{
		if (str[i] == str[size-i-1])
		{
			flag = 0;
		}
		else
		{
			break;
		}
	}
	
	return flag;
}

/*===TESTS:===*/
void StrlenTest()
{
	char str[] = "word";
	printf("I gots da %ld characters, yas!\n", MyStrlen(str));
}

void StrcmpTest()
{
	char *p_1 = "word", *p_2 = "woRd"; 
	int compared = MyStrcmp(p_1, p_2);
	
	printf("The result of comparison is: %d\n", compared);
}

void StrcpyTest()
{
	char str[] = "word", location[] = {'0', '0', '0', '0', '0', '0', '0', '\0'};
	
	MyStrcpy(location, str);
}

void IsPalindromeTest()
{
	char word_arr[] = {'m', 'a', 'a', 'm', '\0'};
	char *str = word_arr; 
	
	if(IsPalindrome(str) == 0)
	{
		printf("Yasss!\n");
	}
	else
	{
		printf("Ney!\n");
	}
}


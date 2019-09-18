#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <string.h> /* memset */

const size_t system_word = sizeof(size_t);


char s1[] = "I am a string and I have manyyyyy characters!";
char c = '.';


/* exercise 1: */
void *MemSet(void *s, int c, size_t n);

int main()
{	
	char *s = s1;
	MemSet(s + 2, c, 34);
	printf("%s\n", s);
	
	return 0;
}

/*
* Reimplementation of string lib's memset:
*/
void *MemSet(void *s, int c, size_t n)
{
	char *buffer = NULL;
	char *s_char_cpy = NULL;
	int i = 0;
	size_t address = 0;

	assert(s);
	s_char_cpy = (char *)s;
	buffer = malloc(system_word);
	assert(buffer);

	/* while s' address doesn't align with system_word, copy byte by byte: */
	while ((0 != (size_t)s_char_cpy % system_word) && (0 < n))
	{
	*s_char_cpy = c;
	s_char_cpy++;
	n--;
	}

	 /* pointer is aligned, if n is higher than system_word, copy word by word: */
	if (system_word <= n)
	{
		/* create a word sized buffer fulll of c: */
		for (; i < system_word; i++)
		{
			*(buffer + i) = c;
		}
		
		/* copy word by word: */
		while (system_word < n)
		{
			*(size_t *) s_char_cpy = *(size_t *) buffer;
			n -= system_word;
			s_char_cpy+=system_word;
		}
		
		free(buffer); buffer = NULL;
	}
	
	/* copy to tail: */
	while (0 < n--)
	{
		*s_char_cpy = c;
		s_char_cpy++;
	}
	
	return s;
}

void *MemCpy(void *dest, const void *src, size_t n)
{
	if (strlen(dest) < n)
	{
		dest = realloc(dest, n);
	}
	
	return dest;
}

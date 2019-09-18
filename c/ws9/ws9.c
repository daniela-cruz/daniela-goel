#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <string.h> /* memset */

const char system_word = sizeof(size_t);


char s1[] = "I am a string and I have manyyyyy characters!";
char c = '.';


/* exercise 1: */
void *MemSet(void *s, int c, size_t n);

int main()
{	
	char *s = s1;
	MemSet(&s1[2], c, 16);
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
	size_t *s_size_t_cpy = NULL;
	int i = 0;
	size_t address = 0;

	assert(s);
	address = (int)s;
	s_size_t_cpy = (size_t*)s;
	s_char_cpy = (char *)s;
	buffer = malloc(system_word);
	assert(buffer);

	/* while s' address doesn't align with system_word, copy byte by byte: */
	while ((0 != address % system_word) && (0 < n))
	{
	*s_char_cpy = c;
	address = (int)s_char_cpy;
	s_char_cpy++;
	n--;
	}

	 /* pointer is aligned, if n is higher than system_word, copy word by word: */
	if (system_word <= (char)n)
	{
		s_size_t_cpy = (size_t *)s_char_cpy; /* continue from where we left off */
		
		/* create a word sized buffer fulll of c: */
		for (; i < system_word; i++, buffer++)
		{
			*buffer = c;
		}
		
		/* copy word by word: */
		while (system_word < (char)n)
		{
			*s_size_t_cpy = *buffer;
			n -= system_word;
			s_size_t_cpy++;
		}
		
		s_char_cpy = (char *)s_size_t_cpy; /* continue from where we left off */
		/*free(buffer); buffer = NULL;*/
	}
	
	/* copy to tail: */
	while (0 < n--)
	{
		*s_char_cpy = c;
		s_char_cpy++;
	}
	
	return s;
}

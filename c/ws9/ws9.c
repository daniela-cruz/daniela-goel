#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t, ptrdiff_t */
#include <assert.h> /* assert */
#include <string.h> /* memset */

const size_t system_word = sizeof(size_t);


char s1[] = "I am a string and I have manyyyyy characters!";
char c = '.';


/* exercise 1: */
void *MemSet(void *s, int c, size_t n);
static void MemSetTest();

void *MemCpy(void *dest, const void *src, size_t n);
static void MemCpyTest();

void *MemMove(void *dest, const void *src, size_t n);

int main()
{	
	char s2[] = "all kinds of characters and words to test if this is working";
	char *dest = NULL;
	char *src = NULL;
	
/*	MemSetTest();*/
/*	MemCpyTest();*/
	
	src = s2;
	dest = s1;
	dest = memmove(src + 22, src, 40);
	dest = MemMove(src + 22, src, 40);
	dest -=22;
	printf("%s\n", dest);
	
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

static void MemSetTest()
{
	char *s = s1;
	MemSet(s + 2, c, 34);
	printf("%s\n", s);
}
void *MemCpy(void *dest, const void *src, size_t n)
{
	size_t *src_cpy = NULL;
	size_t *dest_cpy = NULL;
	char *src_char_cp = NULL;
	char *dest_char_cpy = NULL;
	
	assert(src);
	assert(dest);
	
	src_cpy = (size_t *)src;
	dest_cpy = (size_t *)dest;
	src_char_cp = (char *)src;
	dest_char_cpy = (char *)dest;
	
	/* while dest's address doesn't align with system_word, copy byte by byte: */
	while ((0 != (size_t)dest_char_cpy % system_word) && (0 < n))
	{
		*dest_char_cpy = *src_char_cp;
		dest_char_cpy++;
		src_char_cp++;
		n--;
	}
	
	/* continue from where we left off */
	src_cpy = (size_t *)src_char_cp;
	dest_cpy = (size_t *)dest_char_cpy;
	
	
	while (system_word < n)
	{
		*dest_cpy = *src_cpy;
		dest_cpy++;
		src_cpy++;
		n -= system_word;
	}
	
	src_char_cp = (char *)src_cpy;
	dest_char_cpy = (char *)dest_cpy;
	
	while (0 < n)
	{
		*dest_char_cpy = *src_char_cp;
		dest_char_cpy++;
		src_char_cp++;
		n --;
	}
	
	return dest;
}

static void MemCpyTest()
{
	char *dest = NULL;
	char *src = "all kinds of nonsense and a string that is longer than the original string, you see?";
	
	dest = malloc(strlen(s1) + 1);
	
	dest = strcpy(dest, s1);
	
	MemCpy(dest + 30, src, 17);
	printf("%s\n", dest);
	
	free(dest);
}

/*
* memmove reimplmentation:
*/
void *MemMove(void *dest, const void *src, size_t n)
{
	size_t *src_cpy = NULL;
	size_t *dest_cpy = NULL;
	char *src_char_cp = NULL;
	char *dest_char_cpy = NULL;
	
	assert(src);
	assert(dest);
	
	src_cpy = (size_t *)src;
	src_char_cp = (char *)src_cpy;
	dest_cpy = (size_t *)dest;
	dest_char_cpy = (char *)dest_cpy;
	
	/* make sure n is not passing allocated memory */
	
	if (n > strlen(dest)) 
	{
		n = strlen(dest) + 1;
	}
	
	 /* make sure n is not passing allocated memory */
	if (n > strlen(src))
	{
		n = strlen(src) + 1;
	}
	
	/* handle case of dest overlapping src */
	if (dest_cpy > src_cpy) 
	{

		for (; ((0 != (size_t)src_char_cp % system_word) && (0 < n)); 
				dest_cpy++, src_char_cp++, n --)
		{
			*dest_char_cpy = *src_char_cp;
		}
		

		src_cpy = (size_t *)src_char_cp;
		dest_cpy = (size_t *)dest_char_cpy;
		
		for (; system_word < n; n -= system_word, dest_cpy++, src_cpy++)
		{
			*dest_cpy = *src_cpy;
		}
	}
	
	/* handle if dest address is after source */
	else 
	{
		/* if address n */
		for (; ((0 != (size_t)dest_char_cpy % system_word) && (0 < n)); 
				dest_char_cpy--, src_char_cp--, n --)
		{
			*dest_char_cpy = *src_char_cp;
		}
		
		src_cpy = (size_t *)src_char_cp;
		dest_cpy = (size_t *)dest_char_cpy;
		
		for (; system_word < n; n -= system_word, dest_cpy--, src_cpy--)
		{
			*dest_cpy = *src_cpy;
		}
	}
	
	return dest;
}

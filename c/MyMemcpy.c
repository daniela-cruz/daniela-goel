#include <string.h>
#include <stdint.h>

#define	WORD_SIZE	sizeof(word)
#define	WORD_MASK	(WORD_SIZE - 1)

typedef int word;

void *MyMemcpy(void *destination, const void *source, size_t length);
void *memmove(void *s1, const void *s2, size_t n);
void bcopy(const void *s1, void *s2, size_t n);
static void TestMyMemcpy();

__attribute__((visibility("hidden")))   
void *MyMemcpy(void *destination, const void *source, size_t length)
{
	char *dst = destination;
	const char *src = source;
	size_t src_to_size;
	
	if  (length == 0 || dst == src)
	{
		goto done;
	}
	
	#define	TLOOP(s) if (src_to_size) TLOOP1(s)
	#define	TLOOP1(s) do { s; } while (--src_to_size)
	
	if ((unsigned long)dst < (unsigned long)src) 
	{
		src_to_size = (uintptr_t)src;
		
		if ((src_to_size | (uintptr_t)dst) & WORD_MASK) 
		{
			if ((src_to_size ^ (uintptr_t)dst) & WORD_MASK || 
			  length < WORD_SIZE)
			{
				src_to_size = length;
			}
			else
			{
				src_to_size = WORD_SIZE - (src_to_size & WORD_MASK);
			}
			
			length -= src_to_size;
			TLOOP1(*dst++ = *src++);
		}
		/*
		 * Copy whole words, then mop up any trailing bytes.
		 */
		src_to_size = length / WORD_SIZE;
		TLOOP(*(word *)dst = *(word *)src; src += WORD_SIZE; dst += WORD_SIZE);
		src_to_size = length & WORD_MASK;
		TLOOP(*dst++ = *src++);
	} 
	else 
	{
		/*
		 * Copy backwards.  Otherwise essentially the same.
		 * Alignment works as before, except that it takes
		 * (src_to_size&WORD_MASK) bytes to align, not WORD_SIZE 			
		 * (src_to_size&WORD_MASK).
		 */
		src += length;
		dst += length;
		src_to_size = (uintptr_t)src;
		
		if ((src_to_size | (uintptr_t)dst) & WORD_MASK) 
		{
			if ((src_to_size ^ (uintptr_t)dst) & WORD_MASK || 
			   length <= WORD_SIZE)
			{
				src_to_size = length;
			}
			else
			{
				src_to_size &= WORD_MASK;
			}
			
			length -= src_to_size;
			TLOOP1(*--dst = *--src);
		}
		
		src_to_size = length / WORD_SIZE;
		TLOOP(src -= WORD_SIZE; dst -= WORD_SIZE; *(word *)dst = *(word *)src);
		src_to_size = length & WORD_MASK;
		TLOOP(*--dst = *--src);
	}
	
done:
	return (destination);
}
/*
void *memmove(void *s1, const void *s2, size_t n)
{
	return MyMemcpy(s1, s2, n);
}
*/
/*
__attribute__((visibility("hidden"))) void bcopy(const void *s1, void *s2, size_t n)
{
	MyMemcpy(s2, s1, n);
}
*/
int main()
{
	TestMyMemcpy();
	
	return 0;
}

static void TestMyMemcpy()
{
	void *str_1 = "nonsense is here";
	const char *string_to_copy = "lalalal";
	size_t number_of_chars_to_replace = 5;
	
	MyMemcpy(str_1, string_to_copy, number_of_chars_to_replace);
}

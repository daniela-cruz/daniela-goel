#include <string.h>
#include <stdint.h> /*uintptr_t*/
#include <inttypes.h> /*uint8_t*/

typedef int word;

#define	WORD_SIZE sizeof(word)
#define	WORD_MASK	(WORD_SIZE - 1)

void *MyMemcpy(void *destination, const void *source, size_t length);
void *memmove(void *s1, const void *s2, size_t n);
void bcopy(const void *s1, void *s2, size_t n);
static void TestMyMemcpy();

__attribute__((visibility("hidden")))   
void *MyMemcpy(void *destination, const void *source, size_t length)
{
	char *dst = destination;
	const char *src = source;
	size_t chars_amount;
	
	if  (length == 0 || dst == src) /*if there are no chars to copy return dest as is*/
	{
		goto done;
	}
	
	#define	TLOOP(s) if (chars_amount) TLOOP1(s)
	#define	TLOOP1(s) do { s; } while (--chars_amount)
	
	if ((unsigned long)dst < (unsigned long)src) 
	{
		chars_amount = (uintptr_t)src;
		
		if ((chars_amount | (uintptr_t)dst) & WORD_MASK) 
		{
			if ((chars_amount ^ (uintptr_t)dst) & WORD_MASK || 
			  length < WORD_SIZE)
			{
				chars_amount = length;
			}
			else
			{
				chars_amount = WORD_SIZE - (chars_amount & WORD_MASK);
			}
			
			length -= chars_amount;
			TLOOP1(*dst++ = *src++);
		}
		/*
		 * Copy whole words, then mop up any trailing bytes.
		 */
		chars_amount = length / WORD_SIZE;
		TLOOP(*(word *)dst = *(word *)src; 
		src += WORD_SIZE; 
		dst += WORD_SIZE);
		chars_amount = length & WORD_MASK;
		TLOOP(*dst++ = *src++);
	} 
	else 
	{
		/* Copy backwards*/
		src += length;
		dst += length;
		chars_amount = (uintptr_t)src;
		
		if ((chars_amount | (uintptr_t)dst) & WORD_MASK) 
		{
			if ((chars_amount ^ (uintptr_t)dst) & WORD_MASK || 
			   length <= WORD_SIZE)
			{
				chars_amount = length;
			}
			else
			{
				chars_amount &= WORD_MASK;
			}
			
			length -= chars_amount;
			TLOOP1(*--dst = *--src);
		}
		
		chars_amount = length / WORD_SIZE;
		TLOOP(src -= WORD_SIZE; dst -= WORD_SIZE; *(word *)dst = *(word *)src);
		chars_amount = length & WORD_MASK;
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

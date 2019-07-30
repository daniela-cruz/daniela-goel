#include <stdio.h> /*printf*/
#include <stdlib.h> /*atoi*/
#include <assert.h> /*assert*/
#include <stdint.h> /*uintptr_t*/

typedef unsigned char byte;

void* MyMemset(void* str, int ch, size_t n) ;
static void TestMyMemset();

/*
Get ptr, int and n times

1. ?convert int to char
2. keep a size_t var for char and initialize it with int
3. keep a mask = 1.
4. run n times:
-- shift var 3 bits left
-- OR with current var
-- move mas by 3 left too
5. AND mask with string
6. or string with var

return string
*/


void *MyMemset_2(void *str, int ch, size_t n)
{
	size_t word_char = (size_t)ch;
	byte moved_ch = (byte)ch;
	size_t mask = 1;
	byte bit_shifter = 1;
	byte *destination = NULL;
	
	assert(NULL != str);
	destination = str;
	
	mask <<= (n * sizeof(byte));
	*destination &= mask;
	/*Shift left by word size until string can't be moved:*/
	while (0 < n--)
	{
		 /*prepare repeated char n times*/
		 moved_ch <<= bit_shifter;
		 word_char |= (size_t)moved_ch;
	}
	
	*destination |= *(char *)word_char;
		
	return str;
}


/*========*/
void* MyMemset(void* str, int ch, size_t n) 
{
	unsigned char word_size = sizeof(void *) * sizeof(char);
	size_t *word_runner;
	/*Word sized chunk that is assigned to the content of ch masked:*/
	unsigned char char_aligned = (unsigned char)ch & 0xff; 
	byte* byte_runner = (byte*)str;
	/*byte sized chunk that is assigned to the content of ch masked:*/
	byte byte_chunk = (byte)ch & 0xff;
	unsigned char tail;
	unsigned char i;
	unsigned char bytes_per_word = 3;
	unsigned char mask = 1;
	
	assert(NULL != str);
	
	for (i = 0; (mask << i) < word_size; ++i)
	{
		char_aligned |= char_aligned << (mask << i);
	}
	
	/*in case some bits are left and unaligned move left by a word and copy:*/
	bytes_per_word = 1 << ( mask - 3);

	/*Copy word sized chunk by chunk:*/
	while (((size_t)byte_runner & (bytes_per_word - 1)) && n--)
	{
		*byte_runner++ = byte_chunk;
	}
	
	/*Mask with  bytes_per_word - 1 the amount left:*/
	tail = n & (bytes_per_word - 1);
	word_runner = (size_t*)byte_runner;

	/*Decrement the bits we aligned:*/
	n >>= mask - 3;
	
	/*Copy by word size chunks:*/
	while (n--)
	{
		*word_runner++ = char_aligned;
	}
	
	/* Handle byte sized leftovers:*/
	byte_runner = (byte*)word_runner;
	
	while (tail--)
	{
		*byte_runner = byte_chunk;
		byte_runner++;
	}
	
	return str;
}

int main()
{
	TestMyMemset();
	
	return 0;
}

static void TestMyMemset()
{
	void *str = "123456789";
	char buffer[20];
	char *str_2 = NULL;
	int ch = 65;
	size_t n = 3;
	
	str_2 = buffer;
	str_2 = MyMemset_2(str, ch, n);
	
	printf("%s\n", str_2);
}

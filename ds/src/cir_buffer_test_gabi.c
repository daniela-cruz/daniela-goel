#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

#include "cir_buffer.h"

int main()
{
	cir_buffer_t *buffer = CBCreate(10);
	
	size_t read_chars = 0;
	size_t write_chars = 0;
	
	char *write = "helloworld";
	char *write2 = "abcdefghijklmnopqrstuvwxyz";
	char *read = malloc(11);
	if(NULL == read)
	{
		return 1;
	}
	
	printf("created a circular buffer size %ld. \n", CBCapacity(buffer));
	
	printf("\nwriting in buffer: %s\n", write);
	write_chars = CBWrite(buffer, write, 10);
	
	printf("\nreading 5 bytes from buffer\n");
	read_chars = CBRead(buffer, read, 5);
	/* adding /0 so valgrind wont complain */
	*(read + 5) = '\0';

	printf("\nwrite chars: %ld\n", write_chars);
	printf("read chars: %ld\n", read_chars);
	printf("string read: %s\n", read);
	printf("is empty: %d\n", CBIsEmpty(buffer));
	printf("free space: %ld\n", CBGetFreeSpace(buffer));
	
	write_chars = CBWrite(buffer, write2, 26);
	printf("\nwriting in buffer: %s\n", write2);
	
	read_chars = CBRead(buffer, read, 26);
	printf("\nreading 26 bytes from buffer\n");
	/* adding /0 so valgrind wont complain */
	*(read + 10) = '\0';
	
	printf("\nwrite chars: %ld\n", write_chars);
	printf("read chars: %ld\n", read_chars);
	printf("string read: %s\n", read);
	printf("is empty: %d\n", CBIsEmpty(buffer));
	printf("free space: %ld\n", CBGetFreeSpace(buffer));
	
	printf("\ndestroying buffer.\n");
	free(read); read = NULL;
	CBDestroy(buffer);
	
	return 0;
}


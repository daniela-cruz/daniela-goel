#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

struct cir_buffer_t
{
	char *head; 
	char *tail;
	size_t capacity;
	char buffer[1];
}

cir_buffer_t *CBCreate(size_t capcity)
{
	cir_buffer_t *new_buffer = NULL;
	
	new_buffer = malloc(sizeof(new_buffer));
	if (NULL == new_buffer)
	{
		perror();
		return NULL;
	}
	
	new_buffer->buffer = malloc(sizeof(capacity));
	if (NULL == new_buffer->buffer)
	{
		free(new_buffer);
		perror();
		return NULL;
	}
	
	new_buffer->head = new_buffer->buffer;
	new_buffer->tail = new_buffer->buffer;
	
	return new_buffer;
}

void CBDestroy(cir_buffer_t *c_buff);

size_t CBWrite(cir_buffer_t *c_buff, const void *data, size_t bytes_count);

size_t CBRead(cir_buffer_t *c_buff, size_t bytes_count, size_t bytes_count)
{
	if ()
	{
	
	}
}

size_t CBCapacity(const cir_buffer_t *c_buff);

int CBIsEmpty(const cir_buffer_t *c_buff);

size_t CBGetFreeSpace(const cir_buffer_t *c_buff);


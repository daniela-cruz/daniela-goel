#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "cir_buffer.h" /* all bellow */

struct circular_buff
{
	size_t writer; 
	size_t reader;
	size_t capacity;
	int is_full;
	char buffer[1];
};

/**********************************************
* Circular buffer functions: 				*
**********************************************/
cir_buffer_t *CBCreate(size_t capacity)
{
	cir_buffer_t *new_buffer = NULL;
	
	new_buffer = (cir_buffer_t *)malloc(offsetof(cir_buffer_t, buffer) + capacity + 1);
	if (NULL == new_buffer)
	{
		perror("");
		return NULL;
	}
	
	new_buffer->writer = 0;
	new_buffer->reader = 0;
	new_buffer->is_full = 0;
	new_buffer->capacity = capacity;
	
	return new_buffer;
}

void CBDestroy(cir_buffer_t *c_buff)
{
	free(c_buff);
}

size_t CBWrite(cir_buffer_t *c_buff, const void *data, size_t bytes_count)
{
	size_t i = 0;
	
	for(i = 0; 0 != bytes_count; bytes_count--, i++)
	{
		c_buff->buffer[c_buff->writer] = ((char *)data)[i];
		
		if(1 == c_buff->is_full)
		{
			c_buff->reader = 
					(c_buff->reader + 1) % c_buff->capacity;
		}
		
		c_buff->writer = (c_buff->writer + 1) % c_buff->capacity;
		c_buff->is_full = (c_buff->writer == c_buff->reader);
	}
	

	
	return i;
}

size_t CBRead(cir_buffer_t *c_buff, void *data, size_t bytes_count)
{
	size_t i = 0;
	
	for(i = 0; 0 != bytes_count && !(CBIsEmpty(c_buff)); bytes_count--, i++)
	{
		((char *)data)[i] = c_buff->buffer[c_buff->reader];
		c_buff->reader = (c_buff->reader + 1) % c_buff->capacity;
	}
	
	c_buff->is_full = 0;

	return i;
}

size_t CBCapacity(const cir_buffer_t *c_buff)
{
	return c_buff->capacity;
}

int CBIsEmpty(const cir_buffer_t *c_buff)
{
	return 0 == c_buff->is_full;
}

size_t CBGetFreeSpace(const cir_buffer_t *c_buff)
{
	cir_buffer_t *buff_cpy = (cir_buffer_t *)c_buff;
	if (0 == c_buff->is_full)
	{
		if (c_buff->writer > c_buff->reader)
		{
			return buff_cpy->writer - buff_cpy->reader;
		}
		
		if (c_buff->reader > c_buff->writer)
		{
			return buff_cpy->capacity - buff_cpy->writer - buff_cpy->reader;
		}
	}
	
	
	return 0; 
}

/**********************************************
* Internal functions: 							*
**********************************************/

static void CBAlignToBuffer(cir_buffer_t *c_buff)
{
	if (c_buff->writer == c_buff->capacity)
	{
		c_buff->writer = 0;
	}
	
	if (c_buff->reader  == c_buff->capacity)
	{
		c_buff->reader = 0;
	}
}


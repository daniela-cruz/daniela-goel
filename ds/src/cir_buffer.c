#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "cir_buffer.h" /* all bellow */

struct circular_buff
{
	size_t head; 
	size_t tail;
	size_t capacity;
	size_t free;
	char buffer[1];
};

/* This internal functions aligns head and tail indexes so that:
 * 1. tail won't pass head annd thus read won't pass write
  * 2. none will escape the limits of the capacity size		 		 */
static void CBAlignToBuffer(cir_buffer_t *c_buff);

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
	
	new_buffer->head = 0;
	new_buffer->tail = 0;
	new_buffer->free = capacity;
	new_buffer->capacity = capacity;
	
	return new_buffer;
}

void CBDestroy(cir_buffer_t *c_buff)
{
	free(c_buff);
}

size_t CBWrite(cir_buffer_t *c_buff, const void *data, size_t bytes_count)
{
	int i = 0;
	
	for (i = 0; 
		  i < bytes_count; 
		  i++, c_buff->head++, c_buff->free--)
	{
		CBAlignToBuffer(c_buff);
		c_buff->buffer[c_buff->head] = *(char *)data;
	}
	
	return (size_t)i;
}

size_t CBRead(cir_buffer_t *c_buff, size_t bytes_count)
{
	int i = 0;
	
	for (i = 0; 
		  i < bytes_count; 
		  i++, c_buff->tail++, c_buff->free++)
	{
		CBAlignToBuffer(c_buff);
	}
	
	return (size_t)i;
}

size_t CBCapacity(const cir_buffer_t *c_buff)
{
	return c_buff->capacity;
}

int CBIsEmpty(const cir_buffer_t *c_buff)
{
	return 0 == c_buff->capacity - CBGetFreeSpace(c_buff);
}

size_t CBGetFreeSpace(const cir_buffer_t *c_buff)
{
	cir_buffer_t *buff_cpy = (cir_buffer_t *)c_buff;
	
	if (c_buff->capacity < c_buff->free)
	{
		buff_cpy->free = buff_cpy->capacity;
	}
	
	if (0 > c_buff->free)
	{
		buff_cpy->free = 0;
	}
	
	return c_buff->free; 
}

/**********************************************
* Internal functions: 							*
**********************************************/

static void CBAlignToBuffer(cir_buffer_t *c_buff)
{
	if (c_buff->head >= c_buff->capacity)
	{
		c_buff->head = c_buff->head %c_buff->capacity;
	}
	
	if (c_buff->tail  >= c_buff->capacity)
	{
		c_buff->tail = c_buff->tail % c_buff->capacity;
		
		if (c_buff->tail > c_buff->head)
		{
			c_buff->tail = c_buff->head;
		}
	}
}


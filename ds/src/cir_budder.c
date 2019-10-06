#include <stddef.h> /* size_t */

struct cir_buffer_t
{
	char *buffer;
	char *head, *tail;
	size_t capacity;
}



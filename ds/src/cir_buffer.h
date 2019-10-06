#ifndef __C_BUFFER_H__
#define __C_BUFFER_H__
#include <stddef.h> /* size_t */

typedef struct circular_buff cir_buffer_t;

/* Create a new ring buffer with the given capacity (usable
 * bytes). Note that the actual internal buffer size may be one or
 * more bytes larger than the usable capacity, for bookkeeping.
 * Returns the new ring buffer object, or 0 if there's not enough
 * memory to fulfill the request for the given capacity.					 */
cir_buffer_t *CBCreate(void *data, size_t capcity);

/* Deallocate a ring buffer, and, as a side effect, set the pointer to 0. */
void CBDestroy(cir_buffer_t *c_buff, size_t bash_size);


size_t CBRead(cir_buffer_t *c_buff, size_t bytes_count);

size_t CBWrite(cir_buffer_t *c_buff, const void *data, size_t bytes_count);

/* The usable capacity of the ring buffer, in bytes. Note that this
 * value may be less than the ring buffer's internal buffer size, as
 * returned by ringbuf_buffer_size.												*/
size_t CBCapacity(cir_buffer_t *c_buff);


int CBIsEmpty(cir_buffer_t *c_buff);

/* The number of free/available bytes in the ring buffer. This value
 * is never larger than the ring buffer's usable capacity.					 */
size_t CBGetFreeSpace(cir_buffer_t *c_buff);

#endif /* __C_BUFFER_H__ */

#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* size_t */

typedef struct vsa vsa_t;

vsa_t *VSAInit(void *buffer, size_t buff_size);

void *VSAAlloc(vsa_t *vsa, size_t var_size);

void VSAFree(void *block);

size_t VSAMaxFreeBlock(const vsa_t *vsa);

#endif /* __VSA_H__ */

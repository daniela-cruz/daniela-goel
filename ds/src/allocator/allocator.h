#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* size_t */

typedef struct fsa fsa_t;

fsa_t *FSAInit(void *buffer, size_t buff_size, size_t blick_size);

void FSADestroy(fsa_t *fsa);

void *FSAalloc(fsa_t *fsa);

void FSAFree(void *block);

size_t FSACountFree(const fsa_t *fsa);

size_t FSASuggest(size_t block_num, size_t block_size);

#endif /* __FSA_H__ */

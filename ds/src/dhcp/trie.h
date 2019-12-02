#ifndef __TRIE_H__
#define __TRIE_H__
#include <stddef.h>     /*  size_t  */
#include <stdint.h>     /* uint32_t */

typedef struct trie trie_t;

trie_t *TrieCreate(size_t height);

void *TrieFind(trie_t *bt, uint32_t path);

int TrieFindNextFree(trie_t *bt, uint32_t* path);

int TrieInsert(trie_t *btrie, uint32_t path, void *data);

void TrieRemove(trie_t *bt, uint32_t path);

void TrieDestroy(trie_t *bt);

#endif /* __TRIE_H__ */

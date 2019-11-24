#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h> /* size_t */

typedef struct hash hash_t;

typedef size_t (*hash_func_t)(const void* key);

typedef int (*hash_action_func_t)(void* data, void* param);

typedef int (*hash_cmp_func_t)(const void* data1, const void* data2);

/******************************** Functions ***********************************/

hash_t *HASHCreate(hash_func_t func, hash_cmp_func_t cmp_func, size_t table_size); 

void HASHDestroy(hash_t *hash);

int HASHInsert(hash_t *hash, const void* data);

void HASHRemove(hash_t *hash, const void *data);

size_t HASHSize(const hash_t *hash);

int HASHIsEmpty(const hash_t *hash);

void *HASHFind(const hash_t *hash, const void *data);

int HASHForEach(hash_t *hash, hash_action_func_t action_func, void *param);

#endif /* __HASH_H__ */
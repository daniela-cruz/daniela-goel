#include <stdlib.h>     /* malloc, free */

#include "hash.h"       /* all below */
#include "dll.h"        /* DLLCreate, dll_iter_t */

struct hash
{
    size_t size;
    hash_func_t hash_func;
    hash_cmp_func_t cmp;
    dll_t *table[1];
};

/*----------------------------Forward declarations----------------------------*/
static dll_iter_t IterFinder(const hash_t *hash, const void *data);

static int GetIdx(hash_t *hash, const void *data);

/*---------------------------Primary functionality----------------------------*/
hash_t *HASHCreate(hash_func_t func, hash_cmp_func_t cmp_func, size_t table_size)
{
    hash_t *hash = NULL;
    do
    {
        int i = 0;

        hash = malloc(sizeof(*hash) + (sizeof(dll_t *) * (table_size - 1)));
        if (NULL == hash)
        {
            break;
        }
        
        for ( i = 0; i < table_size; i++)
        {
            hash->table[i] = DLLCreate();
            
        }
        if (i != table_size)
        {
            for ( ; 0 < i; --i)
            {
                DLLDestroy(hash->table[i]);
            }
            
            break;
        }

        hash->cmp = cmp_func;
        hash->hash_func = func;
        hash->size = table_size;

    } while (0);

    /* cleanup */
    if (NULL == hash->table[0])
    {
        free(hash); hash = NULL;
    }
    
    return hash;
} 

void HASHDestroy(hash_t *hash)
{
    int i = 0;

    for ( i = 0; i < hash->size; i++)
    {
        DLLDestroy(hash->table[i]);
    }
    
    free(hash); hash = NULL;
}

int HASHInsert(hash_t *hash, const void* data)
{
    int idx = 0;
    dll_iter_t iter;

    idx = GetIdx(hash, data);
    
    iter = DLLPushFront(hash->table[idx], data);
    if (NULL == iter.curr_node)
    {
        return 1;
    }

    return 0;
}

void HASHRemove(hash_t *hash, const void *data)
{
    DLLRemove(IterFinder(hash, data));
}

size_t HASHSize(const hash_t *hash)
{
    int i = 0;
    size_t size = 0;

    for ( i = 0; i < hash->size; i++)
    {
        size += DLLSize(hash->table[i]);
    }
    
    return size;
}

int HASHIsEmpty(const hash_t *hash)
{
    int is_empty = 1;
    int i = 0;

    for (i = 0; (i < hash->size) && (1 == is_empty); i++)
    {
        is_empty = DLLIsEmpty(hash->table[i]);
    }
    
    return is_empty;
}

void *HASHFind(const hash_t *hash, const void *data)
{   
    return DLLGetData(IterFinder(hash, data));
}

int HASHForEach(hash_t *hash, hash_action_func_t action_func, void *param)
{
<<<<<<< HEAD
    size_t i = 0;
	int status = 0;

	for(i = 0; i < hash->size && 0 == status; i++)
	{
		if(!DLLIsEmpty(hash->table[i]))
		{
			status = DLLForEach(DLLBegin(hash->table[i]),DLLEnd(hash->table[i]), action_func, param);
		}
	}

	return status;
=======
    int i = 0;
    int status = 0;
    dll_iter_t it_begin, it_end;


    for ( i = 0; (i < hash->size) && (!status) ; i++)
    {
        if (!DLLIsEmpty(hash->table[i]))
        {
            it_begin = DLLBegin(hash->table[i]);
            it_end = DLLEnd(hash->table[i]);

            status = DLLForEach(it_begin, it_end, action_func, param);
        }
        
    }
    
    return status;
>>>>>>> 67aafab24d19a1283ecd9f30e9810fe3e92ef02f
}

/*------------------------------Internal funcs--------------------------------*/
static int GetIdx(hash_t *hash, const void *data)
{
    return hash->hash_func(data);
}

static dll_iter_t IterFinder(const hash_t *hash, const void *data)
{
    dll_iter_t it_begin, it_end;
    int idx = 0;

    idx = hash->hash_func(data);
    it_begin = DLLBegin(hash->table[idx]);
    it_end = DLLEnd(hash->table[idx]);

    it_begin = DLLFind(it_begin, it_end, (dll_cmp_func_t)hash->cmp, (void *)data);

    return it_begin;
}
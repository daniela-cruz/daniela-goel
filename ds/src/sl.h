#ifndef __SL_H__
#define __SL_H__

#include <stddef.h>

#include "dll.h" /* dll_iter_t */

typedef struct sorted_list sl_t;
typedef int (*is_before)(void *, void *, void *param);
typedef int (*act_func)(void *, void *param);
typedef int (*cmp_func)(void *, void *param);

typedef struct sl_iterator 
{
	dll_iter_t iterator;
} sl_iter_t;

sl_t *SLCreate(is_before, void *data);

void SLDestroy(sl_t *sorted_list);

sl_iter_t SLInsert(sl_t *sorted_list, sl_iter_t iterator, void *data);

sl_iter_t SLRemove(sl_t *sorted_list, sl_iter_t iterator);

/*****************************************/

sl_iter_t SLBegin((sl_t *sorted_list);

sl_iter_t SLEnd((sl_t *sorted_list);

sl_iter_t SLPrev(sl_iter_t iterator);

sl_iter_t SLNext(sl_iter_t iterator);

int SLForEach(sl_iter_t from, sl_iter_t to, act_func func, void *param);

sl_iter_t  SLFind(sl_iter_t from, sl_iter_t to, cmp_func func, void *param);

#endif /*__SL_H__*/

#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "sl.h" /* all functions below */

struct sorted_list
{
	dll_t *list;
	sl_is_before_t is_before;
};

/*************************************************
 *		 		General functions				*
 ************************************************/
sl_t *SLCreate(sl_is_before_t is_before_func)
{
	sl_t *sl = NULL;
	
	sl = malloc(sizeof(*sl));
	if (NULL == sl)
	{
		return NULL;
	}
	
	sl->list = DLLCreate();
	if (NULL == sl->list)
	{
		free(sl);
		return NULL;
	}
	
	sl->is_before = is_before_func;
	
	return sl;
}

void SLDestroy(sl_t *sorted_list)
{
	DLLDestroy(sorted_list->list);
	free(sorted_list);
}

sl_iter_t SLInsert(sl_iter_t iterator, void *data)
{
	iterator.iterator = DLLInsert(iterator.iterator, data);
	return iterator;
}

sl_iter_t SLRemove(sl_t *sorted_list, sl_iter_t iterator);

int SLIsEmpty(sl_t *list)
{
	return DLLIsEmpty(list->list);
}

size_t SLSize(sl_t *list)
{
	return DLLSize(list->list);
}

/*************************************************
 *		 		Iterator functions					*
 ************************************************/
sl_iter_t SLBegin(sl_t *sorted_list)
{
	sl_iter_t iterator = {NULL};
	
	iterator.iterator = DLLBegin(sorted_list->list);
	
	return iterator;
}
 
sl_iter_t SLEnd(sl_t *sorted_list)
{
	sl_iter_t iterator = {NULL};

	iterator.iterator = DLLEnd(sorted_list->list);

	return iterator;
}

sl_iter_t SLPrev(sl_iter_t iterator)
{
	iterator.iterator = DLLIterPrev(iterator.iterator);
	
	return iterator;
}

sl_iter_t SLNext(sl_iter_t iterator)
{
	iterator.iterator = DLLIterNext(iterator.iterator);
	
	return iterator;
}

void *SLGetData(sl_iter_t iterator)
{
	return DLLGetData(iterator.iterator);
}

/*************************************************
 *		 		Internal functions					*
 ************************************************/

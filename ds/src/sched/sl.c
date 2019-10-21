#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "sl.h" /* all functions below */

struct sorted_list
{
	dll_t *list;
	void *param;
	sl_is_before_t is_before;
};

/*************************************************
 *		 		General functions				*
 ************************************************/
sl_t *SLCreate(sl_is_before_t is_before_func, void *param)
{
	sl_t *sl = NULL;
	
	assert(NULL != param);
	
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
	sl->param = param;
	
	return sl;
}

void SLDestroy(sl_t *sorted_list)
{
	DLLDestroy(sorted_list->list);
	free(sorted_list);
}

sl_iter_t SLInsert(sl_t *list, void *data)
{
	sl_iter_t iterator;
	/*int is_found = 0;*/
	
	assert(NULL != list);
	/*if ((0 == is_found) || (1 == SLIsEmpty(list)))
	{
		iterator = SLEnd(list);
	}*/
	
	for (iterator = SLBegin(list); (!SLIsEqual(iterator, SLEnd(list))); iterator = SLIterNext(iterator))
	{
		if (1 == list->is_before(data, SLGetData(iterator), list->param))
		{
			break;
		}
	}
	
	iterator.iterator = DLLInsert(iterator.iterator, data);
	
	return iterator;
}

sl_iter_t SLRemove(sl_iter_t iterator)
{
	iterator.iterator = DLLRemove(iterator.iterator);
	
	return iterator;
}
/*
sl_iter_t SLInsert(sl_t *sl, const void *data)
{
	sl_iter_t sl_iter = {NULL};
	
	assert(sl && data);	
	
	if (SLIsEmpty(sl))
	{
		sl_iter.iterator = DLLInsert(DLLBegin(sl->list), data);
		return sl_iter;
	}
		
	for (sl_iter = SLBegin(sl) ; !SLIterIsEqual(sl_iter, SLEnd(sl)); 
	 sl_iter = SLIterNext(sl_iter))
	 {
	 	if(sl->IsBefore((void *)data, SLIterGetData(sl_iter), sl->param))
	 	{
	 		sl_iter.iterator = DLLInsert(sl_iter.iterator, data);
	 		return sl_iter;
	 	}
	 }
	 
	 sl_iter.iterator = DLLInsert(DLLEnd(sl->list), data);
	  
	 return sl_iter;
}*/

void *SLPopBack(sl_t *list)
{
	return DLLPopBack(list->list);
}

void *SLPopFront(sl_t *list)
{
	return DLLPopFront(list->list);
}

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
	sl_iter_t iterator = {{NULL, NULL, NULL}, NULL};
	
	iterator.sl = sorted_list;
	iterator.iterator = DLLBegin(sorted_list->list);
	
	return iterator;
}
 
sl_iter_t SLEnd(sl_t *sorted_list)
{
	sl_iter_t iterator = {{NULL, NULL, NULL}, NULL};

	iterator.sl = sorted_list;
	iterator.iterator = DLLEnd(sorted_list->list);

	return iterator;
}

sl_iter_t SLIterPrev(sl_iter_t iterator)
{
	iterator.iterator = DLLIterPrev(iterator.iterator);
	
	return iterator;
}

sl_iter_t SLIterNext(sl_iter_t iterator)
{
	iterator.iterator = DLLIterNext(iterator.iterator);
	
	return iterator;
}

int SLIsEqual(sl_iter_t it1, sl_iter_t it2)
{
	return DLLIterIsEqual(it1.iterator, it2.iterator);
}

void *SLGetData(sl_iter_t iterator)
{
	return DLLGetData(iterator.iterator);
}

/*************************************************
 *		 		Extra functions					*
 ************************************************/
int SLForEach(sl_iter_t from, sl_iter_t to, sl_act_func_t func, void *param)
{
	return DLLForEach(from.iterator, to.iterator, func, param);
}

sl_iter_t  SLFind(sl_iter_t from, sl_iter_t to, void *data)
{
	sl_iter_t iterator;
	
	iterator.iterator = DLLFind(from.iterator, to.iterator, (dll_cmp_func_t)to.sl->is_before, to.sl->param);

	return iterator;
}

sl_iter_t  SLFindIf(sl_iter_t from, sl_iter_t to, sl_cmp_func_t func, void *param)
{
	sl_iter_t iterator;
	
	iterator.iterator = DLLFind(from.iterator, to.iterator, (dll_cmp_func_t)func, param);
	
	return iterator; 	
}

sl_iter_t SLMerge(sl_t *to, sl_t *from)
{
	sl_iter_t dest;

	assert(NULL != from);
	assert(NULL != to);	
	
	for (dest = SLBegin(to); 
		!SLIsEqual(dest, SLEnd(to)) && (!SLIsEqual(SLBegin(from), SLEnd(from))); 
	 	dest = SLIterNext(dest))
	 {
	 	if (to->is_before(SLGetData(SLBegin(from)), SLGetData(dest), to->param))
	 	{
			 dest.iterator = DLLSplice(dest.iterator, DLLBegin(from->list), DLLBegin(from->list));
	 	}
	 }
		 
	if (!SLIsEmpty(from))
	{
		DLLSplice(dest.iterator, DLLBegin(from->list), DLLIterPrev(DLLEnd(from->list)));
	}	 
	 
	return SLBegin(to);
}

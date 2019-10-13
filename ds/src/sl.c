#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "sl.h" /* all functions below */

struct sorted_list
{
	dll_t *list;
	sl_is_before_t *is_before;
};

sl_t *SLCreate(sl_is_before_t *is_before_func)
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

sl_iter_t SLInsert(sl_t *sorted_list, sl_iter_t iterator, void *data);

sl_iter_t SLRemove(sl_t *sorted_list, sl_iter_t iterator);

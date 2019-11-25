#include <stdlib.h> /* malloc, free */

#include "heap.h"   /* all below */
#include "vector.h" /* store queue in dynamic vector */

struct heap
{
    int root_idx;
    is_before_t is_before;
    void *param;
    vector_t *vector;
};

/****************************Forward declarations******************************/
void Heapify(heap_t *heap, int idx);
void SwapData(heap_t *heap, int idx1, int idx2);
void SwapHelper(void *data1, void *data2);

int FindParentIdx(int i);
int FindLeftChildIdx(int i);
int FindRightChildIdx(int i);

/******************************************************************************/
heap_t *HEAPCreate(is_before_t func, void *param)
{
    heap_t *heap = NULL;

    heap = malloc(sizeof(*heap));
    if (NULL == heap)
    {
        return NULL;
    }
    
    heap->vector = VectorCreate(sizeof(size_t *), 1);
    if (NULL == heap->vector)
    {
        free(heap); heap = NULL;
        return NULL;
    }

    heap->is_before = func;
    heap->root_idx = 0;
    heap->param = param;

    return heap;
}

void HEAPDestroy(heap_t *heap)
{
    VectorDestroy(heap->vector);
    free(heap); heap = NULL;
}

int HEAPPush(heap_t *heap, const void *data)
{
    int status = 0;

    status = VectorPushBack(heap->vector, data);

    if (0 == status)
    {
        Heapify(heap, VectorSize(heap->vector) - 1);
    }
    
    return status;
}

void HEAPPop(heap_t *heap);

void *HEAPPeek(heap_t *heap)
{
    return VectorGetItemAddress(heap->vector, VectorSize(heap->vector) - 1);
}

size_t HEAPSize(const heap_t *heap);

int HEAPIsEmpty(const heap_t *heap);

/*******************************Internal function******************************/
void Heapify(heap_t *heap, int idx)
{
    int largest_idx = idx;
    void *element = NULL;
    void *element_left_chld = NULL, *element_right_chld = NULL;
    size_t vec_size = 0;

    vec_size = VectorSize(heap->vector);

    element = VectorGetItemAddress(heap->vector, idx);
    element_left_chld = VectorGetItemAddress(heap->vector, FindLeftChildIdx(idx));
    element_right_chld = VectorGetItemAddress(heap->vector, FindRightChildIdx(idx));

    if ((FindLeftChildIdx(idx) < vec_size) && heap->is_before(element, element_left_chld, heap->param))
    {
        largest_idx = FindLeftChildIdx(idx);
    }

    if ((FindRightChildIdx(idx) < vec_size) && heap->is_before(element, element_right_chld, heap->param))
    {
        largest_idx = FindRightChildIdx(idx);
    }

    if (idx != largest_idx)
    {
        SwapData(heap, idx, largest_idx);
        Heapify(heap, largest_idx);
    }
}

int FindParentIdx(int i)
{
    return (i - 1) / 2;
}

int FindLeftChildIdx(int i)
{
    return (2 * i) + 1;
}

int FindRightChildIdx(int i)
{
    return (2 * i) + 2;
}

void SwapData(heap_t *heap, int idx1, int idx2)
{
    SwapHelper(VectorGetItemAddress(heap->vector, idx1), 
        VectorGetItemAddress(heap->vector, idx2));
}

void SwapHelper(void *data1, void *data2)
{
    size_t temp_data = 0;

    temp_data = *(size_t *)data1;
    *(size_t *)data1 = *(size_t *)data2;
    *(size_t *)data2 = temp_data;
}
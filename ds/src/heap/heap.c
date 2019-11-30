#include <stdlib.h> /* malloc, free */
#include <stdio.h>

#include "heap.h"   /* all below */
#include "vector.h" /* store queue in dynamic vector */

struct heap
{
    is_before_t is_before;
    void *param;
    vector_t *vector;
};

/****************************Forward declarations******************************/
void Heapify(heap_t *heap, int idx);
void SiftUp(heap_t *heap, int idx);
void SiftDown(heap_t *heap, int idx);
void SwapData(heap_t *heap, int idx1, int idx2);
void SwapHelper(void *data1, void *data2);

int FindParentIdx(int i);
int FindLeftChildIdx(int i);
int FindRightChildIdx(int i);

/************************
 *      FUNCTIONS     	*
************************/
heap_t *HEAPCreate(is_before_t func, void *param)
{
    heap_t *heap = NULL;

    heap = malloc(sizeof(*heap));
    if (NULL == heap)
    {
        return NULL;
    }

    heap->vector = VectorCreate(sizeof(void *), 1);
    if (NULL == heap->vector)
    {
        free(heap);
        heap = NULL;

        return NULL;
    }

    heap->is_before = func;
    heap->param = param;

    return heap;
}

void HEAPDestroy(heap_t *heap)
{
    VectorDestroy(heap->vector);
    free(heap);
    heap = NULL;
}

int HEAPPush(heap_t *heap, const void *data)
{
    int status = 0;

    status = VectorPushBack(heap->vector, &data);

    if (0 == status)
    {
        SiftUp(heap, HEAPSize(heap) - 1);
    }

    return status;
}

void HEAPPop(heap_t *heap)
{
    VectorPopBack(heap->vector);
    SiftDown(heap, 1);
}

void HEAPErase(heap_t *heap, heap_is_match_t func, void *data)
{
    int i = 0;
    size_t size = 1;
    void *removable = NULL;

    size = HEAPSize(heap);

    for (i = size - 1; 0 < i; --i)
    {
        removable = VectorGetItemAddress(heap->vector, i);
        if (func(*(void **)removable, data))
        {
            break;
        }
    }

    SwapHelper(removable, VectorGetItemAddress(heap->vector, VectorSize(heap->vector) - 1));
    HEAPPop(heap);
    SiftUp(heap, HEAPSize(heap) - 1);
}

void *HEAPPeek(heap_t *heap)
{
    return *(void **)VectorGetItemAddress(heap->vector, VectorSize(heap->vector) - 1);
}

size_t HEAPSize(const heap_t *heap)
{
    return VectorSize(heap->vector);
}

int HEAPIsEmpty(const heap_t *heap)
{
    return (1 > VectorSize(heap->vector));
}

void HEAPSort(heap_t *heap, size_t size)
{
    int i = 0;

    if (1 >= size)
    {
        return;
    }

    for (i = ((size - 1) / 2) + 1; 0 <= i; i--)
    {
        Heapify(heap, i);
    }

    for (i = size - 1; 0 <= i; i--)
    {
        SwapData(heap, 1, i);
        Heapify(heap, i);
    }
}

/*******************************Internal function******************************/
void Heapify(heap_t *heap, int idx)
{
    int largest_idx = idx;
    int left = 0, right = 0;
    void *element = NULL;
    void *element_left_chld = NULL, *element_right_chld = NULL;
    size_t vec_size = 0;

    vec_size = VectorSize(heap->vector) - 1;
    left = FindLeftChildIdx(idx);
    right = FindRightChildIdx(idx);

    element = VectorGetItemAddress(heap->vector, idx);
    element_left_chld = VectorGetItemAddress(heap->vector, left);

    if ((NULL != element_left_chld) && ((left < vec_size)))
    {
        if (heap->is_before(*(void **)element, *(void **)element_left_chld, heap->param))
        {
            largest_idx = left;
        }

        element_right_chld = VectorGetItemAddress(heap->vector, right);
        if (NULL != element_right_chld)
        {
            if ((right < vec_size) && heap->is_before(*(void **)element,
                                                      *(void **)element_right_chld, heap->param))
            {
                largest_idx = right;
            }
        }
    }

    if (idx != largest_idx)
    {
        SwapData(heap, idx, largest_idx);
        Heapify(heap, largest_idx);
    }
}

void SiftDown(heap_t *heap, int idx)
{
    int right_child_idx = 0, left_child_idx = 0;
    int largest_idx = 0;
    void *right_child = NULL;
    int max_idx = 0;

    largest_idx = idx;
    left_child_idx = FindLeftChildIdx(idx);
    max_idx = HEAPSize(heap) - 1;

    /* if (left_child_idx <= max_idx)
    {
        if (heap->is_before(*(void **)VectorGetItemAddress(heap->vector, 
            left_child_idx), *(void **)VectorGetItemAddress(heap->vector, 
            idx),heap->param))
        {
            largest_idx = left_child_idx;
        }
    }

    right_child_idx = FindRightChildIdx(idx);
    if (right_child_idx <= max_idx)
    {
        if (heap->is_before(*(void **)VectorGetItemAddress(heap->vector, 
            right_child_idx), *(void **)VectorGetItemAddress(heap->vector, 
            idx),heap->param))
        {
            largest_idx = right_child_idx;
        }
    }

    if (largest_idx != idx)
    {
        SwapHelper(VectorGetItemAddress(heap->vector, largest_idx), 
            VectorGetItemAddress(heap->vector, idx));
        SiftDown(heap, largest_idx);
    } */
    
    

    right_child_idx = FindRightChildIdx(idx);

    if (HEAPSize(heap) - 1 >= right_child_idx)
    {
        right_child = VectorGetItemAddress(heap->vector, right_child_idx);
        
        if (heap->is_before(VectorGetItemAddress(heap->vector,
            right_child_idx), VectorGetItemAddress(heap->vector, idx),
            heap->param))
        {
            return;
        }
        else
        {
            SwapHelper(right_child, VectorGetItemAddress(heap->vector, idx));
            SiftDown(heap, right_child_idx);
        }
    }
}

void SiftUp(heap_t *heap, int idx)
{
    void *curr = NULL;
    int parent_idx = 0;

    if (0 < idx) /* maybe 0 instead of 1? */
    {
        parent_idx = FindParentIdx(idx);
        curr = VectorGetItemAddress(heap->vector, idx);
        if (heap->is_before(curr, VectorGetItemAddress(heap->vector, 
            parent_idx), heap->param))
        {
            return;
        }
        else
        {
            SwapHelper(curr, VectorGetItemAddress(heap->vector, parent_idx));
            SiftUp(heap, FindParentIdx(parent_idx));
        }
    }
}

int FindParentIdx(int i)
{
    if (1 >= i)
    {
        return 0;
    }

    return ((i - 1) / 2) + 1;
}

int FindLeftChildIdx(int i)
{
    if (i <= 1)
    {
        return 2;
    }

    return (2 * i) + 1;
}

int FindRightChildIdx(int i)
{
    if (i <= 1)
    {
        return 3;
    }

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

void PrintHeap(heap_t *heap)
{
    size_t i = 0;

    printf("\n");
    for (i = 0; i < VectorSize(heap->vector); ++i)
    {
        printf("%lu - %d\n", i + 1, **(int **)VectorGetItemAddress(heap->vector, i));
    }
}

void PrintHeapVec(heap_t *heap)
{
    size_t i = 0;

    for (i = 0; i < VectorSize(heap->vector) - 1; ++i)
    {
        printf("%d ", **(int **)VectorGetItemAddress(heap->vector, i));
    }

    printf("\n");
}
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
void SiftUp(heap_t *heap);
void SwapData(heap_t *heap, int idx1, int idx2);
void SwapHelper(void **data1, void **data2);

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

    heap->vector = VectorCreate(sizeof(size_t *), 1);
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
        SiftUp(heap);
    }

    return status;
}

void HEAPPop(heap_t *heap)
{
    VectorPopBack(heap->vector);
}

void HEAPRemove(heap_t *heap, void *data)
{
    int i = 0;
    size_t size = 1;
    void **removable = NULL;

    size = HEAPSize(heap);

    for (i = size - 1; 0 < i; --i)
    {
        removable = VectorGetItemAddress(heap->vector, i);
        if (*(void **)removable == data)
        {
            break;
        }
    }

    SwapHelper(removable, VectorGetItemAddress(heap->vector, size - 1));
    HEAPPop(heap);
    Heapify(heap, size - i - 1);
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
        /* SwapData(heap, 1, i);  */
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
        if (heap->is_before(element, element_left_chld, heap->param))
        {
            largest_idx = left;
        }

        element_right_chld = VectorGetItemAddress(heap->vector, right);
        if (NULL != element_right_chld)
        {
            if ((right < vec_size) && heap->is_before(element,
                                                      element_right_chld, heap->param))
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

void SiftUp(heap_t *heap)
{
    int curr = 0;
    int parent = 0;
    void **curr_item = NULL;
    void **parent_item = NULL;

    curr = HEAPSize(heap) - 1;
    curr_item = VectorGetItemAddress(heap->vector, curr);

    parent = FindParentIdx(curr);
    parent_item = VectorGetItemAddress(heap->vector, parent);

    while (0 < curr)
    {
        if (heap->is_before(curr_item, parent_item, heap->param))
        {
            SwapHelper(parent_item, curr_item);
            curr = parent;
            parent = FindParentIdx(curr);
        }
        else
        {
            break;
        }
    }
}

int FindParentIdx(int i)
{
    if (1 >= i)
    {
        return 1;
    }

    return ((i - 1) / 2) + 1;
}

int FindLeftChildIdx(int i)
{
    if (i <= 1)
    {
        return 2;
    }

    return (2 * i);
}

int FindRightChildIdx(int i)
{
    if (i <= 1)
    {
        return 3;
    }

    return (2 * i) + 1;
}

void SwapData(heap_t *heap, int idx1, int idx2)
{
    SwapHelper(VectorGetItemAddress(heap->vector, idx1),
               VectorGetItemAddress(heap->vector, idx2));
}

void SwapHelper(void **data1, void **data2)
{
    void *temp_data = 0;

    temp_data = *data1;
    *data1 = *data2;
    *data2 = temp_data;
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

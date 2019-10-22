/******************************************************************************
 *                                                                            *
 * ------------------------------- dll_test.c ------------------------------- *
 *                                                                            *
 *****************************************************************************/
#include <stdio.h> /* printf */

#include "dll.h"

void PrintMsg(const char *msg);
void PrintListForward(dll_t *list);
void PrintListBackward(dll_t *list);
void PrintListInfo(dll_t *list);

int IntAddNum(void *data, void *param);
/* test */
int IntFindNum(const void *data, void *param);
int GetIntData(dll_iter_t iter);

/* driver program */
int main (void)
{
    /* list */
    dll_t *list1 = NULL;
    dll_t *list2 = NULL;

    /* inputs */
    int iarr[] = {0,1,2,3,4,5,6,7,8,9};
    size_t i = 0;

    int add_num = 100;
    dll_iter_t iter = {NULL,NULL};
    dll_iter_t iter2 = {NULL,NULL};
    dll_iter_t iter3 = {NULL,NULL};

    /* create lists */
    list1 = DLLCreate();
    list2 = DLLCreate();
    
    PrintMsg("TEST START");
    PrintListInfo(list1);
    
    PrintMsg("Front loading list with array elements");
    for (i = 0; i < (sizeof(iarr)/sizeof(*iarr))/2; i++)
    {
        DLLPushFront(list1,&iarr[i]);
    }
    PrintListForward(list1);

    PrintMsg("Back loading list with array elements");
    for (i = sizeof(iarr)/sizeof(*iarr)/2; i < sizeof(iarr)/sizeof(*iarr); i++)
    {
        DLLPushBack(list1,&iarr[i]);
    }
    PrintListForward(list1);
    PrintListInfo(list1);

    /* PopFront */
    PrintMsg("Pop two elements from the front");
    DLLPopFront(list1);
    DLLPopFront(list1);
    PrintListForward(list1);
    PrintListInfo(list1);
    
    /* PopBack */
    PrintMsg("Pop two elements from the back");
    DLLPopBack(list1);
    DLLPopBack(list1);
    PrintListForward(list1);
    PrintListInfo(list1);

    /* check for each */
    PrintMsg("Add number to each element");
    DLLForEach(DLLBegin(list1),DLLEnd(list1),IntAddNum, &add_num);
    PrintListForward(list1);
    
    PrintMsg("Find number position in elements");
    iter = DLLFind(DLLBegin(list1),DLLEnd(list1),IntFindNum, &add_num);
    printf("Found data in iterator, data is: %d\n",DLLIterGetData(iter) ? GetIntData(iter) : -1 );

    /* Insert node at iterator position */
    PrintMsg("Insert the elements found");
    iter = DLLInsert(iter,DLLIterGetData(iter));
    iter = DLLInsert(iter,DLLIterGetData(iter));
    iter = DLLInsert(iter,DLLIterGetData(DLLBegin(list1)));

    /* change value in iter.current->data */
    PrintMsg("Add num to found iterator");
    IntAddNum(DLLIterGetData(iter),&add_num);
    PrintListForward(list1);
    PrintListInfo(list1);

    /* get iteraror to last element */
    PrintMsg("Get Last Element");
    iter = DLLIterPrev((DLLEnd(list1)));
    printf("value in last element is: %d\n",GetIntData(iter));
    
    /* remove last element */
    PrintMsg("Remove last element");
    iter = DLLRemove(iter);
    PrintListForward(list1);

    /* remove every element in the list, starts from begin */
    PrintMsg("Remove all elements, starts from begin");   
    iter = DLLBegin(list1);
    printf("value in first element: %d\n",GetIntData(iter));

    while (!DLLIsEmpty(list1))
    {
        DLLPopBack(list1);
    }
    PrintListInfo(list1);


    /* -----------------------------SPLICE TEST-------------------------------- */
    PrintMsg("SPLICE TEST");
    printf("Inputs:\n");
    for (i = 0; i < (sizeof(iarr)/sizeof(*iarr)); i++)
    {
        printf("%d ",iarr[i] = i);
    }
    printf("\n");

    for (i = 0; i < (sizeof(iarr)/sizeof(*iarr))/2; i++)
    {
        DLLPushBack(list1,&iarr[i]);
    }
    
    for (i = (sizeof(iarr)/sizeof(*iarr))/2 ; i < sizeof(iarr)/sizeof(*iarr); i++)
    {
        DLLPushBack(list2,&iarr[i]);
    }

    /* Print list after Create */
    puts("list1");
    PrintListForward(list1);

    puts("list2");
    PrintListForward(list2);
    
    /* Set dest iterator */ 
    iter = DLLBegin(list1);
    /*iter = DLLIterNext(iter);*/
    
    /* Set Source iterator */
    iter2 = DLLBegin(list2);
    iter3 = DLLIterPrev(DLLEnd(list2));
    
    PrintMsg("After Splice");
    DLLSplice(iter, iter2, iter3);
     
    puts("list1");
    PrintListForward(list1);
    puts("list2");
    PrintListForward(list2);
    
    puts("list1");
    PrintListBackward(list1);
    puts("list2");
    PrintListBackward(list2);

    PrintListInfo(list1);

    /* Destroy list */
    DLLDestroy(list1);
    DLLDestroy(list2);

    return 0;
}

void PrintListForward(dll_t *list)
{
    dll_iter_t iter;
    dll_iter_t start = DLLBegin(list);
    dll_iter_t end = DLLEnd(list);
    
    printf("Print Forward\n");
    for (iter = start; !DLLIterIsEqual(iter,end); iter = DLLIterNext(iter))
    {
        printf("%d ",GetIntData(iter));
    }
    
    printf("\n");
}

void PrintListBackward(dll_t *list)
{
    dll_iter_t iter;
    dll_iter_t start = DLLIterPrev(DLLEnd(list));
    dll_iter_t end = DLLIterPrev(DLLBegin(list));

    printf("Print Backward\n");
    for (iter = start ; !DLLIterIsEqual(iter,end); iter = DLLIterPrev(iter))
    {
        printf("%d ",GetIntData(iter));
    }

    printf("\n");
}

void PrintListInfo(dll_t *list)
{
    printf("List State: %d, %s",DLLIsEmpty(list),"(1: empty, 0: non-empty)\n");
    printf("List Size: %lu\n",DLLSize(list));
}

void PrintMsg(const char *msg)
{
    char *hyphen = "";
    printf("\n%-6s%s%6s\n",hyphen,msg,hyphen);
    puts("_____________________________________");
}

int GetIntData(dll_iter_t iter)
{
    return *(int*)DLLIterGetData(iter);
}

int IntAddNum(void *data, void *param)
{
    *(int *)data += *(int *)param;
    
    return 0;
}

int IntFindNum(const void *data, void *param)
{
    return (*(int *)data == *(int *)param) ? 1 : 0;
}

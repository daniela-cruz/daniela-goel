/*******************************************************************************
 *                                                                             *
 * ------------------------------ pq_test.c ---------------------------------- *
 *                                                                             *
 ******************************************************************************/
#include <stdio.h>  /* printf */

#include "pq.h"     /* priority queue */
#include "person_list.h" /* a person list structe for test */

#define SIZE (10)

/* IsBefore functions for int */
int PQFindPersonId(const void *person, void *param);
int IsBeforePersonById(void *person1, void *person2, void *param);

/* driver program */
int main(void)
{
    /* Containers */
    pq_t *q1 = NULL;
    pl_t *prl1 = NULL;
    p_t *person = NULL;

    size_t i = 0;
    int param = 0;
    
    /* Create Priority queue */
    q1 = PQCreate(IsBeforePersonById,NULL);
    
    /* Create Person list structure */
    prl1 = PRCreatePersonList(SIZE);
    
    /* Insert inputs for person list */
    PRInsertPerson(prl1,0,200255180,"Maor","Moyal");
    PRInsertPerson(prl1,1,200210403,"David","Cohen");
    PRInsertPerson(prl1,2,300520120,"Moshe","Levi");
    PRInsertPerson(prl1,3,311390240,"Rami","Tal");
    PRInsertPerson(prl1,4,212300454,"Yakov","Levin");
    
    for (i = 0; i < 5; i++)
    {
        PQEnqueue(q1,PRGetPerson(prl1,i));
    }

    printf("Count %lu\n",PQCount(q1));
    printf("IsEmpty %d\n",PQIsEmpty(q1));
    
    printf("After Enqueu\n");
    for (i = 0 ; i < PQCount(q1); i++)
    {
        person = PRGetPerson(prl1,i);
        printf("ID: %d\n",PRGetPersonId(person));
        printf("First Name: %s\n",PRGetPersonFname(person));
        printf("Last Name: %s\n",PRGetPersonLname(person));
    }
    puts("");


    person = PQPeek(q1);
    printf("Peek Test\n");
    printf("ID: %d\n",PRGetPersonId(person));
    printf("First Name: %s\n",PRGetPersonFname(person));
    printf("Last Name: %s\n",PRGetPersonLname(person));
    
    
    /* Check erase */
    puts("");
    param = 200255180;
    printf("Looking for person with ID: %d\n", param);
    puts("After Erase");
    if (PQErase(q1, PQFindPersonId, &param))
    {
        printf("Person was found, and erased\n");
    }
    else
    {
        printf("Person was not found\n");
    }

    puts("");
    puts("Check Dequeue");
    while (!PQIsEmpty(q1))
    {
        person = PQDequeue(q1);
        printf("ID: %d\n",PRGetPersonId(person));
        printf("First Name: %s\n",PRGetPersonFname(person));
        printf("Last Name: %s\n",PRGetPersonLname(person));
    }

    printf("Count %lu\n",PQCount(q1));
    printf("IsEmpty %d\n",PQIsEmpty(q1));
     
    /* Destroy */
    PQDestroy(q1);
    PRDestroy(prl1);

    return 0;
}

int IsBeforePersonById(void *person1, void *person2, void *param)
{
    if (NULL == param || *(int *)param == 0)
    {
        return PRGetPersonId((p_t *)person1) < PRGetPersonId((p_t *)person2);
    }
    else
    {
        return PRGetPersonId((p_t *)person1) > PRGetPersonId((p_t *)person2);
    }
}

int PQFindPersonId(const void *person, void *param)
{
    return (PRGetPersonId((p_t *)person) == *(int *)param);
}


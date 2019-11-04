/******************************************************************************
 *                                                                            *
 * --------------------------- person_list.h -------------------------------- *
 *                                                                            *
 *****************************************************************************/
#ifndef __TEST_TMP__
#define __TEST_TMP__

#include <stddef.h> /* size_t */

/*******************************************************************************
*                                                                              *
* Define Person list structure                                                 *
*                                                                              *
*******************************************************************************/
typedef struct person_list pl_t;

typedef struct person p_t;
/*******************************************************************************
*                                                                              *
* ----------------------------- Public Interface ----------------------------  *
*                                                                              *
*******************************************************************************/

pl_t *PRCreatePersonList(size_t size);

int PRInsertPerson(pl_t *person_list, size_t index, int id, char *fname, char *lname);

int PRPushPersonBack(pl_t *person_list, int id, char *fname, char *lname);

size_t PRSize(pl_t *person_list);

p_t* PRGetPerson(pl_t *person_list, size_t index);

int PRGetPersonId(p_t* person);

char *PRGetPersonFname(p_t *person);

char *PRGetPersonLname(p_t *person);

/* Change 
int PRGetId(pl_t *person_list, size_t index);

char *PRGetFname(pl_t *person_list, size_t index);

char *PRGetLname(pl_t *person_list, size_t index);
*/
void PRDestroy(pl_t *person_list);

#endif /* TEST_TMP GUARD */

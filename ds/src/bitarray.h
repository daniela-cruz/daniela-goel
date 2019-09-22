#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stddef.h> /* size_t */

typedef size_t bit_arr_t; /* an array of 64 bits*/

/* Create a new bit array */
bit_arr_t BitArrCreate();

/* 1 if a particular bit is set on else 0 */
int BitArrIsOn(bit_arr_t arr, int bit_location);

/* 1 if a particular bit is set off else 0 */
int BitArrIsOff(bit_arr_t arr, int bit_location);

/* set on all bits in array */
bit_arr_t BitArrSetAll();

/* set off all bits in array*/
bit_arr_t BitArrResetAll();

/* set a particular bit on */
bit_arr_t BitArrSetOn(bit_arr_t arr, int bit_location);

/* set a particular bit off */
bit_arr_t BitArrSetOFF(bit_arr_t arr, int bit_location);

/* rotate arr left n times */
bit_arr_t BitArrRotL(bit_arr_t arr, int n);

/* rotate arr right n times */
bit_arr_t BitArrRotR(bit_arr_t arr, int n);

/* flip a single bit */
bit_arr_t BitArrFlip(bit_arr_t arr, int bit_location);

/* count number of set bits */
int BitArrCountOn(bit_arr_t arr);

/* count number of off bits */
int BitArrCountOff(bit_arr_t arr);

/* mirror bit array */
bit_arr_t Mirror(bit_arr_t arr);

/* convert array to a string */
char *ToString(char *dest, bit_arr_t src);

#endif /* __BIT_ARRAY_H__ */

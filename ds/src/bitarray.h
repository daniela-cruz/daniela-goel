#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stddef.h> /* size_t */

typedef size_t bit_arr_t; /* an array of 64 bits*/

/******************************************
*												*
*		BitArr functions phase I		*
*												*
******************************************/

/* 1 if a particular bit is set on else 0 */
int BitArrIsOn(bit_arr_t arr, int bit_location);

/* 1 if a particular bit is set off else 0 */
int BitArrIsOff(bit_arr_t arr, int bit_location);

/* set on a single bit within the array */
bit_arr_t BitArrSet(bit_arr_t arr, size_t bit_location, int is_set);

/* set on all bits in array */
bit_arr_t BitArrSetAll(bit_arr_t arr);

/* set off all bits in array*/
bit_arr_t BitArrResetAll(bit_arr_t arr);

/* set a particular bit on */
size_t BitArrSetOn(bit_arr_t arr, int n);

/* set a particular bit off. If the user provided wrong input there's an undefined behavior */
size_t BitArrSetOff(bit_arr_t arr, int n);

/* rotate arr left n times */
bit_arr_t BitArrRotL(bit_arr_t arr, size_t n);

/* rotate arr right n times */
bit_arr_t BitArrRotR(bit_arr_t arr, size_t n);

/* flip a single bit */
bit_arr_t BitArrFlip(bit_arr_t arr, int bit_location);

/* count number of set bits */
size_t BitArrCountOn(bit_arr_t arr);

/* count number of off bits */
size_t BitArrCountOff(bit_arr_t arr);

/* mirror bit array */
bit_arr_t BitArrMirror(bit_arr_t arr);

/******************************************
*												*
*		 BitArr functions II: LUT		*
*												*
******************************************/

/* initializes LUT on first call afterwhich an imidiate value can be withdrawn form */
size_t BitArrCountOnLUT(bit_arr_t arr);


/* mirror bit array
* using a LUT table init table if not initialized before
*/
bit_arr_t BitArrMirrorLUT(bit_arr_t arr);

/* convert array to a string */
char *BitArrToString(char *dest, bit_arr_t src);

#endif /* __BIT_ARRAY_H__ */

#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

typedef int bit_arr_t; /* an array of 64 bits*/

/* 1 if a particular bit set on else 0 */
extern int IsOn(const bit_arr_t *arr, size_t bit_location);

/* 1 if a particular bit set off else 0 */
extern int IsOff(const bit_arr_t *arr, size_t bit_location);

/* set on all bits in array*/
extern void SetAll(bit_arr_t *arr);

/* set off all bits in array*/
extern void ResetAll(bit_arr_t *arr);

/* rotate arr left n times */
extern bit_arr_t *RotL(bit_arr_t *arr, size_t n);

/* rotate arr right n times */
extern bit_arr_t *RotR(bit_arr_t *arr, size_t n);

/* flip a single bit */
extern bit_arr_t *Flip(bit_arr_t *arr, size_t bit_location);

/* count number of set bits */
extern size_t CountOn(const bit_arr_t *arr);

/* count number of off bits */
extern size_t CountOff(const bit_arr_t *arr);

/* mirror bit array */
extern bit_arr_t *Mirror(bit_arr_t *arr);

/* convert array to a string */
extern char *ToString(char * dest, bit_arr_t *src);

#endif

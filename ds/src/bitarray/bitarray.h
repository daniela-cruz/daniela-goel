#ifndef __bit_array_h__
#define __bit_array_h__
#include <stddef.h> /* size_t */

/*	 bit array of size size_t	*/
typedef size_t bit_arr_t;

/* count bits that are set to '1'	*/ 
/*		 return count			*/
size_t BitArrCountOn(bit_arr_t bit_arr);
/* count bits that are set to '0'	*/
/*		 return count			*/
size_t BitArrCountOff(bit_arr_t bit_arr);

/* check if bit num "index" is on	*/
/*		return true/false		*/
/*  in case index is bigger than 
	our arr - undefined behavior	*/
int BitArrIsOn(bit_arr_t bit_arr, int index);
/* check if bit num "index" is off	*/
/* 		return true/false		*/
/*  in case index is bigger than 
	our arr - undefined behavior	*/
int BitArrIsOff(bit_arr_t bit_arr, int index);

/* perform "bit reversal" on our value	*/
/*	   return reversed bit array		*/
bit_arr_t BitArrMirror(bit_arr_t bit_arr);

/* set all elements in bit_arr to '1' */
/* 		return new bit array	   */
bit_arr_t BitArrSetAll(bit_arr_t bit_arr);
/* set all elements in bit_arr to '0' */
/* 		return new bit array	   */
bit_arr_t BitArrResetAll(bit_arr_t bit_arr);

/* put elements of bit_arr into string	*/
/* 		return string				*/
char *BitArrToString(bit_arr_t bit_arr, char *str);

/*	flip the value of bit num "index"	*/
/*  		 return new bit array	     */
bit_arr_t BitArrFlip(bit_arr_t bit_arr, int index);

/* set the value of bit num "index in bit arr to '1' */
/*			  return new bit array			   */
/*  		in case index is bigger than 
		our arr - undefined behavior			   */
bit_arr_t BitArrSetOn(bit_arr_t bit_arr, int index);
/* set the value of bit num "index in bit arr to '1' */
/*			  return new bit array			   */
/*  in case index is bigger than 
	our arr - undefined behavior				   */
bit_arr_t BitArrSetOff(bit_arr_t bit_arr, int index);
/* set the value of bit num "index in bit arr to val */
/*			  return new bit array			   */
/*  		in case index is bigger than 
		our arr - undefined behavior			   */
bit_arr_t BitArrSet(bit_arr_t bit_arr, int index, int val);

/* 		 rotate right by num_rotations 		   */
/*			  return new bit array			   */
bit_arr_t BitArrRotR(bit_arr_t bit_arr, size_t num_rotations);
/* 		 rotate left by num_rotations 		   */
/*			  return new bit array			   */
bit_arr_t BitArrRotL(bit_arr_t bit_arr, size_t num_rotations);

/*	 count bits that are set to '1' by using LUT	   */
/* 			    return count 			 	   */
size_t BitArrCountOnLUT(bit_arr_t bit_arr);
/*	    perform "bit reversal" on our value		   */
/* 			return reversed bit array	 	   */
bit_arr_t BitArrMirrorLUT(bit_arr_t bit_arr);

#endif /* end of __bit_array_h__ */


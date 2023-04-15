/*
 * utility.c
 *
 *  Created on: Apr 6, 2023
 *      Author: Cooper Floyd Mattern
 */

#include <stdint.h>

/*	INPUTS:
 * 		num: 8 bit unsigned int to be converted to a 16 bit long bit-map
 *
 *	OUTPUT:
 *		16 bit long bit-map
 *
 *	FUNCTION DESCRIPTION:
 *		translates an 8 bit unsigned int to a 16 bit long bit map
 */
uint16_t btosbm(uint8_t num){
	uint16_t ret_val = 0;
	for(int i = 0; i < num; i++){
		ret_val += (i<<num);
	}
	return ret_val;
}

/*	INPUTS:
 * 		num: 16 bit bit-map to be converted to an 8 bit unsigned int
 *
 *	OUTPUT:
 *		8 bit number
 *
 *	FUNCTION DESCRIPTION:
 *		translates a 16 bit bit-map to an 8 bit unsigned int
 */
uint8_t sbmtob(uint16_t num){
	uint8_t ret_val = 0;
	for(int i = 0; i< num; i++){
		ret_val += num & (1<<i);
	}
	return ret_val;
}

uint16_t bm_arrtos(uint16_t* arr, uint32_t arr_len){
	uint16_t ret_val = 0;
	for(int i = 0; i < arr_len; i++){
		ret_val+=arr[i];
	}
	return ret_val;
}

/*
 * fast 32 bit log base 2 by:
 * miwe on StackOverflow
 *
 * https://stackoverflow.com/a/11398748
 *
 * modified to use uint32_t as return type;
 */

const uint32_t tab32[32] = {
     0,  9,  1, 10, 13, 21,  2, 29,
    11, 14, 16, 18, 22, 25,  3, 30,
     8, 12, 20, 28, 15, 17, 24,  7,
    19, 27, 23,  6, 26,  5,  4, 31};

uint32_t log2_32 (uint32_t value)
{
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return tab32[(uint32_t)(value*0x07C4ACDD) >> 27];
}

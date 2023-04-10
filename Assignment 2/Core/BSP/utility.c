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

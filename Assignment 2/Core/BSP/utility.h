/*
 * utility.h
 *
 *  Created on: Apr 6, 2023
 *      Author: Cooper Floyd Mattern
 */

#ifndef INC_UTILITY_H_
#define INC_UTILITY_H_

#include <stdint.h>
uint16_t btosbm(uint8_t num);
uint8_t sbmtob(uint16_t num);
uint16_t bm_arrtos(uint16_t* arr, uint32_t arr_len);
uint32_t log2_32(uint32_t value);

#endif /* INC_UTILITY_H_ */

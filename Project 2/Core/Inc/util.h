/*
 * util.h
 *
 *  Created on: Jun 13, 2023
 *      Author: Cooper Mattern
 */

#ifndef INC_UTIL_H_
#define INC_UTIL_H_

#include "arm_math.h"

char * dtoa(char *s, double n);
float32_t findMin(float32_t* data, int size);
float32_t findMax(float32_t* data, int size);
float32_t findAvg(float32_t* data, int size);

#endif /* INC_UTIL_H_ */

/*
 * calculator.h
 *
 *  Created on: Jun 8, 2023
 *      Author: cnama
 */

#ifndef INC_CALCULATOR_H_
#define INC_CALCULATOR_H_

#include "util.h"

#define valid_input "enltcsq^*/+-()p,."

float expEval(char input_buf[CHAR_BUFF_SIZE][CHAR_BUFF_SIZE], int input_size);

#endif /* INC_CALCULATOR_H_ */

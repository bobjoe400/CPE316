/*
 * UART.h
 *
 *  Created on: May 8, 2023
 *      Author: Dalee
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32l476xx.h"

#define BAUD 0x271
#define VTSIZE 5

void UART_init(void);
void UART_print(char*);
void UART_ESC_Code(char*);


#endif /* INC_UART_H_ */

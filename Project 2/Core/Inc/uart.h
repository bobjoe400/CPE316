/* * *
Author: Luis Garica and Nilay Patel

Modified by Cooper Mattern

Description: UART Library Header File that permits
* */

//interfacing with STM32L476RG.
#ifndef SRC_UART_H_
#define SRC_UART_H_

#include "stdint.h"
#include "arm_math.h"
#define BAUD_RATE 0x1C200 // 115200
#define SYS_CLOCK 0x1E84800 // 32000000 Hz
#define UART_AF_MODE 0x7

void UART_init(void);
void UART_print(char str[]);
void UART_ESC_Code(char *code);
void UART_graph_print(float32_t volt);
void UART_printData(float32_t freq, float32_t rms, float32_t p2p, float32_t offset, float32_t DC_volt);

uint8_t UART_receive(void);

#endif /* SRC_UART_H_ */

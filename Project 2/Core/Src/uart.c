/*
* *
Author: Luis Garcia and Nilay Patel

Modified by Cooper Mattern

Description: UART Library Implementation File that contains
* *
the functions for interfacing with STM32L476RG.
The main functions are UART_init to setup the pins,
* *
UART_print to print out the user’s strings. Lastly,
there is UART_recieve to accept user input.
*/
#include "uart.h"
#include "util.h"
#include "arm_math.h"
#include <string.h>
#include "stm32l4xx_hal.h"

enum GRAPH_SEL {RMS = 0, DC};

void UART_init(void)
{
	// Enable GPIOA and USART2 clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;

	// Configure USART2 pins for alternate function
	GPIOA->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);
	GPIOA->MODER |= (GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1);
	GPIOA->AFR[0] |= (UART_AF_MODE << GPIO_AFRL_AFSEL2_Pos) | (UART_AF_MODE << GPIO_AFRL_AFSEL3_Pos);

	// Configure USART2 for 115200 baud, 8-bit data, no parity, 1 stop bit
	USART2->BRR = (SYS_CLOCK / BAUD_RATE);
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE;
}

void UART_print(char str[])
{
	while (*str)
	{
		while (!(USART2->ISR & USART_ISR_TXE_Msk));
		USART2->TDR = (*str++);
	}
}

void UART_ESC_Code(char *code) {
	char ESC = 0x1B;
	char print_buff[5] = "\0"; // Assure empty buffer
	memcpy(print_buff, &ESC, sizeof(unsigned char)); // Copy ESC into buffer
	memcpy(print_buff + 1, code, strlen(code)); // Copy code into buffer
	UART_print(print_buff); // Print the code
}

void UART_graph_print(float32_t volt){
	int i = 0;
	for(i = 0; i < volt; i++){
		UART_print("|");
	}
	if(((uint32_t) volt % 100) >= 45) UART_print("|");
	UART_print("\n\r|----|----|----|----|----|----|");
	UART_print("\n\r0   0.5  1.0  1.5  2.0  2.5  3.0");
}

void UART_printData(float32_t freq, float32_t rms, float32_t p2p, float32_t offset, float32_t DC_volt){
	int buff_size = 16;
	char printBuff[buff_size];
	UART_print("------\n\r  AC\n\r-----\n\rFrequency: ");
	memset(printBuff, 0, buff_size);
	dtoa(printBuff,freq);
	UART_print(printBuff);
	UART_print(" mV\n\rDC Offset: ");
	memset(printBuff, 0, buff_size);
	dtoa(printBuff,offset);
	UART_print(printBuff);
	UART_print(" V\n\rPeak-toPeak Voltage: ");
	memset(printBuff, 0, buff_size);
	dtoa(printBuff, p2p);
	UART_print(printBuff);
	UART_print(" Hz\n\rVoltage RMS: ");
	memset(printBuff, 0, buff_size);
	dtoa(printBuff, rms);
	UART_print(printBuff);
	UART_print(" mV\n\n\r");
	UART_graph_print(rms);
	UART_print(printBuff);
	UART_print("\n------\n\r  DC\n\r------\n\rDC Voltage: ");
	memset(printBuff, 0, buff_size);
	dtoa(printBuff, DC_volt);
	UART_print(printBuff);
	UART_print(" mV\n\n\r)");
	UART_graph_print(DC_volt);

}

uint8_t UART_receive(void)
{
    while (!(USART2->ISR & USART_ISR_RXNE_Msk));
    return USART2->RDR;
}

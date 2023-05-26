/*
* *
Author: Luis Garcia and Nilay Patel
Description: UART Library Implementation File that contains
* *
the functions for interfacing with STM32L476RG.
The main functions are UART_init to setup the pins,
* *
UART_print to print out the user’s strings. Lastly,
there is UART_recieve to accept user input.
*/
#include "uart.h"
#include "stm32l4xx_hal.h"

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
uint8_t UART_receive(void)
{
    while (!(USART2->ISR & USART_ISR_RXNE_Msk));
    return USART2->RDR;
}

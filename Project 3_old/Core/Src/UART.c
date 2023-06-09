#include "UART.h"
#include <string.h>

void UART_init(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; 	// Enable Clock to GPIOA
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN; // Enable Clock to UART2

	GPIOA->MODER &= ~(GPIO_MODER_MODE2 | GPIO_MODER_MODE3); 			// Clear MODER
	GPIOA->MODER |= (GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1);			// Enable Alternate Function
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3);				// Push-Pull
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED2 | GPIO_OSPEEDR_OSPEED3);	// Low Speed
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3);				// No Pull-Up/Pull-Down

	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2 | GPIO_AFRL_AFSEL3);	// AF7
	GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos | 7 << GPIO_AFRL_AFSEL3_Pos);

	USART2->CR1 &= ~(USART_CR1_M);							// Set Word Length to 8 bits
	USART2->BRR |= BAUD;									// Set Baud Rate
	USART2->CR2 &= ~(USART_CR2_STOP);						// Set Stop Bits to 1
	USART2->CR1 &= ~(USART_CR1_OVER8);						// Set Over-sampling to 16 bits

	USART2->CR1 |= (USART_CR1_UE | USART_CR1_RXNEIE);		// Enable UART2 and RXNE interrupts

	NVIC->ISER[1] |= (1 << (USART2_IRQn & 0x1F));			// Enable Interrupts in NVIC

	__enable_irq();									// Enable Interrupts Globally

	USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);		// Enable Transmitter and Receiver
}

void UART_print(char *data) {
	for (int i  = 0; i < strlen((char*)data); i++) {
		while (!(USART2->ISR & USART_ISR_TXE)); // Wait Until TX Buffer is Empty
		USART2->TDR = data[i]; 					// Write Data
	}

	while (!(USART2->ISR & USART_ISR_TC)); 		// Wait Until Transmission is Complete
}

void UART_ESC_Code(char *code) {

	char ESC = 0x1B;					// Escape Character ASCII in hex
	char vt[VTSIZE] = "\0";			// Assure empty buffer

	memcpy(vt, &ESC, sizeof(unsigned char)); 	// Copy ESC into buffer

	memcpy(vt + 1, code, strlen((char*)code));			// Copy code into buffer

	UART_print(vt);							// Print the code
}



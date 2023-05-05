/*
 * dac.c
 *
 *  Created on: Apr 28, 2023
 *      Author: cnama
 */
#include "dac.h"
void DAC_init(void){
	// PB12 SPI2_NSS
	// PB13 SPI2_SCK
	// PB14 SPI2_MISO
	// PB15 SPI2_MOSI
	// Enable GPIOB Clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	// Setup Pins as Alternate Function
	GPIOB->MODER &= ~(GPIO_MODER_MODE12 | GPIO_MODER_MODE13 | GPIO_MODER_MODE14 |
	GPIO_MODER_MODE15);
	GPIOB->MODER |= (GPIO_MODER_MODE12_1 | GPIO_MODER_MODE13_1|
	GPIO_MODER_MODE14_1 | GPIO_MODER_MODE15_1);
	// Setup Alternate Function as SPI
	GPIOB->AFR[1] |= (GPIO_AFRH_AFSEL12_0 | GPIO_AFRH_AFSEL12_2 |
	GPIO_AFRH_AFSEL13_0 | GPIO_AFRH_AFSEL13_2
	| GPIO_AFRH_AFSEL14_0 | GPIO_AFRH_AFSEL14_2 |
	GPIO_AFRH_AFSEL15_0 | GPIO_AFRH_AFSEL15_2);
	// Enable SPI Hardware Clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;
	// Controller Mode
	SPI2->CR1 = SPI_CR1_MSTR;
	// hardware Control CS Pin
	SPI2->CR2 = (SPI_CR2_DS_Msk | SPI_CR2_NSSP | SPI_CR2_SSOE);
	// Enable it
	SPI2->CR1 |= SPI_CR1_SPE;
}

void DAC_write(uint32_t data){
	uint16_t buf = data;
	// Add Header to Data
	buf &= ~(DAC_HDR_msk << NUM_BITS);
	buf |= (DAC_HDR << NUM_BITS);
	// Write to SPI
	SPI2->DR = buf;
}

uint32_t DAC_volt_conv(float val_to_conv){
	// Crop Max Value
	if(val_to_conv >= MAX_VOLTS){
		return MAX_VALUE;
	// Minimize negative values to 0
	}else if(val_to_conv < 0){
		return 0;
	}
	// Convert to 12-bit value
	return (uint32_t)((val_to_conv/MAX_VOLTS) * (MAX_VALUE));
}


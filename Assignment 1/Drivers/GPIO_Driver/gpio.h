/*
 * utility.h
 *
 *  Created on: Apr 5, 2023
 *      Author: cnama
 */

#ifndef GPIO_DRIVER_GPIO_H_
#define GPIO_DRIVER_GPIO_H_
#include "stm32l4xx_hal.h"
#include <stdint.h>

#define NUM_GPIO 3

enum SET_OUTPUT{FALSE, TRUE};

enum GIPO_EN_ENUM{GPIO_EN_A=1, GPIO_EN_B=2, GPIO_EN_C=4};

enum GPIO_ENUM {GPIO_A, GPIO_B, GPIO_C};

typedef struct{
	GPIO_TypeDef* GPIO[NUM_GPIO];
	uint16_t GPIO_PINS[NUM_GPIO];
}GPIO_Set;

//Bitwise or of GPIO_EN_A, GPIO_EN_B, and GPIO_EN_C
void GPIO_Init(uint8_t gpio_en, uint16_t num_pins);
void GIPO_Destroy();
GPIO_TypeDef* GPIO_Get(uint8_t gpio_sel);
void Pin_Config(uint16_t field_total, uint8_t gpio_sel, uint8_t* set_output, uint16_t (*pin_setup)[field_total]);

#endif /* GPIO_DRIVER_GPIO_H_ */

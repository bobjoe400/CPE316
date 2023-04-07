/*
 * utility.h
 *
 *  Created on: Apr 5, 2023
 *      Author: Cooper Floyd Mattern
 */

#ifndef GPIO_SETUP_GPIO_H_
#define GPIO_SETUP_GPIO_H_
#include "stm32l4xx_hal.h"
#include <stdint.h>

enum GIPO_EN_ENUM{GPIO_EN_A=1, GPIO_EN_B=2, GPIO_EN_C=4};
enum GPIO_ENUM {GPIO_A, GPIO_B, GPIO_C};

void GPIO_Driver_Init();
void GPIO_Port_Enable(uint8_t gpio_en);
void GPIO_Port_Disable(uint8_t gpio_sel);
GPIO_TypeDef* GPIO_Port_Get(uint8_t gpio_sel);
void GPIO_Port_Pin_Config(uint8_t gpio_sel);

#endif /* GPIO_SETUP_GPIO_H_ */

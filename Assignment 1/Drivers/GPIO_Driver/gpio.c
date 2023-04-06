/*
 * gpio.c
 *
 *  Created on: Apr 5, 2023
 *      Author: cnama
 */
#include "../../Drivers/GPIO_Driver/gpio.h"

#include <string.h>
#include <stdio.h>

#define FIELD_TOTAL 8

typedef union vec3_u{
	struct{
		uint32_t MODER_MASK, MODER_SET, OTYPER_SET, OSPEEDR_MASK, OSPEEDR_SET, PUPDR_MASK, PUPDR_SET, ODR_SET;
	}vec3_s;
	uint32_t vec3_a[FIELD_TOTAL];
}SetupData;

static GPIO_Set GPIO_Data;

/*gpio_en: Bitwise or of GPIO_EN_A, GPIO_EN_B, and GPIO_EN_C
  num_pins: How many pins will be enabled for that GIPO output
*/
void GPIO_Init(uint8_t gpio_en, uint16_t num_pins){
	for(uint8_t gpio_num = GPIO_A; gpio_num < NUM_GPIO; gpio_num++){
		switch(gpio_en & (0x1<<gpio_num)){
			case GPIO_EN_A:
				GPIO_Data.GPIO[GPIO_A] = GPIOA;
				GPIO_Data.GPIO_PINS[GPIO_A] = num_pins;
				break;
			case GPIO_EN_B:
				GPIO_Data.GPIO[GPIO_B] = GPIOB;
				GPIO_Data.GPIO_PINS[GPIO_B] = num_pins;
				break;
			case GPIO_EN_C:
				GPIO_Data.GPIO[GPIO_C] = GPIOC;
				GPIO_Data.GPIO_PINS[GPIO_C] = num_pins;
				break;
		}
	}
}

GPIO_TypeDef* GPIO_Get(uint8_t gpio_sel){
	if(gpio_sel >= NUM_GPIO){
		printf("GPIO SELECTION FAULT\n");
		return (GPIO_TypeDef*) -1;
	}

	GPIO_TypeDef* ret_GPIO;

	if((ret_GPIO = GPIO_Data.GPIO[gpio_sel])==0){
		printf("GPIO IS NOT ENABLED\n");
		return (GPIO_TypeDef*) -1;
	}

	return ret_GPIO;
}

void Pin_Config(uint16_t field_total, uint8_t gpio_sel, uint8_t* set_output, uint16_t (*pin_setup)[field_total]){
	SetupData GPIO_Config;
	GPIO_TypeDef* GPIO_to_Set_Up;
	if((GPIO_to_Set_Up = GPIO_Get(gpio_sel)) < 0){
		return;
	}

	uint16_t num_pins = GPIO_Data.GPIO_PINS[gpio_sel];

	memset(&GPIO_Config, 0, sizeof(SetupData));

	for(uint16_t pin_num = 0; pin_num< num_pins; pin_num++){
		uint16_t setup_field  =  0;
		for(; setup_field < field_total-1; setup_field++){
		  GPIO_Config.vec3_a[setup_field] += pin_setup[pin_num][setup_field];
		}
		GPIO_Config.vec3_a[field_total] += (pin_setup[pin_num][setup_field] & (set_output[pin_num]<<pin_num));
	}

	GPIO_to_Set_Up->MODER 	&= 	~(GPIO_Config.vec3_s.MODER_MASK);
	GPIO_to_Set_Up->MODER 	|= 	  GPIO_Config.vec3_s.MODER_SET;
	GPIO_to_Set_Up->OTYPER 	|= 	  GPIO_Config.vec3_s.OTYPER_SET;
	GPIO_to_Set_Up->OSPEEDR &= 	~(GPIO_Config.vec3_s.OSPEEDR_MASK);
	GPIO_to_Set_Up->OSPEEDR |= 	  GPIO_Config.vec3_s.OSPEEDR_SET;
	GPIO_to_Set_Up->PUPDR 	&= 	~(GPIO_Config.vec3_s.PUPDR_MASK);
	GPIO_to_Set_Up->PUPDR 	|= 	  GPIO_Config.vec3_s.PUPDR_SET;
	GPIO_to_Set_Up->ODR		|=	 (GPIO_Config.vec3_s.ODR_SET);
}


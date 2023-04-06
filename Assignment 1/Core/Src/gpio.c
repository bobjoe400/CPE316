/*
 * gpio.c
 *
 *  Created on: Apr 5, 2023
 *      Author: cnama
 */
#include <string.h>
#include <stdio.h>
#include "gpio.h"

typedef union vec3_u{
	struct{
		uint32_t MODER_MASK, MODER_SET, OTYPER_SET, OSPEEDR_SET, PUPDR_MASK, PUPDR_SET;
	}vec3_s;
	uint32_t vec3_a[6];
}SetupData;

static GPIO_Set* GPIO_Data;

void GPIO_Init(uint8_t gpio_en){
	memset(GPIO_Data, 0, sizeof(GPIO_Set));
	for(int gpio_num = GPIO_A; gpio_num < NUM_GPIO; gpio_num++){
		switch(gpio_num & (0x1<<gpio_num)){
		case GPIO_EN_A:
			GPIO_Data->GPIO[GPIO_A] = GPIOA;
			break;
		case GPIO_EN_B:
			GPIO_Data->GPIO[GPIO_B] = GPIOB;
			break;
		case GPIO_EN_C:
			GPIO_Data->GPIO[GPIO_C] = GPIOC;
		}
	}
}

GPIO_TypeDef* GPIO_Get(uint8_t gpio_sel){
	if(gpio_sel >= NUM_GPIO){
		printf("GPIO SELECTION FAULT\n");
		return (GPIO_TypeDef*) -1;
	}

	GPIO_TypeDef* ret_GPIO;

	if((ret_GPIO = GPIO_Data->GPIO[gpio_sel])==0){
		printf("GPIO IS NOT ENABLED\n");
		return (GPIO_TypeDef*) -1;
	}

	return ret_GPIO;
}

void Pin_Config(uint8_t num_pins, uint8_t num_set, uint8_t gpio_sel, uint8_t (*pin_setup)[num_set]){
	SetupData GPIO_Config;
	GPIO_TypeDef* GPIO_to_Set_Up;
	if((GPIO_to_Set_Up = GPIO_Get(gpio_sel)) < 0){
		return;
	}

	memset(&GPIO_Config, 0, sizeof(SetupData));

	for(int led_num = 0; led_num< num_pins; led_num++){
	  for(int setup_field = 0; setup_field < num_set; setup_field++){
		  GPIO_Config.vec3_a[setup_field] += pin_setup[led_num][setup_field];
	  }
	}

	GPIO_to_Set_Up->MODER &= ~(GPIO_Config.vec3_s.MODER_MASK);
	GPIO_to_Set_Up->MODER |= GPIO_Config.vec3_s.MODER_SET;
	GPIO_to_Set_Up->OTYPER |= GPIO_Config.vec3_s.OTYPER_SET;
	GPIO_to_Set_Up->OSPEEDR |= GPIO_Config.vec3_s.OSPEEDR_SET;
	GPIO_to_Set_Up->PUPDR &= ~(GPIO_Config.vec3_s.PUPDR_MASK);
	GPIO_to_Set_Up->PUPDR |= GPIO_Config.vec3_s.PUPDR_SET;
}


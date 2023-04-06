/*
 * gpio.c
 *
 *  Created on: Apr 5, 2023
 *      Author: cnama
 */
#include "gpio.h"

#include <string.h>
#include <stdio.h>

#define FIELD_TOTAL 8
#define GPIOA_CLK_EN (0x1<<0)
#define GPIOB_CLK_EN (0x1<<1)
#define GPIOC_CLK_EN (0x1<<2)

//Structure for generating the masks and set values that are used by Pin_Config()
typedef union vec3_u{
	struct{
		uint32_t MODER_MASK, MODER_SET, OTYPER_SET, OSPEEDR_MASK, OSPEEDR_SET, PUPDR_MASK, PUPDR_SET, ODR_SET;
	}vec3_s;
	uint32_t vec3_a[FIELD_TOTAL];
}SetupData;

//structure used to hold the GPIO port pointers, their enable status, and their number of pins
typedef struct{
	GPIO_TypeDef* GPIO[NUM_GPIO];
	uint8_t GPIO_EN[NUM_GPIO];
	uint16_t GPIO_PINS[NUM_GPIO];
}GPIO_Set;

static GPIO_Set GPIO_Data;

/* 	INPUTS:
 * 		none
 *
 *  OUTPUTS:
 *  	none
 *
 * 	FUNCTION DESCRIPTION:
 * 		sets all data in the GIPO_Set structure to 0
 */
void GPIO_Driver_Init(){
	for(int i = 0; i< NUM_GPIO; i++){
		GPIO_Data.GPIO[i] = (GPIO_TypeDef*) 0;
		GPIO_Data.GPIO_EN[i] = 0;
		GPIO_Data.GPIO_PINS[i] = 0;
	}
}

/*	INPUTS:
 * 		gpio_en: Bitwise or of GPIO_EN_A, GPIO_EN_B, and GPIO_EN_C for which port(s) to be enabled
 * 		num_pins: How many pins will be enabled for that GIPO output
 *
 *	OUTPUTS:
 * 		none
 *
 * 	FUNCTION DESCRIPTION:
 * 		Allows up to all 3 ports to be enabled and has the GPIO pointer stored in the GPIO_Set GPIO array
 * 		Will also store the number of pins to be enabled for that port in the GPIO_Set GPIO_PINS array
 * 		Finally, enables the clock for that port
 */
void GPIO_Port_Enable(uint8_t gpio_en, uint16_t num_pins){
	for(uint8_t gpio_num = GPIO_A; gpio_num < NUM_GPIO; gpio_num++){
		switch(gpio_en & (0x1<<gpio_num)){
			case GPIO_EN_A:
				GPIO_Data.GPIO[GPIO_A] = GPIOA;
				GPIO_Data.GPIO_EN[GPIO_A] = 0x1;
				GPIO_Data.GPIO_PINS[GPIO_A] = num_pins;
				RCC->AHB2ENR |= GPIOA_CLK_EN;
				break;
			case GPIO_EN_B:
				GPIO_Data.GPIO[GPIO_B] = GPIOB;
				GPIO_Data.GPIO_EN[GPIO_B] = 0x1;
				GPIO_Data.GPIO_PINS[GPIO_B] = num_pins;
				RCC->AHB2ENR |= GPIOB_CLK_EN;
				break;
			case GPIO_EN_C:
				GPIO_Data.GPIO[GPIO_C] = GPIOC;
				GPIO_Data.GPIO_EN[GPIO_C] = 0x1;
				GPIO_Data.GPIO_PINS[GPIO_C] = num_pins;
				RCC->AHB2ENR |= GPIOC_CLK_EN;
				break;
		}
	}
}

/*	INPUTS:
 * 		gpio_sel: the GPIO port to be disabled
 *
 * 	OUTPUTS:
 * 		none
 *
 * 	FUNCTION DESCRIPTION:
 * 		checks that the port exists is enabled
 * 		then disables the port and turns off it's clock
 * 		does not change any of the values stored in the port
 */

void GPIO_Port_Disable(uint8_t gpio_sel){
	if(GPIO_Port_Get(gpio_sel) < 0){
		return;
	}

	GPIO_Data.GPIO_EN[gpio_sel] = 0;
	switch(gpio_sel){
		case GPIO_A:
			RCC->AHB2ENR &= ~(GPIOA_CLK_EN);
			break;
		case GPIO_B:
			RCC->AHB2ENR &= ~(GPIOB_CLK_EN);
			break;
		case GPIO_C:
			RCC->AHB2ENR &= ~(GPIOC_CLK_EN);
			break;
	}
}

/*	INPUTS:
 * 		gpoi_sel: which GPIO port to get the pointer for
 *
 *	OUTPUTS:
 *		the GPIO port pointer
 *
 *	FUNCTION DESCRIPTION:
 *		takes in the a selected GPIO port, checks if the port number is valid and if the port is enabled
 *		returns the pointer to the GPIO port
 */
GPIO_TypeDef* GPIO_Port_Get(uint8_t gpio_sel){
	if(gpio_sel >= NUM_GPIO){
		printf("GPIO SELECTION FAULT\n");
		return NULL;
	}

	if(!GPIO_Data.GPIO_EN[gpio_sel]){
		printf("GPIO IS NOT ENABLED\n");
		return NULL;
	}

	return GPIO_Data.GPIO[gpio_sel];
}

/*	INPUTS:
 * 		field_total: total number of fields to be set on that port (this is defined in constraints.h)
 * 		gpio_sel: the GPIO port to configure
 * 		set_output: an array of bits that defines whether we will set an initial value of output for the port
 * 		pin_setup: the pin configuration values as defined in constraints.h
 *
 *	OUTPUTS:
 *		none
 *
 *	FUNCTION DESCRIPTION:
 *		takes in the parameters above, checks that the GPIO port number is correct and is enabled
 *		then calculates the masks and set values for each of the GIPO port fields
 *		finally sets those values
 */

void GPIO_Port_Pin_Config(uint16_t field_total, uint8_t gpio_sel, uint8_t* set_output, uint16_t (*pin_setup)[field_total]){
	SetupData GPIO_Config;
	GPIO_TypeDef* GPIO_to_Set_Up;
	if((GPIO_to_Set_Up = GPIO_Port_Get(gpio_sel)) == (GPIO_TypeDef*) NULL){
		return;
	}

	uint16_t num_pins = GPIO_Data.GPIO_PINS[gpio_sel];

	memset(&GPIO_Config, 0, sizeof(SetupData));

	for(uint16_t pin_num = 0; pin_num< num_pins; pin_num++){
		uint16_t setup_field  =  0;
		for(; setup_field < field_total-1; setup_field++){
		  GPIO_Config.vec3_a[setup_field] += pin_setup[pin_num][setup_field]; 									//per the library, each of the fields are
		} 	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	//already shifted

		GPIO_Config.vec3_a[setup_field] += (pin_setup[pin_num][setup_field] & (set_output[pin_num]<<pin_num)); 	//only add to the ODR_SET value if we've
	}																											//enabled output initialization

	GPIO_to_Set_Up->MODER 	&= 	~(GPIO_Config.vec3_s.MODER_MASK);
	GPIO_to_Set_Up->MODER 	|= 	  GPIO_Config.vec3_s.MODER_SET;
	GPIO_to_Set_Up->OTYPER 	|= 	  GPIO_Config.vec3_s.OTYPER_SET;
	GPIO_to_Set_Up->OSPEEDR &= 	~(GPIO_Config.vec3_s.OSPEEDR_MASK);
	GPIO_to_Set_Up->OSPEEDR |= 	  GPIO_Config.vec3_s.OSPEEDR_SET;
	GPIO_to_Set_Up->PUPDR 	&= 	~(GPIO_Config.vec3_s.PUPDR_MASK);
	GPIO_to_Set_Up->PUPDR 	|= 	  GPIO_Config.vec3_s.PUPDR_SET;
	GPIO_to_Set_Up->ODR		|=	 (GPIO_Config.vec3_s.ODR_SET);
}


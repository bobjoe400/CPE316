/*
 * gpio.c
 *
 *  Created on: Apr 5, 2023
 *      Author: Cooper Floyd Mattern
 */
#include "../../BSP/GPIO_Setup/gpio.h"

#include "utility.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "../../BSP/GPIO_Setup/constraints.h"


#define GPIOA_CLK_EN (0x1<<0)
#define GPIOB_CLK_EN (0x1<<1)
#define GPIOC_CLK_EN (0x1<<2)

//Structure for generating the masks and set values that are used by Pin_Config()
typedef union SETUP_DATA{
	struct{
		uint32_t MODER_MASK, MODER_SET, OTYPER_SET, OSPEEDR_MASK, OSPEEDR_SET, PUPDR_MASK, PUPDR_SET, ODR_SET;
	}Setup_Data_Struct;
	uint32_t Setup_Data_Array[FIELD_TOTAL];
}SetupData;

//structure used to hold the GPIO port pointers, their enable status, and their number of pins
typedef struct GPIO_SET{
	GPIO_TypeDef* GPIO_Pointer[NUM_GPIO];
	uint8_t GPIO_Enable[NUM_GPIO];
	uint16_t GPIO_Pins[NUM_GPIO];
	uint16_t* GPIO_Pin_Enable[NUM_GPIO];
}GPIO_Set;

static GPIO_Set GPIO_DATA;

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
		GPIO_DATA.GPIO_Pointer[i] = (GPIO_TypeDef*) 0;
		GPIO_DATA.GPIO_Enable[i] = 0;
		GPIO_DATA.GPIO_Pins[i] = 0;
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
void GPIO_Port_Enable(uint8_t gpio_en){
	for(uint8_t gpio_num = GPIO_A; gpio_num < NUM_GPIO; gpio_num++){
		switch(gpio_en & (0x1<<gpio_num)){
			case GPIO_EN_A:
				GPIO_DATA.GPIO_Pointer[GPIO_A] = GPIOA;
				GPIO_DATA.GPIO_Enable[GPIO_A] = 0x1;
				GPIO_DATA.GPIO_Pins[GPIO_A] = GPIOA_NUM_PINS;
				GPIO_DATA.GPIO_Pin_Enable[GPIO_A] = GPIOA_PIN_ENABLE;
				RCC->AHB2ENR |= GPIOA_CLK_EN;
				break;
			case GPIO_EN_B:
				GPIO_DATA.GPIO_Pointer[GPIO_B] = GPIOB;
				GPIO_DATA.GPIO_Enable[GPIO_B] = 0x1;
				GPIO_DATA.GPIO_Pins[GPIO_B] = GPIOB_NUM_PINS;
				GPIO_DATA.GPIO_Pin_Enable[GPIO_B] = GPIOB_PIN_ENABLE;
				RCC->AHB2ENR |= GPIOB_CLK_EN;
				break;
			case GPIO_EN_C:
				GPIO_DATA.GPIO_Pointer[GPIO_C] = GPIOC;
				GPIO_DATA.GPIO_Enable[GPIO_C] = 0x1;
				GPIO_DATA.GPIO_Pins[GPIO_C] = GPIOC_NUM_PINS;
				GPIO_DATA.GPIO_Pin_Enable[GPIO_C] = GPIOC_PIN_ENABLE;
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

	GPIO_DATA.GPIO_Enable[gpio_sel] = 0;
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

	if(!GPIO_DATA.GPIO_Enable[gpio_sel]){
		printf("GPIO IS NOT ENABLED\n");
		return NULL;
	}

	return GPIO_DATA.GPIO_Pointer[gpio_sel];
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

void GPIO_Port_Pin_Config(uint8_t gpio_sel){
	SetupData GPIO_Config;
	GPIO_TypeDef* GPIO_to_Set_Up;
	if((GPIO_to_Set_Up = GPIO_Port_Get(gpio_sel)) == (GPIO_TypeDef*) NULL){
		return;
	}

	uint8_t num_pins = sbmtob(GPIO_DATA.GPIO_Pins[gpio_sel]);

	memset(&GPIO_Config, 0, sizeof(SetupData));

	for(uint16_t pin_num = 0; pin_num < num_pins; pin_num++){
		uint16_t pin = log2_32(GPIO_DATA.GPIO_Pin_Enable[gpio_sel][pin_num]);
		uint16_t setup_field  =  0;
		for(; setup_field < FIELD_TOTAL; setup_field++){
		  GPIO_Config.Setup_Data_Array[setup_field] += GPIO_PIN_SETUP_VALS[gpio_sel][pin][setup_field]; 										//per the library, each of the fields are
		} 	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  										//already shifted
	}

	GPIO_to_Set_Up->MODER 	&= 	~(GPIO_Config.Setup_Data_Struct.MODER_MASK);
	GPIO_to_Set_Up->MODER 	|= 	  GPIO_Config.Setup_Data_Struct.MODER_SET;
	GPIO_to_Set_Up->OTYPER 	|= 	  GPIO_Config.Setup_Data_Struct.OTYPER_SET;
	GPIO_to_Set_Up->OSPEEDR &= 	~(GPIO_Config.Setup_Data_Struct.OSPEEDR_MASK);
	GPIO_to_Set_Up->OSPEEDR |= 	  GPIO_Config.Setup_Data_Struct.OSPEEDR_SET;
	GPIO_to_Set_Up->PUPDR 	&= 	~(GPIO_Config.Setup_Data_Struct.PUPDR_MASK);
	GPIO_to_Set_Up->PUPDR 	|= 	  GPIO_Config.Setup_Data_Struct.PUPDR_SET;
	GPIO_to_Set_Up->ODR		|=	 (GPIO_Config.Setup_Data_Struct.ODR_SET);
}

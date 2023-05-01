/*
 * dac.h
 *
 *  Created on: Apr 28, 2023
 *      Author: cnama
 */

#ifndef INC_DAC_H_
#define INC_DAC_H_
#include "stm32l4xx_hal.h"
#include "main.h"
#define MAX_VOLTS 3.3
#define MAX_VALUE 0xFFF
#define NUM_BITS 12
#define DAC_HDR 0b0011
#define DAC_HDR_msk 0b1111
void DAC_init(void);
void DAC_write(uint32_t data);
uint32_t DAC_volt_conv(float val_to_conv);


#endif /* INC_DAC_H_ */

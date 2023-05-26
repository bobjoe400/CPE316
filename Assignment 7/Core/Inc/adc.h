/*
* adc.h *
Author: Cooper Mattern and Nilay Patel
*/
#ifndef SRC_ADC_H_
#define SRC_ADC_H_

#include <stdint.h>
#include "stm32l4xx_hal.h"

#define NUM_SAMPLES 0x14        // equals 20
#define DELAY_TIME  0xFA0       // equals 4000
#define MULTIPLER   0.795       // the needed m in y = mx + b
#define DIFF        23.5        // the needed b in y = mx + b
#define DELAY       0xF4240     // equals 1000000
#define TENS        0xA         // equals 10
#define UPPER_VOLT  0x3E8       // equal 1000
#define LOWER_VOLT  0x62        // equal 100
#define SMP_47_5	0x4			// sampling to get 47.5
#define SMP_640_5	0x7			// sampling to get 640.5


// Define the ADC global variables
void ADC_init(void);
void printDigitalVoltage(uint16_t digitalVal);
void printFrequency(uint16_t frequency);

// global variables
uint16_t getADCVal(void);
uint8_t getADCRDY(void);
void setADCVal(uint16_t val);
void setADCRDY(uint8_t val);
#endif /* SRC_ADC_H_ */

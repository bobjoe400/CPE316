/*
 * Keypad.h
 *
 *  Created on: Apr 28, 2023
 *      Author: cnama
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "stm32l4xx_hal.h"

#define COL_PORT GPIOB

#define COL_AHB AHB2ENR

#define COL_AHB_PORT RCC_AHB2ENR_GPIOBEN

#define ROW_PORT GPIOC
#define ROW_AHB AHB2ENR
#define ROW_AHB_PORT RCC_AHB2ENR_GPIOCEN

#define NUM_ROWS 4
#define NUM_COLS 3

#define COL_START_PIN 0
#define ROW_START_PIN 0

#define ROW_MASK ((GPIO_IDR_ID0 | GPIO_IDR_ID1 | GPIO_IDR_ID2 | GPIO_IDR_ID3))

#define COL_MASK ((GPIO_ODR_OD0 | GPIO_ODR_OD1 | GPIO_ODR_OD2))

#define HASHTAG 12
#define STAR 10
#define ZERO_KEY 11
#define NO_KEY -1

#define KEYPAD_DELAY 100000

int keypad_read();
void keypad_setup();
int keypad_read_digits(int ndigits);


#endif /* INC_KEYPAD_H_ */
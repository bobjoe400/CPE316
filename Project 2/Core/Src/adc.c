/*
* adc.c
* */
//Author: Luis D. Garcia and Nilay Patel

#include "uart.h"
#include "adc.h"
#include "stm32l4xx_hal.h"
volatile uint16_t adc_value;
volatile uint8_t adc_ready;

void ADC_init(void)
{

	// configure GPIO for channel 5 on analog input pin (PA0)
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;                        // Enable GPIOA Clock
	GPIOA->MODER &=  ~(GPIO_MODER_MODE0_Msk);                   // Clear PA0
	GPIOA->MODER |= (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE0_1);  // Set pin as analog mode
	GPIOA->ASCR |= GPIO_ASCR_ASC0;                              // Set analog switch

	// Enable clock for ADC
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;

	//ADC will run at the same speed as CPU (CLK/1), Prescaler = 1
	ADC123_COMMON->CCR = (1 << ADC_CCR_CKMODE_Pos);

	//Power up the ADC and voltage regulator
	ADC1->CR &=  ~(ADC_CR_DEEPPWD);
	ADC1->CR |= (ADC_CR_ADVREGEN);

	// delay for voltage regulation startup time  ~ 20 us
	for (uint32_t i = 0; i < DELAY_TIME; i++);

	// Calibrate the ADC
	// ensure ADC is disabled and single-ended mode
	ADC1->CR &=  ~(ADC_CR_ADEN | ADC_CR_ADCALDIF);

	// start the calibration
	ADC1->CR |= ADC_CR_ADCAL;

	while(ADC1->CR & ADC_CR_ADCAL);

	// configure for single-ended mode on channel 5
	// must be set before enabling the ADC
	ADC1->DIFSEL &=  ~(ADC_DIFSEL_DIFSEL_5);         // Using ADC123_IN5 channel

	// enable ADC
	ADC1->ISR |= (ADC_ISR_ADRDY);                   // Clear ready bit with a 1
	ADC1->CR |= ADC_CR_ADEN;                        // Enable ADC
	while(!(ADC1->ISR & ADC_ISR_ADRDY));
	ADC1->ISR |= (ADC_ISR_ADRDY);                   // Clear ready bit with a 1 (optional)

	// Configure ADC
	// set sequence for 1 conversion on channel 5
	ADC1->SQR1 |= (5 << ADC_SQR1_SQ1_Pos);
	// 12 bit resolution, software trigger, right align, single conversion
	ADC1->CFGR = 0;
	//start conversion
	ADC1->CR |= (ADC_CR_ADSTART);
	//enable interrupts for ADC
	ADC1->IER |= (ADC_IER_EOC);                     // Interrupt on end of conversion
	ADC1->ISR &=  ~(ADC_ISR_EOC);                    // Clear EOC flag wit h1

	adc_value = 0;
	adc_ready = 0;
}


uint16_t getADCVal(void){
	return adc_value;
}
uint8_t getADCRDY(void){
	return adc_ready;
}
void setADCVal(uint16_t val){
	adc_value = val;
}
void setADCRDY(uint8_t val){
	adc_ready = val;
}

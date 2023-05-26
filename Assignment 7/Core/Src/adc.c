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

void printDigitalVoltage(uint16_t digitalVal)
{
	uint8_t currentChar[5];
	currentChar[1] = '.';
	currentChar[4] = '\0';
	if (digitalVal >= UPPER_VOLT) {
		digitalVal /= TENS;                                     // make it a 3 digit value
		currentChar[0] = (digitalVal / LOWER_VOLT) + '0';       // print the ones first
		currentChar[2] = ((digitalVal/TENS) % TENS) + '0';      // print the tenths second
		currentChar[3] = (digitalVal % TENS) +'0';              // print the hundreths value
		UART_print(currentChar);
	}

	else if (digitalVal >= LOWER_VOLT && digitalVal < UPPER_VOLT) {     // handling voltages in 0.1 - 0.9 V
		currentChar[0] = '0';                                           // the first is 0
		currentChar[2] = (digitalVal / LOWER_VOLT) + '0';               // print the ones first
		currentChar[3] = ((digitalVal / TENS) % TENS) + '0';            // print the tenths second
		UART_print(currentChar);
	}

	else {                                                              // handling voltages in the 0.09 - 0.01 V
		currentChar[0] = '0';                                           // set the one's to 0
		currentChar[2] = '0';                                           // set the tenths to 0
		currentChar[3] = (digitalVal / TENS) + '0';                     // calculate the value in the hundreth's
		UART_print(currentChar);
	}
}

void printFrequency(uint16_t frequency)
{
	if (frequency >= 1000)
		{
			uint8_t frequencyString[5];
			frequencyString[4] = '\0';
			frequencyString[0] = (frequency / 1000) + '0';		        // print the ones first
			frequencyString[1] = ((frequency / 100) % 10) + '0';
			frequencyString[2] = ((frequency / 10) % 10) + '0';		    // print the tenths second
			frequencyString[3] = ((frequency) % 10) + '0';				// print the hundreths value
			UART_print(frequencyString);
		}
		else if (frequency >= 100 && frequency < 1000)
		{
			uint8_t frequencyString[4];
			frequencyString[3] = '\0';
			frequencyString[0] = ((frequency / 100) % 10) + '0';		// print the ones first
			frequencyString[1] = ((frequency / 10) % 10) + '0';
			frequencyString[2] = (frequency % 10) + '0';		        // print the tenths second
			UART_print(frequencyString);
		}
		else if (frequency >= 10 && frequency < 100)
		{
			uint8_t frequencyString[3];
			frequencyString[2] = '\0';
			frequencyString[0] = ((frequency / 10) % 10) + '0';		    // print the ones first
			frequencyString[1] =  (frequency % 10) + '0';
			UART_print(frequencyString);
		}
		else
		{
			uint8_t frequencyString[2];
			frequencyString[1] = '\0';
			frequencyString[0] =  (frequency % 10) + '0';
			UART_print(frequencyString);
		}
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

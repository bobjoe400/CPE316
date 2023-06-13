
/* USER CODE BEGIN Header */
/**
******************************************************************************
* @file      : main.c
* @brief     : Main program body for Project 2 adopted from Assignment 7
* @authors    : Cooper Mattern and Nilay Patel
******************************************************************************
*/
/* USER CODE END Header */
#include "main.h"
#include "uart.h"
#include "util.h"
#include "adc.h"
#include "arm_math.h"
#define FFT_SIZE 2048
#define ADC_SAMPLE_RATE 2048
#define arr 15700
void SystemClock_Config(void);
void ADC_IRQHandler(void);

int main(void)
{
	// Initialization
	HAL_Init();
	SystemClock_Config();
	UART_init();
	ADC_init();

	// FFT related variables
	float32_t adcData[FFT_SIZE];
	float32_t fftOutput[FFT_SIZE];
	float32_t magnitude[(FFT_SIZE/2) - 2];
	uint32_t currentIndex = 0, maxMagnitudeIndex = 2;
	float32_t maxValue = 0;\

	float32_t frequency = 0;
	float32_t rms = 0;

	float32_t max = 0;
	float32_t min = 0;

	float32_t DC_volt = 0;
	float32_t p2p = 0;
	float32_t offset = 0;

	// FFT instance setup
	arm_rfft_fast_instance_f32	fftInstance;
	arm_rfft_fast_init_f32(&fftInstance, FFT_SIZE);

	// Timer setup
	RCC->APB1ENR1 	|= 	RCC_APB1ENR1_TIM2EN;		// turns on the clock
	TIM2->DIER		|=	TIM_DIER_UIE;				// enable update event flag
	TIM2->SR		&=	~(TIM_SR_UIF);				// clear update event flag
	TIM2->ARR		= 	arr - 1;					// configures the ARR for timer2
	TIM2->CR1		|=	(TIM_CR1_CEN);				// starts the timer2

	// NVIC setup
	NVIC->ISER[0] = (1 << (TIM2_IRQn & 0x1F));		// enable interrupt in NVIC for TIM2
	NVIC->ISER[0] |= (1 << (ADC1_2_IRQn & 0x1F));	// Enable interrupt in NVIC for ADC
	NVIC->ISER[0] |= (1 << (USART2_IRQn & 0x1F));	// Enable interrupt in NVIC for UART2

	__enable_irq();                                 // Enable interrupts globally

	UART_ESC_Code("[2J\0");
	UART_ESC_Code("[H\0");

	// Main loop
	while(1)
	{
		if(getADCRDY())											// when flag is set store value
		{

			adcData[currentIndex] = (float32_t) (getADCVal());	// store value based on index
			currentIndex++;										// increment index to avoid overwriting
			setADCRDY(0);										// clear the flag
			if (currentIndex == FFT_SIZE)
			{
				__disable_irq();
				max = findMax(adcData, FFT_SIZE);
				min = findMin(adcData, FFT_SIZE);
				DC_volt = findAvg(adcData, FFT_SIZE);

				p2p = max - min;
				offset = max - (p2p/2);

				arm_rms_f32(adcData, FFT_SIZE, &rms);										// get RMS of values
				arm_rfft_fast_f32(&fftInstance, adcData, fftOutput, 0); 					// execute real Fast Fourier Transform on ADC data
				arm_cmplx_mag_f32(&fftOutput[2], magnitude, (FFT_SIZE/2) - 2); 				// calculate magnitude of complex numbers
				arm_max_f32(magnitude, (FFT_SIZE / 2) - 2, &maxValue, &maxMagnitudeIndex); 	// get the maximum magnitude and its index

				frequency = maxMagnitudeIndex * (ADC_SAMPLE_RATE / FFT_SIZE); 				// convert FFT bin to frequency
				currentIndex = maxMagnitudeIndex = 0; 										// reset index, and maxIndex

				UART_ESC_Code("[2J\0");   					// Clear the screen and reset
				UART_ESC_Code("[0;0H\0");					// Cursor to upper left

				UART_printData(frequency, rms, p2p, offset, DC_volt);

				for (volatile uint32_t i = 0; i < 2000000; i++);
				__enable_irq();
			}
		}
	}
}

void ADC1_2_IRQHandler(void)
{
	if (ADC1->ISR & ADC_ISR_EOC)
	{
		setADCVal(ADC1->DR);				// Save the digital conversion to a global variable
		setADCRDY(1);						// Set the global flag
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM2->SR & TIM_SR_UIF){
	  ADC1->CR |= ADC_CR_ADSTART;		// Start the ADC conversion
	  TIM2->SR &= ~TIM_SR_UIF;	  		// clear the flag
	}
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	/** Configure the main internal regulator output voltage
	*/
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	{
	 Error_Handler();
	}
	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = 0;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_10;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	{
		Error_Handler();
	}
}
/* USER CODE BEGIN 4 */
/* USER CODE END 4 */
/**
 * @brief This function is executed in case of error occurrence.
* @retval None
*/
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{ }
	/* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
* @brief Reports the name of the source file and the source line number
		 where the assert_param error has occurred.
* @param file: pointer to the source file name
*
* @param line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t *file, uint32_t line)
{
/* USER CODE BEGIN 6 */
/* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

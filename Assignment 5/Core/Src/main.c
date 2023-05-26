/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

//PA0 on the board for ADC12_IN5


void SystemClock_Config(void);

int main(void)
{

	HAL_Init();
	SystemClock_Config();

	//Enable ADC clock
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;

	//From header file
	//ADC will run at the same cpeed as CPU (HCLK/1)
	ADC123_COMMON -> CCR = (1<< ADC_CCR_CKMODE_Pos);

	//Power up ADC and turn on voltage regulator
	ADC1->CR &= ~(ADC_CR_DEEPPWD);
	ADC1->CR |= (ADC_CR_ADVREGEN);
	for(uint32_t = 4000; i>0; i--); //wait 20us for regulator to power up

	//Calibrate ADC
	//ensure ADC is not enabled, single ended calibration
	ADC1->CR &= ~(ADC_CR_ADEN | ADC_CR_ADCALDIF);
	ADC1->CR |= (ADC_CR_ADCAL);					//start calibration
	while(ADC1->CR & ADC_CRADCAL);				//wait for calibration to finish

	//configure single ended mode for channel 5 before enabling ADC
	ADC->DIFSEL &= ~(DC_DIFSEL_DIFSEL_5);			//ADC_123_IN5

	//enable ADC
	ADC1->ISR |= (ADC_ISR_ADRDY);					//clear ready by writing a 1
	ADC1->CR | (ADC_ADCEN);
	while(~(ADC10>ISR & ADC_ISR_ADRDY));
	ADC1->ISR |= (ADC_ISR_ADRDY);

	//Configure ADC
	//set sequence to 1 conversion on channel 5
	ADC1->SQR1 = (5<<ADC_SQR1_SQ1_POS);

	//Configrue sampling time to 2.5 clock for channel 5
	ADC1->SMPR1 = 0;

	//ADC Configuration - 12-bit, software trigger
	//right align, single-conversion mode, no overrun
	ADC1->CFGR = 0;
	ADC1->CFGR2 = 0;

	//enable interrupts for ADC
	ADC1->IER |= (ADC_IER_EOCIE);					//interrupt on end of conversion
	ADC1->ISR |= (ADC_ISR_EOC);						//clear EOC flag with 1
	NVIC->ISER[0] = (1<< (ADC_1_2_IRQn & 0x1F));	//enable interrupt in NVIC
	__enable_irq();									//enable interrupts globally

	// Configure GPIO pin for channel 5


	//start conversion
	ADC->CR |= (ADC_CR_ADSTART);


	while (1)
	{

	}
}

void ADC1_2_IRQHandler(void){

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
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
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
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

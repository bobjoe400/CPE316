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
#include "dac.h"
#include "keypad.h"
#include "func_gen.h"


void SystemClock_Config(void);

uint32_t lut_ind = 0;
uint32_t lut_ind_inc_val = 3;
uint32_t val_to_write = 0;

int main(void)
  {
  HAL_Init();
  SystemClock_Config();
  DAC_init();
  // Setup GPIOC as Output
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
  GPIOC->MODER &= ~(GPIO_MODER_MODE0);
  GPIOC->MODER |= (GPIO_MODER_MODE0_0);
  GPIOC->ODR = 0;
  // PA8 Clock Signal
  // Enable MCO, select MSI (4 MHz source)
  RCC->CFGR = ((RCC->CFGR & ~(RCC_CFGR_MCOSEL)) | (RCC_CFGR_MCOSEL_0));
  // Configure MCO output on PA8
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN);
  GPIOA->MODER &= ~(GPIO_MODER_MODE8); // alternate function mode
  GPIOA->MODER |= (2 << GPIO_MODER_MODE8_Pos);
  GPIOA->OTYPER &= ~(GPIO_OTYPER_OT8); // Push-pull output
  GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD8); // no resistor
  GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED8); // high speed
  GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL8); // select MCO function
  // Enable RCC
  RCC->APB1ENR1 |= (RCC_APB1ENR1_TIM2EN);
  // Enable Timer Interrupt and CC1 Interrupt
  TIM2->DIER |= ( TIM_DIER_CC1IE);
  // Clear Timer and CC1 Interrupt Flag
  TIM2->SR &= ~( TIM_SR_CC1IF);
  // Set ARR to 5khz Period
  TIM2->ARR = 0xFFFFFFFF;
  // Set CCR to 1/4 of that period
  TIM2->CCR1 = 107-1;
  // Start Couting
  TIM2->CR1 |= (TIM_CR1_CEN);
  /* USER CODE END 2 */
  // Enable All Interrupts
  NVIC->ISER[0] = (1 << (TIM2_IRQn & 0x1F));
  __enable_irq();
  while (1)
  {
	  if(lut_ind > NUM_SAMPLES){
		  lut_ind = 0;
	  }
	  val_to_write = TRI_LUT[lut_ind];
  }
}
void TIM2_IRQHandler (void)
{
	GPIOC->ODR = 1;
	// Clear Interrupt Flag
	TIM2->SR &= ~(TIM_SR_CC1IF);
	TIM2->CCR1 += 107;
	//Move CCR1 Timer Forwards
	DAC_write(val_to_write);
	lut_ind+= lut_ind_inc_val;
	GPIOC->ODR = 0;

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
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

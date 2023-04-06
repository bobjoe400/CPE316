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

#include <stdint.h>
#include <string.h>
#include "main.h"

#define COUNT_MAX 16
#define NUM_LEDS 4
#define WAIT_TIME 100000

enum MODER_MASK_ENUM{ LED_0_MOD_MASK = GPIO_MODER_MODE0, LED_1_MOD_MASK = GPIO_MODER_MODE1,
					  LED_2_MOD_MASK = GPIO_MODER_MODE2, LED_3_MOD_MASK = GPIO_MODER_MODE3};
enum MODER_SET_ENUM{ LED_0_MOD_SET = GPIO_MODER_MODE0_0, LED_1_MOD_SET = GPIO_MODER_MODE1_0,
	  	  	  	  	 LED_2_MOD_SET = GPIO_MODER_MODE2_0, LED_3_MOD_SET = GPIO_MODER_MODE3_0};
enum OTYPER_ENUM{ LED_0_OT_SET = GPIO_OTYPER_OT0, LED_1_OT_SET = GPIO_OTYPER_OT1,
				  LED_2_OT_SET = GPIO_OTYPER_OT2, LED_3_OT_SET = GPIO_OTYPER_OT3};
enum OSPEEDR_ENUM{ LED_0_SPR_SET = GPIO_OSPEEDR_OSPEED0, LED_1_SPR_SET = GPIO_OSPEEDR_OSPEED1,
				   LED_2_SPR_SET = GPIO_OSPEEDR_OSPEED2, LED_3_SPR_SET = GPIO_OSPEEDR_OSPEED3};
enum PUPDR_MASK_ENUM{ LED_0_PUPD_MASK = GPIO_PUPDR_PUPD0, LED_1_PUPD_MASK = GPIO_PUPDR_PUPD1,
				 	  LED_2_PUPD_MASK = GPIO_PUPDR_PUPD2, LED_3_PUPD_MASK = GPIO_PUPDR_PUPD3};
enum PUPDR_SET_ENUM{ LED_0_PUPD_SET = GPIO_PUPDR_PUPD0_1, LED_1_PUPD_SET = GPIO_PUPDR_PUPD1_1,
	  	  	  	  	 LED_2_PUPD_SET = GPIO_PUPDR_PUPD2_1, LED_3_PUPD_SET = GPIO_PUPDR_PUPD3_1};
enum ODR_ENUM{ LED_0_ODR_SET = GPIO_ODR_OD0, LED_1_ODR_SET = GPIO_ODR_OD1,
			   LED_2_ODR_SET = GPIO_ODR_OD2, LED_3_ODR_SET = GPIO_ODR_OD3};

uint32_t SETUP_PINS_POS[4][6] = {
		{LED_0_MOD_MASK, LED_0_MOD_SET, LED_0_OT_SET, LED_0_SPR_SET, LED_0_PUPD_MASK, LED_0_PUPD_SET},
		{LED_1_MOD_MASK, LED_1_MOD_SET, LED_1_OT_SET, LED_1_SPR_SET, LED_1_PUPD_MASK, LED_1_PUPD_SET},
		{LED_2_MOD_MASK, LED_2_MOD_SET, LED_2_OT_SET, LED_2_SPR_SET, LED_2_PUPD_MASK, LED_2_PUPD_SET},
		{LED_3_MOD_MASK, LED_3_MOD_SET, LED_3_OT_SET, LED_3_SPR_SET, LED_3_PUPD_MASK, LED_3_PUPD_SET}
};

uint16_t ODR_ITR[4] = { LED_0_ODR_SET, LED_1_ODR_SET, LED_2_ODR_SET, LED_3_ODR_SET};

typedef union vec3_u{
	struct{
		uint32_t MODER_MASK, MODER_SET, OTYPER_SET, OSPEEDR_SET, PUPDR_MASK, PUPDR_SET;
	}vec3_s;
	uint32_t vec3_a[6];
}SetupData;

void Pin_Config();
void Num_to_Bits(uint8_t, uint8_t[]);
void Set_LEDs(uint8_t[]);
void SystemClock_Config(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  Pin_Config();

  RCC->CR |= RCC_MSION;

  uint8_t counter = 0;
  uint8_t leds_on[NUM_LEDS] = {0};
  while (1)
  {
	  Num_to_Bits(counter, leds_on);
	  Set_LEDs(leds_on);
	  counter++;
	  if(counter== COUNT_MAX){
		  counter = 0;
	  }
  }
}

void Pin_Config(){
	SetupData GPIO_C;
	memset(&GPIO_C, 0, sizeof(SetupData));

	for(int led_num = 0; led_num< NUM_LEDS; led_num++){
	  for(int setup_field = 0; setup_field <6; setup_field++){
		  GPIO_C.vec3_a[setup_field] += SETUP_PINS_POS[led_num][setup_field];
	  }
	}

	GPIOC->MODER &= GPIO_C.vec3_s.MODER_MASK;
	GPIOC->MODER |= GPIO_C.vec3_s.MODER_SET;
	GPIOC->OTYPER |= GPIO_C.vec3_s.OTYPER_SET;
	GPIOC->OSPEEDR |= GPIO_C.vec3_s.OSPEEDR_SET;
	GPIOC->PUPDR &= ~(GPIO_C.vec3_s.PUPDR_MASK);
	GPIOC->PUPDR |= GPIO_C.vec3_s.PUPDR_SET;
}

void Num_to_Bits(uint8_t num, uint8_t num_arr[]){
	for(int i = 0; i < NUM_LEDS; i++){
		num_arr[i] = (num>>i) & 0x1;
	}
}

void Set_LEDs(uint8_t led_arr[]){
	uint32_t ODR = 0;
	for(int i = 0; i< NUM_LEDS; i++){
		ODR += led_arr[i] & ODR_ITR[i];
	}
	GPIOC->ODR = ODR;
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

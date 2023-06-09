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

#include "LCD16x2/LCD16x2.h"
#include "UART.h"
#include "util.h"
#include "ftoa.h"
#include "calculator.h"

#include <string.h>
#include <math.h>
#include <stdint.h>

enum PRINT_LENGTHS {SQRT = 5, SIN  = 4, COS = 4, TAN = 4, LOG = 4, LN = 3, EPOW = 2, POW = 1};									// Length to printed to LCD
enum MIN_ARG_LEN {SQRT_LEN = 2, SIN_LEN = 2, COS_LEN  = 2, TAN_LEN = 2, LOG_LEN = 2, LN_LEN = 2, EPOW_LEN = 1, POW_LEN = 1};	// Arg Length Needed to Avoid Errors

char print_buff[CHAR_BUFF_SIZE];

/* -----------------UART Stuff---------------- */

#define CR 0x0d

char data = 0;
char dataBuf[2];

/* ------------------------------------------- */

/* -----------------Input Processing----------- */
char num_buff[CHAR_BUFF_SIZE];						// Store individual numbers
char input_buff[CHAR_BUFF_SIZE][CHAR_BUFF_SIZE];	// Store Entire Numbers and Function Keys in Separate Lists


#define PI 0xF7

uint8_t PROCESS_FLAG = 0;
uint8_t PROCESSED_FLAG = 0;

uint8_t num_disp = 0;				// Initialize to 0
uint8_t input_buff_index = 0;		// Initialize to 0
uint8_t num_buff_index = 0;			// Initialize to 0

/*---------------------------------------------*/

void SystemClock_Config(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    LCD_Init();
    LCD_Clear();
    LCD_Set_Cursor(1,1);
    LCD_CMD(0x0);			// Write 0x0 to access lower bits
    LCD_CMD(0xf);			// Blinking Cursor

	/* Initialize All Buffers to 0 */
    memset(print_buff, 0, CHAR_BUFF_SIZE * sizeof(char));
    memset(input_buff, 0, (CHAR_BUFF_SIZE*CHAR_BUFF_SIZE) * sizeof(char));
    memset(num_buff, 0, (CHAR_BUFF_SIZE) * sizeof(char));

    UART_init();

    while (1)
    {
    	if(PROCESS_FLAG){
    		__disable_irq();

    		PROCESS_FLAG = 0;

    		float answer;
    		if((answer = expEval(input_buff, input_buff_index)) != NAN){
    			ftoa(answer, print_buff, 3);
    		}else{
    			strcpy(print_buff, "ERROR");
    		}

    		LCD_Clear_Line(2, MAX_DISP);
			LCD_Write_String(print_buff);

			memset(print_buff, 0, CHAR_BUFF_SIZE * sizeof(char));

    		PROCESSED_FLAG = 1;

    		__enable_irq();
    	}
    }
}

/* Handles LCD writing for functions
 * Author: Cooper Mattern
 * */
void validateComplex(char data, char* str, int str_len, int min_arg_len){
	if((num_disp + str_len + min_arg_len) < MAX_DISP){	// If function can be printed to LCD successfully
		input_buff[input_buff_index++][0] = data;		// Write function char to input_buf
		if(data != 'e'){								// Exponent handling
			input_buff[input_buff_index++][0] = '(';
		}
		LCD_Write_String(str);							// Write function str to LCD
		num_disp+=str_len;
	}
}

//written by Cooper Mattern
void USART2_IRQHandler(void){
	if(USART2->ISR & USART_ISR_RXNE){

		if(PROCESSED_FLAG){

			PROCESSED_FLAG = 0;				// Clear Flag

			LCD_Clear_Line(1, MAX_DISP);	// Clear 1st Line on LCD

			num_disp = 0;

			input_buff_index = 0;
			memset(input_buff, 0, (CHAR_BUFF_SIZE * CHAR_BUFF_SIZE) * sizeof(char));	// Set Input Buffer to all 0's

			num_buff_index = 0;
			memset(num_buff, 0, CHAR_BUFF_SIZE * sizeof(char)); // Set Num Buffer to all 0's
		}

		data = USART2->RDR;

		/* If we are not at end of LCD screen */

		if (data == CR){				// If ENTER is hit, begin processing
			if(num_buff_index != 0){
				memcpy(input_buff[input_buff_index++], num_buff, num_buff_index);	// Copy num_buf into input_buf
				num_buff_index = 0;
				memset(num_buff, 0, CHAR_BUFF_SIZE*sizeof(char));					// Clear num_buf
			}
			PROCESS_FLAG = 1;
		}else if(num_disp < MAX_DISP){
			if((('0' <= data) &&  (data <= '9')) || data == '.'){	// If data input is 0-9
				num_buff[num_buff_index++] = data;	// Write to Num Buffer
				LCD_Write_Char(data);				// Write to LCD
				num_disp++;							// Move to next column
			}else if(strchr(valid_input, data) != NULL){								// Non-Number key
				if(num_buff_index != 0){
					memcpy(input_buff[input_buff_index++], num_buff, num_buff_index);	// Copy num_buf into input_buf
					num_buff_index = 0;
					memset(num_buff, 0, CHAR_BUFF_SIZE*sizeof(char));				    // Clear num_buf
				}

				/* Buffer/LCD Handling */
				switch(data){
				case 'p':
					input_buff[input_buff_index++][0] = 'p';
					LCD_Write_Char(PI);
					num_disp++;
					break;
				case 'q':	// square root
					validateComplex(data, "sqrt(", SQRT, SQRT);
					break;
				case 's':	// sin
					validateComplex(data, "sin(", SIN, SIN);
					break;
				case 'c':	// cos
					validateComplex(data, "cos(", COS, COS);
					break;
				case 't':	// tan
					validateComplex(data, "tan(", TAN, TAN);
					break;
				case 'l':	// log
					validateComplex(data, "log(", LOG, LOG);
					break;
				case 'n':	// ln
					validateComplex(data, "ln(", LN, LN);
					break;
				case 'e':	// e^x
					validateComplex(data, "e^", EPOW, EPOW);
					break;
				case ',':
					LCD_Write_Char(data);						// Write , to LCD
					num_disp++;
					break;
				default:
					input_buff[input_buff_index++][0] = data;
					LCD_Write_Char(data);
					num_disp++;
					break;
				}
			}
		}

		/* Debugging */
		memcpy(dataBuf, &data, sizeof(unsigned char));
		memcpy(dataBuf + 1, "\0", sizeof(unsigned char));
		UART_print(dataBuf);
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
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 36;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
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

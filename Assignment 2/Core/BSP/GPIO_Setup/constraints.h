/*
 * contraints.h
 *
 *  Created on: Apr 5, 2023
 *      Author: Cooper Floyd Mattern
 */

#ifndef GPIO_SETUP_CONSTRAINTS_H_
#define GPIO_SETUP_CONSTRAINTS_H_

#include "stm32l4xx_hal.h"

#define FIELD_TOTAL 8
#define PIN_TOTAL 16
#define NUM_GPIO 3
#define GPIO_NUM_PINS(x) (sizeof(x)/sizeof(x[0]))

/*---------------------------------------------------GPIO A----------------------------------------------------------*/

/*
 * UNCOMMENT LINES TO ENABLE PIN
 * SET TO 0x01 IF PIN WILL BE SET HIGH ON INITIALIZATION, OTHERWISE 0x00
 */
uint8_t GPIOA_PIN_HILO_ENABLE[] = {
//	/*PIN 0*/			0x00,
//	/*PIN 1*/			0x00,
//	/*PIN 2*/			0x00,
//	/*PIN 3*/			0x00,
//	/*PIN 4*/			0x00,
//	/*PIN 5*/			0x00,
//	/*PIN 6*/			0x00,
//	/*PIN 7*/			0x00,
//	/*PIN 8*/			0x00,
//	/*PIN 9*/			0x00,
//	/*PIN 10*/			0x00,
//	/*PIN 11*/			0x00,
//	/*PIN 12*/			0x00,
//	/*PIN 13*/			0x00,
//	/*PIN 14*/			0x00,
//	/*PIN 15*/			0x00
};

#define GPIOA_NUM_PINS GPIO_NUM_PINS(GPIOA_PIN_HILO_ENABLE)

/*
 * USE THIS SECTION TO EDIT THE VALUES THAT WILL BE SET BY THE DRIVER UPON PORT ENABLE
 */
enum GPOIA_ENUM	{
						/*-----------------------PIN 0--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_0_MOD_MASK 	=	GPIO_MODER_MODE0,
								GPIOA_0_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED0,
								GPIOA_0_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED0,

								/*---------------SET BITS-------------------*/
								GPIOA_0_MOD_SET 	= 	GPIO_MODER_MODE0_0,
								GPIOA_0_OT_SET 		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_0_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_0_PUPD_SET	= 	GPIO_PUPDR_PUPD0_1,
								GPIOA_0_ODR_SET 	= 	GPIO_ODR_OD0,

						/*-----------------------PIN 1--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_1_MOD_MASK 	= 	GPIO_MODER_MODE1,
								GPIOA_1_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED1,
								GPIOA_1_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED1,

								/*---------------SET BITS-------------------*/
								GPIOA_1_MOD_SET 	= 	GPIO_MODER_MODE1_0,
								GPIOA_1_OT_SET 		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_1_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_1_PUPD_SET 	= 	GPIO_PUPDR_PUPD1_1,
								GPIOA_1_ODR_SET 	= 	GPIO_ODR_OD1,

						/*-----------------------PIN 2--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_2_MOD_MASK 	= 	GPIO_MODER_MODE2,
								GPIOA_2_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED2,
								GPIOA_2_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED2,

								/*---------------SET BITS-------------------*/
								GPIOA_2_MOD_SET 	= 	GPIO_MODER_MODE2_0,
								GPIOA_2_OT_SET	 	= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_2_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_2_PUPD_SET 	= 	GPIO_PUPDR_PUPD2_1,
								GPIOA_2_ODR_SET 	= 	GPIO_ODR_OD2,

						/*-----------------------PIN 3--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_3_MOD_MASK	= 	GPIO_MODER_MODE3,
								GPIOA_3_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED3,
								GPIOA_3_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED3,

								/*---------------SET BITS-------------------*/
								GPIOA_3_MOD_SET 	= 	GPIO_MODER_MODE3_0,
								GPIOA_3_OT_SET	 	= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_3_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_3_PUPD_SET	= 	GPIO_PUPDR_PUPD3_1,
								GPIOA_3_ODR_SET 	= 	GPIO_ODR_OD3,

						/*-----------------------PIN 4--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_4_MOD_MASK	= 	GPIO_MODER_MODE4,
								GPIOA_4_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED4,
								GPIOA_4_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED4,

								/*---------------SET BITS-------------------*/
								GPIOA_4_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOA_4_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_4_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_4_PUPD_SET	= 	GPIO_PUPDR_PUPD4_1,
								GPIOA_4_ODR_SET		= 	GPIO_ODR_OD4,

						/*-----------------------PIN 5--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_5_MOD_MASK	= 	GPIO_MODER_MODE5,
								GPIOA_5_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED5,
								GPIOA_5_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED5,

								/*---------------SET BITS-------------------*/
								GPIOA_5_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOA_5_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_5_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_5_PUPD_SET	= 	GPIO_PUPDR_PUPD5_1,
								GPIOA_5_ODR_SET		= 	GPIO_ODR_OD5,

						/*-----------------------PIN 6--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_6_MOD_MASK	= 	GPIO_MODER_MODE6,
								GPIOA_6_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED6,
								GPIOA_6_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED6,

								/*---------------SET BITS-------------------*/
								GPIOA_6_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOA_6_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_6_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_6_PUPD_SET	= 	GPIO_PUPDR_PUPD6_1,
								GPIOA_6_ODR_SET		= 	GPIO_ODR_OD6,

						/*-----------------------PIN 7--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_7_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED7,
								GPIOA_7_MOD_MASK	= 	GPIO_MODER_MODE7,
								GPIOA_7_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED7,

								/*---------------SET BITS-------------------*/
								GPIOA_7_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOA_7_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_7_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_7_PUPD_SET	= 	GPIO_PUPDR_PUPD7_1,
								GPIOA_7_ODR_SET		= 	GPIO_ODR_OD7,

						/*-----------------------PIN 8--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_8_MOD_MASK	= 	GPIO_MODER_MODE8,
								GPIOA_8_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED8,
								GPIOA_8_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED8,

								/*---------------SET BITS-------------------*/
								GPIOA_8_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOA_8_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_8_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_8_PUPD_SET	= 	GPIO_PUPDR_PUPD8_1,
								GPIOA_8_ODR_SET		= 	GPIO_ODR_OD8,

						/*-----------------------PIN 9--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_9_MOD_MASK	= 	GPIO_MODER_MODE9,
								GPIOA_9_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED9,
								GPIOA_9_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED9,

								/*---------------SET BITS-------------------*/
								GPIOA_9_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOA_9_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_9_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_9_PUPD_SET	= 	GPIO_PUPDR_PUPD9_1,
								GPIOA_9_ODR_SET		= 	GPIO_ODR_OD9,

						/*-----------------------PIN 10-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_10_MOD_MASK	= 	GPIO_MODER_MODE10,
								GPIOA_10_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED10,
								GPIOA_10_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED10,

								/*---------------SET BITS-------------------*/
								GPIOA_10_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOA_10_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_10_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_10_PUPD_SET	= 	GPIO_PUPDR_PUPD10_1,
								GPIOA_10_ODR_SET	= 	GPIO_ODR_OD10,

						/*-----------------------PIN 11-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_11_MOD_MASK	= 	GPIO_MODER_MODE11,
								GPIOA_11_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED11,
								GPIOA_11_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED11,

								/*---------------SET BITS-------------------*/
								GPIOA_11_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOA_11_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_11_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_11_PUPD_SET	= 	GPIO_PUPDR_PUPD11_1,
								GPIOA_11_ODR_SET	= 	GPIO_ODR_OD11,

						/*-----------------------PIN 12-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_12_MOD_MASK	= 	GPIO_MODER_MODE12,
								GPIOA_12_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED12,
								GPIOA_12_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED12,

								/*---------------SET BITS-------------------*/
								GPIOA_12_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOA_12_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_12_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_12_PUPD_SET	= 	GPIO_PUPDR_PUPD12_1,
								GPIOA_12_ODR_SET	= 	GPIO_ODR_OD12,

						/*-----------------------PIN 13-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_13_MOD_MASK	= 	GPIO_MODER_MODE13,
								GPIOA_13_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED13,
								GPIOA_13_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED13,

								/*---------------SET BITS-------------------*/
								GPIOA_13_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOA_13_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_13_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_13_PUPD_SET	= 	GPIO_PUPDR_PUPD13_1,
								GPIOA_13_ODR_SET	= 	GPIO_ODR_OD13,

						/*-----------------------PIN 14-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_14_MOD_MASK	= 	GPIO_MODER_MODE14,
								GPIOA_14_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED14,
								GPIOA_14_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED14,

								/*---------------SET BITS-------------------*/
								GPIOA_14_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOA_14_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_14_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_14_PUPD_SET	= 	GPIO_PUPDR_PUPD14_1,
								GPIOA_14_ODR_SET	= 	GPIO_ODR_OD14,

						/*-----------------------PIN 15-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOA_15_MOD_MASK	= 	GPIO_MODER_MODE15,
								GPIOA_15_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED15,
								GPIOA_15_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED15,

								/*---------------SET BITS-------------------*/
								GPIOA_15_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOA_15_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOA_15_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOA_15_PUPD_SET	= 	GPIO_PUPDR_PUPD15_1,
								GPIOA_15_ODR_SET	= 	GPIO_ODR_OD15
};

/*---------------------------------------------------GPIO B----------------------------------------------------------*/

/*
 * UNCOMMENT LINES TO ENABLE PIN
 * SET TO 0x01 IF PIN WILL BE SET HIGH ON INITIALIZATION, OTHERWISE 0x00
 */
uint8_t GPIOB_PIN_HILO_ENABLE[] = {
	/*PIN 0*/			0x01,
	/*PIN 1*/			0x01,
	/*PIN 2*/			0x01,
	/*PIN 3*/			0x01,
//	/*PIN 4*/			0x00,
//	/*PIN 5*/			0x00,
//	/*PIN 6*/			0x00,
//	/*PIN 7*/			0x00,
//	/*PIN 8*/			0x00,
//	/*PIN 9*/			0x00,
//	/*PIN 10*/			0x00,
//	/*PIN 11*/			0x00,
//	/*PIN 12*/			0x00,
//	/*PIN 13*/			0x00,
//	/*PIN 14*/			0x00,
//	/*PIN 15*/			0x00
};

#define GPIOB_NUM_PINS GPIO_NUM_PINS(GPIOB_PIN_HILO_ENABLE)

/*
 * USE THIS SECTION TO EDIT THE VALUES THAT WILL BE SET BY THE DRIVER UPON PORT ENABLE
 */
enum GPIOB_ENUM	{
						/*-----------------------PIN 0--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_0_MOD_MASK 	=	GPIO_MODER_MODE0,
								GPIOB_0_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED0,
								GPIOB_0_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED0,

								/*---------------SET BITS-------------------*/
								GPIOB_0_MOD_SET 	= 	GPIO_MODER_MODE0_0,
								GPIOB_0_OT_SET 		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_0_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_0_PUPD_SET	= 	GPIO_PUPDR_PUPD0_Pos,
								GPIOB_0_ODR_SET 	= 	GPIO_ODR_OD0,

						/*-----------------------PIN 1--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_1_MOD_MASK 	= 	GPIO_MODER_MODE1,
								GPIOB_1_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED1,
								GPIOB_1_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED1,

								/*---------------SET BITS-------------------*/
								GPIOB_1_MOD_SET 	= 	GPIO_MODER_MODE1_0,
								GPIOB_1_OT_SET 		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_1_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_1_PUPD_SET 	= 	GPIO_PUPDR_PUPD0_Pos,
								GPIOB_1_ODR_SET 	= 	GPIO_ODR_OD1,

						/*-----------------------PIN 2--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_2_MOD_MASK 	= 	GPIO_MODER_MODE2,
								GPIOB_2_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED2,
								GPIOB_2_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED2,

								/*---------------SET BITS-------------------*/
								GPIOB_2_MOD_SET 	= 	GPIO_MODER_MODE2_0,
								GPIOB_2_OT_SET	 	= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_2_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_2_PUPD_SET 	= 	GPIO_PUPDR_PUPD0_Pos,
								GPIOB_2_ODR_SET 	= 	GPIO_ODR_OD2,

						/*-----------------------PIN 3--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_3_MOD_MASK	= 	GPIO_MODER_MODE3,
								GPIOB_3_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED3,
								GPIOB_3_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED3,

								/*---------------SET BITS-------------------*/
								GPIOB_3_MOD_SET 	= 	GPIO_MODER_MODE3_0,
								GPIOB_3_OT_SET	 	= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_3_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_3_PUPD_SET	= 	GPIO_PUPDR_PUPD0_Pos,
								GPIOB_3_ODR_SET 	= 	GPIO_ODR_OD3,

						/*-----------------------PIN 4--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_4_MOD_MASK	= 	GPIO_MODER_MODE4,
								GPIOB_4_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED4,
								GPIOB_4_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED4,

								/*---------------SET BITS-------------------*/
								GPIOB_4_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOB_4_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_4_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_4_PUPD_SET	= 	GPIO_PUPDR_PUPD4_1,
								GPIOB_4_ODR_SET		= 	GPIO_ODR_OD4,

						/*-----------------------PIN 5--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_5_MOD_MASK	= 	GPIO_MODER_MODE5,
								GPIOB_5_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED5,
								GPIOB_5_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED5,

								/*---------------SET BITS-------------------*/
								GPIOB_5_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOB_5_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_5_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_5_PUPD_SET	= 	GPIO_PUPDR_PUPD5_1,
								GPIOB_5_ODR_SET		= 	GPIO_ODR_OD5,

						/*-----------------------PIN 6--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_6_MOD_MASK	= 	GPIO_MODER_MODE6,
								GPIOB_6_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED6,
								GPIOB_6_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED6,

								/*---------------SET BITS-------------------*/
								GPIOB_6_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOB_6_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_6_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_6_PUPD_SET	= 	GPIO_PUPDR_PUPD6_1,
								GPIOB_6_ODR_SET		= 	GPIO_ODR_OD6,

						/*-----------------------PIN 7--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_7_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED7,
								GPIOB_7_MOD_MASK	= 	GPIO_MODER_MODE7,
								GPIOB_7_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED7,

								/*---------------SET BITS-------------------*/
								GPIOB_7_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOB_7_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_7_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_7_PUPD_SET	= 	GPIO_PUPDR_PUPD7_1,
								GPIOB_7_ODR_SET		= 	GPIO_ODR_OD7,

						/*-----------------------PIN 8--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_8_MOD_MASK	= 	GPIO_MODER_MODE8,
								GPIOB_8_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED8,
								GPIOB_8_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED8,

								/*---------------SET BITS-------------------*/
								GPIOB_8_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOB_8_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_8_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_8_PUPD_SET	= 	GPIO_PUPDR_PUPD8_1,
								GPIOB_8_ODR_SET		= 	GPIO_ODR_OD8,

						/*-----------------------PIN 9--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_9_MOD_MASK	= 	GPIO_MODER_MODE9,
								GPIOB_9_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED9,
								GPIOB_9_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED9,

								/*---------------SET BITS-------------------*/
								GPIOB_9_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOB_9_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_9_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_9_PUPD_SET	= 	GPIO_PUPDR_PUPD9_1,
								GPIOB_9_ODR_SET		= 	GPIO_ODR_OD9,

						/*-----------------------PIN 10-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_10_MOD_MASK	= 	GPIO_MODER_MODE10,
								GPIOB_10_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED10,
								GPIOB_10_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED10,

								/*---------------SET BITS-------------------*/
								GPIOB_10_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOB_10_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_10_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_10_PUPD_SET	= 	GPIO_PUPDR_PUPD10_1,
								GPIOB_10_ODR_SET	= 	GPIO_ODR_OD10,

						/*-----------------------PIN 11-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_11_MOD_MASK	= 	GPIO_MODER_MODE11,
								GPIOB_11_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED11,
								GPIOB_11_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED11,

								/*---------------SET BITS-------------------*/
								GPIOB_11_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOB_11_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_11_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_11_PUPD_SET	= 	GPIO_PUPDR_PUPD11_1,
								GPIOB_11_ODR_SET	= 	GPIO_ODR_OD11,

						/*-----------------------PIN 12-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_12_MOD_MASK	= 	GPIO_MODER_MODE12,
								GPIOB_12_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED12,
								GPIOB_12_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED12,

								/*---------------SET BITS-------------------*/
								GPIOB_12_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOB_12_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_12_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_12_PUPD_SET	= 	GPIO_PUPDR_PUPD12_1,
								GPIOB_12_ODR_SET	= 	GPIO_ODR_OD12,

						/*-----------------------PIN 13-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_13_MOD_MASK	= 	GPIO_MODER_MODE13,
								GPIOB_13_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED13,
								GPIOB_13_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED13,

								/*---------------SET BITS-------------------*/
								GPIOB_13_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOB_13_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_13_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_13_PUPD_SET	= 	GPIO_PUPDR_PUPD13_1,
								GPIOB_13_ODR_SET	= 	GPIO_ODR_OD13,

						/*-----------------------PIN 14-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_14_MOD_MASK	= 	GPIO_MODER_MODE14,
								GPIOB_14_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED14,
								GPIOB_14_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED14,

								/*---------------SET BITS-------------------*/
								GPIOB_14_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOB_14_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_14_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_14_PUPD_SET	= 	GPIO_PUPDR_PUPD14_1,
								GPIOB_14_ODR_SET	= 	GPIO_ODR_OD14,

						/*-----------------------PIN 15-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOB_15_MOD_MASK	= 	GPIO_MODER_MODE15,
								GPIOB_15_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED15,
								GPIOB_15_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED15,

								/*---------------SET BITS-------------------*/
								GPIOB_15_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOB_15_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOB_15_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOB_15_PUPD_SET	= 	GPIO_PUPDR_PUPD15_1,
								GPIOB_15_ODR_SET	= 	GPIO_ODR_OD15
};

/*---------------------------------------------------GPIO C----------------------------------------------------------*/

/*
 * UNCOMMENT LINES TO ENABLE PIN
 * SET TO 0x01 IF PIN WILL BE SET HIGH ON INITIALIZATION, OTHERWISE 0x00
 */
uint8_t GPIOC_PIN_HILO_ENABLE[] = {
	/*PIN 0*/			0x00,
	/*PIN 1*/			0x00,
	/*PIN 2*/			0x00,
	/*PIN 3*/			0x00,
//	/*PIN 4*/			0x00,
//	/*PIN 5*/			0x00,
//	/*PIN 6*/			0x00,
//	/*PIN 7*/			0x00,
//	/*PIN 8*/			0x00,
//	/*PIN 9*/			0x00,
//	/*PIN 10*/			0x00,
//	/*PIN 11*/			0x00,
//	/*PIN 12*/			0x00,
//	/*PIN 13*/			0x00,
//	/*PIN 14*/			0x00,
//	/*PIN 15*/			0x00
};

#define GPIOC_NUM_PINS GPIO_NUM_PINS(GPIOC_PIN_HILO_ENABLE)

/*
 * USE THIS SECTION TO EDIT THE VALUES THAT WILL BE SET BY THE DRIVER UPON PORT ENABLE
 */
enum GPIOC_ENUM	{
						/*-----------------------PIN 0--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_0_MOD_MASK 	=	GPIO_MODER_MODE0,
								GPIOC_0_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED0,
								GPIOC_0_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED0,

								/*---------------SET BITS-------------------*/
								GPIOC_0_MOD_SET 	= 	GPIO_MODER_MODE0_Pos,
								GPIOC_0_OT_SET 		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_0_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_0_PUPD_SET	= 	GPIO_PUPDR_PUPD0_1,
								GPIOC_0_ODR_SET 	= 	GPIO_ODR_OD0,

						/*-----------------------PIN 1--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_1_MOD_MASK 	= 	GPIO_MODER_MODE1,
								GPIOC_1_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED1,
								GPIOC_1_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED1,

								/*---------------SET BITS-------------------*/
								GPIOC_1_MOD_SET 	= 	GPIO_MODER_MODE0_Pos,
								GPIOC_1_OT_SET 		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_1_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_1_PUPD_SET 	= 	GPIO_PUPDR_PUPD1_1,
								GPIOC_1_ODR_SET 	= 	GPIO_ODR_OD1,

						/*-----------------------PIN 2--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_2_MOD_MASK 	= 	GPIO_MODER_MODE2,
								GPIOC_2_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED2,
								GPIOC_2_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED2,

								/*---------------SET BITS-------------------*/
								GPIOC_2_MOD_SET 	= 	GPIO_MODER_MODE0_Pos,
								GPIOC_2_OT_SET	 	= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_2_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_2_PUPD_SET 	= 	GPIO_PUPDR_PUPD2_1,
								GPIOC_2_ODR_SET 	= 	GPIO_ODR_OD2,

						/*-----------------------PIN 3--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_3_MOD_MASK	= 	GPIO_MODER_MODE3,
								GPIOC_3_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED3,
								GPIOC_3_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED3,

								/*---------------SET BITS-------------------*/
								GPIOC_3_MOD_SET 	= 	GPIO_MODER_MODE0_Pos,
								GPIOC_3_OT_SET	 	= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_3_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_3_PUPD_SET	= 	GPIO_PUPDR_PUPD3_1,
								GPIOC_3_ODR_SET 	= 	GPIO_ODR_OD3,

						/*-----------------------PIN 4--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_4_MOD_MASK	= 	GPIO_MODER_MODE4,
								GPIOC_4_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED4,
								GPIOC_4_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED4,

								/*---------------SET BITS-------------------*/
								GPIOC_4_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOC_4_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_4_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_4_PUPD_SET	= 	GPIO_PUPDR_PUPD4_1,
								GPIOC_4_ODR_SET		= 	GPIO_ODR_OD4,

						/*-----------------------PIN 5--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_5_MOD_MASK	= 	GPIO_MODER_MODE5,
								GPIOC_5_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED5,
								GPIOC_5_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED5,

								/*---------------SET BITS-------------------*/
								GPIOC_5_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOC_5_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_5_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_5_PUPD_SET	= 	GPIO_PUPDR_PUPD5_1,
								GPIOC_5_ODR_SET		= 	GPIO_ODR_OD5,

						/*-----------------------PIN 6--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_6_MOD_MASK	= 	GPIO_MODER_MODE6,
								GPIOC_6_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED6,
								GPIOC_6_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED6,

								/*---------------SET BITS-------------------*/
								GPIOC_6_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOC_6_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_6_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_6_PUPD_SET	= 	GPIO_PUPDR_PUPD6_1,
								GPIOC_6_ODR_SET		= 	GPIO_ODR_OD6,

						/*-----------------------PIN 7--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_7_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED7,
								GPIOC_7_MOD_MASK	= 	GPIO_MODER_MODE7,
								GPIOC_7_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED7,

								/*---------------SET BITS-------------------*/
								GPIOC_7_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOC_7_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_7_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_7_PUPD_SET	= 	GPIO_PUPDR_PUPD7_1,
								GPIOC_7_ODR_SET		= 	GPIO_ODR_OD7,

						/*-----------------------PIN 8--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_8_MOD_MASK	= 	GPIO_MODER_MODE8,
								GPIOC_8_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED8,
								GPIOC_8_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED8,

								/*---------------SET BITS-------------------*/
								GPIOC_8_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOC_8_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_8_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_8_PUPD_SET	= 	GPIO_PUPDR_PUPD8_1,
								GPIOC_8_ODR_SET		= 	GPIO_ODR_OD8,

						/*-----------------------PIN 9--------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_9_MOD_MASK	= 	GPIO_MODER_MODE9,
								GPIOC_9_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED9,
								GPIOC_9_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED9,

								/*---------------SET BITS-------------------*/
								GPIOC_9_MOD_SET		= 	GPIO_MODER_MODE3_0,
								GPIOC_9_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_9_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_9_PUPD_SET	= 	GPIO_PUPDR_PUPD9_1,
								GPIOC_9_ODR_SET		= 	GPIO_ODR_OD9,

						/*-----------------------PIN 10-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_10_MOD_MASK	= 	GPIO_MODER_MODE10,
								GPIOC_10_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED10,
								GPIOC_10_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED10,

								/*---------------SET BITS-------------------*/
								GPIOC_10_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOC_10_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_10_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_10_PUPD_SET	= 	GPIO_PUPDR_PUPD10_1,
								GPIOC_10_ODR_SET	= 	GPIO_ODR_OD10,

						/*-----------------------PIN 11-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_11_MOD_MASK	= 	GPIO_MODER_MODE11,
								GPIOC_11_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED11,
								GPIOC_11_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED11,

								/*---------------SET BITS-------------------*/
								GPIOC_11_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOC_11_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_11_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_11_PUPD_SET	= 	GPIO_PUPDR_PUPD11_1,
								GPIOC_11_ODR_SET	= 	GPIO_ODR_OD11,

						/*-----------------------PIN 12-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_12_MOD_MASK	= 	GPIO_MODER_MODE12,
								GPIOC_12_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED12,
								GPIOC_12_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED12,

								/*---------------SET BITS-------------------*/
								GPIOC_12_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOC_12_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_12_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_12_PUPD_SET	= 	GPIO_PUPDR_PUPD12_1,
								GPIOC_12_ODR_SET	= 	GPIO_ODR_OD12,

						/*-----------------------PIN 13-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_13_MOD_MASK	= 	GPIO_MODER_MODE13,
								GPIOC_13_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED13,
								GPIOC_13_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED13,

								/*---------------SET BITS-------------------*/
								GPIOC_13_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOC_13_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_13_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_13_PUPD_SET	= 	GPIO_PUPDR_PUPD13_1,
								GPIOC_13_ODR_SET	= 	GPIO_ODR_OD13,

						/*-----------------------PIN 14-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_14_MOD_MASK	= 	GPIO_MODER_MODE14,
								GPIOC_14_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED14,
								GPIOC_14_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED14,

								/*---------------SET BITS-------------------*/
								GPIOC_14_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOC_14_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_14_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_14_PUPD_SET	= 	GPIO_PUPDR_PUPD14_1,
								GPIOC_14_ODR_SET	= 	GPIO_ODR_OD14,

						/*-----------------------PIN 15-------------------------*/

								/*---------------MASKS----------------------*/
								GPIOC_15_MOD_MASK	= 	GPIO_MODER_MODE15,
								GPIOC_15_OSPD_MASK	= 	GPIO_OSPEEDR_OSPEED15,
								GPIOC_15_PUPD_MASK	= 	GPIO_OSPEEDR_OSPEED15,

								/*---------------SET BITS-------------------*/
								GPIOC_15_MOD_SET	= 	GPIO_MODER_MODE3_0,
								GPIOC_15_OT_SET		= 	GPIO_OTYPER_OT0_Pos,
								GPIOC_15_OSPD_SET	= 	GPIO_OSPEEDR_OSPEED0_Pos,
								GPIOC_15_PUPD_SET	= 	GPIO_PUPDR_PUPD15_1,
								GPIOC_15_ODR_SET	= 	GPIO_ODR_OD15
};

uint32_t GPIO_PIN_SETUP_VALS[NUM_GPIO][PIN_TOTAL][FIELD_TOTAL] = {
		{
			{GPIOA_0_MOD_MASK,  GPIOA_0_MOD_SET,  GPIOA_0_OT_SET,  GPIOA_0_OSPD_MASK,  GPIOA_0_OSPD_SET,  GPIOA_0_PUPD_MASK,  GPIOA_0_PUPD_SET,  GPIOA_0_ODR_SET},
			{GPIOA_1_MOD_MASK,  GPIOA_1_MOD_SET,  GPIOA_1_OT_SET,  GPIOA_1_OSPD_MASK,  GPIOA_1_OSPD_SET,  GPIOA_1_PUPD_MASK,  GPIOA_1_PUPD_SET,  GPIOA_1_ODR_SET},
			{GPIOA_2_MOD_MASK,  GPIOA_2_MOD_SET,  GPIOA_2_OT_SET,  GPIOA_2_OSPD_MASK,  GPIOA_2_OSPD_SET,  GPIOA_2_PUPD_MASK,  GPIOA_2_PUPD_SET,  GPIOA_2_ODR_SET},
			{GPIOA_3_MOD_MASK,  GPIOA_3_MOD_SET,  GPIOA_3_OT_SET,  GPIOA_3_OSPD_MASK,  GPIOA_3_OSPD_SET,  GPIOA_3_PUPD_MASK,  GPIOA_3_PUPD_SET,  GPIOA_3_ODR_SET},
			{GPIOA_4_MOD_MASK,  GPIOA_4_MOD_SET,  GPIOA_4_OT_SET,  GPIOA_4_OSPD_MASK,  GPIOA_4_OSPD_SET,  GPIOA_4_PUPD_MASK,  GPIOA_4_PUPD_SET,  GPIOA_4_ODR_SET},
			{GPIOA_5_MOD_MASK,  GPIOA_5_MOD_SET,  GPIOA_5_OT_SET,  GPIOA_5_OSPD_MASK,  GPIOA_5_OSPD_SET,  GPIOA_5_PUPD_MASK,  GPIOA_5_PUPD_SET,  GPIOA_5_ODR_SET},
			{GPIOA_6_MOD_MASK,  GPIOA_6_MOD_SET,  GPIOA_6_OT_SET,  GPIOA_6_OSPD_MASK,  GPIOA_6_OSPD_SET,  GPIOA_6_PUPD_MASK,  GPIOA_6_PUPD_SET,  GPIOA_6_ODR_SET},
			{GPIOA_7_MOD_MASK,  GPIOA_7_MOD_SET,  GPIOA_7_OT_SET,  GPIOA_7_OSPD_MASK,  GPIOA_7_OSPD_SET,  GPIOA_7_PUPD_MASK,  GPIOA_7_PUPD_SET,  GPIOA_7_ODR_SET},
			{GPIOA_8_MOD_MASK,  GPIOA_8_MOD_SET,  GPIOA_8_OT_SET,  GPIOA_8_OSPD_MASK,  GPIOA_8_OSPD_SET,  GPIOA_8_PUPD_MASK,  GPIOA_8_PUPD_SET,  GPIOA_8_ODR_SET},
			{GPIOA_9_MOD_MASK,  GPIOA_9_MOD_SET,  GPIOA_9_OT_SET,  GPIOA_9_OSPD_MASK,  GPIOA_9_OSPD_SET,  GPIOA_9_PUPD_MASK,  GPIOA_9_PUPD_SET,  GPIOA_9_ODR_SET},
			{GPIOA_10_MOD_MASK, GPIOA_10_MOD_SET, GPIOA_10_OT_SET, GPIOA_10_OSPD_MASK, GPIOA_10_OSPD_SET, GPIOA_10_PUPD_MASK, GPIOA_10_PUPD_SET, GPIOA_10_ODR_SET},
			{GPIOA_11_MOD_MASK, GPIOA_11_MOD_SET, GPIOA_11_OT_SET, GPIOA_11_OSPD_MASK, GPIOA_11_OSPD_SET, GPIOA_11_PUPD_MASK, GPIOA_11_PUPD_SET, GPIOA_11_ODR_SET},
			{GPIOA_12_MOD_MASK, GPIOA_12_MOD_SET, GPIOA_12_OT_SET, GPIOA_12_OSPD_MASK, GPIOA_12_OSPD_SET, GPIOA_12_PUPD_MASK, GPIOA_12_PUPD_SET, GPIOA_12_ODR_SET},
			{GPIOA_13_MOD_MASK, GPIOA_13_MOD_SET, GPIOA_13_OT_SET, GPIOA_13_OSPD_MASK, GPIOA_13_OSPD_SET, GPIOA_13_PUPD_MASK, GPIOA_13_PUPD_SET, GPIOA_13_ODR_SET},
			{GPIOA_14_MOD_MASK, GPIOA_14_MOD_SET, GPIOA_14_OT_SET, GPIOA_14_OSPD_MASK, GPIOA_14_OSPD_SET, GPIOA_14_PUPD_MASK, GPIOA_14_PUPD_SET, GPIOA_14_ODR_SET},
			{GPIOA_15_MOD_MASK, GPIOA_15_MOD_SET, GPIOA_15_OT_SET, GPIOA_15_OSPD_MASK, GPIOA_15_OSPD_SET, GPIOA_15_PUPD_MASK, GPIOA_15_PUPD_SET, GPIOA_15_ODR_SET}
			},
		{
			{GPIOB_0_MOD_MASK,  GPIOB_0_MOD_SET,  GPIOB_0_OT_SET,  GPIOB_0_OSPD_MASK,  GPIOB_0_OSPD_SET,  GPIOB_0_PUPD_MASK,  GPIOB_0_PUPD_SET,  GPIOB_0_ODR_SET},
			{GPIOB_1_MOD_MASK,  GPIOB_1_MOD_SET,  GPIOB_1_OT_SET,  GPIOB_1_OSPD_MASK,  GPIOB_1_OSPD_SET,  GPIOB_1_PUPD_MASK,  GPIOB_1_PUPD_SET,  GPIOB_1_ODR_SET},
			{GPIOB_2_MOD_MASK,  GPIOB_2_MOD_SET,  GPIOB_2_OT_SET,  GPIOB_2_OSPD_MASK,  GPIOB_2_OSPD_SET,  GPIOB_2_PUPD_MASK,  GPIOB_2_PUPD_SET,  GPIOB_2_ODR_SET},
			{GPIOB_3_MOD_MASK,  GPIOB_3_MOD_SET,  GPIOB_3_OT_SET,  GPIOB_3_OSPD_MASK,  GPIOB_3_OSPD_SET,  GPIOB_3_PUPD_MASK,  GPIOB_3_PUPD_SET,  GPIOB_3_ODR_SET},
			{GPIOB_4_MOD_MASK,  GPIOB_4_MOD_SET,  GPIOB_4_OT_SET,  GPIOB_4_OSPD_MASK,  GPIOB_4_OSPD_SET,  GPIOB_4_PUPD_MASK,  GPIOB_4_PUPD_SET,  GPIOB_4_ODR_SET},
			{GPIOB_5_MOD_MASK,  GPIOB_5_MOD_SET,  GPIOB_5_OT_SET,  GPIOB_5_OSPD_MASK,  GPIOB_5_OSPD_SET,  GPIOB_5_PUPD_MASK,  GPIOB_5_PUPD_SET,  GPIOB_5_ODR_SET},
			{GPIOB_6_MOD_MASK,  GPIOB_6_MOD_SET,  GPIOB_6_OT_SET,  GPIOB_6_OSPD_MASK,  GPIOB_6_OSPD_SET,  GPIOB_6_PUPD_MASK,  GPIOB_6_PUPD_SET,  GPIOB_6_ODR_SET},
			{GPIOB_7_MOD_MASK,  GPIOB_7_MOD_SET,  GPIOB_7_OT_SET,  GPIOB_7_OSPD_MASK,  GPIOB_7_OSPD_SET,  GPIOB_7_PUPD_MASK,  GPIOB_7_PUPD_SET,  GPIOB_7_ODR_SET},
			{GPIOB_8_MOD_MASK,  GPIOB_8_MOD_SET,  GPIOB_8_OT_SET,  GPIOB_8_OSPD_MASK,  GPIOB_8_OSPD_SET,  GPIOB_8_PUPD_MASK,  GPIOB_8_PUPD_SET,  GPIOB_8_ODR_SET},
			{GPIOB_9_MOD_MASK,  GPIOB_9_MOD_SET,  GPIOB_9_OT_SET,  GPIOB_9_OSPD_MASK,  GPIOB_9_OSPD_SET,  GPIOB_9_PUPD_MASK,  GPIOB_9_PUPD_SET,  GPIOB_9_ODR_SET},
			{GPIOB_10_MOD_MASK, GPIOB_10_MOD_SET, GPIOB_10_OT_SET, GPIOB_10_OSPD_MASK, GPIOB_10_OSPD_SET, GPIOB_10_PUPD_MASK, GPIOB_10_PUPD_SET, GPIOB_10_ODR_SET},
			{GPIOB_11_MOD_MASK, GPIOB_11_MOD_SET, GPIOB_11_OT_SET, GPIOB_11_OSPD_MASK, GPIOB_11_OSPD_SET, GPIOB_11_PUPD_MASK, GPIOB_11_PUPD_SET, GPIOB_11_ODR_SET},
			{GPIOB_12_MOD_MASK, GPIOB_12_MOD_SET, GPIOB_12_OT_SET, GPIOB_12_OSPD_MASK, GPIOB_12_OSPD_SET, GPIOB_12_PUPD_MASK, GPIOB_12_PUPD_SET, GPIOB_12_ODR_SET},
			{GPIOB_13_MOD_MASK, GPIOB_13_MOD_SET, GPIOB_13_OT_SET, GPIOB_13_OSPD_MASK, GPIOB_13_OSPD_SET, GPIOB_13_PUPD_MASK, GPIOB_13_PUPD_SET, GPIOB_13_ODR_SET},
			{GPIOB_14_MOD_MASK, GPIOB_14_MOD_SET, GPIOB_14_OT_SET, GPIOB_14_OSPD_MASK, GPIOB_14_OSPD_SET, GPIOB_14_PUPD_MASK, GPIOB_14_PUPD_SET, GPIOB_14_ODR_SET},
			{GPIOB_15_MOD_MASK, GPIOB_15_MOD_SET, GPIOB_15_OT_SET, GPIOB_15_OSPD_MASK, GPIOB_15_OSPD_SET, GPIOB_15_PUPD_MASK, GPIOB_15_PUPD_SET, GPIOB_15_ODR_SET}
		},
		{
			{GPIOC_0_MOD_MASK,  GPIOC_0_MOD_SET,  GPIOC_0_OT_SET,  GPIOC_0_OSPD_MASK,  GPIOC_0_OSPD_SET,  GPIOC_0_PUPD_MASK,  GPIOC_0_PUPD_SET,  GPIOC_0_ODR_SET},
			{GPIOC_1_MOD_MASK,  GPIOC_1_MOD_SET,  GPIOC_1_OT_SET,  GPIOC_1_OSPD_MASK,  GPIOC_1_OSPD_SET,  GPIOC_1_PUPD_MASK,  GPIOC_1_PUPD_SET,  GPIOC_1_ODR_SET},
			{GPIOC_2_MOD_MASK,  GPIOC_2_MOD_SET,  GPIOC_2_OT_SET,  GPIOC_2_OSPD_MASK,  GPIOC_2_OSPD_SET,  GPIOC_2_PUPD_MASK,  GPIOC_2_PUPD_SET,  GPIOC_2_ODR_SET},
			{GPIOC_3_MOD_MASK,  GPIOC_3_MOD_SET,  GPIOC_3_OT_SET,  GPIOC_3_OSPD_MASK,  GPIOC_3_OSPD_SET,  GPIOC_3_PUPD_MASK,  GPIOC_3_PUPD_SET,  GPIOC_3_ODR_SET},
			{GPIOC_4_MOD_MASK,  GPIOC_4_MOD_SET,  GPIOC_4_OT_SET,  GPIOC_4_OSPD_MASK,  GPIOC_4_OSPD_SET,  GPIOC_4_PUPD_MASK,  GPIOC_4_PUPD_SET,  GPIOC_4_ODR_SET},
			{GPIOC_5_MOD_MASK,  GPIOC_5_MOD_SET,  GPIOC_5_OT_SET,  GPIOC_5_OSPD_MASK,  GPIOC_5_OSPD_SET,  GPIOC_5_PUPD_MASK,  GPIOC_5_PUPD_SET,  GPIOC_5_ODR_SET},
			{GPIOC_6_MOD_MASK,  GPIOC_6_MOD_SET,  GPIOC_6_OT_SET,  GPIOC_6_OSPD_MASK,  GPIOC_6_OSPD_SET,  GPIOC_6_PUPD_MASK,  GPIOC_6_PUPD_SET,  GPIOC_6_ODR_SET},
			{GPIOC_7_MOD_MASK,  GPIOC_7_MOD_SET,  GPIOC_7_OT_SET,  GPIOC_7_OSPD_MASK,  GPIOC_7_OSPD_SET,  GPIOC_7_PUPD_MASK,  GPIOC_7_PUPD_SET,  GPIOC_7_ODR_SET},
			{GPIOC_8_MOD_MASK,  GPIOC_8_MOD_SET,  GPIOC_8_OT_SET,  GPIOC_8_OSPD_MASK,  GPIOC_8_OSPD_SET,  GPIOC_8_PUPD_MASK,  GPIOC_8_PUPD_SET,  GPIOC_8_ODR_SET},
			{GPIOC_9_MOD_MASK,  GPIOC_9_MOD_SET,  GPIOC_9_OT_SET,  GPIOC_9_OSPD_MASK,  GPIOC_9_OSPD_SET,  GPIOC_9_PUPD_MASK,  GPIOC_9_PUPD_SET,  GPIOC_9_ODR_SET},
			{GPIOC_10_MOD_MASK, GPIOC_10_MOD_SET, GPIOC_10_OT_SET, GPIOC_10_OSPD_MASK, GPIOC_10_OSPD_SET, GPIOC_10_PUPD_MASK, GPIOC_10_PUPD_SET, GPIOC_10_ODR_SET},
			{GPIOC_11_MOD_MASK, GPIOC_11_MOD_SET, GPIOC_11_OT_SET, GPIOC_11_OSPD_MASK, GPIOC_11_OSPD_SET, GPIOC_11_PUPD_MASK, GPIOC_11_PUPD_SET, GPIOC_11_ODR_SET},
			{GPIOC_12_MOD_MASK, GPIOC_12_MOD_SET, GPIOC_12_OT_SET, GPIOC_12_OSPD_MASK, GPIOC_12_OSPD_SET, GPIOC_12_PUPD_MASK, GPIOC_12_PUPD_SET, GPIOC_12_ODR_SET},
			{GPIOC_13_MOD_MASK, GPIOC_13_MOD_SET, GPIOC_13_OT_SET, GPIOC_13_OSPD_MASK, GPIOC_13_OSPD_SET, GPIOC_13_PUPD_MASK, GPIOC_13_PUPD_SET, GPIOC_13_ODR_SET},
			{GPIOC_14_MOD_MASK, GPIOC_14_MOD_SET, GPIOC_14_OT_SET, GPIOC_14_OSPD_MASK, GPIOC_14_OSPD_SET, GPIOC_14_PUPD_MASK, GPIOC_14_PUPD_SET, GPIOC_14_ODR_SET},
			{GPIOC_15_MOD_MASK, GPIOC_15_MOD_SET, GPIOC_15_OT_SET, GPIOC_15_OSPD_MASK, GPIOC_15_OSPD_SET, GPIOC_15_PUPD_MASK, GPIOC_15_PUPD_SET, GPIOC_15_ODR_SET}
		}
};
#endif /* GPIO_SETUP_CONSTRAINTS_H_ */

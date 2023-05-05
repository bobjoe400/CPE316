/*
 * Written by Francisco Wilken
 * Adapted by Cooper Mattern and used with permission
 *
 */

#include "keypad.h"
#include "math.h"
void keypad_setup()
{
	// Column Setup
	RCC->COL_AHB |= COL_AHB_PORT;

	// Clear Mode Reg
	COL_PORT->MODER &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 | GPIO_MODER_MODE2);

	// Set Mode Reg to Output
	COL_PORT->MODER |= ( GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE2_0);

	// Set Type Reg to Push-Pull
	COL_PORT->OTYPER &= ~(GPIO_OTYPER_OT0 | GPIO_OTYPER_OT1 | GPIO_OTYPER_OT2);

	// Set Speed Reg to Low Speed
	COL_PORT->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0 | GPIO_OSPEEDR_OSPEED1 | GPIO_OSPEEDR_OSPEED2);

	// Set PUPD Reg to No Pull-Up/Pull-Down
	COL_PORT->PUPDR &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 | GPIO_PUPDR_PUPD2);

	// Row Setup
	RCC->ROW_AHB |= ROW_AHB_PORT;

	// Setup Inputs
	ROW_PORT->MODER &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 | GPIO_MODER_MODE2 | GPIO_MODER_MODE3);

	// Set Mode Reg to Input
	ROW_PORT->MODER &= ~( GPIO_MODER_MODE0 | GPIO_MODER_MODE1 | GPIO_MODER_MODE2 | GPIO_MODER_MODE3);

	// Clear PUPD Reg
	ROW_PORT->PUPDR &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 | GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3);

	// Set PUPD Reg to Pull-Down
	ROW_PORT->PUPDR |= (GPIO_PUPDR_PUPD0_1 | GPIO_PUPDR_PUPD1_1 | GPIO_PUPDR_PUPD2_1 | GPIO_PUPDR_PUPD3_1);
}

uint32_t keypad_read()
{
	uint16_t col = 0;
	uint16_t row = 0;

	// Enable Columns just in case
	COL_PORT -> ODR |= COL_MASK;

	uint16_t row_val = ROW_PORT->IDR & ROW_MASK;

	uint32_t ret_val = NO_KEY;

	// Check If Button Pressed
	if (row_val == 0)
	{
		return NO_KEY;
	}

	for (col = 0; col < NUM_COLS; col++)
	{
		// Turn Off All Cols
		COL_PORT -> ODR &= ~(COL_MASK);

		// Turn On Specific Col
		COL_PORT -> ODR |= (1 << (COL_START_PIN + col));

		// Test Row
		row_val = ROW_PORT->IDR & ROW_MASK;
		if (row_val != 0)
		{
			// Row Bits are now bottom N bits
			row_val = row_val >> ROW_START_PIN;
			// Check Each Row Bit
			for (row = 0; row < NUM_ROWS; row++)
			{
				if (row_val & (1 << row))
				{
					// Set Cols High Again
					COL_PORT -> ODR |= COL_MASK;

					// Return Key Val
					ret_val = 1 + col + 3 * row;

					return ret_val;
				}
			}
		}
	}

	// Set Cols High Again
	COL_PORT -> ODR |= COL_MASK;
	// No Button Found
	return NO_KEY;
}
uint32_t keypad_read_digits(uint32_t ndigits)
{
	uint32_t i, val;
	uint32_t ret = 0;
	for (i = 0; i < ndigits; i++)
	{
		uint32_t wait = 0;

		// Calculate place value
		uint32_t base = pow(10, (ndigits - i - 1));

		// Wait for Valid Input
		/*while ((*/val = keypad_read()/*) == NO_KEY)*/;

		ret += base * val;
		// Wait a bit till next value

	}
	return ret;
}

/*
 * util.c
 *
 *  Created on: Jun 8, 2023
 *      Author: cnama
 */

#include <stdint.h>

/*float to string. written by Escher
 * https://stackoverflow.com/questions/23191203/convert-float-to-string-without-sprintf
 */

char * float_to_char(float x, char *p, int buff_size) {
    char *s = p + buff_size; // go to end of buffer
    uint16_t decimals;  // variable to store the decimals
    int units;  // variable to store the units (part to left of decimal place)
    if (x < 0) { // take care of negative numbers
        decimals = (int)(x * -100) % 100; // make 1000 for 3 decimals etc.
        units = (int)(-1 * x);
    } else { // positive numbers
        decimals = (int)(x * 100) % 100;
        units = (int)x;
    }

    *--s = (decimals % 10) + '0';
    decimals /= 10; // repeat for as many decimal places as you need
    *--s = (decimals % 10) + '0';
    *--s = '.';

    while (units > 0) {
        *--s = (units % 10) + '0';
        units /= 10;
    }
    if (x < 0) *--s = '-'; // unary minus sign for negative numbers
    return s;
}

/* Takes a string and converts to an integer */
int32_t strtoint(char* str) {

	int32_t result = 0;
	int8_t sign = 1;
 	uint8_t i = 0;

 	if (str[0] == '-') {
     	sign = -1;
     	i = 1;
   	}

   while (str[i] != '\0') {
     result = (result * 10) + (str[i] - '0');
     i++;
   }

   return (result * sign);
}

/* Takes a string and converts to a float */
float strtofloat(char* str) {

 	float result = 0;
 	int8_t sign = 1;
 	uint8_t i = 0;

 	if (str[0] == '-') {
     	sign = -1;
     	i = 1;
   	}

   while ((str[i] != '\0') && (str[i] != '.')) {
     	result = (result * 10) + (str[i] - '0');
     	i++;
   }

   // Made it to decimal
   i++;
   float decimal = 0.1;
   while (str[i] != '\0') {
   		result += ((str[i] - '0') * decimal);
   		decimal *= 0.1;
   		i++;
   }

   return (result * sign);
}

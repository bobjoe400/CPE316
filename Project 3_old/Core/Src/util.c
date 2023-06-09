/*
 * util.c
 *
 *  Created on: Jun 8, 2023
 *      Author: cnama
 */

#include <stdint.h>

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

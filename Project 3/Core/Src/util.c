/*
 * util.c
 *
 *  Created on: Jun 8, 2023
 *      Author: cnama
 */

#include <math.h>
#include <string.h>
#include <stdint.h>

/* Takes a string and converts to a float
 * Author: Dalee Roland
 */
float strtofloat(char* str) {

 	float result = 0;
 	int8_t sign = 1;
 	uint8_t i = 0;

	if (str[0] == '-') {
		sign = -1;
		i = 1;
	}

   while ((str[i] != '\0') && (str[i] != '.')) {
	   if(str[i] != ','){
			result = (result * 10) + (str[i] - '0');
	   }
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



/**
 * Double to ASCII
 * Author: androider
 * Source: https://stackoverflow.com/questions/2302969/convert-a-float-to-a-string
 */
static double PRECISION = 0.000001;


char * dtoa(char *s, double n) {
    // handle special cases
    if (isnan(n)) {
        strcpy(s, "nan");
    } else if (isinf(n)) {
        strcpy(s, "inf");
    } else if (n == 0.0) {
        strcpy(s, "0");
    } else {
        int digit, m, m1;
        char *c = s;
        int neg = (n < 0);
        if (neg)
            n = -n;
        // calculate magnitude
        m = log10(n);
        int useExp = (m >= 14 || (neg && m >= 9) || m <= -9);
        if (neg)
            *(c++) = '-';
        // set up for scientific notation
        if (useExp) {
            if (m < 0)
               m -= 1.0;
            n = n / pow(10.0, m);
            m1 = m;
            m = 0;
        }
        if (m < 1.0) {
            m = 0;
        }
        // convert the number
        while (n > PRECISION || m >= 0) {
            double weight = pow(10.0, m);
            if (weight > 0 && !isinf(weight)) {
                digit = floor(n / weight);
                n -= (digit * weight);
                *(c++) = '0' + digit;
            }
            if (m == 0 && n > 0)
                *(c++) = '.';
            m--;
        }
        if (useExp) {
            // convert the exponent
            int i, j;
            *(c++) = 'e';
            if (m1 > 0) {
                *(c++) = '+';
            } else {
                *(c++) = '-';
                m1 = -m1;
            }
            m = 0;
            while (m1 > 0) {
                *(c++) = '0' + m1 % 10;
                m1 /= 10;
                m++;
            }
            c -= m;
            for (i = 0, j = m-1; i<j; i++, j--) {
                // swap without temporary
                c[i] ^= c[j];
                c[j] ^= c[i];
                c[i] ^= c[j];
            }
            c += m;
        }
        *(c) = '\0';
    }
    return s;
}

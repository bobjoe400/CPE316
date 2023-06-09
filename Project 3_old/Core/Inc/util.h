/*
 * util.h
 *
 *  Created on: Jun 8, 2023
 *      Author: cnama
 */

#ifndef INC_UTIL_H_
#define INC_UTIL_H_

#include <stdint.h>

/* -----------------Stack Stuff--------------- */

#define OPERATOR_STACK_SIZE 7
#define OPERAND_STACK_SIZE 8

#define push(sp, n) (*((sp)++) = (n))
#define pop(sp) (*(--(sp)))
#define peek(sp) (*(sp-1))

typedef struct {
    char stack[OPERATOR_STACK_SIZE];
    char* sp;
} OperatorStack;

typedef struct {
    float stack[OPERAND_STACK_SIZE];
    float* sp;
} OperandStack;

typedef struct {
    OperatorStack operatorStack;
    OperandStack operandStack;
} StackContainer;

/* -------------------------------------------- */

#define MAX_DISP 16
#define CHAR_BUFF_SIZE MAX_DISP + 1

int32_t strtoint(char* str);
float strtofloat(char* str);

#endif /* INC_UTIL_H_ */

/*
 * util.h
 *
 *  Created on: Jun 8, 2023
 *      Author: cnama
 */

#ifndef INC_UTIL_H_
#define INC_UTIL_H_

/* -----------------Stack Stuff--------------- */

#define OPERATOR_STACK_SIZE 7
#define OPERAND_STACK_SIZE 8

#define push(sp, n) (*((sp)++) = (n))
#define pop(sp) (*--(sp))

typedef struct {
    char stack[OPERATOR_STACK_SIZE];
    char* sp;
} OperatorStack;

typedef struct {
    float stack[OPERAND_STACK_SIZE];
    char* sp;
} OperandStack;

typedef struct {
    OperatorStack operatorStack;
    OperandStack operandStack;
} StackContainer;

/* -------------------------------------------- */

char * float_to_char(float x, char *pm, int buff_size);
int32_t strtoint(char* str);
float strtofloat(char* str);

#endif /* INC_UTIL_H_ */

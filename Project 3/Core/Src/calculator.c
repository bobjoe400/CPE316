/*
 * calculator.c
 *
 *  Created on: Jun 8, 2023
 *      Author: cnama
 */

#include "util.h"
#include "calculator.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define operators "enltcsq^*/+-"

/* Given a specific command, performs a mathematical operation
 * Author: Dalee Roland
 */
static float calculate(float op1, float op2, char operator) {

	float result;

	switch(operator) {
    	case '+':	// add
    		result = op1 + op2;		break;
    	case '-':	// subtract
    		result = op1 - op2;		break;
    	case '*':	// multiply
    		result = op1 * op2;		break;
    	case '/':	// divide
    		result = op1 / op2;		break;
    	case 'q':	// square root
    		result = sqrtf(op1);	break;
    	case 's':	// sin
    		result = sinf(op1);		break;
    	case 'c':	// cos
    		result = cosf(op1);		break;
    	case 't':	// tan
    		result = tanf(op1);		break;
    	case 'l':	// log
    		result = log10f(op1);	break;
    	case 'n':	// ln
    		result = logf(op1);		break;
    	case 'e':	// e^x
    		result = expf(op1);		break;
    	case '^':	// power
    		result = pow(op1, op2);	break;
    	default: // Error Handling
    		break;
		}
	return result;
}

/* Returns the precedence of a mathematical operator
 * Author: Cooper Mattern
 */
static int getPrecedence(char op){
	switch(op){
	case '^':
		return 1;
	case '*':
		return 2;
	case '\\':
		return 2;
	case '/':
		return 2;
	case '+':
		return 3;
	case '-':
		return 3;
	case '(':
		return 4;
	case ')':
		return 4;
	default:
		return 0;
	}
}

/* Evaluates the expression inputed by the user
 *  Author: Cooper Mattern
 */
float expEval(char input_buf[CHAR_BUFF_SIZE][CHAR_BUFF_SIZE], int input_size){

    StackContainer sc;
    memset(sc.operatorStack.stack, 0, OPERATOR_STACK_SIZE * sizeof(char));
    sc.operatorStack.sp = sc.operatorStack.stack;
    memset(sc.operandStack.stack, 0, OPERAND_STACK_SIZE * sizeof(float));
    sc.operandStack.sp = sc.operandStack.stack;

	int i;

	for(i = 0; i < input_size; i++){
		char curr = input_buf[i][0];

		if((('0' <= curr) && (curr <= '9')) || curr == '`'){
			if(curr == '`'){
				input_buf[i][0] = '-';
			}
			float num = strtofloat(input_buf[i]);
			push(sc.operandStack.sp, num);
		}else if(curr == 'p'){
			push(sc.operandStack.sp, M_PI);
		}else if(strchr(operators, curr) != NULL){
			char top = peek(sc.operatorStack.sp);
			if(sc.operatorStack.sp == sc.operatorStack.stack){
				push(sc.operatorStack.sp, curr);
			}else{
				int curr_op_prec = getPrecedence(curr);
				int top_prec = getPrecedence(top);
				if(curr_op_prec <= top_prec || top == '(' || top == ')'){
					push(sc.operatorStack.sp, curr);
				}else{
					while((sc.operatorStack.sp != sc.operatorStack.stack) && curr_op_prec > top_prec){
						char operator = pop(sc.operatorStack.sp);
						char* arith_start = strchr(operators, '^');
						char* op_loc = strchr(operators, operator);
						float operand1, operand2;

						if(op_loc < arith_start){
							operand1 = pop(sc.operandStack.sp);
							push(sc.operandStack.sp, calculate(operand1, 0.0, operator));
						}else{
							operand2 = pop(sc.operandStack.sp);
							operand1 = pop(sc.operandStack.sp);
							push(sc.operandStack.sp, calculate(operand1, operand2, operator));
						}
						top_prec = getPrecedence((top = peek(sc.operatorStack.sp)));
					}
					push(sc.operatorStack.sp, curr);
				}
			}
		}else if(curr == '('){
			push(sc.operatorStack.sp, curr);
		}else if(curr == ')'){
			while(peek(sc.operatorStack.sp) != '('){
				char operator = pop(sc.operatorStack.sp);
				char* arith_start = strchr(operators, '^');
				char* op_loc = strchr(operators, operator);
				float operand1, operand2;

				if(op_loc < arith_start){
					operand1 = pop(sc.operandStack.sp);
					push(sc.operandStack.sp, calculate(operand1, 0.0, operator));
				}else{
					operand2 = pop(sc.operandStack.sp);
					operand1 = pop(sc.operandStack.sp);
					push(sc.operandStack.sp, calculate(operand1, operand2, operator));
				}
			}
			pop(sc.operatorStack.sp);
		}
	}

	while(sc.operatorStack.sp != sc.operatorStack.stack && sc.operandStack.sp != sc.operandStack.stack){
		char operator = pop(sc.operatorStack.sp);
		char* arith_start = strchr(operators, '^');
		char* op_loc = strchr(operators, operator);
		float operand1, operand2;

		if(op_loc < arith_start){
			operand1 = pop(sc.operandStack.sp);
			push(sc.operandStack.sp, calculate(operand1, 0.0, operator));
		}else{
			operand2 = pop(sc.operandStack.sp);
			operand1 = pop(sc.operandStack.sp);
			push(sc.operandStack.sp, calculate(operand1, operand2, operator));
		}
	}

	if(sc.operatorStack.sp != sc.operatorStack.stack){
		return NAN;
	}

	float retval = pop(sc.operandStack.sp);
	if(sc.operandStack.sp != sc.operandStack.stack){
		return NAN;
	}
	return retval;
}

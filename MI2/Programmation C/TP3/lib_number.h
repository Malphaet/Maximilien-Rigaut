/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

#ifndef LIB_NUMBER_H
#define LIB_NUMBER_H
/* ========= Includes =========*/

#include "lib_rational.h"
#include "lib_complex.h"

/* ========= Typedef ==========*/

enum TypeNumber {integer, rational, floating, complex};

typedef struct nb {
	enum TypeNumber tn;
	union val {
		int intnb;
		Rational rationalnb;
		double floatnb;
		Complex complexnb;
	} value ;
} Number;

/* ======== Prototype =========*/

void printNumber(Number n);
void convertNumber(Number *n1, enum TypeNumber type);
void equaliseNumber(Number *n1, Number *n2);

Number addNumber(Number n1, Number n2);
Number mulNumber(Number n1, Number n2);
Number subNumber(Number n1, Number n2);
Number divNumber(Number n1, Number n2);
int isequalNumber(Number n1, Number n2);

#endif

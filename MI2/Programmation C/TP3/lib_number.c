/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include "lib_number.h"

/* ========= Defines ==========*/

/* ========= Functions ========*/

void printNumber(Number n){
	switch (n.tn){
		case (integer):
			printf("%d",n.value.intnb);
			break;
		case (rational):
			printRational(n.value.rationalnb);
			break;
		case (floating):
			printf("%f",n.value.floatnb);
			break;
		case (complex):
			printComplex(n.value.complexnb);
			break;
	}
}

void equalyseNumber(Number n1, Number n2){
	if (n1.nb>n2.nb) convertNumber(&n1,n2.tn);
	if (n1.nb<n2.nb) convertNumber(&n2,n1.tn);
}

Number convertNumber(int *n1, enum TypeNumber type){
	if (n1.tn<rational){
		n1=int2Rational(n1.value.integernb);
	}
	if (n1.tn<floating){
		n1=Rational2double(n1.value.floatingnb);
	}
	if (n1.tn<complex){
		n1=Rational2Complex(n1.value.rationalnb);
	}
}
/*Number addNumber(Number n1, Number n2);
Number mulNumber(Number n1, Number n2);
Number subNumber(Number n1, Number n2);
Number divNumber(Number n1, Number n2);
Number isequalNumber(Number n1, Number n2);
*/

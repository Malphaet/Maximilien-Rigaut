/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include "lib_number.h"
#include "lib_rational.h"
#include "lib_complex.h"

/* ========= Defines ==========*/

#define PRINTN(text,value) printf(text); printNumber(value); printf("\n")

/* =========== Main ===========*/

int main(void){
	Number n1, n2, n3;
	
	n1.tn = rational;
	n1.value.rationalnb.num=1;
	n1.value.rationalnb.den=4;
	
	n2.tn = integer;
	n2.value.intnb = 4;
	
	n3.tn = complex;
	n3.value.complexnb.im = 2.54;
	n3.value.complexnb.re = 4.45;
	
	PRINTN("n1 : ",n1);
	PRINTN("n2 : ",n2);
	PRINTN("n3 : ",n3);
	
	/*PRINTN("divnumber(mulnumber(n1,n2),n3)",divnumber(mulnumber(n1,n2),n3));*/
	
	return 0;
}

/* ========= Functions ========*/


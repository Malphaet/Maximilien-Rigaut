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
	
	/*
	Number divNumber(Number n1, Number n2);
	Number isequalNumber(Number n1, Number n2);
	*/
	
	PRINTN("addNumber(n1,n2) : ",addNumber(n1, n2));
	PRINTN("addNumber(n2,n3) : ",addNumber(n2, n3));
	
	PRINTN("mulNumber(n2,n2) : ",mulNumber(n2, n2));
	PRINTN("mulNumber(n3,n1) : ",mulNumber(n1, n3));
	
	PRINTN("subNumber(n3,n3) : ",subNumber(n2, n2));
	PRINTN("subNumber(n3,n2) : ",subNumber(n1, n3));
	
	PRINTN("divNumber(n3,n1) : ",divNumber(n3, n1));
	PRINTN("divNumber(n3,n2) : ",divNumber(n3, n2));
	
	printf("isequalNumber(n1,n1) : %d\n",isequalNumber(n1, n1));
	printf("isequalNumber(n1,n2) : %d\n",isequalNumber(n1, n2));
	
	
	PRINTN("divnumber(mulnumber(n1,n2),n3) : ",divNumber(mulNumber(n1,n2),n3));
	
	return 0;
}

/* ========= Functions ========*/


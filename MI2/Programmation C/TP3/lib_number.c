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

void equaliseNumber(Number *n1, Number *n2){
	if (n1->tn<n2->tn) convertNumber(n1,n2->tn);
	if (n1->tn>n2->tn) convertNumber(n2,n1->tn);
}

void convertNumber(Number *n, enum TypeNumber type){
	Number n1,n2,n3;
	if (n->tn < rational && rational <= type){
		n1.tn=rational;
		n1.value.rationalnb=int2Rational((*n).value.intnb);
		(*n)=n1;
	}
	if (n->tn < floating && floating <= type){
		n2.tn=floating;
		n2.value.floatnb=Rational2double((*n).value.rationalnb);
		(*n)=n2;
	}
	if (n->tn < complex && complex <= type){
		n3.tn=complex;
		n3.value.complexnb=double2Complex((*n).value.floatnb);
		(*n)=n3;
	}
}

Number addNumber(Number N1, Number N2){
	Number n,n1=N1,n2=N2;
	equaliseNumber(&n1,&n2);
	switch (n1.tn){
		case (integer):
			n.tn=integer;
			n.value.intnb=n1.value.intnb+n2.value.intnb;
			break;
		case (rational):
			n.tn=rational;
			n.value.rationalnb=addRational(n1.value.rationalnb,n2.value.rationalnb);
			break;
		case (floating):
			n.tn=floating;
			n.value.floatnb=n1.value.floatnb+n2.value.floatnb;
			break;
		case (complex):
			n.tn=complex;
			n.value.complexnb=addComplex(n1.value.complexnb,n2.value.complexnb);
			break;
		}
	return n;
}

Number mulNumber(Number N1, Number N2){
	Number n,n1=N1,n2=N2;
	equaliseNumber(&n1,&n2);
	switch (n1.tn){
		case (integer):
			n.tn=integer;
			n.value.intnb=n1.value.intnb*n2.value.intnb;
			break;
		case (rational):
			n.tn=rational;
			n.value.rationalnb=mulRational(n1.value.rationalnb,n2.value.rationalnb);
			break;
		case (floating):
			n.tn=floating;
			n.value.floatnb=n1.value.floatnb*n2.value.floatnb;
			break;
		case (complex):
			n.tn=complex;
			n.value.complexnb=mulComplex(n1.value.complexnb,n2.value.complexnb);
			break;
		}
	return n;
}

/* Less CPU Efficient
Number subNumber(Number n1, Number n2){
	Number n;
	n.tn=integer;
	n.value.intnb=-1;
	return addNumber(mulNumber(n,n1),n2);
}*/


Number subNumber(Number N1, Number N2){
	Number n,n1=N1,n2=N2;
	equaliseNumber(&n1,&n2);
	switch (n1.tn){
		case (integer):
			n.tn=integer;
			n.value.intnb=n1.value.intnb-n2.value.intnb;
			break;
		case (rational):
			n.tn=rational;
			n.value.rationalnb=subRational(n1.value.rationalnb,n2.value.rationalnb);
			break;
		case (floating):
			n.tn=floating;
			n.value.floatnb=n1.value.floatnb-n2.value.floatnb;
			break;
		case (complex):
			n.tn=complex;
			n.value.complexnb=subComplex(n1.value.complexnb,n2.value.complexnb);
			break;
		}
	return n;
}

Number divNumber(Number N1, Number N2){
	Number n,n1=N1,n2=N2;
	equaliseNumber(&n1,&n2);
	switch (n1.tn){
		case (integer):
			n.tn=integer;
			n.value.intnb=n1.value.intnb/n2.value.intnb;
			break;
		case (rational):
			n.tn=rational;
			n.value.rationalnb=divRational(n1.value.rationalnb,n2.value.rationalnb);
			break;
		case (floating):
			n.tn=floating;
			n.value.floatnb=n1.value.floatnb/n2.value.floatnb;
			break;
		case (complex):
			n.tn=complex;
			n.value.complexnb=divComplex(n1.value.complexnb,n2.value.complexnb);
			break;
	}
	return n;
}

int isequalNumber(Number N1, Number N2){
	Number n1=N1,n2=N2;
	int i;
	equaliseNumber(&n1,&n2);
	switch (n1.tn){
		case (integer):
			i=(n1.value.intnb==n2.value.intnb);
			break;
		case (rational):
			i=isequalRational(n1.value.rationalnb,n2.value.rationalnb);
			break;
		case (floating):
			i=(n1.value.floatnb==n2.value.floatnb);
			break;
		case (complex):
			i=isequalComplex(n1.value.complexnb,n2.value.complexnb);
			break;
	}
	return i;
}


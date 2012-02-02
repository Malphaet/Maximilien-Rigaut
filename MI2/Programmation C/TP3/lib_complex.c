/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <math.h>
#include "lib_complex.h"

/* ========= Defines ==========*/


/* ========= Functions ========*/

void printComplex(Complex c){
	printf("%f + %fi",c.re,c.im);
}

Complex addComplex(Complex c1,Complex c2){
	Complex c;
	c.im=c1.im+c2.im;
	c.re=c1.re+c2.re;
	return c;
}

Complex mulComplex(Complex c1, Complex c2){
	Complex c;
	c.re=c1.re*c2.re-c1.im*c2.im;
	c.im=c1.re*c2.im+c1.im*c2.re;
	return c;
}

Complex double2Complex(double f){
	Complex c;
	c.im=0;c.re=f;
	return c;
}


Complex subComplex(Complex c1, Complex c2){
	Complex c=c2;
	c.re*=-1;c.im*=-1;
	return addComplex(c1,c);
}

Complex divComplex(Complex c1, Complex c2){
	Complex c=c2;
	double m=c2.re*c2.re+c2.im*c2.im;
	c.im*=-1;
	c=mulComplex(c1,c);
	c.im/=m; c.re/=m;
	return c;
}

double modComplex(Complex c){
	return sqrt(c.re*c.re+c.im*c.im);
}

double argComplex(Complex c){
	return 2*atan(c.im/(c.re+modComplex(c)));
}

int isequalComplex(Complex c1,Complex c2){
	if (c1.im==c2.im && c1.re==c2.re) return 1;
	return 0;
}

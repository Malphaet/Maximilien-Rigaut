/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* Rational Number Library     */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include "lib_rational.h"

/* ========= Defines ==========*/

/* ========= Functions ========*/

void printRational(Rational r){
	printf("%d/%d",r.num,r.den);
}

Rational addRational(Rational r1,Rational r2){
	int gc;
	Rational r;
	if (r1.num==0) return r=r2;
	if (r2.num==0) return r=r1;
	
	gc=gcd(r1.den,r2.den);
	
	r.num=r1.num*(r2.den/gc)+r2.num*(r1.den/gc);
	r.den=r1.den*r2.den/gc;
	
	return r;
}


Rational mulRational(Rational r1,Rational r2){
	Rational r;
	r.num=r1.num*r2.num;
	r.den=r1.den*r2.den;

	return r;
}

Rational int2Rational(int i){
	Rational r;
	r.num=i;
	r.den=1;
	return r;
}

double Rational2double(Rational r){
	return (float)r.num/r.den;
}

int gcd(int a,int b){
	int r=a;
	if (b<a) {r=b;b=a;}
	while (b!=0){
		r=b;
		b=a%b;
		a=r;
	}
	return a;
}


Rational subRational(Rational r1,Rational r2){
	Rational r=r2;
	r.num*=-1;
	return addRational(r1,r);
}

Rational divRational(Rational r1,Rational r2) {
	Rational r;
	r.num=r1.num*r2.den;
	r.den=r1.den*r2.num;
	
	return r;
}

Rational normalRational(Rational r1){
	Rational r=r1;
	int lcm;
	
	lcm=(r.num*r.den)/gcd(r.num,r.den);
	r.num/=lcm;
	r.den/=lcm;
	return r;
}

int isequalRational(Rational r1,Rational r2){
	if (r1.num*r2.den==r1.den*r2.num) return 1;
	return 0;
}

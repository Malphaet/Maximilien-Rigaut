/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* Model                       */
/*-----------------------------*/

#ifndef LIB_RATIONAL_H
#define LIB_RATIONAL_H

/* ========= Defines ==========*/

/* ========= Typedef ==========*/

typedef struct {
	int num; 
	int den;
} Rational;


/* ======== Prototype =========*/

void printRational(Rational r);
Rational addRational(Rational r1,Rational r2);
Rational mulRational(Rational r1,Rational r2);
Rational int2Rational(int i);
double Rational2double(Rational r);
int gcd(int a,int b);


Rational subRational(Rational r1,Rational r2);
Rational divRational(Rational r1,Rational r2);
Rational normalRational(Rational r1);
int isequalRational(Rational r1,Rational r2);


#endif

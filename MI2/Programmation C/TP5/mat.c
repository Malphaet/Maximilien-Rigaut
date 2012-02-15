/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <math.h>
#include "mat.h"
/* ========= Defines ==========*/

#define M(x) (a+(b-a)*(etapes+(x))/n)

/* ========= Functions ========*/

double integrale(double (*funct)(double), double a, double b, int n){
	int etapes=n;
	double res=0;
	while (etapes) res+=(b-a)*(*funct)(a+(((double)etapes--)*(b-a))/n)/n;
	return res;
}

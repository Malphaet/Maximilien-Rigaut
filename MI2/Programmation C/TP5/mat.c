/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <math.h>
#include "mat.h"
/* ========= Defines ==========*/

/* ========= Functions ========*/

double integrale(double (*funct)(double x),double a, double b, int n){
	int etapes=n;
	long int res=0;
	while (etapes) {
		res+=(*funct)(a+(b-a)*etapes--/n);
	}
	return res;
}

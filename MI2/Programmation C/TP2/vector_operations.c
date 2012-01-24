/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* Operations                  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "constants.h"

/* ========= Functions ========*/

TYPE_PRECISE norm2(TYPE_VECT vect[], int sizeV){
	TYPE_PRECISE sum=0;
	int i;
	for (i=0; i<sizeV;i++){
		sum+=vect[i]*vect[i];
	}
	return sqrt(sum);
}

TYPE_PRECISE norm1(TYPE_VECT vect[], int sizeV){
	TYPE_PRECISE sum=0;
	int i;
	for (i=0;i<sizeV;i++){
		sum+=fabs(vect[i]);
	}
	return sum;
}

TYPE_PRECISE normInfinite(TYPE_VECT vect[], int sizeV){
	int i,p;
	p=0;
	for (i=0;i<sizeV;i++){
		if (vect[p]<vect[i]) p=i;
	}
	return vect[p];
}

TYPE_PRECISE scalarProduct(TYPE_VECT vectA[], TYPE_VECT vectB[], int sizeV){
	int i;
	TYPE_PRECISE sum=0;
	for (i=0;i<sizeV; i++){
		sum+=vectA[i]*vectB[i];
	}
	return sum;
}

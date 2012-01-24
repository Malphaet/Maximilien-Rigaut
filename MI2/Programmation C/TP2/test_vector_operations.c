/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* TP2                         */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include "vector_operations.h"
#include "constants.h"

/* ========= Defines ==========*/

/* =========== Main ===========*/

int main(void){
	TYPE_VECT vect[5]={0,1,3,4,5};
	printf("Norme 1: %f, Norme 2= %f, Norme Inf=%f \n",norm1(vect,5),norm2(vect,5),normInfinite(vect,5));
	printf("V*V= %f, Norme2(V)^2=%f \n",scalarProduct(vect,vect,5),(TYPE_PRECISE) norm2(vect,5)*norm2(vect,5));
	return 0;
}

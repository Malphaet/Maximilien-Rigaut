/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include "lib_complex.h"

/* ========= Defines ==========*/

#define RPRINT(text,command) printf(text); printComplex(command); printf("\n");

/* =========== Main ===========*/

int main(void){
	Complex c1={13,37},c2={19,84};
	
	RPRINT("printComplex(c1) : ",c1);
	RPRINT("printComplex(c2) : ",c2);
	
	RPRINT("addComplex(r1,r2) : " , addComplex(c1,c2));
	RPRINT("mulComplex(r1,r2) : ", mulComplex(c1,c2));
	RPRINT("subComplex(c1,c2) : ",subComplex(c1,c2));
	RPRINT("divComplex(c1,c2) : ",divComplex(c1,c2));
	printf("argComplex(c1) : %f\n",argComplex(c1));
	printf("modComplex(c1) : %f\n",modComplex(c1));
	printf("isequalComplex(c1,c1) (c1,c2): %i %i\n",isequalComplex(c1,c1),isequalComplex(c1,c2));
	return 0;
}


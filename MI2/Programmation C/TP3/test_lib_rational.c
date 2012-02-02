/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include "lib_rational.h"

/* ========= Defines ==========*/

#define RPRINT(text,command) printf(text); printRational(command); printf("\n")

/* =========== Main ===========*/

int main(void){
	Rational r1={13,37},r2={19,84},r3={48,8};
	
	RPRINT("printRational(r1) : ",r1);
	RPRINT("printRational(r2) : ",r2);
	
	RPRINT("addRational(r1,r2) : " , addRational(r1,r2));
	RPRINT("mulRational(r1,r2) : ", mulRational(r1,r2));
	printf("Rational2double(r1) : "); printf("%f\n",Rational2double(r1));
	
	RPRINT("subRational(r1,r2) : " , subRational(r1,r2));
	RPRINT("divRational(r1,r2) : " , divRational(r1,r2));
	RPRINT("normalRational(4/2) : " , normalRational(r3));
	printf("isequalRational(r1,r2) : ") ; printf("%d\n",isequalRational(r1,r2));

	return 0;
}

/* ========= Functions ========*/


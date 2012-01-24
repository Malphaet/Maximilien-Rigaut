/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* TD2                         */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>

/* ========= Defines ==========*/
#define TYPEL long long int

/* ======== Prototype =========*/
TYPEL power(TYPEL x, int n);

/* =========== Main ===========*/

int main(void){
	printf("10^6=%lli",power(10,6));
	return 0;
}

/* ========= Functions ========*/

TYPEL power(TYPEL x, int n){
    TYPEL pow;
    if (!n) return 1;
    if (n%2) {
        pow=power(x,n/2);
        return pow*pow;
    }else{
        pow=power(x,(n-1)/2);
        return x*pow*pow;
    }
}

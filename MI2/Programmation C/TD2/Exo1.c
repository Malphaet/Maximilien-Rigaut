/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* TD2                         */
/*-----------------------------*/


#include <stdio.h>

int nb_identical(int A[],int B[],int a);

int main(void){
    int a=5;
    int A[5] = {12,13,45,42,42};
    int B[5] = {12,12,45,45,42};
	printf("Il y as %i occurences identiques\n",nb_identical(A,B,a));
	return 0;
}

int nb_identical(int A[], int B[], int a){
    int i,nb=0;
    for (i=0; i<a; i++){
        if (A[i]==B[i]) nb++;
    }
    return nb;
}

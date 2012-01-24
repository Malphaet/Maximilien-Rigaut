/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* TD2                         */
/*-----------------------------*/


#include <stdio.h>

int rang(int A[], int sizea);
int pp_elt(int A[], int sizea);

int main(void){
    int A[5]={32,2,4,8,16};
	printf("Valeur minimum du tableau: %i\n",pp_elt(A,5));
	return 0;
}

int pp_elt(int A[],int sizea){
    return A[rang(A,sizea)];
}

int rang(int A[], int sizea){
    int i=0;
    int rang=0;
    for (i=0;i<sizea;i++){
        if (A[i]<A[rang]) rang=i;
    }
    return rang;
}

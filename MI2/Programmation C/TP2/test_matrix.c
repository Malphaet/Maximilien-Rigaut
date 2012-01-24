/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* TP2                         */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "show_matrix.h"

/* ========= Defines ==========*/

#define MatM 2
#define MatN 3
#define MatP 4

/* =========== Main ===========*/

int main(void){
	int i,j;
		
	TYPE_MATRIX a;
	TYPE_MATRIX b;
	TYPE_MATRIX u;
	TYPE_MATRIX ab;
	TYPE_MATRIX ua;
	
	
	a = newMatrix(MatM,MatN);
	b = newMatrix(MatN,MatP);
	u = newMatrix(MatM,MatM);
	
	for (i=0;i<MatM;i++){
		for (j=0;j<MatN;j++){
			M(a,i,j)=1;
		}
	}
	
	for (i=0;i<MatN;i++){
		for (j=0;j<MatP;j++){
			M(b,i,j)=(j+i*(MatN));
		}
	}
	
	for (i=0; i<MatM;i++){
		for (j=0;j<MatM;j++){
			if (i==j) M(u,i,j)=1;
			else M(u,i,j)=0;
		}
	}
	

	printf("A:\n");
	showMatrix(a);
	printf("B:\n");
	showMatrix(b);
	printf("U:\n");
	showMatrix(u);

	ua=newMatrix(MatN,MatN);
	ua=multMatrix(u,a);
	ab=newMatrix(MatN,MatP);
	ab=multMatrix(a,b);
	
	printf("AB:\n");
	showMatrix(ab);
	printf("UA:\n");
	showMatrix(ua);
	return 0;
}

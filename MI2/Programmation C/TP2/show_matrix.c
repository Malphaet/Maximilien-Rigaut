/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* Test matrix                 */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "matrix.h"

/* ========= Functions ========*/

void showMatrix(struct matrix m){
	int i,j;
	for (i=0;i<m.rows;i++){
		printf("|");
		for (j=0;j<m.cols;j++){
			printf("%f ",M(m,i,j));
		}
		printf("|\n");
	}
	printf("\n");
}

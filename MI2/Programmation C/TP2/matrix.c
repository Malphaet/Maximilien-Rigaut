/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* Operations                  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "matrix.h"

/* ========= Functions ========*/

TYPE_MATRIX newMatrix(int rows,int cols){
	struct matrix m;
	m.cols=cols;
	m.rows=rows;
	m.t=(TYPE_PRECISE *)malloc(sizeof(TYPE_PRECISE)*cols*rows);
	return m;
}

TYPE_MATRIX multMatrix(TYPE_MATRIX a,TYPE_MATRIX b){
	int x,y,z;
	TYPE_MATRIX m;
	m=newMatrix(a.rows,b.cols);
	for (x=0;x<a.rows;x++){
		for (y=0;y<b.cols;y++){
			M(m,x,y)=0.0;
			for (z=0;z<a.cols;z++){
				M(m,x,y)+=M(a,x,z)*M(b,z,y);
			}
		}
	}
	return m;
}



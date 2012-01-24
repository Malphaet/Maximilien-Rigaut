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

TYPE_MATRIX newMatrix(int cols,int rows){
	struct matrix m;
	m.cols=cols;
	m.rows=rows;
	m.t=(TYPE_PRECISE *)malloc(sizeof(TYPE_PRECISE)*cols*rows);
	return m;
}

TYPE_MATRIX multMatrix(TYPE_MATRIX a,TYPE_MATRIX b){
	int x,y,z;
	TYPE_MATRIX m;
	m=newMatrix(a.rows,a.rows);
	for (x=0;x<a.rows;x++){
		for (y=0;y<b.cols;y++){
			M(m,x,y)=0.0;
			for (z=0;z<a.cols;z++){
				M(m,x,y)+=M(a,z,x)*M(b,y,z);
			}
		}
	}
	return m;
}



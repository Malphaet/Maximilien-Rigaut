/*--------------------------------*/
/* Copyleft Maximilien Rigaut     */
/* Operations                     */
/* Spetials thanks to Sather      */
/*--------------------------------*/

/* ========= Includes =========*/

#include "constants.h"
#include <stdlib.h>

/* ========= Defines ==========*/
#define M(m,x,y) m.t[x+y*m.cols] /* Acces to matrix */

/* ========= Typedef =========*/

struct matrix{
	int rows; /* Number of rows */
	int cols; /* Number of cols */
	TYPE_PRECISE *t; /* Table */
};

/* ======== Prototype =========*/

TYPE_MATRIX newMatrix(int cols, int rows);
TYPE_MATRIX multMatrix(TYPE_MATRIX a,TYPE_MATRIX b);

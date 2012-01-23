/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* Show double tables          */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include "constants.h"

/* ======== Prototype =========*/

void show_vector(TYPE_VECT t[],int sizeT);

/* ========= Functions ========*/

void show_vector(TYPE_VECT t[],int sizeT){
    int i;
    printf("(");
    for (i=0;i<sizeT;i++){
        printf("%f",t[i]);
        if (i<sizeT-1) printf(",");
    }
    printf(")\n");
}

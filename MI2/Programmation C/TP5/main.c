/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "str.h"
#include "mat.h"
#include "utils.h"
#include "main.h"

/* =========== Main ===========*/

int main(void){
	char *c="Mooooo";
	char *c2;
	OUT("%p: %s\n",c,c);
	c2=strcopy(c);
	OUT("%p: %s\n",c2,c2);
	c2=int2string(120445);
	OUT("%s\n",c2);
	OUT("%f\n",integrale(f,0,1,10000));
	return 0;

}

/* ========= Functions ========*/
double f(double x){
	return sin(x)-cos(x);
}

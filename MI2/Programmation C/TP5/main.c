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
	char *rangerChar="Alice\nBob\nZorglub\nMetatron\nUriel\nZelel\n";
	OUT("%s\n","############ Nouvelle execution ##########");
	OUT("%s\n","======== Avant copie ======");
	OUT("%p: ",c); OUT("%s\n",c);
	c2=strcopy(c);
	OUT("%s\n","======== Apres copie ======");
	OUT("%p: ",c2); OUT("%s\n",c2);
	OUT("%s\n","======== Conversion en chaine ======");
	c2=int2string(120445);
	OUT("%s\n",c2);
	OUT("%s\n","======== Integrale ======");
	OUT("%f\n",integrale(f,0,1,10000));

	OUT("%s\n","======== Tableau avant rangement ======");
	OUT("%s",rangerChar);
	OUT("%s\n","======== Apres rangement ======");
	OUT("%s",ranger(rangerChar));
	return 0;
}

/* ========= Functions ========*/
double f(double x){
	return sin(x)-cos(x);
}

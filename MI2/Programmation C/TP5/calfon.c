/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "utils.h"
#include "str.h"

#define NB_FUNCT 4

/* =========== Main ===========*/

int main(int nbargs, char ** kwargs){
	int i=nbargs; /*Strictement inutile, mais pas de warnings a la compilation*/
	double (*t_funct[NB_FUNCT])(double)={sin,cos,log,sqrt};
	char t_names[NB_FUNCT][5]={"sin","cos","log","sqrt"};
	TEST(kwargs[1]);TEST(kwargs[2]);
	for (i=0;i<NB_FUNCT;i++)
		if (!strcmp(t_names[i],kwargs[1]))
			{
				OUT("%f\n",(*t_funct[i])(string2double(kwargs[2])));
				return 0;
			}
	OUT("%s: La fonction n'existe pas !\n",kwargs[1]);
	return EXIT_FAILURE;
}


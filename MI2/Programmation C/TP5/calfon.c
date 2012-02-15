/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "utils.h"
#include "str.h"

#define NB_FUNCT 4

/* =========== Main ===========*/

int main(int nbargs, char ** kwargs){
	int i;
	double (*t_funct[NB_FUNCT])(double x)={sin,cos,log,sqrt};
	char t_names[NB_FUNCT][5]={"sin","cos","log","sqrt"};
	
	for (i=0;i<NB_FUNCT;i++)
		if (!strcmp(t_names[i],kwargs[1]))
			OUT("%f\n",(*t_funct[i])(string2double(kwargs[2])));
	return 0;
}


/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/* =========== Main ===========*/

int main(int nargs, char **argv){
	int nb=atoi(argv[1]);
	while (nb--) OUT("%s\n",getenv("USER"));
	return 0*nargs;
}

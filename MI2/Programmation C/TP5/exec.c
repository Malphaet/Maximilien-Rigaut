/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/* =========== Main ===========*/

int main(int nargs, char **argv){
	char *user=getenv("USER");
	char *nb_c=argv[1];
	int nb_i;
	TEST(user); TEST(nb_c);
	nb_i=atoi(nb_c);
	while (nb_i--) OUT("%s\n",user);
	return 0*nargs;
}

/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/* ========= Defines ==========*/

/* ========= Functions ========*/
char *strcopy(char *c){
	char *c2=malloc(sizeof(c));
	char *cr=c2;
	TEST(c2);	
	while (*c) *c2++=*c++;
	return cr;
}

char *int2string(int i){
	int b=10,res,t;
	char *c;
	while (t<i) t*=10;
	c=malloc(t*sizeof(char));
	t=0;
	while (i){
		res=i%b;
		i/=b;
		*(c+t++)='0'+res;
	}
	return c;
}



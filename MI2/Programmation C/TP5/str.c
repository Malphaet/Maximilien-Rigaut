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
	int b=10,res,t=1,s=0;
	char *c;
	while (t<i) {t*=10;s++;};
	c=malloc(t*sizeof(char));
	while (i){
		res=i%b;
		i/=b;
		*(c+--s)='0'+res;
	}
	return c;
}

double string2double(char *str){
	double *nb,*dec,*p;
	int t=1;
	nb=malloc(sizeof(double));TEST(nb);*nb=0;
	dec=malloc(sizeof(double));TEST(dec);*dec=0;
	p=NULL;
	while (*str){
		if (*str=='.'||*str==',') {p=nb; nb=dec; dec=p; t=1;str++;}		
		*nb=t**nb+(double) (*str++-'0'); /* Trusting blindly user is not such a good idea but meh ... */
		t*=10;
	}
	if (p==NULL) return *nb;
	return (*dec+*nb/t);
}

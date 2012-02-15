/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "str.h"

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

char *ranger(char *texte){
	int t_table=0;
	char *chaine=texte;
	char **table=malloc(sizeof(char*));
	TEST(table);
	while (*texte){
		if (*texte=='\n') {
			table=realloc(table,++t_table*sizeof(char*)); TEST(table);
			*(table+t_table-1)=chaine;
			chaine=++texte; TEST(chaine);
		}
		texte++;
	}
	printf("%d\n",comp("Mooo\n","Mooo\nioiiooio"));
	qsort(texte,t_table,t_table,comp);
	return "Moo";
}

int comp(const void *C1,const void *C2){
	/*Empty string is equal to any string... why not ?*/
	char *c1=(char*)C1,*c2=(char*)C2;
	while (*c1!='\n'||*c2!='\n') if (*c1++!=*c2++) return *(c1-1)-*(c2-1);
	return 0;
}

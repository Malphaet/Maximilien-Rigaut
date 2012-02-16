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
	/* Ranger renvoie la liste triee dans l'ordre inverse a comp, et je m'en fiche. */
	int t_table=0;
	int j=0;
	char *ret; /* On ne sait si on peut modifier la chaine. */
	char *pret;
	char *chaine=texte;
	char **table=malloc(sizeof(char*));
	
	TEST(table);

	while (*texte){
		if (*texte=='\n') {
			table=realloc(table,++t_table*sizeof(char*)); TEST(table);
			*(table+t_table-1)=chaine;
			chaine=++texte; TEST(chaine);
		}
		j++;
		texte++;
	}
	ret=malloc((1+j)*sizeof(char)); TEST(ret);
	qsort(table,t_table,sizeof(char*),comp);
	pret=ret;
	
	j=0;
	while(t_table--) {
		while(*(*(table+t_table)+j)!='\n') *pret++=*(*(table+t_table)+j++);
		*pret++='\n'; j=0;
	}
	return ret;
}

static int comp(void const *C1,void const *C2){
	char * const *c1 = C1;
	char * const *c2 = C2;
	int i=0,j=0;

	while (*(*c1+i)!='\n'||*(*c2+j)!='\n') if (*(*c1+i++)!=*(*c2+j++)) return *(*c2+i-1)-*(*c1+j-1);
	return 0;
}

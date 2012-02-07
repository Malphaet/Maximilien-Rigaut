/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include "lib_string.h"
/* ========= Defines ==========*/

/* =========== Main ===========*/

int main(void){
	char m1[]="Ramadane";
	char m2[]="Meriem";
	char m3[]="Charly";
	char m4[]="Mamadou";
	char m5[]="Thomas";
	char m6[]="Stephane";
	char m7[]="Aboucadar Sidy";
	char m8[]="Etc.";
	char *table[8];
	table[0]=m1;
	table[1]=m2;
	table[2]=m3;
	table[3]=m4;
	table[4]=m5;
	table[5]=m6;
	table[6]=m7;
	table[7]=m8;
	
	printf("=> Array before sorting <=\n");
	print_table_strings(table,8);
	
	/*printf("%d\n",string_length_cmp(m7,m1));*/
	
	melting_sort(table,8);
	printf("=> Static array of pointers melting <=\n");
	print_table_strings(table,8);
	
	return 0;
}

/* ========= Functions ========*/
/*---------------------*/
/*     Sorting      */
/*---------------------*/

/* Switch in place */
void string_flip(char *s){
	int i=0; char t;
	int size=string_length(s);
	while (i<size/2){
		t=*(s+i); *(s+i)=*(s+size-i-1); *(s+size-i-1)=t;i++;
	}
}

/* Recursive melting sort */
void melting_sort(char **t1,int N){
	char **t2;
	if (N<=1) return;
	t2=(char **)(t1+N/2);
	
	melting_sort(t1,N/2);
	melting_sort(t2,N-N/2);
	
	melt(t1,t2,N/2,N-N/2);
}

/* Static array of pointer Melting */
void melt(char **t1,char **t2,int N1,int N2){
	int i=0,j=0;
	char *p; /* Melting pointer */
	while (i<N1 && j<N2){
		switch (string_cmp( *(t1+i),  *(t2+j) )){
			case 0:
				i++;
				break;
			case 1:
				p=*(t1+i); *(t1+i)=*(t2+j); *(t2+j)=p;
				i++;
				break;
			case -1:
				j++;
				break;
		}
	}
	
}

/*---------------------*/
/*     Comparison      */
/*---------------------*/

int string_length(char *s){
	return !*s?0:1+string_length(s+1);
}

int string_cmp(char *s1,char *s2){	
	if (!*s1 && !*s2) return 0;
	if (*s1==*s2) return string_cmp(s1+1,s2+1);
	return *s1>*s2?1:-1;
}

int string_length_cmp(char *s1,char *s2){
	return *s1||!*s2?*s1-*s2?*s1>*s2?1:-1:0:string_length_cmp(s1+1,s2+1);
}

/*---------------------*/
/*   Printing thingy   */
/*---------------------*/

void print_table_strings(char **t,int N){
	int i=-1;
	while (N-++i) print_string(*(t+(char)i));
}

void print_string(char *s){
	int i=0;
	while (*(s+i)) printf("%c",*(s+++i));
	printf("\n");
}

void print_slice(char *s,int N){
	int i=0;
	while (i<N) printf("%c",*(s+++i));
	printf("\n");
}

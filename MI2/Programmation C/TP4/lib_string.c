/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "lib_string.h"
/* ========= Defines ==========*/
#define LENGTH_SORT 1

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
/*     Sorting         */
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

/* Array of pointer Melting */
void melt(char **t1,char **t2,int N1,int N2){
	char **t=(char**) malloc(sizeof(char)*(N1));
	int i=0,j=0;
	/* Save first table */
	while (i<N1) {*(t+i)=*(t1+i);i++;} i=0; 
	while (i<N1 && j<N2){
		#if LENGTH_SORT==0
		if (string_cmp(*(t+i),*(t2+j))<0){
		#else
		if (!string_length_cmp(*(t+i),*(t2+j))?string_cmp(*(t+i),*(t2+j))<0:string_length_cmp(*(t+i),*(t2+j))>0){
		#endif
			*(t1+i+j)=*(t+i);
			i++;
		}else{
			*(t1+i+j)=*(t2+j);
			j++;
		}
	}
	/* Copy the rest of the longer array */
	while (N2>j){ *(t1+i+j)=*(t2+j); j++; }
	while (N1>i){ *(t1+i+j)=*(t+i); i++; }
	/*free(t);*/
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
	return !*s1||!*s2?*s1-*s2?*s1>*s2?1:-1:0:string_length_cmp(s1+1,s2+1);
}

/*---------------------*/
/*   Printing thingy   */
/*---------------------*/

void print_table_strings(char **t,int N){
	int i=-1;
	while (N-++i) print_string(*(t+i));
}

void print_string(char *s){
	int i=0;
	while (*(s+i)) printf("%c",*(s+++i));
	printf("\n");
}

/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include "lib_string.h"
/* ========= Defines ==========*/

/* =========== Main ===========*/

int main(void){
	char t[]="This is a sentence";
	char m1[]="HUMANS";
	char m2[]="AFTER";
	char m3[]="ALL";
	
	char *table[3];
	table[0]=m1;table[1]=m2;table[2]=m3;
	
	
	printf("%d\n",string_length("This sentence is 31 letter long"));
	printf("%d\n",string_cmp("ffa","ffe"));
	print_string(t); string_flip(t); print_string(t);
	
	print_table_strings(table,3);
	return 0;
}

/* ========= Functions ========*/

int string_length(char *s){
	if (*s=='\0') return 0;
	return 1+string_length(s+1);
}

/*Do a copy and change pointers*/
/*void string_flip(char *s){
	int i=0;
	char *t= (char *) malloc(sizeof(s));
	if (*t==NULL) return;
	while (*(s+i)!=0){
		*t=*(s+i)
		i+=1;
	}
	return;
}*/

/*switch in place */
void string_flip(char *s){
	int i=0; char t;
	int size=string_length(s);
	while (i<size/2){
		t=*(s+i); *(s+i)=*(s+size-i-1); *(s+size-i-1)=t;i++;
	}
}

int string_cmp(char *s1,char *s2){	
	if (!*s1 && !*s2) return 0;
	if (*s1==*s2) return string_cmp(s1+1,s2+1);
	return *s1>*s2?1:-1;
}

void print_table_strings(char **t,int N){
	int i=-1;
	while (N-++i) print_string(*(t+(char)i));
}

void print_string(char *s){
	int i=0;
	while (*(s+i)) printf("%c",*(s+++i));
	printf("\n");
}

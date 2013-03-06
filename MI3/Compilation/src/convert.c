/*
 * convert.c
 * 
 * Copyright 2013 Maximilien Rigaut <max[dot]rigaut[at]orange.fr>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"
#include <string.h>
#include "lexeme.h"

char*convertToUpperCase(const char *sPtr){
	int i,len=strlen(sPtr);
	char*new=malloc(sizeof(char*)*(len+1));
	if (!new) OUT("Malloc error");
	
	for(i=0;i<len;i++) new[i]=toupper(sPtr[i]);
	
	return new;
}

/*
char*translateStrange(const char *txt){
	int i,len=strlen(sPtr);
	char*new=malloc(sizeof(char*)*(len*4+1));
	if (!new) OUT("Malloc error");
	
	for(i=0;i<len;i++) {
		new[i]=toupper(sPtr[i]);
	
	return new;
}
*/

int main(int argc, char **argv){
	FILE*f;
	int i;
	char*new;
	if (argc<2){printf("Error: not evough parameters\n");return -1;}
	f=fopen(argv[1],"w+");
	if (f==NULL) {	printf("Error : can't open %s\n",argv[1]);return -1;}
	
	fprintf(f,"#ifndef SYMBOL_TABLE_H\n");
	fprintf(f,"#define SYMBOL_TABLE_H\n");
	fprintf(f,"\n");
	
	i=0;
	fprintf(f,"#define SDOT_DOT %d\n",VAL_SYMBOLS(i++));
	fprintf(f,"#define SDOT_EQL %d\n",VAL_SYMBOLS(i++));
	fprintf(f,"#define SINF_EQL %d\n",VAL_SYMBOLS(i++));
	fprintf(f,"#define SDIF_THN %d\n",VAL_SYMBOLS(i++));
	fprintf(f,"#define SSUP_EQL %d\n",VAL_SYMBOLS(i++));
	fprintf(f,"#define SIDENT   %d\n",VAL_KEYWORDS(SIZE_KEYWORDS+1));
	fprintf(f,"#define SNUMERAL %d\n",VAL_KEYWORDS(SIZE_KEYWORDS+2));
	for(i=0;i<SIZE_KEYWORDS;i++) {	
		new=convertToUpperCase(KEYWORDS[i]);
		fprintf(f,"#define S%s %d\n",new,VAL_KEYWORDS(i));
		free(new);
	}

	fprintf(f,"#endif");	
	return 0;
}


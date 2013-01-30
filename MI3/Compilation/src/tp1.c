/*
 * tp1.c
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */



/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "lexeme.h"

/* ========= Defines ==========*/
#define WHERE		printf("In %s line %d (%s)\n",__FILE__,__LINE__,__func__)
#define ERROR(msg)	{WHERE; perror(msg);printf("\n");exit(EXIT_FAILURE);}
#define OUT(msg)	{WHERE; fprintf(stderr,msg);fprintf(stderr,"\n");exit(EXIT_FAILURE);}

/* =========== Main ===========*/

char yytext[256];
FILE *yyin;

char VAR[256];

int main(int argc, char **argv) {
	int uniteCourante;
	if (argc<2) OUT("Not enough arguments");
	
	yyin = fopen(argv[1], "r");
	if(yyin == NULL) ERROR("Impossible d'ouvrir le fichier");
	
	uniteCourante = yylex();
	while (uniteCourante != 0) {
		printf("(%s, %d)\n", yytext, uniteCourante);
		uniteCourante = yylex();
	}
	return 0;
}

int is_symbol(const char chr){
	int i;
	char nc;
	for(i=0;i<SIZE_ONESYMS;i++)
		if (ONESYMS[i][0]==chr) {
			if (chr==':' && (nc=getc(yyin))=='=') {
				ungetc(chr,yyin);
				return 0;
			}
			if (chr=='.' && (nc=getc(yyin))=='.') {
				ungetc(chr,yyin);
				return 0;
			}
			return i+257;
		}
	return 0;
}


int yylex(){
	int val,nbchar;
	char chr=getc(yyin);
	if ((val=is_symbol(chr))) {
		yytext[0]=chr;
		yytext[1]=0;
		return val;
	}
	/* Add chars, compare */
	return 0;
}


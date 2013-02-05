/*
 * lexeme.c
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
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "lexeme.h"
#include "lexicana.h"

/* =========== Functions ===========*/

int is_single_symbol(const char chr){
	int i;
	char nc;
	for(i=0;i<SIZE_ONESYMS;i++)
		if (ONESYMS[i][0]==chr) {
			if (chr==':') if ((nc=getc(yyin))=='=') {
				ungetc(chr,yyin);
				WHERE;
				return -1;
			}
			if (chr=='.') if ((nc=getc(yyin))=='.') {
				ungetc(chr,yyin);
				return -1;
			}
			return VAL_ONESYMS(i);
		}
	return 0;
}

int is_symbol(const char*str){
	int i,j;
	for(i=0;i<SIZE_SYMBOLS;i++){
		j=strcmp(SYMBOLS[i],str);
		if (j==0) return VAL_SYMBOLS(i);
		if (j>0) break;
	}
	
	for(i=0;i<SIZE_KEYWORDS;i++){
		j=strcmp(KEYWORDS[i],str);
		if (j==0) return VAL_KEYWORDS(i);
		if (j>0) break;
	}
	return 0;
}

int yylex(){
	int val,nbchar=0;
	char chr;
	
	do {chr=getc(yyin);}
	while (isspace(chr));
	
	yytext[0]=chr;
	if (chr==EOF) return 0;
	
	/* Either it's a single character symbol*/
	if ((val=is_single_symbol(chr))>0) {
		yytext[1]=0;
		return val;
	}
	
	/* Either it's a multiple character symbol */
	while ((chr=getc(yyin))!=EOF){ 
		if (isspace(chr)) {
			yytext[++nbchar]=0;
			return is_symbol(yytext);
		}
		if ((val<0)&(ispunct(chr))) {
			yytext[++nbchar]=chr;
			yytext[++nbchar]=0;
			return is_symbol(yytext);
		}
		yytext[++nbchar]=chr;
	}
	
	/* Else it's alphanum */
	
	return 0;
}


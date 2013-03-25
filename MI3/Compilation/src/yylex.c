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
 * 
 */

/* ========= Includes =========*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "lexeme.h"
#include "identifiers.h"
#include "yylex.h"

/* =========== Defines ===========*/


#define DOUBLE_SYMBOL_CHECK(b) if((nc)==(b)) {ungetc(nc,yyin);char_number--; return-1;}
#define ADD_LINE if (chr=='\n') {line_number++;char_number=0;} else char_number++;
#define DEL_LINE(c) do {ungetc(c,yyin);\
						if (!char_number) {char_number=char_number_old;line_number--;}\
						else char_number--;}\
					 while (0);

int commenting=0;

/* =========== Functions ===========*/

int is_single_symbol(const char chr){
	int i,char_number_old=char_number;
	char nc;
	
	/* Check if it's a double symbol */
	nc=get_next_char();
	switch(chr){
		case ':': DOUBLE_SYMBOL_CHECK('=') break;
		case '.': DOUBLE_SYMBOL_CHECK('.') break;
		case '<': DOUBLE_SYMBOL_CHECK('=') DOUBLE_SYMBOL_CHECK('>') break;
		case '>': DOUBLE_SYMBOL_CHECK('=') break;
		default: 
			DEL_LINE(nc);
			for(i=0;i<SIZE_ONESYMS;i++) if (ONESYMS[i][0]==chr) return VAL_ONESYMS(chr);
			return 0;
	}
	DEL_LINE(nc);
	return VAL_ONESYMS(chr);
}

int is_symbol(const char*str){
	int i,j;
	for(i=0;i<SIZE_SYMBOLS;i++){
		j=strcmp(SYMBOLS[i],str);
		if (j==0) return VAL_SYMBOLS(i);
		if (j>0) break;
	}
	return 0;
}

int is_reserved(const char*str){
	int i,j;
	for(i=0;i<SIZE_KEYWORDS;i++){
		j=strcmp(KEYWORDS[i],str);
		if (j==0) return VAL_KEYWORDS(i);
		if (j>0) break;
	}
	return 0;
}

char get_next_char(){
	char chr;
	if ((chr=getc(yyin))!='{') {
		ADD_LINE;
		return chr;
	}
	
	do {
		chr=getc(yyin);
		ADD_LINE;
	} while ((chr!='}')||(chr==EOF));
	
	return get_next_char();
}
	
int yylex(){
	int val=0,char_number_old;
	char chr;
	word_size=0;
	/** Strip leading spaces */
	do {chr=get_next_char();}
	while (isspace(chr));
	
	
	/** Putting first character in the table */
	yytext[0]=chr;
	if (chr==EOF) return 0;
	
	/** Check for symbol presence */
	if ((val=is_single_symbol(chr))>0) { /* Either it's a single character symbol*/
		yytext[++word_size]=0;
		return val;
	} else if (val<0){ /* This one is expecting one more character */
		chr=get_next_char();
		yytext[++word_size]=chr;
		yytext[++word_size]=0;
		return is_symbol(yytext);
	}
	
	/* Either it's a multiple character symbol */
	char_number_old=char_number;
	while ((chr=get_next_char())!=EOF){ 
		if (isspace(chr)||ispunct(chr)) {
			yytext[++word_size]=0;
			DEL_LINE(chr);
			if ((val=is_reserved(yytext))) return val; /**@todo Update this to get clever */
			else break;
		}
		yytext[++word_size]=chr;
		char_number_old=char_number;
	}
	word_size--;
	/* Else it's an alphanumeric variable or constant */
	char_number_old=char_number;
	while ((chr=get_next_char())!=EOF){		
		if (isspace(chr)||((chr!='_')&&(ispunct(chr)))) {
			DEL_LINE(chr);
			yytext[++word_size]=0; word_size--;
			/*for(i=0;i<word_size;i++)*/ if(!isdigit(yytext[0])) return SIDENT;
			return SNUMERAL;
		}
		yytext[++word_size]=chr; char_number_old=char_number;
	}
	
	return 0;
}


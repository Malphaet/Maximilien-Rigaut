/*
 * lexeme.h
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


/* ======== Constants =========*/
#ifndef LEXEME_H
#define LEXEME_H

const char *ONESYMS[]={
	"(", ")", "*", "+",",", "-", ".", "/", ":", ";", "<", "=", ">", "[", "]"
};

const char *SYMBOLS[]={
	"..", ":=", "<=", ">="
};
const char *KEYWORDS[]={
	"array", "begin", "boolean", "do", "else", 
	"end", "false", "function", "if", "integer",
	"mod", "of", "procedure", "program", "read", 
	"then", "true", "var", "while"
};

#define SIZE_CHAR 256
const int SIZE_ONESYMS=sizeof(ONESYMS)/sizeof(char*);
const int SIZE_SYMBOLS=sizeof(SYMBOLS)/sizeof(char*);
const int SIZE_KEYWORDS=sizeof(KEYWORDS)/sizeof(char*);

#define VAL_ONESYMS(index) index
#define VAL_SYMBOLS(index) SIZE_CHAR+1+index
#define VAL_KEYWORDS(index) SIZE_CHAR+1+SIZE_SYMBOLS+1+index

/*
#define VAL_CHAR(index) index
#define VAL_ONESYMS(index) SIZE_CHAR+1+index
#define VAL_SYMBOLS(index) SIZE_CHAR+1+SIZE_ONESYMS+1+index
#define VAL_KEYWORDS(index) SIZE_CHAR+1+SIZE_ONESYMS+1+SIZE_SYMBOLS+1+index
*/

#endif

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

#define VAL_CHAR(index) index
#define VAL_ONESYMS(index) SIZE_CHAR+1+index
#define VAL_SYMBOLS(index) SIZE_CHAR+1+SIZE_ONESYMS+1+index
#define VAL_KEYWORDS(index) SIZE_CHAR+1+SIZE_ONESYMS+1+SIZE_SYMBOLS+1+index


/* UPGRADE IT */
#define ARRAY 		VAL_KEYWORDS( 1)
#define BEGIN 		VAL_KEYWORDS( 2)
#define BOOLEAN 	VAL_KEYWORDS( 3)
#define DO			VAL_KEYWORDS( 4)
#define ELSE 		VAL_KEYWORDS( 5)
#define END		VAL_KEYWORDS( 6)
#define NO			VAL_KEYWORDS( 7)
#define FUNCTION	VAL_KEYWORDS( 8)
#define IF			VAL_KEYWORDS( 9)
#define INTEGER	VAL_KEYWORDS(10)
#define MOD		VAL_KEYWORDS(11)
#define OF			VAL_KEYWORDS(12)
#define PROCEDURE	VAL_KEYWORDS(13)
#define PROGRAM	VAL_KEYWORDS(14)
#define READ		VAL_KEYWORDS(15)
#define THEN		VAL_KEYWORDS(16)
#define YES		VAL_KEYWORDS(17)
#define VAR		VAL_KEYWORDS(18)
#define WHILE		VAL_KEYWORDS(19)

#define IDENT 		WHILE+1

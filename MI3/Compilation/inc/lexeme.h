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
	"(", ")", "*", "+", "-", ".", "/", ":", ";", "<", "=", ">", "[", "]"
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

/* UUUUUUPGRADE IT */

#define ARRAY 		1
#define BEGIN 		2
#define BOOLEAN 	3
#define DO			4
#define ELSE 		5
#define END		6
#define FALSE		7
#define FUNCTION	8
#define IF			9
#define INTEGER	10
#define MOD		11
#define OF			12
#define PROCEDURE	13
#define PROGRAM	14
#define READ		15
#define THEN		16
#define TRUE		17
#define VAR		18
#define WHILE		19

#define IDENT 500

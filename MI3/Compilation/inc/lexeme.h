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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#ifndef LEXEME
#define LEXEME
/* ========= Includes =========*/

/* ========= Defines ==========*/

/* ========= Typedef ==========*/


char *ONESYMS[]={
	"(", ")", "*", "+", "-", ".", "/", ":", ";", "<", "=", ">", "[", "]"
};

char *SYMBOLS[]={
	"..", ":=", "<=", ">="
};
char *KEYWORDS[]={
	"array of", "begin", "boolean", "do", "else", "end", "false", "function", "if", "integer", "mod", "procedure", "program", "read", "then", "true", "var", "while", "while"
};

#define SIZE_CHAR 256
int SIZE_ONESYMS=sizeof(ONESYMS)/sizeof(char*);
int SIZE_SYMBOLS=sizeof(SYMBOLS)/sizeof(char*);
int SIZE_KEYWORDS=sizeof(KEYWORDS)/sizeof(char*);

#define VAL_CHAR(index) index
#define VAL_ONESYMS(index) SIZE_CHAR+1+index
#define VAL_SYMBOLS(index) SIZE_CHAR+1+SIZE_ONESYMS+1+index
#define VAL_KEYWORDS(index) SIZE_CHAR+1+SIZE_ONESYMS+1+SIZE_SYMBOLS+1+index
/* ======== Prototype =========*/

int yylex();


/*
enum type{
	INTEGER,
	BOOLEAN,
	ARRAY OF,
	MOD,
	BEGIN,
	END,
	IF,
	THEN,
	ELSE,
	WHILE,
	DO,
	FUNCTION,
	PROCEDURE,
	WHILE,
	READ,
	PROGRAM,
	VAR
};*/

/*
typedef struct t_lexm{
	enum type type;
	char*val;
}*/
/*
char TYPES[][]={
	"begin",
}*/
#endif

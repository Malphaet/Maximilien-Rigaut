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

/** @file lexeme.h List of all recognised lexemes */
/* ======== Constants =========*/
#ifndef LEXEME_H
#define LEXEME_H

const char *ONESYMS[]={
	"(", ")", "*", "+",",", "-", ".", "/", ":", ";", "<", "=", ">", "[", "]"
}; /**< One character symbols */

const char *SYMBOLS[]={
	"..", ":=", "<=", "<>", ">="
}; /**< Two character symbols */
const char *KEYWORDS[]={
	"and", "array", "begin", "boolean", "do", "else", 
	"end", "false", "function", "if", "integer",
	"mod", "not", "of", "or", "procedure", "program", 
	"read","real","then", "true", "var", "while","write"
};/**< All keywords recognised as lexemes */

#define SIZE_CHAR 256										/**< The number of char symbols */
const int SIZE_ONESYMS=sizeof(ONESYMS)/sizeof(char*);	/**< The size of the one-symbol table */
const int SIZE_SYMBOLS=sizeof(SYMBOLS)/sizeof(char*);	/**< The size of the two-symbols table */
const int SIZE_KEYWORDS=sizeof(KEYWORDS)/sizeof(char*);	/**< The size of the keyboard table */

#define VAL_ONESYMS(index) index							/**< The id of the one symbol at given index */
#define VAL_SYMBOLS(index) SIZE_CHAR+1+index				/**< The id of the symbol at given index */
#define VAL_KEYWORDS(index) SIZE_CHAR+1+SIZE_SYMBOLS+1+index /**< The id of the keyword at given index */

#endif

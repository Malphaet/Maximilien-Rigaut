/*
 * yyparse.c
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
 */

#include <stdio.h>
#include <stdlib.h>
#include "identifiers.h"
#include "yylex.h"
#include "yyparse.h"
#include "utils.h"

//extern char yytext[512];
//extern char *file_in_progress;
//extern unsigned int line_number,char_number;
//FILE *yyin;

/************* Rules */

#define PLCC_SYNTAX_ERROR(expected) PLCC_ERROR("Syntax error : Expected %s found '%s' <%d>",expected,yytext,uc);
//#define PLCC_GET(exp_id,exp) if ((uc=yylex())!=exp_id) PLCC_SYNTAX_ERROR(exp);
#define PLCC_NEW  (uc=yylex())

void Programme(){
	//Program -> PROGRAM ID ';' Body '.'
	
	char *s = "program";
	markupOpen(s);
	
	if (PLCC_NEW!=SIDENT) PLCC_SYNTAX_ERROR("identifier");
	markupLeaf("id",yytext);
	
	if (PLCC_NEW!=';') PLCC_SYNTAX_ERROR("';'");
	PLCC_NEW; Corps();
	
	if (PLCC_NEW!='.') PLCC_SYNTAX_ERROR("'.'");
	markupClose(s);
}

void Corps(){
	char *s = "body";
	markupOpen(s);
	
	if (uc==SVAR){
		markupOpen("var");
		PLCC_NEW; ListeDeclVar();
		if (PLCC_NEW!=';') PLCC_SYNTAX_ERROR("';'");
		PLCC_NEW;
		markupClose("var");
	}
	while (uc==SPROCEDURE){
		//DeclProcFun();
		//if (PLCC_NEW!=';') PLCC_SYNTAX_ERROR("';'");
		PLCC_NEW;
	}
	//BlocInstr();
	
	markupClose(s);
}

void ListeDeclVar(){
	//while (uc==SID){
		//while (uc==SID){
		//}
	//}
}
/*
	+Programme -> PROGRAM ID ';' Corps '.'
	Corps ->[ VAR ListeDeclVar ';' ] { DeclProcFun ';' } BlocInstr
	ListeDeclVar -> DeclVar{ ';' DeclVar }
DeclVar -> ID { ',' ID } ':' Type
Type -> INTEGER | BOOLEAN | ARRAY '[' NUMERAL '..' NUMERAL ']' OF Type
DeclProcFun -> DeclProcedure | DeclFunction 
DeclProcedure -> PROCEDURE ID [ '(' ListeDeclVar ')' ] ; Corps 
DeclFunction -> FUNCTION ID '(' ListeDeclVar ')' ':' Type ';' Corps 

Instruction -> AffectInstr | AppelProcedure | IfInstr | WhileInstr | BlocInstr | Empty 
AffectInstr -> Variable AFFECT Expression 
AppelProcedure -> ID [ '(' ParameterList ')' ] 
AppelFunction -> ID '(' ListeParam ')'
ListeParam -> Expression [ ',' Expression ] 
IfInstr -> IF Expression THEN Instruction [ ELSE Instruction ] 
WhileInstr -> WHILE Expression DO Instruction 
BlocInstr -> BEGIN Instruction { ';' Instruction } END 

Expression -> Simpleexpression [ Relation Simpleexpression ]
Relation -> '<' | '=' | '>' | INFEG | DIFF | SUPEG 
Simpleexpression -> Facteur [ OpAdd Simpleexpression ] 
OpAdd -> '+' | '-' | OR
Facteur -> [ RelationUnaire ] Predicat [ OpMult Facteur ] 
RelationUnaire -> '-' | NOT
OpMult -> '*' | DIV | MOD | AND
Predicat -> AppelFunction | NUMERAL | Variable | '(' Expression ')' 
Variable -> ID [ '[' Expression ']' ] 
*/

/********** Affichage */

void markupOpen(char *s){
	printf("<%s>\n",s);
}

void markupClose(char *s){
	printf("</%s>\n",s);
}

void markupLeaf(char *s, char *val){
	printf("<%s>%s</%s>\n",s , val, s);
}

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

extern char yytext[512];
FILE *yyin;

/************* Rules */

void programme(){
  /*
  Programme -> PROGRAM ID ';' Corps '.'
  */
  char *s = "program";
  markupOpen(s);
  if ((uc=yylex())!=IDENT) PLCC_ERROR("Syntax error : Expected identifier");
  markupLeaf("id",yytext);
  if ((uc=yylex())!=';') PLCC_ERROR("Syntax error : Expected ; found %s",yytext);
  markupOpen(s);
}

/*
  Programme -> PROGRAM ID ';' Corps '.'
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

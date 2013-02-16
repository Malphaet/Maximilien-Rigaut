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

#define PLCC_SYNTAX_ERROR(expected,got,id) PLCC_ERROR("Syntax error : Expected %s. Found '%s' <%d>",expected,got,id);
#define PLCC_GET(exp_id,exp) if ((uc=yylex())!=exp_id) PLCC_SYNTAX_ERROR(exp,yytext,uc);

void Programme(){
    /*
    Program -> PROGRAM ID ';' Body '.'
    */
    char *s = "program";
    markupOpen(s);
    
    PLCC_GET(SIDENT,"identifier");
    markupLeaf("id",yytext);
    PLCC_GET(';',"';'");
    
    Corps();
    PLCC_GET('.',"'.'");
    
    
    markupClose(s);
}

void Corps(){
    char *s = "body";
    markupOpen(s);
    
    PLCC_GET(SVAR,"var");
    markupOpen("var");
    
    //ListeDeclVar();
    
    markupClose("var");
    PLCC_GET(';',"';'");
    
    markupClose(s);
}

void ListeDeclVar(){
    
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

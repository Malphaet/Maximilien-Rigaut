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
#include <string.h>
#include "identifiers.h"
#include "yylex.h"
#include "yyparse.h"
#include "utils.h"

//extern char yytext[512];
//extern char *file_in_progress;
//extern unsigned int line_number,char_number;
//FILE *yyin;

/************* Rules */
unsigned int ident_level=0;

#define PLCC_SYNTAX_ERROR(expected) {WHERE; PLCC_ERROR("Syntax error : Expected %s found '%s' <%d>",expected,yytext,uc);}
#define PLCC_NOT_IMPLEMENTED 		{WHERE; PLCC_ERROR("Not implemented error: %s <%d>",yytext,uc);}
#define PLCC_IF(exp_id) if (uc==exp_id)
#define PLCC_IFNOT(exp_id,exp) if (uc!=exp_id) PLCC_SYNTAX_ERROR(exp)
#define PLCC_NEW  (uc=yylex())

void Programme(){
	//Program -> PROGRAM ID ';' Body '.'
	
	PLCC_IFNOT(SPROGRAM,"program")
	markupOpen("program"); PLCC_NEW; 
	
	PLCC_IFNOT(SIDENT,"identifier") 
	markupLeaf("identifier",yytext); PLCC_NEW; 
	
	PLCC_IFNOT(';',"';'");
	PLCC_NEW; Corps(); 
	
	PLCC_IFNOT('.',"'.'");
	markupClose("program");
}

//! Corps ->[ VAR ListeDeclVar ';' ] { DeclProcFun ';' } BlocInstr
void Corps(){
	markupOpen("body");
	PLCC_IF(SVAR){
		PLCC_NEW;
		ListeDeclVar();
	}
	while (uc==SPROCEDURE||uc==SFUNCTION){
		DeclProcFun();
		PLCC_NEW;
	}
	BlocInstr();
	
	markupClose("body");
}

//! ListeDeclVar -> DeclVar{ ';' DeclVar }
void ListeDeclVar(){
	while (uc==SIDENT){
		markupOpen("var");
		DeclVar(); //PLCC_NEW;
		if (uc!=';') {return;}
		PLCC_NEW;
		markupClose("var");
	}
}

//! DeclVar -> ID { ',' ID } ':' Type
void DeclVar(){
	while (1){
		PLCC_IFNOT(SIDENT,"identifier");
		markupLeaf("id",yytext); PLCC_NEW; 
		
		PLCC_IF(':') break;
		else PLCC_IFNOT(',',"','");
		
		PLCC_NEW;
	}
	PLCC_NEW; Type();
}

//! Type -> INTEGER | BOOLEAN | ARRAY '[' NUMERAL '..' NUMERAL ']' OF Type
void Type(){
	PLCC_IF(SINTEGER) markupLeaf("type",yytext);
	else PLCC_IF(SBOOLEAN) markupLeaf("type",yytext);
	else PLCC_IF(SARRAY){
		PLCC_NEW; PLCC_IFNOT('[',"'['");
		markupOpen("array");
		
		PLCC_NEW; PLCC_IFNOT(SNUMERAL,"number");
		markupLeaf("from",yytext);
		PLCC_NEW; PLCC_IFNOT(SDOT_DOT,"'..'");
		PLCC_NEW; PLCC_IFNOT(SNUMERAL,"number");
		markupLeaf("to",yytext);
		PLCC_NEW; PLCC_IFNOT(']',"']'");
		PLCC_NEW; PLCC_IFNOT(SOF,"of");
		markupOpen("of");
		PLCC_NEW; Type();
		markupClose("of");
		markupClose("array");
	} else PLCC_SYNTAX_ERROR("type");
	PLCC_NEW;
}

//! DeclProcFun -> DeclProcedure | DeclFunction
void DeclProcFun(){
	if (uc==SPROCEDURE) DeclProcedure();
	else if (uc==SFUNCTION) DeclFunction();
	else PLCC_SYNTAX_ERROR("procedure or function");
	
}

//! DeclProcedure -> PROCEDURE ID [ '(' ListeDeclVar ')' ] ; Corps
void DeclProcedure(){
	PLCC_IFNOT(SPROCEDURE,"procedure");
	markupOpen("procedure");
	
	PLCC_NEW; PLCC_IFNOT(SIDENT,"identifier");
	markupLeaf("id",yytext);
	
	PLCC_NEW; PLCC_IF('(') {
		ListeDeclVar();
		PLCC_NEW; PLCC_IFNOT(')',"')'");
	}
	
	PLCC_NEW; PLCC_IFNOT(';',"';'");
	Corps();
}

//! DeclFunction -> FUNCTION ID '(' ListeDeclVar ')' ':' Type ';' Corps
void DeclFunction(){
	PLCC_IFNOT(SFUNCTION,"function");
	markupOpen("function");
	
	PLCC_NEW; PLCC_IFNOT(SIDENT,"id");
	markupLeaf("id",yytext);
	PLCC_NEW; PLCC_IFNOT('(',"'('");
	PLCC_NEW; ListeDeclVar();
	
	PLCC_IFNOT(')',"')'");
	
	PLCC_NEW; PLCC_IFNOT(':',"':'");
	
	markupOpen("return");
	PLCC_NEW; Type();
	markupClose("return");
	
	PLCC_IFNOT(';',"';'");
	PLCC_NEW; Corps();
	markupClose("function");
}

//! BlocInstr -> BEGIN Instruction { ';' Instruction } ';' END
void BlocInstr(){
	PLCC_IFNOT(SBEGIN,"begin");
	markupOpen("block_instr");
	do {
		Instruction(SEND);
	} while (uc==';');
	PLCC_IFNOT(SEND,"end");
	
	markupClose("block_instr");
}

//! Instruction -> AffectInstr | AppelProcedure | IfInstr | WhileInstr | BlocInstr | Empty 
//! All of them will be treated in one call
void Instruction(int next_id){
	char inst_name[512];
	markupOpen("instruction");
	PLCC_IF(next_id) return; 	// Empty instruction
	PLCC_IF(';') return; 		// Empty also
	
	PLCC_IF(SIDENT) {			// Either it's a procedure or an affect
		strcpy(inst_name,yytext);
		PLCC_NEW;
		PLCC_IF(';') {			//!< AppelProcedure -> ID [ '(' ListeParam ')' ]
			markupOpen("procedure");
			markupLeaf("id",inst_name);
			PLCC_NEW;
			markupClose("procedure");
		} else PLCC_IF('('){	//!< AppelProcedure -> ID [ '(' ListeParam ')' ]
			markupOpen("procedure");
			markupLeaf("id",inst_name);
			PLCC_NEW; ListeParam();
			PLCC_IFNOT(')',"')'");
			markupClose("procedure");
		} else PLCC_IF('['){	//!< Variable -> ID [ '[' Expression ']' ] 
			//Variable
		} else PLCC_IF(SDOT_EQL){//!< Variable -> ID [ '[' Expression ']' ] 
			//Variable
		} else PLCC_SYNTAX_ERROR("procedure or affect");
	} else PLCC_IF(SIF){ //!< IfInstr -> IF Expression THEN Instruction [ ELSE Instruction ] 
		markupOpen("if_instr");
		
		PLCC_NOT_IMPLEMENTED;
	} else PLCC_IF(SWHILE){
		PLCC_NOT_IMPLEMENTED;
	} else PLCC_IF(SBEGIN){
		BlocInstr();
		PLCC_NOT_IMPLEMENTED;
	} else PLCC_SYNTAX_ERROR("instruction");
	
	PLCC_NEW;
}

void Expression(){
	PLCC_NOT_IMPLEMENTED;
}

void ListeParam(){
	PLCC_NOT_IMPLEMENTED;
}
/*
	+ Programme -> PROGRAM ID ';' Corps '.'
	+ Corps ->[ VAR ListeDeclVar ';' ] { DeclProcFun ';' } BlocInstr
	* ListeDeclVar -> DeclVar{ ';' DeclVar }
	* DeclVar -> ID { ',' ID } ':' Type
	* Type -> INTEGER | BOOLEAN | ARRAY '[' NUMERAL '..' NUMERAL ']' OF Type
	+ DeclProcFun -> DeclProcedure | DeclFunction 
	* DeclProcedure -> PROCEDURE ID [ '(' ListeDeclVar ')' ] ; Corps 
	+ DeclFunction -> FUNCTION ID '(' ListeDeclVar ')' ':' Type ';' Corps 
	
	Instruction -> AffectInstr | AppelProcedure | IfInstr | WhileInstr | BlocInstr | Empty 
	AffectInstr -> Variable AFFECT Expression 
	AppelProcedure -> ID [ '(' ListeParam ')' ]
	ListeParam -> Expression { ',' Expression } | Empty
	IfInstr -> IF Expression THEN Instruction [ ELSE Instruction ] 
	WhileInstr -> WHILE Expression DO Instruction 
	BlocInstr -> BEGIN Instruction { ';' Instruction } ';' END 

AppelFunction -> ID '(' ListeParam ')'

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
	unsigned int i;
	for(i=0;i<ident_level;i++) printf(" ");
	printf("<%s>\n",s);
	
	ident_level+=2;
}

void markupClose(char *s){
	unsigned int i;
	ident_level-=2;
	
	for(i=0;i<ident_level;i++) printf(" ");
	printf("</%s>\n",s);
}

void markupLeaf(char *s, char *val){
	unsigned int i;
	for(i=0;i<ident_level;i++) printf(" ");
	printf("<%s>%s</%s>\n",s , val, s);
}

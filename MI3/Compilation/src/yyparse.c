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
int ident_level=0;

#define PLCC_SYNTAX_ERROR(expected) {WHERE; PLCC_ERROR("Syntax error : Expected %s found '%s' <%d>",expected,yytext,uc);}
#define PLCC_NOT_IMPLEMENTED 		{WHERE; PLCC_ERROR("Not implemented error: %s <%d>",yytext,uc);}
#define PLCC_UNTESTED				{WHERE; PLCC_WARNING("The current section is untested/untrusted\n");}
#define PLCC_ILL_IMPLEMENED		{WHERE; PLCC_WARNING("The current section isn't fully implemented yet\n");}
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
		if (uc!=';') {markupClose("var"); return;}
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
	PLCC_UNTESTED;
	if (uc==SPROCEDURE) DeclProcedure();
	else if (uc==SFUNCTION) DeclFunction();
	else PLCC_SYNTAX_ERROR("procedure or function");
}

//! DeclProcedure -> PROCEDURE ID [ '(' ListeDeclVar ')' ] ; Corps
void DeclProcedure(){
	PLCC_UNTESTED;
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
	PLCC_UNTESTED;
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
		PLCC_NEW; Instruction(SEND);
	} while (uc==';');
	PLCC_IFNOT(SEND,"end"); PLCC_NEW;
	markupClose("block_instr");
}

//! Instruction -> AffectInstr | AppelProcedure | IfInstr | WhileInstr | BlocInstr | Empty 
//! All options will be treated without subroutine call
void Instruction(int next_id){
	char inst_name[512];
	
	PLCC_IF(next_id) return; // Empty instruction
	PLCC_IF(';') return; 		// Empty also
	
	markupOpen("instruction");
	PLCC_IF(SIDENT) {			// AppelProcedure | AffectInstr
		strcpy(inst_name,yytext); PLCC_NEW;
		PLCC_IF(';') {			//!< AppelProcedure -> ID @todo Upgrade for lame pascal specification
			markupOpen("procedure");
			markupLeaf("id",inst_name);
			PLCC_NEW;
			markupClose("procedure");
			//markupClose("instruction");
		} else PLCC_IF('('){	//!< AppelProcedure -> ID '(' ListeParam ')'
			markupOpen("procedure");
			markupLeaf("id",inst_name);
			PLCC_NEW; ListeParam();
			PLCC_IFNOT(')',"')'"); PLCC_NEW;
			markupClose("procedure");
		} else PLCC_IF('['){	//!	AffectInstr -> Variable AFFECT Expression
			//!< Variable -> ID '[' Expression ']'
			markupOpen("affect");
			markupOpen("table");
				markupLeaf("id",inst_name);
				markupOpen("at");
				PLCC_NEW; Expression();
				PLCC_IFNOT(']',"']'"); PLCC_NEW;
				markupClose("at");
			markupClose("table");
			
			PLCC_IFNOT(SDOT_EQL,"':='");
			
			markupOpen("value");
				PLCC_NEW; Expression();
			markupClose("value");
			markupClose("affect");
			
		} else PLCC_IF(SDOT_EQL){ //!	AffectInstr -> Variable AFFECT Expression
			//!< Variable -> ID
			markupOpen("affect");
			markupLeaf("var",inst_name);
			
			PLCC_IFNOT(SDOT_EQL,"':='");
			markupOpen("value");
				PLCC_NEW; Expression();
			markupClose("value");
			markupClose("affect");
			
		} else PLCC_SYNTAX_ERROR("procedure or affect");
	} else PLCC_IF(SIF){ //!< IfInstr -> IF Expression THEN Instruction [ ELSE Instruction ] 
		markupOpen("if_instr");
			markupOpen("if");
				PLCC_IFNOT(SIF,"if"); PLCC_NEW;
				Expression();
			markupClose("if");
			markupOpen("then");
				PLCC_IFNOT(STHEN,"then"); PLCC_NEW;
				Instruction(SELSE);
				PLCC_IF(';') PLCC_NEW;
			markupClose("then");
		PLCC_IF(SELSE) {
			markupOpen("else");
				PLCC_NEW;
				Instruction(';');
			markupClose("else");
		}
		markupClose("if_instr");
	} else PLCC_IF(SWHILE){ //!< WhileInstr -> WHILE Expression DO Instruction
		markupOpen("while_instr");
			markupOpen("while");
				PLCC_IFNOT(SWHILE,"while"); PLCC_NEW;
				Expression();
				PLCC_IFNOT(SDO,"do"); PLCC_NEW;
			markupClose("while");
			markupOpen("do");
				Instruction(SEND);
			markupClose("do");
		markupClose("while_instr");
	} else PLCC_IF(SBEGIN){ //!< BlocInstr -> BEGIN Instruction { ';' Instruction } ';' END 
		BlocInstr();
	} else PLCC_SYNTAX_ERROR("instruction");
	
	markupClose("instruction");
}

//! ListeParam -> Expression { ',' Expression } | Empty
void ListeParam(){
	PLCC_IF(')') return;
	markupOpen("liste_params");
	while (1){
		markupOpen("value");
		Expression();
		markupClose("value");
		PLCC_IF(',') PLCC_NEW;
		else break;
	}
	markupClose("liste_params");
}

//! Simpleexpression [ Relation Simpleexpression ]
void Expression(){
	markupOpen("expression");
	SimpleExpression();
	if(uc=='<'||uc=='='||uc=='>'||uc==SINF_EQL||uc==SSUP_EQL||uc==SDIF_THN) {
		Relation();
		SimpleExpression();
	}
	markupClose("expression");
}

//! SimpleExpression -> Facteur [ OpAdd SimpleExpression ] 
void SimpleExpression(){
	markupOpen("simple_expression");
	Facteur(); 
	if (uc=='+' || uc=='-' || uc==SOR) {OpAdd(); SimpleExpression();}
	markupClose("simple_expression");
}

//! Facteur -> [ RelationUnaire ] Predicat [ OpMult Facteur ] 
void Facteur(){
	markupOpen("factor");
	if (uc=='-'||uc==SNOT)	RelationUnaire();
	Predicat();
	if (uc=='*'||uc==SMOD||uc==SAND||uc=='/') {OpMult();Facteur();}
	markupClose("factor");
}

//! Predicat -> AppelFunction | NUMERAL | Variable | '(' Expression ')' 
void Predicat(){
	char inst_name[512];
	markupOpen("predicat");
	PLCC_IF(SNUMERAL) {
		markupLeaf("numeral",yytext);
	} else PLCC_IF(SIDENT){
		strcpy(inst_name,yytext); PLCC_NEW;
		PLCC_IF('('){			//!< AppelFunction -> ID '(' ListeParam ')'
			markupLeaf("function",inst_name);
			PLCC_NEW; ListeParam();
			PLCC_IFNOT(')',"')'");
		} else PLCC_IF('['){ 	//!< Variable -> ID '[' Expression ']'
			markupOpen("table");
			markupLeaf("id",inst_name);
			markupOpen("at");
			PLCC_NEW; Expression();
			PLCC_IFNOT(']',"']'");
			markupClose("table");
			markupClose("at");
		} else {				//!< Variable -> ID
			markupLeaf("variable",inst_name);  
			markupClose("predicat");
			return;
		}
	} else PLCC_IF('('){		//< '(' Expression ')'
			PLCC_NEW; Expression();
			PLCC_IFNOT(')',"')'");
	} else PLCC_SYNTAX_ERROR("identifier, numeral or '('");
	
	PLCC_NEW;
	markupClose("predicat");
}

//! OpMult -> '*' | DIV | MOD | AND
void OpMult(){
	PLCC_IF('*'){
		markupLeaf("operation","*");
	} else PLCC_IF('/'){
		markupLeaf("operation","/");
	} else PLCC_IF(SMOD){
		markupLeaf("operation","mod");
	} else PLCC_IF(SAND){
		markupLeaf("operation","and");
	} else PLCC_SYNTAX_ERROR("'*','/', 'mod' or 'and'");
	PLCC_NEW;
}

//! OpAdd -> '+' | '-' | OR
void OpAdd(){
	PLCC_IF('+'){
		markupLeaf("operation","+");
	} else PLCC_IF('-'){
		markupLeaf("operation","-");
	} else PLCC_IF(SOR){
		markupLeaf("operation","or");
	} else PLCC_SYNTAX_ERROR("'+','-' or 'or'");
	PLCC_NEW;
}

//! Relation -> '<' | '=' | '>' | INFEG | DIFF | SUPEG 
void Relation(){
	PLCC_IF('<'){
		markupLeaf("relation","'<'");
	} else PLCC_IF('='){
		markupLeaf("relation","'='");
	}else PLCC_IF('>'){
		markupLeaf("relation","'>'");
	}else PLCC_IF(SINF_EQL){
		markupLeaf("relation","'<='");
	}else PLCC_IF(SSUP_EQL){
		markupLeaf("relation","'>='");
	}else PLCC_IF(SDIF_THN){
		markupLeaf("relation","'!='");
	}else PLCC_SYNTAX_ERROR("relation");
	PLCC_NEW;
}

//! RelationUnaire -> '-' | NOT
void RelationUnaire(){
	PLCC_IF('-'){
		markupLeaf("relation_unaire","'-'");
	} else PLCC_IF(SNOT){
		markupLeaf("relation_unaire","not");
	} else PLCC_SYNTAX_ERROR("relation");
	
	PLCC_NEW;
}
//! AppelFunction -> ID '(' ListeParam ')'
void AppelFunction(){
	PLCC_NOT_IMPLEMENTED;
}

/*
	* Programme -> PROGRAM ID ';' Corps '.'
	+ Corps ->[ VAR ListeDeclVar ';' ] { DeclProcFun ';' } BlocInstr
	* ListeDeclVar -> DeclVar{ ';' DeclVar }
	* DeclVar -> ID { ',' ID } ':' Type
	* Type -> INTEGER | BOOLEAN | ARRAY '[' NUMERAL '..' NUMERAL ']' OF Type
	+ DeclProcFun -> DeclProcedure | DeclFunction 
	* DeclProcedure -> PROCEDURE ID [ '(' ListeDeclVar ')' ] ; Corps 
	+ DeclFunction -> FUNCTION ID '(' ListeDeclVar ')' ':' Type ';' Corps 
	
	+ BlocInstr -> BEGIN Instruction { ';' Instruction } ';' END 
	- Instruction -> AffectInstr | AppelProcedure | IfInstr | WhileInstr | BlocInstr | Empty 
	- AffectInstr -> Variable AFFECT Expression 
	+ AppelProcedure -> ID [ '(' ListeParam ')' ]
	- IfInstr -> IF Expression THEN Instruction [ ELSE Instruction ] 
	+ WhileInstr -> WHILE Expression DO Instruction 
	

	+ ListeParam -> Expression { ',' Expression } | Empty
	AppelFunction -> ID '(' ListeParam ')'

	+ Expression -> Simpleexpression [ Relation SimpleExpression ]
	+ Relation -> '<' | '=' | '>' | INFEG | DIFF | SUPEG 
	+ SimpleExpression -> Facteur [ OpAdd SimpleExpression ] 
	+ OpAdd -> '+' | '-' | OR
	+ Facteur -> [ RelationUnaire ] Predicat [ OpMult Facteur ] 
	+ RelationUnaire -> '-' | NOT
	+ OpMult -> '*' | DIV | MOD | AND
	+ Predicat -> AppelFunction | NUMERAL | Variable | '(' Expression ')' 
	X Variable -> ID [ '[' Expression ']' ] 
*/

/********** Affichage */

void markupOpen(char *s){
	int i;
	for(i=0;i<ident_level;i++) printf(" ");
	printf("\033[1;30m<%s>\033[0m\n",s);
	
	ident_level+=2;
}

void markupClose(char *s){
	int i;
	ident_level-=2;
	
	for(i=0;i<ident_level;i++) printf(" ");
	printf("\033[1;30m</%s>\033[0m\n",s);
}

void markupLeaf(char *s, char *val){
	int i;
	for(i=0;i<ident_level;i++) printf(" ");
	
	printf("\033[1;31m<%s>\033[32m%s\033[1;31m</%s>\033[0m\n",s , val, s);
}

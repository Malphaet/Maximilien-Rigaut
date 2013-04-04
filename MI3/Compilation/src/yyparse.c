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
#include "dico.h"

/************* Rules */
int ident_level=0;



//! Program -> PROGRAM ID ';' Body '.'
n_prog *Programme(){
	n_prog*prog;
	
	PLCC_IFNOT(SPROGRAM,"program");PLCC_NEW; 
	PLCC_IFNOT(SIDENT,"identifier");PLCC_NEW; 
	/*yytext: program name*/
	
	PLCC_IFNOT(';',"';'");
	PLCC_NEW; prog=Corps(); 
	PLCC_IFNOT('.',"'.'");
	
	return prog;
}

//! Corps ->[ VAR ListeDeclVar ';' ] { DeclProcFun ';' } BlocInstr
n_prog *Corps(){
	n_l_dec*var=NULL;
	n_l_fun_dec*tete=NULL,*queue;
	
	n_fun_dec*fun=NULL;
	n_instr*inst=NULL;
	
	PLCC_IF(SVAR){
		PLCC_NEW;
		var=ListeDeclVar();
	}
	if (uc==SPROCEDURE||uc==SFUNCTION) {
		queue=tete=cree_n_l_fun_dec(NULL,NULL);
		while (1){
			fun=DeclProcFun(); queue->tete=fun;
			PLCC_NEW;
			if (uc==SPROCEDURE||uc==SFUNCTION) queue->queue=cree_n_l_fun_dec(NULL,NULL);
			else break;
		}
	}
	inst=BlocInstr();
	
	return cree_n_prog(var,tete,inst);
}

//! ListeDeclVar -> DeclVar{ ';' DeclVar }
n_l_dec* ListeDeclVar(){
	n_l_dec*decl=NULL;
	while (uc==SIDENT){
		decl=DeclVar(decl);
		if (uc!=';') break;
		PLCC_NEW; 
	}
	return decl;
}

//! DeclVar -> ID { ',' ID } ':' Type
n_l_dec*DeclVar(n_l_dec*next){
	n_l_dec*tete,*queue;
	char*var; n_type*ty,*tt=malloc(sizeof(n_type)); CHECK_PTR(tt);
	tete=queue=cree_n_l_dec(NULL,NULL);
	
	while (1){
		PLCC_IFNOT(SIDENT,"identifier");
		var=malloc(sizeof(char)*(word_size+3)); CHECK_PTR(var);
		strcpy(var,yytext);
		queue->tete=cree_n_dec_var(var,tt);
		PLCC_NEW; PLCC_IF(':') break;
		else PLCC_IFNOT(',',"','");
		queue->queue=cree_n_l_dec(NULL,NULL);
		queue=queue->queue; PLCC_NEW;
	}
	
	queue->queue=next;
	PLCC_NEW; ty=Type();*tt=*ty;
	free(ty); return tete;
}

//! Type -> INTEGER | BOOLEAN | ARRAY '[' NUMERAL '..' NUMERAL ']' OF Type
n_type*Type(){
	n_type*t=NULL; int d,f;
	
	PLCC_IF(SINTEGER) t=cree_n_type_int();
	else PLCC_IF(SBOOLEAN) t=cree_n_type_bool();
	else PLCC_IF(SARRAY){
		PLCC_NEW; PLCC_IFNOT('[',"'['");
		PLCC_NEW; PLCC_IFNOT(SNUMERAL,"number");
		d=atoi(yytext);
		PLCC_NEW; PLCC_IFNOT(SDOT_DOT,"'..'");
		PLCC_NEW; PLCC_IFNOT(SNUMERAL,"number");
		f=atoi(yytext);
		PLCC_NEW; PLCC_IFNOT(']',"']'");
		PLCC_NEW; PLCC_IFNOT(SOF,"of");
		PLCC_NEW; t=Type();
		t=cree_n_type_array(t,d,f);
	} else PLCC_SYNTAX_ERROR("type");
	
	PLCC_NEW; return t;
}

//! DeclProcFun -> DeclProcedure | DeclFunction
n_fun_dec *DeclProcFun(){
	n_fun_dec*decl=NULL;
	
	if (uc==SPROCEDURE) decl=DeclProcedure();
	else if (uc==SFUNCTION) decl=DeclFunction();
	else PLCC_SYNTAX_ERROR("procedure or function");
	return decl;
	
}

//! DeclProcedure -> PROCEDURE ID [ '(' ListeDeclVar ')' ] ; Corps
n_fun_dec*DeclProcedure(){
	char *nom;
	n_type *t=NULL;
	n_l_dec *param=NULL,*variables=NULL;
	n_prog*corps;
	
	PLCC_IFNOT(SPROCEDURE,"procedure");
	
	entreefonction();	
	PLCC_NEW; PLCC_IFNOT(SIDENT,"identifier");
	markupLeaf("id",yytext);
	nom=NULL;
	PLCC_NEW; PLCC_IF('(') {
		param=ListeDeclVar();
		PLCC_NEW; PLCC_IFNOT(')',"')'");
	}
	
	PLCC_NEW; PLCC_IFNOT(';',"';'");
	corps=Corps();
	variables=corps->variables;
	sortiefonction();
	return cree_n_dec_fonc(nom,t,param,variables,corps);
}

//! DeclFunction -> FUNCTION ID '(' ListeDeclVar ')' ':' Type ';' Corps
n_fun_dec*DeclFunction(){
	char *nom;	n_type *t=NULL;
	n_l_dec *param=NULL,*variables=NULL;
	n_prog *corps;
	
	PLCC_IFNOT(SFUNCTION,"function");
	PLCC_NEW; PLCC_IFNOT(SIDENT,"id");
	
	entreefonction();
	nom=malloc((3+word_size)*sizeof(char)); CHECK_PTR(nom);
	strcpy(nom,yytext);
	PLCC_NEW; PLCC_IFNOT('(',"'('");
	PLCC_NEW; variables=ListeDeclVar();
	PLCC_IFNOT(')',"')'");
	
	PLCC_NEW; PLCC_IFNOT(':',"':'");
	PLCC_NEW; t=Type();
	PLCC_IFNOT(';',"';'");
	PLCC_NEW; corps=Corps();
	
	sortiefonction();
	return cree_n_dec_fonc(nom,t,param,variables,corps);
}

//! BlocInstr -> BEGIN Instruction { ';' Instruction } ';' END
n_instr *BlocInstr(){
	n_l_instr*tete,*queue;n_instr*inst;
	PLCC_IFNOT(SBEGIN,"begin");
	
	tete=queue=cree_n_l_instr(NULL,NULL);
	while(1) {
		PLCC_NEW; inst=Instruction(SEND);
		queue->tete=inst;
		PLCC_IF(';') {
			queue->queue=cree_n_l_instr(NULL,NULL);
			queue=queue->queue;
		} else break;
	}
	PLCC_IFNOT(SEND,"end"); PLCC_NEW;
	return cree_n_instr_bloc(tete);
}

//! Instruction -> AffectInstr | AppelProcedure | IfInstr | WhileInstr | BlocInstr | Empty 
//! All options will be treated without subroutine call
n_instr*Instruction(int next_id){
	n_instr*instr,*instr2=NULL;
	n_var*var; n_exp*exp;
	n_l_exp*param;
	char*inst_name=malloc(sizeof(char)*(word_size+3)); CHECK_PTR(inst_name);
	
	PLCC_IF(next_id) return cree_n_instr_vide(); 	// Empty instruction
	PLCC_IF(';') return cree_n_instr_vide(); 		// Empty also
	
	PLCC_IF(SIDENT) {			// AppelProcedure | AffectInstr
		strcpy(inst_name,yytext); PLCC_NEW;
		PLCC_IF(';') {			//!< AppelProcedure -> ID @todo Upgrade for lame pascal specification
			PLCC_NEW;
			instr=cree_n_instr_appel(cree_n_appel(inst_name,cree_n_l_exp(NULL,NULL)));
		} else PLCC_IF('('){	//!< AppelProcedure -> ID '(' ListeParam ')'
			PLCC_NEW; param=ListeParam();
			PLCC_IFNOT(')',"')'"); PLCC_NEW;
			instr=cree_n_instr_appel(cree_n_appel(inst_name,param));
		} else PLCC_IF('['){	//!	AffectInstr -> Variable AFFECT Expression
			//!< Variable -> ID '[' Expression ']'
			PLCC_NEW; exp=Expression();
			
			var=cree_n_var_indicee(inst_name,exp);
			PLCC_IFNOT(']',"']'"); PLCC_NEW;
			PLCC_IFNOT(SDOT_EQL,"':='");
			PLCC_NEW; exp=Expression();
			
			instr=cree_n_instr_affect(var,exp);
		} else PLCC_IF(SDOT_EQL){ //!	AffectInstr -> Variable AFFECT Expression
			//!< Variable -> ID
			var=cree_n_var_simple(inst_name);
			PLCC_IFNOT(SDOT_EQL,"':='");
			PLCC_NEW; exp=Expression();
			instr=cree_n_instr_affect(var,exp);
		} else PLCC_SYNTAX_ERROR("procedure or affect");
	} else PLCC_IF(SIF){ //!< IfInstr -> IF Expression THEN Instruction [ ELSE Instruction ] 
		PLCC_IFNOT(SIF,"if"); PLCC_NEW;
		exp=Expression();
		PLCC_IFNOT(STHEN,"then"); PLCC_NEW;
		instr=Instruction(SELSE);
		PLCC_IF(';') PLCC_NEW;
		PLCC_IF(SELSE) {PLCC_NEW;instr2=Instruction(';');}
		instr=cree_n_instr_si(exp,instr,instr2);
	} else PLCC_IF(SWHILE){ //!< WhileInstr -> WHILE Expression DO Instruction
		PLCC_IFNOT(SWHILE,"while"); PLCC_NEW;
		exp=Expression();
		PLCC_IFNOT(SDO,"do"); PLCC_NEW;
		instr=Instruction(SEND);
		instr=cree_n_instr_tantque(exp,instr);
	} else PLCC_IF(SBEGIN){ //!< BlocInstr -> BEGIN Instruction { ';' Instruction } ';' END 
		instr=BlocInstr();
	} else PLCC_IF(SWRITE){
		PLCC_NEW; PLCC_IFNOT('(',"'('");
		PLCC_NEW; exp=Expression();
		instr=cree_n_instr_ecrire(exp);
		PLCC_NEW;
	} else PLCC_SYNTAX_ERROR("instruction");
	
	return instr;
}

//! ListeParam -> Expression { ',' Expression } | Empty
n_l_exp*ListeParam(){
	n_l_exp*curr,*tete,*queue;
	PLCC_IF(')') return NULL;
	curr=tete=cree_n_l_exp(Expression(),NULL);
	
	PLCC_IF(',') PLCC_NEW;
	else goto listeparamEnd;
	while (1){
		queue=cree_n_l_exp(Expression(),NULL);
		curr->queue=queue;
		
		PLCC_IF(',') PLCC_NEW;
		else goto listeparamEnd;
	}
	
	listeparamEnd: return tete;
}

//! Expression -> Simpleexpression [ Relation Simpleexpression ]
n_exp*Expression(){
	n_exp*exp1,*exp2;operation op;
	exp1=SimpleExpression();
	if(uc=='<'||uc=='='||uc=='>'||uc==SINF_EQL||uc==SSUP_EQL||uc==SDIF_THN) {
		op=Relation(); exp2=SimpleExpression();
		exp1=cree_n_exp_op(op,exp1,exp2);
	}
	return exp1;
}

//! SimpleExpression -> Facteur [ OpAdd SimpleExpression ] 
n_exp*SimpleExpression(){
	n_exp*exp1,*exp2; operation op;
	exp1=Facteur(); 
	if (uc=='+' || uc=='-' || uc==SOR) {
		op=OpAdd();
		exp2=SimpleExpression();
		exp1=cree_n_exp_op(op,exp1,exp2);
	}
	return exp1;
}

//! Facteur -> [ RelationUnaire ] Predicat [ OpMult Facteur ] 
n_exp*Facteur(){
	n_exp *exp1,*exp2;operation op;
	if (uc=='-'||uc==SNOT)	{
		op=RelationUnaire();
		exp1=Predicat();
		exp1=cree_n_exp_op(op,exp1,NULL);
	} else exp1=Predicat();
	
	if (uc=='*'||uc==SMOD||uc==SAND||uc=='/') {
		op=OpMult();
		exp2=Facteur();
		exp1=cree_n_exp_op(op,exp1,exp2);
	}
	return exp1;
}

//! Predicat -> AppelFunction | NUMERAL | Variable | '(' Expression ')' | read()
n_exp*Predicat(){
	n_exp*exp; n_l_exp*args;
	char*inst_name=malloc(sizeof(char)*(word_size+3)); CHECK_PTR(inst_name);
	
	PLCC_IF(SNUMERAL) {
		exp=cree_n_exp_entier(atoi(yytext));
	} else PLCC_IF(SIDENT){
		strcpy(inst_name,yytext); PLCC_NEW;
		PLCC_IF('('){			//!< AppelFunction -> ID '(' ListeParam ')'
			PLCC_NEW; args=ListeParam();
			PLCC_IFNOT(')',"')'");
			exp=cree_n_exp_appel(cree_n_appel(inst_name,args));
		} else PLCC_IF('['){ 	//!< Variable -> ID '[' Expression ']'
			PLCC_NEW; exp=Expression();
			PLCC_IFNOT(']',"']'");
			exp=cree_n_exp_var(cree_n_var_indicee(inst_name,exp));
		} else {				//!< Variable -> ID
			return cree_n_exp_var(cree_n_var_simple(inst_name));;
		}
	} else PLCC_IF('('){		//< '(' Expression ')'
		PLCC_NEW; exp=Expression();
		PLCC_IFNOT(')',"')'");
	} else PLCC_IF(SREAD) {
		exp=cree_n_exp_lire();
		PLCC_NEW; PLCC_IFNOT('(',"'('");
		PLCC_NEW; PLCC_IFNOT(')',"')'");
	} else PLCC_SYNTAX_ERROR("identifier, numeral or '('");
	
	PLCC_NEW;
	return exp;
}

//! OpMult -> '*' | DIV | MOD | AND
operation OpMult(){
	operation op;
	PLCC_IF('*') op=fois;
	else PLCC_IF('/') op=divise;
	else PLCC_IF(SMOD) op=modulo;
	else PLCC_IF(SAND) op=et;
	else PLCC_SYNTAX_ERROR("'*','/', 'mod' or 'and'");
	PLCC_NEW; return op;
}

//! OpAdd -> '+' | '-' | OR
operation OpAdd(){
	operation op;
	PLCC_IF('+') op=plus;
	else PLCC_IF('-') op=moins;
	else PLCC_IF(SOR) op=ou;
	else PLCC_SYNTAX_ERROR("'+','-' or 'or'");
	
	PLCC_NEW; return op;
}

//! Relation -> '<' | '=' | '>' | INFEG | DIFF | SUPEG 
operation Relation(){
	operation op=0;
	PLCC_IF('<') op=inf;
	else PLCC_IF('=') op=egal;
	else PLCC_IF('>')	op=sup;
	else PLCC_IF(SINF_EQL)	op=infeg;
	else PLCC_IF(SSUP_EQL)	op=supeg;
	else PLCC_IF(SDIF_THN)	op=diff;
	else PLCC_SYNTAX_ERROR("relation");
	
	PLCC_NEW; return op;
}

//! RelationUnaire -> '-' | NOT
operation RelationUnaire(){
	operation op;
	//PLCC_INFO("Weee");
	PLCC_IF('-') op=negatif;
	else PLCC_IF(SNOT) op=non;
	else PLCC_SYNTAX_ERROR("relation");
	
	PLCC_NEW; return op;
}


/*
	- Programme -> PROGRAM ID ';' Corps '.'
	 Corps ->[ VAR ListeDeclVar ';' ] { DeclProcFun ';' } BlocInstr
	+ ListeDeclVar -> DeclVar{ ';' DeclVar }
	+ DeclVar -> ID { ',' ID } ':' Type
	+ Type -> INTEGER | BOOLEAN | ARRAY '[' NUMERAL '..' NUMERAL ']' OF Type
	 DeclProcFun -> DeclProcedure | DeclFunction 
	 DeclProcedure -> PROCEDURE ID [ '(' ListeDeclVar ')' ] ; Corps 
	- DeclFunction -> FUNCTION ID '(' ListeDeclVar ')' ':' Type ';' Corps 
	
	+ BlocInstr -> BEGIN Instruction { ';' Instruction } ';' END 
	+ Instruction -> AffectInstr | AppelProcedure | IfInstr | WhileInstr | BlocInstr | Empty 
	X AffectInstr -> Variable AFFECT Expression 
	X AppelProcedure -> ID [ '(' ListeParam ')' ]
	X IfInstr -> IF Expression THEN Instruction [ ELSE Instruction ] 
	X WhileInstr -> WHILE Expression DO Instruction 
	

	+ ListeParam -> Expression { ',' Expression } | Empty
	X AppelFunction -> ID '(' ListeParam ')'

	+ Expression -> Simpleexpression [ Relation SimpleExpression ]
	+ Relation -> '<' | '=' | '>' | INFEG | DIFF | SUPEG 
	+ SimpleExpression -> Facteur [ OpAdd SimpleExpression ] 
	+ OpAdd -> '+' | '-' | OR
	+ Facteur -> [ RelationUnaire ] Predicat [ OpMult Facteur ] 
	+ RelationUnaire -> '-' | NOT
	+ OpMult -> '*' | DIV | MOD | AND
	+ Predicat -> AppelFunction | NUMERAL | Variable | '(' Expression ')' | read()
	X Variable -> ID [ '[' Expression ']' ] 
*/

/********** Affichage */

void markupOpen(char *s){
	int i;
	for(i=0;i<ident_level;i++) printf(" ");
	printf("%s<%s>%s\n",C_GREY,s,C_CLEAR);
	ident_level+=2;
}

void markupClose(char *s){
	int i;
	ident_level-=2;
	for(i=0;i<ident_level;i++) printf(" ");
	printf("%s</%s>%s\n",C_GREY,s,C_CLEAR);
}

void markupLeaf(char *s, char *val){
	int i;
	for(i=0;i<ident_level;i++) printf(" ");
	printf("%s<%s>%s%s%s</%s>%s\n",C_RED,s,C_GREEN,val,C_RED,s,C_CLEAR);
}

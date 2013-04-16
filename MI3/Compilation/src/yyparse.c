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

#define PLCC_SYNTAX_ERROR(expected){WHERE; PLCC_ERROR("Syntax error : Expected %s found '%s' <%d>",expected,yytext,uc);}
#define PLCC_NOT_IMPLEMENTED 		{WHERE; PLCC_ERROR("Not implemented error: %s <%d>",yytext,uc);}
#define PLCC_UNTESTED				{WHERE; PLCC_WARNING("The current section is untested/untrusted\n");}
#define PLCC_ILL_IMPLEMENED		{WHERE; PLCC_WARNING("The current section isn't fully implemented yet\n");}
#define PLCC_IF(exp_id) if (uc==exp_id)
#define PLCC_IFNOT(exp_id,exp) if (uc!=exp_id) PLCC_SYNTAX_ERROR(exp)
#define PLCC_NEW  (uc=yylex())

//! Program -> PROGRAM ID ';' Body '.'
n_prog *Programme(){
	n_prog*prog;
	
	PLCC_IFNOT(SPROGRAM,"program");
	markupOpen("program"); PLCC_NEW; 
	PLCC_IFNOT(SIDENT,"identifier");
	markupLeaf("identifier",yytext); PLCC_NEW; 
	/*yytext: program name*/
	
	PLCC_IFNOT(';',"';'");
	PLCC_NEW; prog=Corps(); 
	PLCC_IFNOT('.',"'.'");
	
	markupClose("program");
	return prog;
}

//! Corps ->[ VAR ListeDeclVar ';' ] { DeclProcFun ';' } BlocInstr
n_prog *Corps(){
	n_l_dec*var=NULL;
	n_l_fun_dec*tete=NULL,*queue;
	
	n_fun_dec*fun=NULL;
	n_instr*inst=NULL;
	
	markupOpen("body");
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
	markupClose("body");
	
	return cree_n_prog(var,tete,inst);
}

//! ListeDeclVar -> DeclVar{ ';' DeclVar }
n_l_dec* ListeDeclVar(){
	n_l_dec*decl=NULL;
	while (uc==SIDENT){
		markupOpen("var");
		decl=DeclVar(decl);
		markupClose("var");
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
		PLCC_IFNOT(SIDENT,"identifier"); markupLeaf("id",yytext);
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
	
	PLCC_IF(SINTEGER) {
		t=cree_n_type_int(); markupLeaf("type",yytext);
	} else PLCC_IF(SBOOLEAN) {
		t=cree_n_type_bool(); markupLeaf("type",yytext);
	}  else PLCC_IF(SARRAY){
		PLCC_NEW; PLCC_IFNOT('[',"'['");
		markupOpen("array");
		
		PLCC_NEW; PLCC_IFNOT(SNUMERAL,"number");
		markupLeaf("from",yytext); d=atoi(yytext);
		
		PLCC_NEW; PLCC_IFNOT(SDOT_DOT,"'..'");
		PLCC_NEW; PLCC_IFNOT(SNUMERAL,"number");
		markupLeaf("to",yytext); f=atoi(yytext);
		
		PLCC_NEW; PLCC_IFNOT(']',"']'");
		PLCC_NEW; PLCC_IFNOT(SOF,"of");
		markupOpen("of");
		PLCC_NEW; t=Type();
		markupClose("of");
		markupClose("array");
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
	
	markupOpen("procedure");
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
	
	markupOpen("function");
	PLCC_IFNOT(SFUNCTION,"function");
	PLCC_NEW; PLCC_IFNOT(SIDENT,"id");
	markupLeaf("id",yytext);
	
	entreefonction();
	nom=malloc((3+word_size)*sizeof(char)); CHECK_PTR(nom);
	strcpy(nom,yytext);
	PLCC_NEW; PLCC_IFNOT('(',"'('");
	PLCC_NEW; variables=ListeDeclVar();
	PLCC_IFNOT(')',"')'");
	
	PLCC_NEW; PLCC_IFNOT(':',"':'");
	markupOpen("return");
	PLCC_NEW; t=Type();
	markupClose("return");
	PLCC_IFNOT(';',"';'");
	PLCC_NEW; corps=Corps();
	markupClose("function");
	
	sortiefonction();
	return cree_n_dec_fonc(nom,t,param,variables,corps);
}

//! BlocInstr -> BEGIN Instruction { ';' Instruction } ';' END
n_instr *BlocInstr(){
	n_l_instr*tete,*queue;n_instr*inst;
	PLCC_IFNOT(SBEGIN,"begin");
	markupOpen("block_instr");
	
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
	markupClose("block_instr");
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
	
	markupOpen("instruction");
	PLCC_IF(SIDENT) {			// AppelProcedure | AffectInstr
		strcpy(inst_name,yytext); PLCC_NEW;
		PLCC_IF(';') {			//!< AppelProcedure -> ID @todo Upgrade for lame pascal specification
			markupOpen("procedure"); 
			markupLeaf("id",inst_name); PLCC_NEW;
			markupClose("procedure");
			instr=cree_n_instr_appel(cree_n_appel(inst_name,cree_n_l_exp(NULL,NULL)));
		} else PLCC_IF('('){	//!< AppelProcedure -> ID '(' ListeParam ')'
			markupOpen("procedure");
			markupLeaf("id",inst_name); PLCC_NEW; param=ListeParam();
			PLCC_IFNOT(')',"')'"); PLCC_NEW;
			markupClose("procedure");
			instr=cree_n_instr_appel(cree_n_appel(inst_name,param));
		} else PLCC_IF('['){	//!	AffectInstr -> Variable AFFECT Expression
			//!< Variable -> ID '[' Expression ']'
			markupOpen("affect");
			markupOpen("table");
				markupLeaf("id",inst_name);
				markupOpen("at");
				PLCC_NEW; exp=Expression();
			markupClose("at");
			markupClose("table");
			var=cree_n_var_indicee(inst_name,exp);
			PLCC_IFNOT(']',"']'"); PLCC_NEW;
			PLCC_IFNOT(SDOT_EQL,"':='");
			markupOpen("value");
				PLCC_NEW; exp=Expression();
			markupClose("value");
			markupClose("affect");
			instr=cree_n_instr_affect(var,exp);
		} else PLCC_IF(SDOT_EQL){ //!	AffectInstr -> Variable AFFECT Expression
			//!< Variable -> ID
			markupOpen("affect");
			markupLeaf("var",inst_name);
			var=cree_n_var_simple(inst_name);
			PLCC_IFNOT(SDOT_EQL,"':='");
			markupOpen("value");
				PLCC_NEW; exp=Expression();
			markupClose("value");
			markupClose("affect");
			instr=cree_n_instr_affect(var,exp);
		} else PLCC_SYNTAX_ERROR("procedure or affect");
	} else PLCC_IF(SIF){ //!< IfInstr -> IF Expression THEN Instruction [ ELSE Instruction ] 
		markupOpen("if_instr");
			markupOpen("if");
			PLCC_IFNOT(SIF,"if"); PLCC_NEW;
				exp=Expression();
			markupClose("if");
			markupOpen("then");
				PLCC_IFNOT(STHEN,"then"); PLCC_NEW;
				instr=Instruction(SELSE);
				PLCC_IF(';') PLCC_NEW;
			markupClose("then");
			PLCC_IF(SELSE) {
				markupOpen("else");
				PLCC_NEW;instr2=Instruction(';');
				markupClose("else");
			}
			instr=cree_n_instr_si(exp,instr,instr2);
		markupClose("if_instr");
	} else PLCC_IF(SWHILE){ //!< WhileInstr -> WHILE Expression DO Instruction
		markupOpen("while_instr");
			markupOpen("while");
				PLCC_IFNOT(SWHILE,"while"); PLCC_NEW;
				exp=Expression();
			markupClose("while");
			markupOpen("do");
			PLCC_IFNOT(SDO,"do"); PLCC_NEW;
				instr=Instruction(SEND);
				instr=cree_n_instr_tantque(exp,instr);
			markupClose("do");
		markupClose("while_instr");
	} else PLCC_IF(SBEGIN){ //!< BlocInstr -> BEGIN Instruction { ';' Instruction } ';' END 
		instr=BlocInstr();
	} else PLCC_IF(SWRITE){
		PLCC_NEW; PLCC_IFNOT('(',"'('");
		PLCC_NEW; exp=Expression();
		instr=cree_n_instr_ecrire(exp);
		PLCC_NEW;
	} else PLCC_SYNTAX_ERROR("instruction");
	markupClose("instruction");
	return instr;
}

//! ListeParam -> Expression { ',' Expression } | Empty
n_l_exp*ListeParam(){
	n_l_exp*curr,*tete,*queue;
	PLCC_IF(')') return NULL;
	markupOpen("liste_params");
	curr=tete=cree_n_l_exp(Expression(),NULL);
	
	PLCC_IF(',') PLCC_NEW;
	else goto listeparamEnd;
	while (1){
		markupOpen("value");
		queue=cree_n_l_exp(Expression(),NULL);
		curr->queue=queue;
		markupClose("value");
		PLCC_IF(',') PLCC_NEW;
		else goto listeparamEnd;
	}
	
	listeparamEnd: 
		markupClose("liste_params");
		return tete;
}

//! Expression -> Simpleexpression [ Relation Simpleexpression ]
n_exp*Expression(){
	n_exp*exp1,*exp2;operation op;
	markupOpen("expression");
	exp1=SimpleExpression();
	if(uc=='<'||uc=='='||uc=='>'||uc==SINF_EQL||uc==SSUP_EQL||uc==SDIF_THN) {
		op=Relation(); exp2=SimpleExpression();
		exp1=cree_n_exp_op(op,exp1,exp2);
	}
	markupClose("expression");
	return exp1;
}

//! SimpleExpression -> Facteur [ OpAdd SimpleExpression ] 
n_exp*SimpleExpression(){
	n_exp*exp1,*exp2; operation op;
	markupOpen("simple_expression");
	exp1=Facteur(); 
	if (uc=='+' || uc=='-' || uc==SOR) {
		op=OpAdd();
		exp2=SimpleExpression();
		exp1=cree_n_exp_op(op,exp1,exp2);
	}
	markupClose("simple_expression");
	return exp1;
}

//! Facteur -> [ RelationUnaire ] Predicat [ OpMult Facteur ] 
n_exp*Facteur(){
	n_exp *exp1,*exp2;operation op;
	markupOpen("factor");
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
	markupClose("factor");
	return exp1;
}

//! Predicat -> AppelFunction | NUMERAL | Variable | '(' Expression ')' | read()
n_exp*Predicat(){
	n_exp*exp; n_l_exp*args;
	char*inst_name=malloc(sizeof(char)*(word_size+3)); CHECK_PTR(inst_name);
	
	markupOpen("predicat");
	PLCC_IF(SNUMERAL) {
		markupLeaf("numeral",yytext);
		exp=cree_n_exp_entier(atoi(yytext));
	} else PLCC_IF(SIDENT){
		strcpy(inst_name,yytext); PLCC_NEW;
		PLCC_IF('('){			//!< AppelFunction -> ID '(' ListeParam ')'
			markupLeaf("function",inst_name);
			PLCC_NEW; args=ListeParam();
			PLCC_IFNOT(')',"')'");
			exp=cree_n_exp_appel(cree_n_appel(inst_name,args));
		} else PLCC_IF('['){ 	//!< Variable -> ID '[' Expression ']'
			markupOpen("table");
			markupLeaf("id",inst_name);
			markupOpen("at");
			PLCC_NEW; exp=Expression();
			PLCC_IFNOT(']',"']'");
			markupClose("table");
			markupClose("at");
			exp=cree_n_exp_var(cree_n_var_indicee(inst_name,exp));
		} else {				//!< Variable -> ID
			markupLeaf("variable",inst_name);  
			markupClose("predicat");
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
	markupClose("predicat");
	return exp;
}

//! OpMult -> '*' | DIV | MOD | AND
operation OpMult(){
	operation op;
	PLCC_IF('*') {markupLeaf("operation","*");op=fois;}
	else PLCC_IF('/') {markupLeaf("operation","/");op=divise;}
	else PLCC_IF(SMOD) {markupLeaf("operation","mod");op=modulo;}
	else PLCC_IF(SAND) {markupLeaf("operation","and");op=et;}
	else PLCC_SYNTAX_ERROR("'*','/', 'mod' or 'and'");
	PLCC_NEW; return op;
}

//! OpAdd -> '+' | '-' | OR
operation OpAdd(){
	operation op;
	PLCC_IF('+') {markupLeaf("operation","+");op=plus;}
	else PLCC_IF('-') {markupLeaf("operation","-");op=moins;}
	else PLCC_IF(SOR) {markupLeaf("operation","or");op=ou;}
	else PLCC_SYNTAX_ERROR("'+','-' or 'or'");
	
	PLCC_NEW; return op;
}

//! Relation -> '<' | '=' | '>' | INFEG | DIFF | SUPEG 
operation Relation(){
	operation op=0;

	PLCC_IF('<') {markupLeaf("relation","'<'");op=inf;}
	else PLCC_IF('=') {markupLeaf("relation","'='");op=egal;}
	else PLCC_IF('>')	{markupLeaf("relation","'>'");op=sup;}
	else PLCC_IF(SINF_EQL)	{markupLeaf("relation","'<='");op=infeg;}
	else PLCC_IF(SSUP_EQL)	{markupLeaf("relation","'>='");op=supeg;}
	else PLCC_IF(SDIF_THN)	{markupLeaf("relation","'!='");op=diff;}
	else PLCC_SYNTAX_ERROR("relation");
	
	PLCC_NEW; return op;
}

//! RelationUnaire -> '-' | NOT
operation RelationUnaire(){
	operation op;
	PLCC_IF('-') {markupLeaf("relation_unaire","'-'");op=negatif;}
	else PLCC_IF(SNOT) {markupLeaf("relation_unaire","'non'");op=non;}
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

#ifdef MK_SYN
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
	printf("%s<%s>%s%s%s</%s>%s\n",C_ORANGE,s,C_GREEN,val,C_ORANGE,s,C_CLEAR);
}
#endif

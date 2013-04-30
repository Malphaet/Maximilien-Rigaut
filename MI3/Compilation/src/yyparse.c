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
	
	PLCC_IFNOT(SPROGRAM,"program");
	pOpen("program"); PLCC_NEW; 
	PLCC_IFNOT(SIDENT,"identifier");
	pLeaf("identifier",yytext); PLCC_NEW; 
	/*yytext: program name*/
	
	PLCC_IFNOT(';',"';'");
	PLCC_NEW; prog=Corps(); 
	PLCC_IFNOT('.',"'.'");
	
	pClse("program");
	return prog;
}

//! Corps ->[ VAR ListeDeclVar ';' ] { DeclProcFun ';' } BlocInstr
n_prog *Corps(){
	n_l_dec*var=NULL;
	n_l_fun_dec*tete=NULL,*queue;
	
	n_fun_dec*fun=NULL;
	n_instr*inst=NULL;
	pOpen("body"); //tOpen("l_funct");
	
	PLCC_IF(SVAR){
		PLCC_NEW;
		var=ListeDeclVar();
	}
	if (uc==SPROCEDURE||uc==SFUNCTION) {
		queue=tete=cree_n_l_fun_dec(NULL,NULL);
		while (1){
			fun=DeclProcFun(); queue->tete=fun;
			PLCC_NEW;
			if (uc==SPROCEDURE||uc==SFUNCTION) {
				queue->queue=cree_n_l_fun_dec(NULL,NULL);
			} else break;
		}
	}
	inst=BlocInstr();
	pClse("body"); ////tClse("l_funct");
	return cree_n_prog(var,tete,inst);
}

//! ListeDeclVar -> DeclVar{ ';' DeclVar }
n_l_dec* ListeDeclVar(){
	n_l_dec*decl=NULL;
	while (uc==SIDENT){
		pOpen("var");
		decl=DeclVar(decl);
		pClse("var");
		if (uc!=';') break;
		PLCC_NEW;
	}
	return decl;
}

//! DeclVar -> ID { ',' ID } ':' Type
n_l_dec*DeclVar(n_l_dec*next){
	n_l_dec*tete,*queue;
	char*var; n_type*ty,*tt=calloc(1,sizeof(n_type)); CHECK_PTR(tt);
	tete=queue=cree_n_l_dec(NULL,NULL);
	
	while (1){
		PLCC_IFNOT(SIDENT,"identifier"); pLeaf("id",yytext);
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
		t=cree_n_type_int(); pLeaf("type",yytext);//tOne("t_int");
	} else PLCC_IF(SBOOLEAN) {
		t=cree_n_type_bool(); pLeaf("type",yytext);//tOne("t_bool");
	} else PLCC_IF(SREAL) {
		t=cree_n_type_real(); pLeaf("type",yytext);//tOne("t_bool");
	} else PLCC_IF(SARRAY){
		PLCC_NEW; PLCC_IFNOT('[',"'['");
		pOpen("array");
		
		PLCC_NEW; PLCC_IFNOT(SNUMERAL,"number");
		pLeaf("from",yytext); d=atoi(yytext);
		
		PLCC_NEW; PLCC_IFNOT(SDOT_DOT,"'..'");
		PLCC_NEW; PLCC_IFNOT(SNUMERAL,"number");
		pLeaf("to",yytext); f=atoi(yytext);
		
		PLCC_NEW; PLCC_IFNOT(']',"']'");
		PLCC_NEW; PLCC_IFNOT(SOF,"of");
		pOpen("of");
		PLCC_NEW; t=Type();
		pClse("of");
		pClse("array");
		t=cree_n_type_array(t,d,f); //tOne("t_array");
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
	
	pOpen("procedure");
	PLCC_IFNOT(SPROCEDURE,"procedure");
	
	entreefonction();
	PLCC_NEW; PLCC_IFNOT(SIDENT,"identifier");
	pLeaf("id",yytext);
	
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
	
	pOpen("function");
	PLCC_IFNOT(SFUNCTION,"function");
	PLCC_NEW; PLCC_IFNOT(SIDENT,"id");
	pLeaf("id",yytext);
	
	entreefonction();
	nom=malloc((3+word_size)*sizeof(char)); CHECK_PTR(nom);
	strcpy(nom,yytext);
	PLCC_NEW; PLCC_IFNOT('(',"'('");
	PLCC_NEW; variables=ListeDeclVar();
	PLCC_IFNOT(')',"')'");
	
	PLCC_NEW; PLCC_IFNOT(':',"':'");
	pOpen("return");
	PLCC_NEW; t=Type();
	pClse("return");
	PLCC_IFNOT(';',"';'");
	PLCC_NEW; corps=Corps();
	pClse("function");
	
	sortiefonction();
	return cree_n_dec_fonc(nom,t,param,variables,corps);
}

//! BlocInstr -> BEGIN Instruction { ';' Instruction } ';' END
n_instr *BlocInstr(){
	n_l_instr*tete,*queue;n_instr*inst;
	PLCC_IFNOT(SBEGIN,"begin");
	pOpen("block_instr"); //tOpen("l_instr");
										
	tete=queue=cree_n_l_instr(NULL,NULL);
	while(1) {
		PLCC_NEW; inst=Instruction(SEND);
		queue->tete=inst;
		//tClse("l_instr");
		PLCC_IF(';') {
			//tOpen("l_instr");
			queue->queue=cree_n_l_instr(NULL,NULL);
			queue=queue->queue;
		} else break;
	}
	PLCC_IFNOT(SEND,"end"); PLCC_NEW;
	
	pClse("block_instr");
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
	pOpen("instruction");
	PLCC_IF(SIDENT) {			// AppelProcedure | AffectInstr
		strcpy(inst_name,yytext); PLCC_NEW;
		PLCC_IF(';') {			//!< AppelProcedure -> ID @todo Upgrade for lame pascal specification
			pOpen("procedure"); //tOpen("appel");
			pLeaf("id",inst_name); PLCC_NEW;
			//tOne(inst_name);
			instr=cree_n_instr_appel(cree_n_appel(inst_name,cree_n_l_exp(NULL,NULL)));
			pClse("procedure"); //tClse("appel");
		} else PLCC_IF('('){	//!< AppelProcedure -> ID '(' ListeParam ')'
			pOpen("procedure"); //tOpen("appel");
			pLeaf("id",inst_name); PLCC_NEW; param=ListeParam();
			PLCC_IFNOT(')',"')'"); PLCC_NEW;
			instr=cree_n_instr_appel(cree_n_appel(inst_name,param));
			pClse("procedure"); //tClse("appel");
		} else PLCC_IF('['){	//!	AffectInstr -> Variable AFFECT Expression
			//!< Variable -> ID '[' Expression ']'
			//tOpen("indicee");
			pOpen("affect");
			pOpen("table");
				pLeaf("id",inst_name);
				pOpen("at");
				PLCC_NEW; exp=Expression();
			pClse("at");
			pClse("table");
			//tOpen("indicee");
				//tOne(inst_name);
				var=cree_n_var_indicee(inst_name,exp);
			//tClse("indicee");
			PLCC_IFNOT(']',"']'"); PLCC_NEW;
			PLCC_IFNOT(SDOT_EQL,"':='");
			pOpen("value");
				PLCC_NEW; exp=Expression();
			pClse("value");
			pClse("affect");
			//tClse("indicee");
			instr=cree_n_instr_affect(var,exp);
		} else PLCC_IF(SDOT_EQL){ //!	AffectInstr -> Variable AFFECT Expression
			//!< Variable -> ID
			//tOpen("affect");
			pOpen("affect");
			pLeaf("var",inst_name);
			//tOne(inst_name);
			var=cree_n_var_simple(inst_name);
			PLCC_IFNOT(SDOT_EQL,"':='");
			pOpen("value");
				PLCC_NEW; exp=Expression();
			pClse("value");
			pClse("affect");
			//tClse("affect");
			instr=cree_n_instr_affect(var,exp);
		} else PLCC_SYNTAX_ERROR("procedure or affect");
	} else PLCC_IF(SIF){ //!< IfInstr -> IF Expression THEN Instruction [ ELSE Instruction ] 
		pOpen("if_instr");
			pOpen("if");
			PLCC_IFNOT(SIF,"if"); PLCC_NEW;
				exp=Expression();
			pClse("if");
			pOpen("then");
				PLCC_IFNOT(STHEN,"then"); PLCC_NEW;
				instr=Instruction(SELSE);
				PLCC_IF(';') PLCC_NEW;
			pClse("then");
			PLCC_IF(SELSE) {
				pOpen("else");
				PLCC_NEW;instr2=Instruction(';');
				pClse("else");
			}
			instr=cree_n_instr_si(exp,instr,instr2);
		pClse("if_instr");
	} else PLCC_IF(SWHILE){ //!< WhileInstr -> WHILE Expression DO Instruction
		pOpen("while_instr");
			pOpen("while");
				PLCC_IFNOT(SWHILE,"while"); PLCC_NEW;
				exp=Expression();
			pClse("while");
			pOpen("do");
			PLCC_IFNOT(SDO,"do"); PLCC_NEW;
				instr=Instruction(SEND);
				instr=cree_n_instr_tantque(exp,instr);
			pClse("do");
		pClse("while_instr");
	} else PLCC_IF(SBEGIN){ //!< BlocInstr -> BEGIN Instruction { ';' Instruction } ';' END 
		instr=BlocInstr();
	} else PLCC_IF(SWRITE){
		PLCC_NEW; PLCC_IFNOT('(',"'('");
		PLCC_NEW; exp=Expression();
		pOpen("write");
		instr=cree_n_instr_ecrire(exp);
		pClse("write");
		PLCC_NEW;
	} else PLCC_SYNTAX_ERROR("instruction");
	pClse("instruction");
	
	return instr;
}

//! ListeParam -> Expression { ',' Expression } | Empty
n_l_exp*ListeParam(){
	n_l_exp*curr,*tete,*queue;
	PLCC_IF(')') return NULL;
	pOpen("liste_params");
	curr=tete=cree_n_l_exp(Expression(),NULL);
	//tOpen("l_exp");
	PLCC_IF(',') PLCC_NEW;
	else goto listeparamEnd;
	while (1){
		pOpen("value");
		//tOpen("l_exp");
		queue=cree_n_l_exp(Expression(),NULL);
		//tClse("l_exp");
		curr->queue=queue;
		pClse("value");
		PLCC_IF(',') PLCC_NEW;
		else goto listeparamEnd;
	}
	listeparamEnd: 
		//tClse("l_exp");
		pClse("liste_params");
		return tete;
}

//! Expression -> Simpleexpression [ Relation Simpleexpression ]
n_exp*Expression(){
	n_exp*exp1,*exp2;operation op;
	pOpen("expression");
	exp1=SimpleExpression();
	if(uc=='<'||uc=='='||uc=='>'||uc==SINF_EQL||uc==SSUP_EQL||uc==SDIF_THN) {
		op=Relation(); exp2=SimpleExpression();
		exp1=cree_n_exp_op(op,exp1,exp2);
	}
	pClse("expression");
	return exp1;
}

//! SimpleExpression -> Facteur [ OpAdd SimpleExpression ] 
n_exp*SimpleExpression(){
	n_exp*exp1,*exp2; operation op;
	pOpen("simple_expression");
	//PLCC_ILL_IMPLEMENED;
	exp1=Facteur(); 
	if (uc=='+' || uc=='-' || uc==SOR) {
		//tOpen("op_expr");
		op=OpAdd();
		exp2=SimpleExpression();
		exp1=cree_n_exp_op(op,exp1,exp2);
		//tClse("op_expr");
	}
	pClse("simple_expression");
	return exp1;
}

//! Facteur -> [ RelationUnaire ] Predicat [ OpMult Facteur ] 
n_exp*Facteur(){
	n_exp *exp1,*exp2;operation op;
	//PLCC_ILL_IMPLEMENED;
	pOpen("factor");
	if (uc=='-'||uc==SNOT||uc==SINTEGER||uc==SREAL||uc==SBOOLEAN){
		//tOpen("op_expr");
		op=RelationUnaire();
		exp1=Predicat();
		exp1=cree_n_exp_op(op,exp1,NULL);
		//tClse("op_expr");
	} else exp1=Predicat();
	
	if (uc=='*'||uc==SMOD||uc==SAND||uc=='/') {
		//tOpen("op_expr");
		op=OpMult();
		exp2=Facteur();
		exp1=cree_n_exp_op(op,exp1,exp2);
		//tClse("op_expr");
	}
	pClse("factor");
	return exp1;
}

//! Predicat -> AppelFunction | NUMERAL | Variable | '(' Expression ')' | read()
n_exp*Predicat(){
	n_exp*exp=NULL; n_l_exp*args;
	char*inst_name=malloc(sizeof(char)*(word_size+3)); CHECK_PTR(inst_name);
	
	pOpen("predicat");
	PLCC_IF(SNUMERAL) {
		pLeaf("numeral",yytext); //tOne(yytext);
		exp=cree_n_exp_entier(atoi(yytext));
	}PLCC_IF(SNUMEREAL) {
		pLeaf("numeral",yytext); //tOne(yytext);
		exp=cree_n_exp_real(atof(yytext));
	} else PLCC_IF(SIDENT){
		strcpy(inst_name,yytext); PLCC_NEW;
		PLCC_IF('('){			//!< AppelFunction -> ID '(' ListeParam ')'
			//tOpen("appel");
			//tOne(inst_name);
			pLeaf("function",inst_name);
			PLCC_NEW; args=ListeParam();
			PLCC_IFNOT(')',"')'");
			exp=cree_n_exp_appel(cree_n_appel(inst_name,args));
			//tClse("appel");
		} else PLCC_IF('['){ 	//!< Variable -> ID '[' Expression ']'
			pOpen("table");
			pLeaf("id",inst_name);
			pOpen("at");
			PLCC_NEW; exp=Expression();
			PLCC_IFNOT(']',"']'");
			pClse("table");
			pClse("at");
			exp=cree_n_exp_var(cree_n_var_indicee(inst_name,exp));
		} else {				//!< Variable -> ID
			pLeaf("variable",inst_name); //tOne(inst_name);
			pClse("predicat");
			return cree_n_exp_var(cree_n_var_simple(inst_name));;
		}
	} else PLCC_IF(STRUE){
		exp=cree_n_exp_true();
	} else PLCC_IF(SFALSE){
		exp=cree_n_exp_false();
	} else PLCC_IF('('){		//< '(' Expression ')'
		PLCC_NEW; exp=Expression();
		PLCC_IFNOT(')',"')'");
	} else PLCC_IF(SREAD) {
		exp=cree_n_exp_lire();
		PLCC_NEW; PLCC_IFNOT('(',"'('");
		PLCC_NEW; PLCC_IFNOT(')',"')'");
	} else PLCC_SYNTAX_ERROR("identifier, numeral or '('");
	
	PLCC_NEW;
	pClse("predicat");
	return exp;
}

//! OpMult -> '*' | DIV | MOD | AND
operation OpMult(){
	operation op;
	PLCC_IF('*') {pLeaf("operation","*");//tOne("*");
	op=fois;}
	else PLCC_IF('/') {pLeaf("operation","/");//tOne("/");
	op=divise;}
	else PLCC_IF(SMOD) {pLeaf("operation","mod");//tOne("%");
	op=modulo;}
	else PLCC_IF(SAND) {pLeaf("operation","and");//tOne("&");
	op=et;}
	else PLCC_SYNTAX_ERROR("'*','/', 'mod' or 'and'");
	PLCC_NEW; return op;
}

//! OpAdd -> '+' | '-' | OR
operation OpAdd(){
	operation op;
	PLCC_IF('+') {pLeaf("operation","+");//tOne("+");
	op=plus;}
	else PLCC_IF('-') {pLeaf("operation","-");//tOne("-");
	op=moins;}
	else PLCC_IF(SOR) {pLeaf("operation","or");//tOne("|");
	op=ou;}
	else PLCC_SYNTAX_ERROR("'+','-' or 'or'");
	
	PLCC_NEW; return op;
}

//! Relation -> '<' | '=' | '>' | INFEG | DIFF | SUPEG 
operation Relation(){
	operation op=0;

	PLCC_IF('<') {pLeaf("relation","'<'");//tOne("<");
	op=inf;}
	else PLCC_IF('=') {pLeaf("relation","'='");//tOne("=");
	op=egal;}
	else PLCC_IF('>')	{pLeaf("relation","'>'");//tOne(">");
	op=sup;}
	else PLCC_IF(SINF_EQL)	{pLeaf("relation","'<='");//tOne("<=");
	op=infeg;}
	else PLCC_IF(SSUP_EQL)	{pLeaf("relation","'>='");//tOne(">=");
	op=supeg;}
	else PLCC_IF(SDIF_THN)	{pLeaf("relation","'!='");//tOne("!=");
	op=diff;}
	else PLCC_SYNTAX_ERROR("relation");
	
	PLCC_NEW; return op;
}

//! RelationUnaire -> '-' | NOT
operation RelationUnaire(){
	operation op;
	PLCC_IF('-') {pLeaf("relation_unaire","'-'");//tOne("-");
	op=negatif;}
	else PLCC_IF(SNOT) {pLeaf("relation_unaire","'non'");//tOne("!");
	op=non;}
	else PLCC_IF(SINTEGER){
		pLeaf("relation_unaire","'int'");op=c_int;
	}else PLCC_IF(SBOOLEAN){
		pLeaf("relation_unaire","'bool'");op=c_bool;
	}else PLCC_IF(SREAL){
		pLeaf("relation_unaire","'real'");op=c_real;
	}else PLCC_SYNTAX_ERROR("relation");
	
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

#ifdef MK_MARKUP
void markupOpen(const char *s){
	int i;
	for(i=0;i<ident_level;i++) printf(" ");
	printf("%s<%s>%s\n",C_GREY,s,C_CLEAR);
	ident_level+=2;
}

void markupClose(const char *s){
	int i;
	ident_level-=2;
	for(i=0;i<ident_level;i++) printf(" ");
	printf("%s</%s>%s\n",C_GREY,s,C_CLEAR);
}

void markupLeaf(const char *s, const char *val){
	int i;
	for(i=0;i<ident_level;i++) printf(" ");
	printf("%s<%s>%s%s%s</%s>%s\n",C_ORANGE,s,C_GREEN,val,C_ORANGE,s,C_CLEAR);
}
void markupOne(const char *s){
	int i;
	for(i=0;i<ident_level;i++) printf(" ");
	printf("%s<%s />%s\n",C_ORANGE,s,C_CLEAR);
}
#endif

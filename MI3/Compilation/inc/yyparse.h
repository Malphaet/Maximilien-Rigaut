/*
 * yyparse.h
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

#ifndef YYPARSE_H
#define YYPARSE_H
/* ========= Includes =========*/

#include "arbre.h"

/* ========= Defines  ==========*/
#define PLCC_SYNTAX_ERROR(expected){WHERE; PLCC_ERROR("Syntax error : Expected %s found '%s' <%d>",expected,yytext,uc);}
#define PLCC_NOT_IMPLEMENTED 		{WHERE; PLCC_ERROR("Not implemented error: %s <%d>",yytext,uc);}
#define PLCC_UNTESTED				{WHERE; PLCC_WARNING("The current section is untested/untrusted\n");}
#define PLCC_ILL_IMPLEMENED		{WHERE; PLCC_WARNING("The current section isn't fully implemented yet\n");}
#define PLCC_IF(exp_id) if (uc==exp_id)
#define PLCC_IFNOT(exp_id,exp) if (uc!=exp_id) PLCC_SYNTAX_ERROR(exp)
#define PLCC_NEW  (uc=yylex())
/* ======== Prototype =========*/


int uc; /**< Processed lexeme */

/* Xml tags */
#ifdef MK_SYN
	void markupClose(char *s);
	void markupOpen(char *s);
	void markupLeaf(char *s, char *val);
	#define mOpn 	markupOpen
	#define mCls	markupClose
	#define mLea	markupLeaf
#else
	#define markupLeaf(a,b)
	#define markupClose(a)
	#define markupOpen(a)
#endif

/* Lexical analisys' functions */
n_prog*		Programme();
n_prog*		Corps();
n_l_dec*	ListeDeclVar();
n_l_dec*	DeclVar(n_l_dec*);
n_type*		Type();
n_fun_dec*	DeclProcFun();
n_fun_dec*	DeclProcedure();
n_fun_dec*	DeclFunction();
n_l_exp*	ListeParam();

n_instr*	BlocInstr();
n_instr*	Instruction(int);
n_exp*		Expression();
n_exp*		SimpleExpression();
n_exp*		Facteur();
n_exp*		Predicat();
operation	OpAdd();
operation	OpMult();
operation	Relation();
operation	RelationUnaire();
#endif

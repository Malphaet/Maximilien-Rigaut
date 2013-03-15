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

/* ========= Typedef ==========*/
/* ======== Prototype =========*/

/* Processed lexeme */
int uc; 

/* Xml tags */
void markupClose(char *s);
void markupOpen(char *s);
void markupLeaf(char *s, char *val);

/*
typedef struct n_l_instr_ n_l_instr;
typedef struct n_instr_ n_instr;
typedef struct n_exp_ n_exp;
typedef struct n_l_exp_ n_l_exp;
typedef struct n_var_ n_var;
typedef struct n_l_dec_ n_l_dec;
typedef struct n_dec_ n_dec;
typedef struct n_type_ n_type;
typedef struct n_l_fun_dec_ n_l_fun_dec;
typedef struct n_fun_dec_ n_fun_dec;
typedef struct n_prog_ n_prog;
typedef struct n_appel_ n_appel;
*/

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

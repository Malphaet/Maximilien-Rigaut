/*
 * code3.c
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbre.h"
#include "dico.h"
#include "code3.h"
#include "utils.h"

#define SIZE_CODE_INIT 20

/** Walk down the prog tree, and convert it to code3 */
void walk_code(n_prog *n){
	init_code();
	walk_inst(n->corps);
}
/*
void walk_prog(n_prog *n){
}*/

void walk_inst(n_instr *i){
	n_l_instr*nxt;
	if (!i) PLCC_ERROR("Null instruction"); // WTF ?
	switch (i->type){
		case videInst:
			break;
		case incrInst:
			break; // What is it anyway ?
		case affecteInst:
			
		case siInst:
			
		case tantqueInst:
		case appelInst:
			//entering;
			entreefonction();
			
			sortiefonction();
			//exiting;
			break;
		case ecrireInst:
			//! @todo test
			walk_exp(i->u.ecrire_);
			add_line(write,line_code3,0,NULL);
			break;
		case blocInst:
			//! @todo test
			nxt=i->u.liste;
			do {walk_inst(nxt->tete);} while ((nxt=nxt->queue)!=NULL);
			break;
	}
		
}
	/*
	struct n_instr_ {
    enum {incrInst,affecteInst,siInst,tantqueInst,appelInst,ecrireInst,videInst,blocInst} 
        type; 
    union{
        n_exp *incr;
        struct{n_exp *test; struct n_instr_ *alors; struct n_instr_ *sinon;} si_;
        struct{n_exp *test; struct n_instr_ *faire;} tantque_;
        n_appel *appel;
        struct{n_var *var; n_exp *exp;} affecte_;
        struct{n_exp *expression;} retour_;
        struct{n_exp *expression;} ecrire_;
        n_l_instr *liste;
    }u;
	};*/


void walk_exp(n_exp *e){
	if (!e) PLCC_ERROR("Null expression");
/*struct n_exp_ {
    enum{varExp, intExp, opExp, trueExp, falseExp, appelExp, lireExp} type; 
    union{
        struct{operation op; struct n_exp_ *op1; struct n_exp_ *op2;} opExp_;
        n_var *var;     
        int entier;     
        n_appel *appel; 
    }u;  
};*/
}
/** Utilities */
void init_code(){
    size_code3 = SIZE_CODE_INIT;
    code = (struct three_tuple *) malloc (size_code3 * sizeof(struct three_tuple)); CHECK_PTR(code);
    line_code3 = 0;
}

void add_line(c3_op op, int arg1, int arg2, char *var){
    if (line_code3 >= size_code3){
        size_code3 *= 2;
        code = realloc (code, size_code3 * sizeof(struct three_tuple));
        PLCC_INFO("Realloc taking place weeee !"); 
    }
    code[line_code3].op = op;
    code[line_code3].arg1 = arg1;
    code[line_code3].arg2 = arg2;
    code[line_code3++].var = var;
}

void show_code(){
    /* Affiche le code, s'il respecte la table du TP. L'ordre dans le
         tableau op2string doit correspondre à celui des opérations
         dans code3adr.h. */
    char *op2string[] = {"add", "sub", "time", "div", "mod", 
		             "eql", "dif", "inf", "sup", "infeq", "supeq", 
		             "or", "and", "no", "neg", 	            
		             "read", "write", "load", "store", "ltab", "stab", "loadimm",
		             "addimm", "jump", "jumpif0", 
		             "param", "call", "entering", "exiting"};    
    int l;
    for (l=0; l<line_code3; l++){
        printf("%i:\t%s\t", l, op2string[code[l].op]);
        if (code[l].op < 15){
            printf("%i", code[l].arg1);
            if (code[l].op < 13)
	printf(", %i", code[l].arg2);
        }
        else switch(code[l].op){
            case store:
	printf("%i, ", code[l].arg1);
            case load: 
            case call:
            case entering:
            case exiting:
	printf("%s", code[l].var);
	break;
            case stab:
	printf("%i, ", code[l].arg1);
            case ltab: 
	printf("%s[%i]", code[l].var, code[l].arg2);
	break;
            case loadimm:
            case write:
            case param:
	printf("%i", code[l].arg1);
	break;
            case addimm:
	printf("%i, %i", code[l].arg1, code[l].arg2);
	break;
            case jumpif0:
	printf("%i, ", code[l].arg1);	
            case jump:
	printf("%i", code[l].arg2);	
            default: break;
            }
        putchar('\n');
    }    
}

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
void walk_code(n_prog*n){
	init_code();
	walk_inst(n->corps);
}
/*
void walk_prog(n_prog *n){
}*/

#define TODO	OUT("Section is to be done ARrrrrrrrRR !");
void walk_inst(n_instr *i){
	n_l_instr*nxt;char*nom;
	n_l_exp*vars;int arg1,arg2,*jumpto=0;
	if (!i) PLCC_ERROR("plcc fatal error: Unexpected null pointer");
	
	switch (i->type){
		case videInst:
			break;
		case incrInst:
			break; // What is it anyway ?
		case affecteInst:
			walk_exp(i->u.affecte_.exp);
			arg1=line_code3-1;
			if (i->u.affecte_.var->type==simple) add_line(store,arg1,0,i->u.affecte_.var->nom);
			else {
				walk_exp(i->u.affecte_.var->indice); arg2=line_code3-1;
				add_line(stab,arg1,arg2,i->u.affecte_.var->nom);
			}
			break;
		case siInst:
			TODO;
		case tantqueInst:
			arg2=line_code3; // Jump back to here while true
			walk_exp(i->u.tantque_.test); arg1=line_code3-1; add_line(jumpif0,arg1,0,NULL); 
			jumpto=&code[line_code3-1].arg2; // The line to jump to exit (still unknown)
			
			walk_inst(i->u.tantque_.faire); add_line(jump,0,arg2,NULL);
			*jumpto=line_code3;
			break;
		case appelInst:
			vars=i->u.appel->args;
			do {walk_exp(vars->tete);} while ((vars=vars->queue)!=NULL);
			nom=i->u.appel->fonction;
			add_line(call,0,0,nom);
			break;
		case ecrireInst:
			//! @todo test
			walk_exp(i->u.ecrire_);
			add_line(write,line_code3-1,0,NULL);
			break;
		case blocInst:
			//! @todo test
			nxt=i->u.liste;
			do {walk_inst(nxt->tete);} while ((nxt=nxt->queue)!=NULL);
			break;
		default:
			OUT("plcc fatal error: Unhandled mode in switch");
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
	c3_op op=0; int arg1,arg2;
	if (!e) PLCC_ERROR("plcc fatal error: Unexpected null pointer");
	
	switch (e->type){
		case varExp:
			CHECK_VAR(e->u.var->nom);
			if (e->u.var->type==simple) add_line(load,0,0,e->u.var->nom);
			else {
				walk_exp(e->u.var->indice);
				arg1=line_code3-1;
				add_line(ltab,0,arg1,e->u.var->nom);
			}
			break;
		case intExp:
			add_line(loadimm,e->u.entier,0,NULL);
			break;
		case opExp:
			switch(e->u.opExp_.op){
				case plus: 		op=c3_add; break;
				case moins:		op=c3_sub; break;
				case fois: 		op=c3_times; break;
				case divise:	op=c3_div; break;
				case modulo:	op=c3_mod; break;
				case egal:		op=c3_eql; break;
				case diff:		op=c3_dif; break;
				case inf:		op=c3_inf; break;
				case sup:		op=c3_sup; break;
				case infeg:		op=c3_infeq; break;
				case supeg:		op=c3_supeq; break;
				case ou:		op=c3_or; break;
				case et:		op=c3_and; break;
				case non:		op=c3_no; break;
				case negatif:	op=c3_neg; break;
			}
			walk_exp(e->u.opExp_.op1); arg1=line_code3-1;
			walk_exp(e->u.opExp_.op2); arg2=line_code3-1;
			
			add_line(op,arg1,arg2,NULL);
			break;
		case trueExp:
			add_line(loadimm,1,0,NULL);
			break;
		case falseExp:
			add_line(loadimm,0,0,NULL);
			break;
		case appelExp:
			CHECK_VAR(e->u.appel->fonction);
			add_line(call,0,0,e->u.appel->fonction);
			break;
		case lireExp:
			add_line(read,0,0,NULL);
			break;
		default:
			show_code(NULL);
			OUT("plcc fatal error: Unhandled mode in switch");
			break;
	}
	//entreefonction();
	//sortiefonction();
	//add_line(entering,0,0,nom);
	//add_line(exiting,0,0,nom);
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

/* Print the code to stdout, with prettiness is available */
void show_code(FILE*f){
	int l=0,s=1;
    char format[51];
    char *op2string[] = {"add", "sub", "time", "div", "mod", 
		             "eql", "dif", "inf", "sup", "infeq", "supeq", 
		             "or", "and", "no", "neg", 	            
		             "read", "write", "load", "store", "ltab", "stab", "loadimm",
		             "addimm", "jump", "jumpif0", 
		             "param", "call", "entering", "exiting"};    
	while (line_code3>s) {s*=10; l++;}
	if (f==NULL) {
		f=stdout; sprintf(format,"%s%%0%ii %s|%s %%-8s %s|%s ",C_YELLOW,l,C_GREY,C_GREEN,C_GREY,C_BLUE);
	} else sprintf(format,"%%-%ii | %%-8s | ",l);
	
    for (l=0; l<line_code3; l++){
		fprintf(f,format, l, op2string[code[l].op]);
		if (code[l].op < 15){ 
			fprintf(f,"%i", code[l].arg1);
			if (code[l].op < 13) fprintf(f,", %i", code[l].arg2);
        }else switch(code[l].op){
			case store:
				fprintf(f,"%i, ", code[l].arg1);
			case load: 
			case call:
			case entering:
			case exiting:
				fprintf(f,"%s", code[l].var);
				break;
			case stab:
				fprintf(f,"%i, ", code[l].arg1);
			case ltab: 
				fprintf(f,"%s[%i]", code[l].var, code[l].arg2);
				break;
			case loadimm:
			case write:
			case param:
				fprintf(f,"%i", code[l].arg1);
				break;
			case addimm:
				fprintf(f,"%i, %i", code[l].arg1, code[l].arg2);
				break;
			case jumpif0:
				fprintf(f,"%i, ", code[l].arg1);	
			case jump:
				fprintf(f,"%i", code[l].arg2);	
			default: break;
			}
        fprintf(f,"\n");
    }
    printf("%s",C_CLEAR);
}

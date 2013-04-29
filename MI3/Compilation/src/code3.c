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
#include "register.h"
#include "utils.h"

char *op2string[] = {"add", "sub", "mul", "div", "mod", "eql", "dif", "inf", "sup", "infeq", "supeq", 
		             "or", "and", "no", "neg","read", "write", "load", "store", "ltab", "stab", "loadimm",
		             "addimm", "jump", "jumpif0","param", "call", "entering", "exiting"};

//char *op2code[] = {"add", "sub", "mul", "div", "rem", 
					//"eql", "dif", "inf", "sup", "infeq", "supeq", 
		             //"or", "and", "not", "neg",
		             //"read", "write", "load", "store", "ltab", "stab", 
		             //"li","addi","j", "beqz",
		             //"param", "call", "entering", "exiting"};

char* jump_targets;
/** Walk down the prog tree, and convert it to code3 */
void walk_code(n_prog*n){
	init_code();
	walk_prog(n);
}

#define ADD_APPEL(appel) CHECK_VAR(appel->fonction); vars=appel->args; do {walk_exp(vars->tete);\
							add_line(param,line_code3-1,0,NULL);} while ((vars=vars->queue)!=NULL);\
							add_line(call,0,0,appel->fonction);

#define LOAD_VARS(vars)	while (vars!=NULL){PLCC_INFO("NOT loading vars");\
								ajoutevariable(vars->tete->nom,vars->tete->type);vars=vars->queue;}
								
void walk_prog(n_prog *n){
	n_l_fun_dec*l=n->fonctions; int jumpto;
	n_l_dec /**prms,*/ *vars=n->variables;
	
	if (context_var==LOCAL) LOAD_VARS(vars);
	
	if (l!=NULL) {add_line(jump,0,0,NULL);jumpto=line_code3-1;}
	while (l!=NULL) {
		entreefonction();
		add_line(entering,0,0,l->tete->nom);
		vars=l->tete->variables; LOAD_VARS(vars);
		
		//prms=l->tete->param;//LOAD_VARS(prms);
		walk_prog(l->tete->corps);
		add_line(exiting,0,0,l->tete->nom);
		code[jumpto].arg2=line_code3;
		l=l->queue;
		sortiefonction();
	}
	walk_inst(n->corps);
}

void walk_inst(n_instr *i){
	n_l_instr*nxt;n_l_exp*vars;
	int arg1,arg2,addr,jumpto,jumpto2;
	if (!i) OUT("plcc fatal error: Unexpected null pointer");
	
	switch (i->type){
		case videInst:
			break;
		case incrInst:
			break; // What is it anyway ?
		case affecteInst:
			walk_exp(i->u.affecte_.exp);
			arg1=line_code3-1;
			
			if ((addr=cherche(i->u.affecte_.var->nom))<0) PLCC_ERROR("%s doesn't exist",i->u.affecte_.var->nom);
			if (i->u.affecte_.var->type==simple) add_line_var(store,arg1,0,i->u.affecte_.var->nom,addr,dico.tab[addr].mode);
			else {
				walk_exp(i->u.affecte_.var->indice); arg2=line_code3-1;
				add_line(addimm,line_code3-1,1,NULL); //< @todo Add the first value of the table, is it always 1 ?
				add_line_var(stab,arg1,arg2,i->u.affecte_.var->nom,addr,dico.tab[addr].mode);
			}
			break;
		case siInst:
			walk_exp(i->u.si_.test); arg1=line_code3-1; add_line(jumpif0,arg1,0,NULL);
			jumpto=line_code3-1; // The line to jump if false (still unknown)
			
			walk_inst(i->u.si_.alors); add_line(jump,0,0,NULL);
			jumpto2=line_code3-1; // The line to exit (still unknown)
			//printf("%p %p \n",jumpto,jumpto2);
			if (i->u.si_.sinon!=NULL) {
				code[jumpto].arg2=line_code3;
				walk_inst(i->u.si_.sinon);
				code[jumpto2].arg2=line_code3;
			} else code[jumpto].arg2=code[jumpto2].arg2=line_code3;
			break;
		case tantqueInst:
			arg2=line_code3; // Jump back to here while true
			walk_exp(i->u.tantque_.test); arg1=line_code3-1; add_line(jumpif0,arg1,0,NULL); 
			jumpto=line_code3-1; // The line to jump to exit (still unknown)
			
			walk_inst(i->u.tantque_.faire); add_line(jump,0,arg2,NULL);
			code[jumpto].arg2=line_code3;
			break;
		case appelInst:
			ADD_APPEL(i->u.appel);
			break;
		case ecrireInst:
			//! @todo test
			walk_exp(i->u.ecrire_.expression);
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

void walk_exp(n_exp *e){
	c3_op op=0; int arg1,arg2=0,addr,unaire=0; n_l_exp*vars;
	if (!e) OUT("plcc fatal error: Unexpected null pointer");
	
	switch (e->type){
		case varExp:
			if ((addr=cherche(e->u.var->nom))<0) PLCC_ERROR("%s doesn't exist",e->u.var->nom);
			if (e->u.var->type==simple) add_line_var(load,0,0,e->u.var->nom,addr,dico.tab[addr].mode);
			else {
				walk_exp(e->u.var->indice);
				add_line(addimm,line_code3-1,1,NULL); //< @todo Add the first value of the table, is it always 1 ?
				arg1=line_code3-1;
				add_line_var(ltab,0,arg1,e->u.var->nom,addr,dico.tab[addr].mode);
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
				
				case non:		op=c3_no; unaire=1;break;
				case negatif:	op=c3_neg; unaire=1; break;
				default: OUT("plcc fatal error: Unhandled mode in switch");
			}
			walk_exp(e->u.opExp_.op1); arg1=line_code3-1;
			if (!unaire) {walk_exp(e->u.opExp_.op2); arg2=line_code3-1;}
			else arg2=-1;
			add_line(op,arg1,arg2,NULL);
			break;
		case trueExp:
			add_line(loadimm,1,0,NULL);
			break;
		case falseExp:
			add_line(loadimm,0,0,NULL);
			break;
		case appelExp:
			ADD_APPEL(e->u.appel);
			break;
		case lireExp:
			add_line(read,0,0,NULL);
			break;
		default:
			show_code(NULL);
			OUT("plcc fatal error: Unhandled mode in switch");
			break;
	}
}

/** Utilities */
void init_code(){
    size_code3 = SIZE_CODE_INIT;
    code = (struct three_tuple*)malloc(size_code3*sizeof(struct three_tuple)); CHECK_PTR(code);
    jump_targets=(char*) malloc(size_code3*sizeof(char)); CHECK_PTR(jump_targets);
    line_code3 = 0;
}

void add_line(c3_op op, int arg1, int arg2, char *var){
    if (line_code3 >= size_code3){
        size_code3 *= 2;
        code = realloc(code,size_code3*sizeof(struct three_tuple)); CHECK_PTR(code);
        //jump_targets=realloc(jump_targets, size_code3*sizeof(char)); CHECK_PTR(jump_targets);
    }
    code[line_code3].op = op;
    code[line_code3].arg1 = arg1;
    code[line_code3].arg2 = arg2;
    code[line_code3++].var = var;
}

void add_line_var(c3_op op, int arg1, int arg2, char *var,int addr, int mode){
	add_line(op,arg1,arg2,var);
	code[line_code3-1].adresse=addr;
	code[line_code3-1].mode=mode;
}

/** Print the code to stdout, with prettiness if available */
void show_code(FILE*f){
	int l=0,s=1;
    char format[51];
		             
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
			case read:
				break;
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
				break;
			default:
				fprintf(f,"\n%i: %i %i %i %s\n",l, code[l].op,code[l].arg1,code[l].arg2,code[l].var);	
				PLCC_WARNING("Unhandled mode in switch");
				break;
			}
        fprintf(f,"\n");
    }
    printf("%s",C_CLEAR);
}

#define NEW_R		r=nouveau_registre(dernier, l)
#define FIND_R1	r1=trouve_registre(code[l].arg1)
#define FIND_R2	r2=trouve_registre(code[l].arg2)
#define CHECK(a)	free_register(a,l);
#define UNDEF		THR_REG("UDEF"); CHECK(r1); CHECK(r2); CHECK(r);
//#define CMNT(a)	fprintf(f,"# %s",a);

/** Show assembly code, with prettyness if stdout and available */
void show_assembly(FILE*f){
	int l=0,s=1,r,r1,r2; char instr[20],line[20],reg[20],*vide/*,label[10]*/;
	while (line_code3>s) {s*=10; l++;}
	vide=malloc(sizeof(char)*(l+4)); CHECK_PTR(vide); for(s=0;s<l+4;s++) vide[s]=' '; vide[l+4]=0;
	if (f==NULL) {f=stdout;} 
	//sprintf(format,"j%%-%dd : %%-5s$t%%-2i, $t%%-2i, $t%%-2i",l);
	sprintf(line,"j%%-%dd : ",l);
	sprintf(instr,"%%-7s ");
	sprintf(reg,"$%%c%%d");
	//sprintf(label,"%%s");
	
	#define REG(t,n)	fprintf(f,reg,t,n);
	#define LABEL(...)	fprintf(f,__VA_ARGS__);
	#define COMMENT(...)fprintf(f,__VA_ARGS__);
	#define SEP		fprintf(f,", ");
	#define NL			fprintf(f,"\n");
	#define THR_REG(s)	LINE_N(s);REG('t',NEW_R);SEP;REG('t',FIND_R1);SEP;REG('t',FIND_R2);
	
	#define LINE_N(s)	fprintf(f,line,/*(jump_targets[l])?l:-1*/l);fprintf(f,instr,s);
	#define LINE_V(s)	fprintf(f,"%s",vide);fprintf(f,instr,s);
	
	LINE_V(".data");NL;
	fprintf(f,"vars:");NL;
	PLCC_WARNING("vars not implemented"); 
	LINE_V(".text");NL;
	
	for(l=0;l<line_code3;l++){
		switch (code[l].op){
			case c3_add:
				THR_REG("add"); CHECK(r1); CHECK(r2);
				break;
			case c3_sub:
				THR_REG("sub"); CHECK(r1); CHECK(r2);
				break;
			case c3_times:
				THR_REG("mul"); CHECK(r1); CHECK(r2);
				break;
			case c3_div:
				THR_REG("div"); CHECK(r1); CHECK(r2);
				break;
			case c3_mod:
				THR_REG("rem"); CHECK(r1); CHECK(r2);
				break;
			case c3_eql:
				LINE_N("li"); REG('t',NEW_R); 		SEP; LABEL("1"); NL;
				LINE_V("beq"); 	REG('t',FIND_R1); 	SEP; REG('t',FIND_R2); SEP; LABEL("j%d",l+1); NL;
				LINE_V("li"); 	REG('t',r1); 		SEP; LABEL("1");
				CHECK(r1); CHECK(r2);
				break;
			case c3_dif:
				break;
			case c3_inf:
				THR_REG("slt"); CHECK(r1); CHECK(r2);
				break;
			case c3_sup:
				LINE_N("slt");REG('t',NEW_R);SEP;REG('t',FIND_R2);SEP;REG('t',FIND_R1);
				CHECK(r1); CHECK(r2);
				break;
			case c3_infeq:
				LINE_N("li"); REG('t',NEW_R); 		SEP; LABEL("1"); NL;
				LINE_V("ble"); 	REG('t',FIND_R1); 	SEP; REG('t',FIND_R2); SEP; LABEL("j%d",l+1); NL;
				LINE_V("li"); 	REG('t',r1); 		SEP; LABEL("1");
				break;
			case c3_supeq:
				UNDEF;
				break;
			case c3_or:
				THR_REG("or"); CHECK(r1); CHECK(r2);
				break;
			case c3_and:
				THR_REG("and"); CHECK(r1); CHECK(r2);
				break;
			case c3_no:
				THR_REG("not"); CHECK(r1); CHECK(r2);
				break;
			case c3_neg:
				THR_REG("neg"); CHECK(r1); CHECK(r2);
				break;
			case read:
				LINE_N("li"); REG('v',0); SEP; LABEL("%d",5); NL;
				LINE_V("syscall");NL;
				LINE_V("move"); REG('t',NEW_R); SEP; REG('v',0);
				break;
			case write:
				LINE_N("move");REG('a',0);	SEP; REG('t',FIND_R1);NL;
				LINE_V("li");REG('v',0);	SEP; LABEL("%d",1);NL;
				LINE_V("syscall"); CHECK(r1);
				break;
			case load:
				LINE_N("la"); REG('t',FIND_R1); SEP; LABEL("vars");NL;
				LINE_V("lw"); REG('t',r1); SEP; LABEL("%d($t%d)",0,r1); 		COMMENT("\t# %s",code[l].var);
				CHECK(r1);
				break;
			case store:
				LINE_N("la"); REG('t',NEW_R); 	 SEP; LABEL("%s",code[l].var); NL;
				LINE_V("sw"); REG('t',FIND_R1); SEP; LABEL("%d($t%d)",0,r);  	COMMENT("\t# %s",code[l].var);
				CHECK(r1); CHECK(r);
				break;
			case ltab:
				UNDEF;
				break;
			case stab:
				UNDEF;
				break;
			case loadimm:
				LINE_N("li");REG('t',NEW_R);SEP;LABEL("%d",code[l].arg1);
				break;
			case addimm:
				LINE_N("li");REG('t',FIND_R1);SEP;LABEL("%d",code[l].arg2);
				break;
			case jump:
				LINE_N("j");LABEL("j%d",code[l].arg2);
				break;
			case jumpif0:
				LINE_N("beqz");REG('t',FIND_R1);SEP;LABEL("j%d",code[l].arg2);
				CHECK(r1);
				break;
			case param:
				UNDEF;
				break;
			case call:
				UNDEF;
				break;
			case entering:
				UNDEF;
				break;
			case exiting:
				UNDEF;
				break;
			default:
				PLCC_WARNING("Unhandled mode in switch");
		}
		fprintf(f,"\n");
	}
	
	LINE_N("li"); REG('v',0); SEP; LABEL("%d",0); NL;
	LINE_V("syscall"); NL;
	
	printf("%s",C_CLEAR);
}
#undef NEW_R
#undef FIND_R1
#undef FIND_R2
#undef UNDEF

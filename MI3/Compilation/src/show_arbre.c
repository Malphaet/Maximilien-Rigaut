/*
 * show_arbre.c
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

#include "show_arbre.h"

#define OPN	tOpen(__func__+7)
#define CLS	tClse(__func__+7)

/*------ PROGRAMME ------*/
void show_n_prog(n_prog*p){
	OPN;
	show_n_l_dec(p->variables);
	show_n_l_fun_dec(p->fonctions);
	show_n_instr(p->corps);
	CLS;
}

/*------ INSTRUCTIONS ------*/
void show_n_instr(n_instr*l){
	if (!l) return;
	switch (l->type){
		case incrInst:
			tOpen("incrInst");
			show_n_exp(l->u.incr);
			tClse("incrInst");
			break;
		case siInst:
			tOpen("siInst");
			show_n_exp(l->u.si_.test);
			show_n_instr(l->u.si_.alors);
			show_n_instr(l->u.si_.sinon);
			tClse("siInst");
			break;
		case blocInst:
			tOpen("blocInst");
			show_n_l_instr(l->u.liste);
			tClse("blocInst");
			break;
		case tantqueInst:
			tOpen("tantqueInst");
			show_n_exp(l->u.tantque_.test);
			show_n_instr(l->u.tantque_.faire);
			tClse("tantqueInst");
			break;
		case affecteInst:
			tOpen("affecteInst");
			show_n_var(l->u.affecte_.var);
			show_n_exp(l->u.affecte_.exp);
			tClse("affecteInst");
			break;
		case appelInst:
			tOpen("appelInst");
			show_n_appel(l->u.appel);
			tClse("appelInst");
			break;
		case ecrireInst:
			tOpen("ecrireInst");
			show_n_exp(l->u.ecrire_.expression);
			tClse("ecrireInst");
			break;
		case videInst:
			tOne("videInst");
			break;
	}
}

/*------ EXPRESSIONS ------*/
 char *op2string[] = {"add", "sub", "time", "div", "mod", "eql", "dif", "inf", "sup", "infeq", "supeq", 
		             "or", "and", "no", "neg","read", "write", "load", "store", "ltab", "stab", "loadimm",
		             "addimm", "jump", "jumpif0","param", "call", "entering", "exiting"};
void show_n_exp(n_exp*e){
	char*str;
	if (!e) return;
	switch(e->type){
		case varExp:
			tOpen("varExp");
			show_n_var(e->u.var);
			tClse("varExp");
			break;
		case intExp:
			tOpen("intExp");
			str=malloc(sizeof(char)*(e->u.entier/10+1)+1);CHECK_PTR(str);
			sprintf(str,"%d",e->u.entier); tOne(str);
			tClse("intExp");
			break;
		case opExp:
			tOpen("opExp");
			tOne(op2string[e->u.opExp_.op]);
			show_n_exp(e->u.opExp_.op1);
			show_n_exp(e->u.opExp_.op1);
			tClse("opExp");
			break;
		case trueExp:
			tOne("trueExp");
			break;
		case falseExp:
			tOne("falseExp");
			break;
		case appelExp:
			tOpen("lireExp");
			show_n_appel(e->u.appel);
			tClse("lireExp");
			break;
		case lireExp:
			tOne("lireExp");
			break;
	}
}
//struct n_exp_ {
    //enum{varExp, intExp, opExp, trueExp, falseExp, appelExp, lireExp} type; /**< The type of the aforementioned expression */
    //union{
        //struct{operation op; struct n_exp_ *op1; struct n_exp_ *op2;} opExp_;
        //n_var *var;     /**< The variable contained by the said expression */
        //int entier;     /**< The integer contained by the said expresion */
        //n_appel *appel; /**< The function call containned by the said expression */
    //}u;  /**< The operation of the said expression */
//};

void show_n_appel(n_appel*a){
	OPN;
	tOne(a->fonction);
	show_n_l_exp(a->args);
	CLS;
}

void show_n_var(n_var*v){
	if (v->type==indicee){
		tOpen("indicee");
		tOne(v->nom);
		tClse("indicee");
	} else {
		tOpen("simple");
		tOne(v->nom);
		show_n_exp(v->indice);
		tClse("simple");
	}
}

/*------ LISTES D'OBJETS------*/
void show_n_l_fun_dec(n_l_fun_dec*l){
	if (!l) return; OPN;
	show_n_dec_fonc(l->tete);
	if (l->queue) show_n_l_fun_dec(l->queue);
	CLS;
}

void show_n_l_exp(n_l_exp*l){
	if (!l) return; OPN;
	show_n_exp(l->tete);
	if (l->queue) show_n_l_exp(l->queue);
	CLS;
}

void show_n_l_instr(n_l_instr*l){
	if (!l) return; OPN;
	show_n_instr(l->tete);
	if (l->queue) show_n_l_instr(l->queue);
	CLS;
}

void show_n_l_dec(n_l_dec*l){
	if (!l) return; OPN;
	show_n_dec_var(l->tete);
	if (l->queue) show_n_l_dec(l->queue);
	CLS;
}

/*------ DECLARATIONS ------*/
void show_n_dec_var(n_dec*d){
	if (!d) return; OPN;
	tOne(d->nom);
	show_n_type(d->type);
	CLS;
}

void show_n_dec_fonc(n_fun_dec*d){
	if (!d) return; OPN;
	tOne(d->nom);
	show_n_type(d->type);
	show_n_l_dec(d->param);
	show_n_l_dec(d->variables);
	show_n_prog(d->corps);
	CLS;
}

#define MAX(a,b)	(a)>(b)?(a):(b)
void show_n_type(n_type*t){
	char*str;
	if (!t) return;
	if (t->type==t_int) tOne("entier");
	else if (t->type==t_bool) tOne("bool");
	else if (t->type==t_array) {
		tOpen("arrayOf");
		str=malloc(sizeof(char)*(MAX(t->debut,t->fin)/10+1)+1);CHECK_PTR(str);
		show_n_type(t->arrayof);
		sprintf(str,"%d",t->debut);tOne(str);
		sprintf(str,"%d",t->fin);tOne(str);
		tClse("arrayOf");
		free(str);
	}
}
#undef MAX
///*------ EXPRESSIONS ------*/
//n_exp       *cree_n_exp_op          (operation type, n_exp *op1, n_exp *op2);
//n_exp       *cree_n_exp_entier      (int entier);
//n_exp       *cree_n_exp_var         (n_var *var);
//n_exp       *cree_n_exp_appel       (n_appel *app);
//n_exp       *cree_n_exp_lire        (void);
//n_exp       *cree_n_exp_true        (void);
//n_exp       *cree_n_exp_false       (void);

#undef OPN
#undef CLS
